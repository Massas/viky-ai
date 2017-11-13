/*
 *  Glue means whether a position is glued to another
 *  Copyright (c) 2017 Pertimm, by Patrick Constant
 *  Dev : October 2017
 *  Version 1.0
 */
#include "ogm_nlp.h"

og_status NlpGlueInit(og_nlp_th ctrl_nlp_th)
{
  ctrl_nlp_th->glue_hash = g_hash_table_new(g_direct_hash, g_direct_equal);
  DONE;
}

og_status NlpGlueFlush(og_nlp_th ctrl_nlp_th)
{
  g_hash_table_destroy(ctrl_nlp_th->glue_hash);
  DONE;
}

og_status NlpGlueReset(og_nlp_th ctrl_nlp_th)
{
  g_hash_table_remove_all(ctrl_nlp_th->glue_hash);
  DONE;
}

/*
 * For example "dix huit", word dix has start=0, length=3,
 * word huit has start 4 and length 4
 * so we build the link between, 3 and 4 and 4 and 3
 */

og_status NlpGlueBuild(og_nlp_th ctrl_nlp_th)
{
  int request_word_used = OgHeapGetCellsUsed(ctrl_nlp_th->hrequest_word);
  struct request_word *request_word_all = OgHeapGetCell(ctrl_nlp_th->hrequest_word, 0);
  IFN(request_word_all) DPcErr;

  for (int i = 0; i + 1 < request_word_used; i++)
  {
    struct request_word *request_word1 = request_word_all + i;
    struct request_word *request_word2 = request_word_all + i + 1;

    int position1 = request_word1->start_position + request_word1->length_position;
    int position2 = request_word2->start_position;

    if (position1 == position2) continue;
    g_hash_table_insert(ctrl_nlp_th->glue_hash, GINT_TO_POINTER(position1), GINT_TO_POINTER(position2));
    g_hash_table_insert(ctrl_nlp_th->glue_hash, GINT_TO_POINTER(position2), GINT_TO_POINTER(position1));
  }
  DONE;
}

enum nlp_glue_status NlpGluedGetStatusForPositions(og_nlp_th ctrl_nlp_th, int position1, int position2)
{
  if (position1 == position2) return nlp_glue_status_Stuck;
  gpointer result = g_hash_table_lookup(ctrl_nlp_th->glue_hash, GINT_TO_POINTER(position1));
  IFN(result) return nlp_glue_status_Loose;
  int found_position = GPOINTER_TO_INT(result);
  if (found_position == position2) return nlp_glue_status_Glued;
  return nlp_glue_status_Loose;
}
