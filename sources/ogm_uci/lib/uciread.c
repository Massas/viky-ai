/*
 *	Initialization for ogm_uci functions
 *	Copyright (c) 2006 Pertimm by Patrick Constant
 *	Dev : July,September 2006, January,March 2007
 *	Version 1.3
*/
#include "ogm_uci.h"
#include <limits.h>


STATICF(int) GetTopLevelTag(pr_(struct og_ctrl_uci *) pr_(int) pr_(unsigned char *) pr_(int *) pr(unsigned char *));
STATICF(int) GetEndingTopLevelTag(pr_(struct og_ctrl_uci *) pr_(int) pr_(unsigned char *) pr_(int) pr(unsigned char *));
STATICF(int) RemoveChunk(pr_(struct og_ctrl_uci *) pr(struct og_ucir_output *));
STATICF(int) HhScan(pr_(void *) pr_(int) pr(unsigned char *));



/*
 * Reads the socket and puts the information into the output structure.
*/

int OgUciRead(handle,input,output)
void *handle; struct og_ucir_input *input;
struct og_ucir_output *output;
{
int itlt=0,found_tlt=0,found_ending_tlt=0; unsigned char tlt[DPcPathSize];
struct og_ctrl_uci *ctrl_uci = (struct og_ctrl_uci *)handle;
int read_length,timed_out,found_header=0,state=1;
unsigned char *socket_buffer = ctrl_uci->Ba;
int ssocket_buffer = ctrl_uci->BaSize-1;
int max_buffer_size_to_read=0;
char erreur[DOgErrorSize];
int isocket_buffer=0;
ogint64_t t0,t1;

t0=OgMicroClock();

memset(output,0,sizeof(struct og_ucir_output));

// unset content length
output->hh.content_length = SIZE_MAX;

while(1) {
  if (ssocket_buffer-isocket_buffer <= 0) {
    sprintf(erreur,"OgUciRead: buffer with size %d is full, stop reading the socket",ssocket_buffer);
    OgErr(ctrl_uci->herr,erreur); DPcErr;
    }
  t1=OgMicroClock();
  read_length=OgTimeoutRecvSocket(ctrl_uci->herr,input->hsocket, socket_buffer+isocket_buffer
    , ssocket_buffer-isocket_buffer,input->timeout,&timed_out);
  output->elapsed_recv+=(int)(OgMicroClock()-t1);
  IF(read_length) {
    /** When the trace is zero, we do not even want error message **/
    IFn(ctrl_uci->loginfo->trace) OgErrReset(ctrl_uci->herr);
    OgMsgErr(ctrl_uci->hmsg,"OgUciRead",0,0,0,DOgMsgSeverityError
      ,DOgErrLogFlagNoSystemError+DOgErrLogFlagNotInErr);

    if (ctrl_uci->loginfo->trace & DOgUciTraceMinimal) {
      OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog+DOgMlogInErr+DOgMlogDateIn
        ,"OgUciRead: error reading socket hsocket=%d",input->hsocket);
      }
    DPcErr;
    }
  if (timed_out) {
    if (ctrl_uci->loginfo->trace & DOgUciTraceMinimal) {
      OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
        ,"OgUciRead: Timed-out while reading request");
      }
    output->timed_out=1;
    DPcErr;
    }
  /* if recv() returns 0, then the other end closed connection.
   * this is unlikely to occur if your application protocol is
   * well defined, and unnecessary if you have registered for
   * FD_CLOSE, but nonetheless you might want handle it. */
  IFn(read_length) { 
    if (ctrl_uci->loginfo->trace & DOgUciTraceMinimal) {
      OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
        ,"OgUciRead: Nothing to read anymore");
      }
    break;
    }
  isocket_buffer += read_length;
  if (ctrl_uci->loginfo->trace & DOgUciTraceSocketSize) {
    OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
      ,"OgUciRead: read_length=%d read_total=%d",read_length,isocket_buffer);
    }

  /** before header **/
  if (state==1) {
    IFE(found_header=OgHttpHeaderLength(ctrl_uci->hhttp,isocket_buffer,socket_buffer,&output->header_length));
    if (found_header) {
      if (ctrl_uci->loginfo->trace & DOgUciTraceSocketSize) {
        OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
          ,"OgUciRead: header length 1 = %d",output->header_length);
        }
      IFE(OgHttpHeaderRead(ctrl_uci->hhttp,isocket_buffer,socket_buffer,&output->hh));
      if (ctrl_uci->loginfo->trace & DOgUciTraceSocketSize) {
        OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
          ,"OgUciRead: header length 2 = %d",output->hh.header_length);
        OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
          ,"OgUciRead: content length = %d",output->hh.content_length);
        }
      if (output->hh.content_length != SIZE_MAX) {
        max_buffer_size_to_read = output->hh.header_length + output->hh.content_length;
        state=2;
        }
      else state=3;
      }
    else if (ctrl_uci->header_mandatory) state=1;
    else state=3;
    }
  /** header found with content-length **/
  if (state==2) {
    if (isocket_buffer >= max_buffer_size_to_read) {
      if (ctrl_uci->loginfo->trace & DOgUciTraceSocketSize) {
        OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
          ,"OgUciRead: reached content length (read %d, max %d)"
          , isocket_buffer, max_buffer_size_to_read);
        }
      break;
      }
    }
  /* header found without content-length,
   * or header not found but not mandatory */
  else if (state==3) {
    if (!found_tlt) {
      /* Getting the name of the top level tag
       *   <?xml version="1.0" encoding="UTF-8"?>
       *   <top_level_tag> */
      IFE(found_tlt=GetTopLevelTag(ctrl_uci,isocket_buffer,socket_buffer,&itlt,tlt));
      if (found_tlt) strcpy(output->top_level_tag,tlt);
      }
    if (!found_tlt) continue;
    IFE(found_ending_tlt=GetEndingTopLevelTag(ctrl_uci,isocket_buffer,socket_buffer,itlt,tlt));
    if (found_ending_tlt) {
      if (ctrl_uci->loginfo->trace & DOgUciTraceSocketSize) {
        OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
          ,"OgUciRead: found ending top level tag '%s'",tlt);
        }
      break;
      }
    }
  }

socket_buffer[isocket_buffer]=0;
output->content=socket_buffer;
output->content_length=isocket_buffer;

ctrl_uci->chunked=0;
IFE(OgHttpHeaderScanValues(ctrl_uci->hhttp,&output->hh,DOgHttpHeaderLineTransferEncoding,HhScan,ctrl_uci));
if (ctrl_uci->chunked) {
  IFE(RemoveChunk(ctrl_uci,output));
  }

if (ctrl_uci->loginfo->trace & DOgUciTraceSocket) {
  int max_log_size=output->content_length;
  char buffer[DPcPathSize]; buffer[0]=0;
  if (max_log_size>DOgMlogMaxMessageSize/2) {
    max_log_size=DOgMlogMaxMessageSize/2;
    sprintf(buffer,", log truncated");
    }
  OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
    ,"OgUciRead: socket_buffer (%d%s) [\n%.*s|%.*s]"
    , output->content_length, buffer, output->header_length
    , socket_buffer, max_log_size, socket_buffer+output->header_length);
  if (found_header) {
    OgMsg(ctrl_uci->hmsg,"",DOgMlogInLog
      ,"OgUciRead: header found:");
    IFE(OgHttpHeader2Log(ctrl_uci->hhttp,&output->hh));
    }
  }

output->elapsed_total=(int)(OgMicroClock()-t0);

DONE;
}





STATICF(int) GetTopLevelTag(ctrl_uci,is,s,pitlt,tlt)
struct og_ctrl_uci *ctrl_uci; int is; unsigned char *s;
int *pitlt; unsigned char *tlt;
{
int i,c,state=1,found=0,start=0,itlt=0;

for (i=0; i<is; i++) {
  c=s[i]; 
  switch(state) {
    case 1:
      if (i+5<=is && !Ogmemicmp(s+i,"<?xml",5)) state=2;
      break;
    case 2:
      if (c=='>') state=3;
      break;
    case 3:
      if (c=='<') { state=4; start=i+1; }
      break;
    case 4:
      if (c=='>' || PcIsspace(c)) { 
        itlt=i-start; 
        if (itlt<DOgMaxTopLevelTagSize) {
          memcpy(tlt,s+start,itlt); tlt[itlt]=0; 
          found=1; goto endGetTopLevelTag;
          }
        }
      break;
    }
  }
endGetTopLevelTag:
*pitlt=itlt;

return(found);
}







STATICF(int) GetEndingTopLevelTag(ctrl_uci,is,s,itlt,tlt)
struct og_ctrl_uci *ctrl_uci; int is; unsigned char *s;
int itlt; unsigned char *tlt;
{
unsigned char t[DOgMaxTopLevelTagSize+3];
int i,it;

sprintf(t,"</%s>",tlt); it=itlt+3;

for (i=is-it; i>=0; i--) {
  if (!Ogmemicmp(s+i,t,it)) { return(1); break; }
  }

return(0);
}





/*
 *  Removes chunks from a grabbed page, this happens,
 *  when we receive a header with a field:
 *  Transfer-Encoding: chunked
 *  See RFC2616 for more details, excerpt:
       Chunked-Body   = *chunk
                        last-chunk
                        trailer
                        CRLF

       chunk          = chunk-size [ chunk-extension ] CRLF
                        chunk-data CRLF
       chunk-size     = 1*HEX
       last-chunk     = 1*("0") [ chunk-extension ] CRLF

       chunk-extension= *( ";" chunk-ext-name [ "=" chunk-ext-val ] )
       chunk-ext-name = token
       chunk-ext-val  = token | quoted-string
       chunk-data     = chunk-size(OCTET)
       trailer        = *(entity-header CRLF)
*/

STATICF(int) RemoveChunk(ctrl_uci,output)
struct og_ctrl_uci *ctrl_uci;
struct og_ucir_output *output;
{
unsigned char *content=output->content+output->header_length;
int content_length=output->content_length-output->header_length;
int start_chunk_size,end_chunk_size;
int is=content_length;
char *nil,*s=content;
int start_chunk=0;
int i,chunk_size;

while(1) {
  s=content+start_chunk;
  is=content_length-start_chunk;
  if (s[0]==0xd) start_chunk_size=2;
  else start_chunk_size=0;
  chunk_size=strtol(s+start_chunk_size,&nil,16);
  if (chunk_size==0) { content_length=start_chunk; break; }
  end_chunk_size=0;
  for (i=start_chunk_size; i+1<is; i++) {
    if (s[i]==0xd && s[i+1]==0xa) { end_chunk_size=i+2; break; }
    }
  IFn(end_chunk_size) break;
  memmove(s,s+end_chunk_size,is-end_chunk_size);
  content_length=start_chunk+is-end_chunk_size;
  start_chunk += chunk_size;
  }

output->content_length = output->header_length + content_length;

DONE;
}







STATICF(int) HhScan(ptr,ivalue,value)
void *ptr; int ivalue; unsigned char *value;
{
struct og_ctrl_uci *ctrl_uci = (struct og_ctrl_uci *)ptr;
if (!Ogstricmp(value,"chunked")) {
  ctrl_uci->chunked=1;
  return(1);
  }
return(0);
}






