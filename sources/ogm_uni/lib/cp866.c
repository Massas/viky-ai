/*
 *	Handling code page 866.
 *	Copyright (c) 2009 Pertimm by Patrick Constant
 *	Dev : September 2009
 *	Version 1.0
 */
#include <loguni.h>


static unsigned OgCp866[256];

/*
 *  Changes a Unicode char to a cp866 char. This function returns
 *  a truncated char if the Unicode code does not correspond.
 */

PUBLIC(int) OgUniToCp866(u,truncated)
int u,*truncated;
{
if (truncated) *truncated=0;
switch(u) {
  case 0x0410: return(0x80);  /* CYRILLIC CAPITAL LETTER A */
  case 0x0411: return(0x81);  /* CYRILLIC CAPITAL LETTER BE */
  case 0x0412: return(0x82);  /* CYRILLIC CAPITAL LETTER VE */
  case 0x0413: return(0x83);  /* CYRILLIC CAPITAL LETTER GHE */
  case 0x0414: return(0x84);  /* CYRILLIC CAPITAL LETTER DE */
  case 0x0415: return(0x85);  /* CYRILLIC CAPITAL LETTER IE */
  case 0x0416: return(0x86);  /* CYRILLIC CAPITAL LETTER ZHE */
  case 0x0417: return(0x87);  /* CYRILLIC CAPITAL LETTER ZE */
  case 0x0418: return(0x88);  /* CYRILLIC CAPITAL LETTER I */
  case 0x0419: return(0x89);  /* CYRILLIC CAPITAL LETTER SHORT I */
  case 0x041a: return(0x8A);  /* CYRILLIC CAPITAL LETTER KA */
  case 0x041b: return(0x8B);  /* CYRILLIC CAPITAL LETTER EL */
  case 0x041c: return(0x8C);  /* CYRILLIC CAPITAL LETTER EM */
  case 0x041d: return(0x8D);  /* CYRILLIC CAPITAL LETTER EN */
  case 0x041e: return(0x8E);  /* CYRILLIC CAPITAL LETTER O */
  case 0x041f: return(0x8F);  /* CYRILLIC CAPITAL LETTER PE */
  case 0x0420: return(0x90);  /* CYRILLIC CAPITAL LETTER ER */
  case 0x0421: return(0x91);  /* CYRILLIC CAPITAL LETTER ES */
  case 0x0422: return(0x92);  /* CYRILLIC CAPITAL LETTER TE */
  case 0x0423: return(0x93);  /* CYRILLIC CAPITAL LETTER U */
  case 0x0424: return(0x94);  /* CYRILLIC CAPITAL LETTER EF */
  case 0x0425: return(0x95);  /* CYRILLIC CAPITAL LETTER HA */
  case 0x0426: return(0x96);  /* CYRILLIC CAPITAL LETTER TSE */
  case 0x0427: return(0x97);  /* CYRILLIC CAPITAL LETTER CHE */
  case 0x0428: return(0x98);  /* CYRILLIC CAPITAL LETTER SHA */
  case 0x0429: return(0x99);  /* CYRILLIC CAPITAL LETTER SHCHA */
  case 0x042a: return(0x9A);  /* CYRILLIC CAPITAL LETTER HARD SIGN */
  case 0x042b: return(0x9B);  /* CYRILLIC CAPITAL LETTER YERU */
  case 0x042c: return(0x9C);  /* CYRILLIC CAPITAL LETTER SOFT SIGN */
  case 0x042d: return(0x9D);  /* CYRILLIC CAPITAL LETTER E */
  case 0x042e: return(0x9E);  /* CYRILLIC CAPITAL LETTER YU */
  case 0x042f: return(0x9F);  /* CYRILLIC CAPITAL LETTER YA */
  case 0x0430: return(0xA0);  /* CYRILLIC SMALL LETTER A */
  case 0x0431: return(0xA1);  /* CYRILLIC SMALL LETTER BE */
  case 0x0432: return(0xA2);  /* CYRILLIC SMALL LETTER VE */
  case 0x0433: return(0xA3);  /* CYRILLIC SMALL LETTER GHE */
  case 0x0434: return(0xA4);  /* CYRILLIC SMALL LETTER DE */
  case 0x0435: return(0xA5);  /* CYRILLIC SMALL LETTER IE */
  case 0x0436: return(0xA6);  /* CYRILLIC SMALL LETTER ZHE */
  case 0x0437: return(0xA7);  /* CYRILLIC SMALL LETTER ZE */
  case 0x0438: return(0xA8);  /* CYRILLIC SMALL LETTER I */
  case 0x0439: return(0xA9);  /* CYRILLIC SMALL LETTER SHORT I */
  case 0x043a: return(0xAA);  /* CYRILLIC SMALL LETTER KA */
  case 0x043b: return(0xAB);  /* CYRILLIC SMALL LETTER EL */
  case 0x043c: return(0xAC);  /* CYRILLIC SMALL LETTER EM */
  case 0x043d: return(0xAD);  /* CYRILLIC SMALL LETTER EN */
  case 0x043e: return(0xAE);  /* CYRILLIC SMALL LETTER O */
  case 0x043f: return(0xAF);  /* CYRILLIC SMALL LETTER PE */
  case 0x2591: return(0xB0);  /* LIGHT SHADE */
  case 0x2592: return(0xB1);  /* MEDIUM SHADE */
  case 0x2593: return(0xB2);  /* DARK SHADE */
  case 0x2502: return(0xB3);  /* BOX DRAWINGS LIGHT VERTICAL */
  case 0x2524: return(0xB4);  /* BOX DRAWINGS LIGHT VERTICAL AND LEFT */
  case 0x2561: return(0xB5);  /* BOX DRAWINGS VERTICAL SINGLE AND LEFT DOUBLE */
  case 0x2562: return(0xB6);  /* BOX DRAWINGS VERTICAL DOUBLE AND LEFT SINGLE */
  case 0x2556: return(0xB7);  /* BOX DRAWINGS DOWN DOUBLE AND LEFT SINGLE */
  case 0x2555: return(0xB8);  /* BOX DRAWINGS DOWN SINGLE AND LEFT DOUBLE */
  case 0x2563: return(0xB9);  /* BOX DRAWINGS DOUBLE VERTICAL AND LEFT */
  case 0x2551: return(0xBA);  /* BOX DRAWINGS DOUBLE VERTICAL */
  case 0x2557: return(0xBB);  /* BOX DRAWINGS DOUBLE DOWN AND LEFT */
  case 0x255d: return(0xBC);  /* BOX DRAWINGS DOUBLE UP AND LEFT */
  case 0x255c: return(0xBD);  /* BOX DRAWINGS UP DOUBLE AND LEFT SINGLE */
  case 0x255b: return(0xBE);  /* BOX DRAWINGS UP SINGLE AND LEFT DOUBLE */
  case 0x2510: return(0xBF);  /* BOX DRAWINGS LIGHT DOWN AND LEFT */
  case 0x2514: return(0xC0);  /* BOX DRAWINGS LIGHT UP AND RIGHT */
  case 0x2534: return(0xC1);  /* BOX DRAWINGS LIGHT UP AND HORIZONTAL */
  case 0x252c: return(0xC2);  /* BOX DRAWINGS LIGHT DOWN AND HORIZONTAL */
  case 0x251c: return(0xC3);  /* BOX DRAWINGS LIGHT VERTICAL AND RIGHT */
  case 0x2500: return(0xC4);  /* BOX DRAWINGS LIGHT HORIZONTAL */
  case 0x253c: return(0xC5);  /* BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL */
  case 0x255e: return(0xC6);  /* BOX DRAWINGS VERTICAL SINGLE AND RIGHT DOUBLE */
  case 0x255f: return(0xC7);  /* BOX DRAWINGS VERTICAL DOUBLE AND RIGHT SINGLE */
  case 0x255a: return(0xC8);  /* BOX DRAWINGS DOUBLE UP AND RIGHT */
  case 0x2554: return(0xC9);  /* BOX DRAWINGS DOUBLE DOWN AND RIGHT */
  case 0x2569: return(0xCA);  /* BOX DRAWINGS DOUBLE UP AND HORIZONTAL */
  case 0x2566: return(0xCB);  /* BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL */
  case 0x2560: return(0xCC);  /* BOX DRAWINGS DOUBLE VERTICAL AND RIGHT */
  case 0x2550: return(0xCD);  /* BOX DRAWINGS DOUBLE HORIZONTAL */
  case 0x256c: return(0xCE);  /* BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL */
  case 0x2567: return(0xCF);  /* BOX DRAWINGS UP SINGLE AND HORIZONTAL DOUBLE */
  case 0x2568: return(0xD0);  /* BOX DRAWINGS UP DOUBLE AND HORIZONTAL SINGLE */
  case 0x2564: return(0xD1);  /* BOX DRAWINGS DOWN SINGLE AND HORIZONTAL DOUBLE */
  case 0x2565: return(0xD2);  /* BOX DRAWINGS DOWN DOUBLE AND HORIZONTAL SINGLE */
  case 0x2559: return(0xD3);  /* BOX DRAWINGS UP DOUBLE AND RIGHT SINGLE */
  case 0x2558: return(0xD4);  /* BOX DRAWINGS UP SINGLE AND RIGHT DOUBLE */
  case 0x2552: return(0xD5);  /* BOX DRAWINGS DOWN SINGLE AND RIGHT DOUBLE */
  case 0x2553: return(0xD6);  /* BOX DRAWINGS DOWN DOUBLE AND RIGHT SINGLE */
  case 0x256b: return(0xD7);  /* BOX DRAWINGS VERTICAL DOUBLE AND HORIZONTAL SINGLE */
  case 0x256a: return(0xD8);  /* BOX DRAWINGS VERTICAL SINGLE AND HORIZONTAL DOUBLE */
  case 0x2518: return(0xD9);  /* BOX DRAWINGS LIGHT UP AND LEFT */
  case 0x250c: return(0xDA);  /* BOX DRAWINGS LIGHT DOWN AND RIGHT */
  case 0x2588: return(0xDB);  /* FULL BLOCK */
  case 0x2584: return(0xDC);  /* LOWER HALF BLOCK */
  case 0x258c: return(0xDD);  /* LEFT HALF BLOCK */
  case 0x2590: return(0xDE);  /* RIGHT HALF BLOCK */
  case 0x2580: return(0xDF);  /* UPPER HALF BLOCK */
  case 0x0440: return(0xE0);  /* CYRILLIC SMALL LETTER ER */
  case 0x0441: return(0xE1);  /* CYRILLIC SMALL LETTER ES */
  case 0x0442: return(0xE2);  /* CYRILLIC SMALL LETTER TE */
  case 0x0443: return(0xE3);  /* CYRILLIC SMALL LETTER U */
  case 0x0444: return(0xE4);  /* CYRILLIC SMALL LETTER EF */
  case 0x0445: return(0xE5);  /* CYRILLIC SMALL LETTER HA */
  case 0x0446: return(0xE6);  /* CYRILLIC SMALL LETTER TSE */
  case 0x0447: return(0xE7);  /* CYRILLIC SMALL LETTER CHE */
  case 0x0448: return(0xE8);  /* CYRILLIC SMALL LETTER SHA */
  case 0x0449: return(0xE9);  /* CYRILLIC SMALL LETTER SHCHA */
  case 0x044a: return(0xEA);  /* CYRILLIC SMALL LETTER HARD SIGN */
  case 0x044b: return(0xEB);  /* CYRILLIC SMALL LETTER YERU */
  case 0x044c: return(0xEC);  /* CYRILLIC SMALL LETTER SOFT SIGN */
  case 0x044d: return(0xED);  /* CYRILLIC SMALL LETTER E */
  case 0x044e: return(0xEE);  /* CYRILLIC SMALL LETTER YU */
  case 0x044f: return(0xEF);  /* CYRILLIC SMALL LETTER YA */
  case 0x0401: return(0xF0);  /* CYRILLIC CAPITAL LETTER IO */
  case 0x0451: return(0xF1);  /* CYRILLIC SMALL LETTER IO */
  case 0x0404: return(0xF2);  /* CYRILLIC CAPITAL LETTER UKRAINIAN IE */
  case 0x0454: return(0xF3);  /* CYRILLIC SMALL LETTER UKRAINIAN IE */
  case 0x0407: return(0xF4);  /* CYRILLIC CAPITAL LETTER YI */
  case 0x0457: return(0xF5);  /* CYRILLIC SMALL LETTER YI */
  case 0x040e: return(0xF6);  /* CYRILLIC CAPITAL LETTER SHORT U */
  case 0x045e: return(0xF7);  /* CYRILLIC SMALL LETTER SHORT U */
  case 0x00b0: return(0xF8);  /* DEGREE SIGN */
  case 0x2219: return(0xF9);  /* BULLET OPERATOR */
  case 0x00b7: return(0xFA);  /* MIDDLE DOT */
  case 0x221a: return(0xFB);  /* SQUARE ROOT */
  case 0x2116: return(0xFC);  /* NUMERO SIGN */
  case 0x00a4: return(0xFD);  /* CURRENCY SIGN */
  case 0x25a0: return(0xFE);  /* BLACK SQUARE */
  case 0x00a0: return(0xFF);  /* NO-BREAK SPACE */
  }
if (truncated) { if (u>0xff) *truncated=1; }
return(u&0xff);
}





/*
 *  reverse function.
 */

PUBLIC(int) OgCp866ToUni(c)
int c;
{
if (c<256) return(OgCp866[c]);
else return(c);
}



static unsigned OgCp866[256] = {
  0x0000, /* 0x00  NULL */
  0x0001, /* 0x01  START OF HEADING */
  0x0002, /* 0x02  START OF TEXT */
  0x0003, /* 0x03  END OF TEXT */
  0x0004, /* 0x04  END OF TRANSMISSION */
  0x0005, /* 0x05  ENQUIRY */
  0x0006, /* 0x06  ACKNOWLEDGE */
  0x0007, /* 0x07  BELL */
  0x0008, /* 0x08  BACKSPACE */
  0x0009, /* 0x09  HORIZONTAL TABULATION */
  0x000A, /* 0x0A  LINE FEED */
  0x000B, /* 0x0B  VERTICAL TABULATION */
  0x000C, /* 0x0C  FORM FEED */
  0x000D, /* 0x0D  CARRIAGE RETURN */
  0x000E, /* 0x0E  SHIFT OUT */
  0x000F, /* 0x0F  SHIFT IN */
  0x0010, /* 0x10  DATA LINK ESCAPE */
  0x0011, /* 0x11  DEVICE CONTROL ONE */
  0x0012, /* 0x12  DEVICE CONTROL TWO */
  0x0013, /* 0x13  DEVICE CONTROL THREE */
  0x0014, /* 0x14  DEVICE CONTROL FOUR */
  0x0015, /* 0x15  NEGATIVE ACKNOWLEDGE */
  0x0016, /* 0x16  SYNCHRONOUS IDLE */
  0x0017, /* 0x17  END OF TRANSMISSION BLOCK */
  0x0018, /* 0x18  CANCEL */
  0x0019, /* 0x19  END OF MEDIUM */
  0x001A, /* 0x1A  SUBSTITUTE */
  0x001B, /* 0x1B  ESCAPE */
  0x001C, /* 0x1C  FILE SEPARATOR */
  0x001D, /* 0x1D  GROUP SEPARATOR */
  0x001E, /* 0x1E  RECORD SEPARATOR */
  0x001F, /* 0x1F  UNIT SEPARATOR */
  0x0020, /* 0x20  SPACE */
  0x0021, /* 0x21  EXCLAMATION MARK */
  0x0022, /* 0x22  QUOTATION MARK */
  0x0023, /* 0x23  NUMBER SIGN */
  0x0024, /* 0x24  DOLLAR SIGN */
  0x0025, /* 0x25  PERCENT SIGN */
  0x0026, /* 0x26  AMPERSAND */
  0x0027, /* 0x27  APOSTROPHE */
  0x0028, /* 0x28  LEFT PARENTHESIS */
  0x0029, /* 0x29  RIGHT PARENTHESIS */
  0x002A, /* 0x2A  ASTERISK */
  0x002B, /* 0x2B  PLUS SIGN */
  0x002C, /* 0x2C  COMMA */
  0x002D, /* 0x2D  HYPHEN-MINUS */
  0x002E, /* 0x2E  FULL STOP */
  0x002F, /* 0x2F  SOLIDUS */
  0x0030, /* 0x30  DIGIT ZERO */
  0x0031, /* 0x31  DIGIT ONE */
  0x0032, /* 0x32  DIGIT TWO */
  0x0033, /* 0x33  DIGIT THREE */
  0x0034, /* 0x34  DIGIT FOUR */
  0x0035, /* 0x35  DIGIT FIVE */
  0x0036, /* 0x36  DIGIT SIX */
  0x0037, /* 0x37  DIGIT SEVEN */
  0x0038, /* 0x38  DIGIT EIGHT */
  0x0039, /* 0x39  DIGIT NINE */
  0x003A, /* 0x3A  COLON */
  0x003B, /* 0x3B  SEMICOLON */
  0x003C, /* 0x3C  LESS-THAN SIGN */
  0x003D, /* 0x3D  EQUALS SIGN */
  0x003E, /* 0x3E  GREATER-THAN SIGN */
  0x003F, /* 0x3F  QUESTION MARK */
  0x0040, /* 0x40  COMMERCIAL AT */
  0x0041, /* 0x41  LATIN CAPITAL LETTER A */
  0x0042, /* 0x42  LATIN CAPITAL LETTER B */
  0x0043, /* 0x43  LATIN CAPITAL LETTER C */
  0x0044, /* 0x44  LATIN CAPITAL LETTER D */
  0x0045, /* 0x45  LATIN CAPITAL LETTER E */
  0x0046, /* 0x46  LATIN CAPITAL LETTER F */
  0x0047, /* 0x47  LATIN CAPITAL LETTER G */
  0x0048, /* 0x48  LATIN CAPITAL LETTER H */
  0x0049, /* 0x49  LATIN CAPITAL LETTER I */
  0x004A, /* 0x4A  LATIN CAPITAL LETTER J */
  0x004B, /* 0x4B  LATIN CAPITAL LETTER K */
  0x004C, /* 0x4C  LATIN CAPITAL LETTER L */
  0x004D, /* 0x4D  LATIN CAPITAL LETTER M */
  0x004E, /* 0x4E  LATIN CAPITAL LETTER N */
  0x004F, /* 0x4F  LATIN CAPITAL LETTER O */
  0x0050, /* 0x50  LATIN CAPITAL LETTER P */
  0x0051, /* 0x51  LATIN CAPITAL LETTER Q */
  0x0052, /* 0x52  LATIN CAPITAL LETTER R */
  0x0053, /* 0x53  LATIN CAPITAL LETTER S */
  0x0054, /* 0x54  LATIN CAPITAL LETTER T */
  0x0055, /* 0x55  LATIN CAPITAL LETTER U */
  0x0056, /* 0x56  LATIN CAPITAL LETTER V */
  0x0057, /* 0x57  LATIN CAPITAL LETTER W */
  0x0058, /* 0x58  LATIN CAPITAL LETTER X */
  0x0059, /* 0x59  LATIN CAPITAL LETTER Y */
  0x005A, /* 0x5A  LATIN CAPITAL LETTER Z */
  0x005B, /* 0x5B  LEFT SQUARE BRACKET */
  0x005C, /* 0x5C  REVERSE SOLIDUS */
  0x005D, /* 0x5D  RIGHT SQUARE BRACKET */
  0x005E, /* 0x5E  CIRCUMFLEX ACCENT */
  0x005F, /* 0x5F  LOW LINE */
  0x0060, /* 0x60  GRAVE ACCENT */
  0x0061, /* 0x61  LATIN SMALL LETTER A */
  0x0062, /* 0x62  LATIN SMALL LETTER B */
  0x0063, /* 0x63  LATIN SMALL LETTER C */
  0x0064, /* 0x64  LATIN SMALL LETTER D */
  0x0065, /* 0x65  LATIN SMALL LETTER E */
  0x0066, /* 0x66  LATIN SMALL LETTER F */
  0x0067, /* 0x67  LATIN SMALL LETTER G */
  0x0068, /* 0x68  LATIN SMALL LETTER H */
  0x0069, /* 0x69  LATIN SMALL LETTER I */
  0x006A, /* 0x6A  LATIN SMALL LETTER J */
  0x006B, /* 0x6B  LATIN SMALL LETTER K */
  0x006C, /* 0x6C  LATIN SMALL LETTER L */
  0x006D, /* 0x6D  LATIN SMALL LETTER M */
  0x006E, /* 0x6E  LATIN SMALL LETTER N */
  0x006F, /* 0x6F  LATIN SMALL LETTER O */
  0x0070, /* 0x70  LATIN SMALL LETTER P */
  0x0071, /* 0x71  LATIN SMALL LETTER Q */
  0x0072, /* 0x72  LATIN SMALL LETTER R */
  0x0073, /* 0x73  LATIN SMALL LETTER S */
  0x0074, /* 0x74  LATIN SMALL LETTER T */
  0x0075, /* 0x75  LATIN SMALL LETTER U */
  0x0076, /* 0x76  LATIN SMALL LETTER V */
  0x0077, /* 0x77  LATIN SMALL LETTER W */
  0x0078, /* 0x78  LATIN SMALL LETTER X */
  0x0079, /* 0x79  LATIN SMALL LETTER Y */
  0x007A, /* 0x7A  LATIN SMALL LETTER Z */
  0x007B, /* 0x7B  LEFT CURLY BRACKET */
  0x007C, /* 0x7C  VERTICAL LINE */
  0x007D, /* 0x7D  RIGHT CURLY BRACKET */
  0x007E, /* 0x7E  TILDE */
  0x007F, /* 0x7F  DELETE */
  0x0410, /* 0x80  CYRILLIC CAPITAL LETTER A */
  0x0411, /* 0x81  CYRILLIC CAPITAL LETTER BE */
  0x0412, /* 0x82  CYRILLIC CAPITAL LETTER VE */
  0x0413, /* 0x83  CYRILLIC CAPITAL LETTER GHE */
  0x0414, /* 0x84  CYRILLIC CAPITAL LETTER DE */
  0x0415, /* 0x85  CYRILLIC CAPITAL LETTER IE */
  0x0416, /* 0x86  CYRILLIC CAPITAL LETTER ZHE */
  0x0417, /* 0x87  CYRILLIC CAPITAL LETTER ZE */
  0x0418, /* 0x88  CYRILLIC CAPITAL LETTER I */
  0x0419, /* 0x89  CYRILLIC CAPITAL LETTER SHORT I */
  0x041a, /* 0x8A  CYRILLIC CAPITAL LETTER KA */
  0x041b, /* 0x8B  CYRILLIC CAPITAL LETTER EL */
  0x041c, /* 0x8C  CYRILLIC CAPITAL LETTER EM */
  0x041d, /* 0x8D  CYRILLIC CAPITAL LETTER EN */
  0x041e, /* 0x8E  CYRILLIC CAPITAL LETTER O */
  0x041f, /* 0x8F  CYRILLIC CAPITAL LETTER PE */
  0x0420, /* 0x90  CYRILLIC CAPITAL LETTER ER */
  0x0421, /* 0x91  CYRILLIC CAPITAL LETTER ES */
  0x0422, /* 0x92  CYRILLIC CAPITAL LETTER TE */
  0x0423, /* 0x93  CYRILLIC CAPITAL LETTER U */
  0x0424, /* 0x94  CYRILLIC CAPITAL LETTER EF */
  0x0425, /* 0x95  CYRILLIC CAPITAL LETTER HA */
  0x0426, /* 0x96  CYRILLIC CAPITAL LETTER TSE */
  0x0427, /* 0x97  CYRILLIC CAPITAL LETTER CHE */
  0x0428, /* 0x98  CYRILLIC CAPITAL LETTER SHA */
  0x0429, /* 0x99  CYRILLIC CAPITAL LETTER SHCHA */
  0x042a, /* 0x9A  CYRILLIC CAPITAL LETTER HARD SIGN */
  0x042b, /* 0x9B  CYRILLIC CAPITAL LETTER YERU */
  0x042c, /* 0x9C  CYRILLIC CAPITAL LETTER SOFT SIGN */
  0x042d, /* 0x9D  CYRILLIC CAPITAL LETTER E */
  0x042e, /* 0x9E  CYRILLIC CAPITAL LETTER YU */
  0x042f, /* 0x9F  CYRILLIC CAPITAL LETTER YA */
  0x0430, /* 0xA0  CYRILLIC SMALL LETTER A */
  0x0431, /* 0xA1  CYRILLIC SMALL LETTER BE */
  0x0432, /* 0xA2  CYRILLIC SMALL LETTER VE */
  0x0433, /* 0xA3  CYRILLIC SMALL LETTER GHE */
  0x0434, /* 0xA4  CYRILLIC SMALL LETTER DE */
  0x0435, /* 0xA5  CYRILLIC SMALL LETTER IE */
  0x0436, /* 0xA6  CYRILLIC SMALL LETTER ZHE */
  0x0437, /* 0xA7  CYRILLIC SMALL LETTER ZE */
  0x0438, /* 0xA8  CYRILLIC SMALL LETTER I */
  0x0439, /* 0xA9  CYRILLIC SMALL LETTER SHORT I */
  0x043a, /* 0xAA  CYRILLIC SMALL LETTER KA */
  0x043b, /* 0xAB  CYRILLIC SMALL LETTER EL */
  0x043c, /* 0xAC  CYRILLIC SMALL LETTER EM */
  0x043d, /* 0xAD  CYRILLIC SMALL LETTER EN */
  0x043e, /* 0xAE  CYRILLIC SMALL LETTER O */
  0x043f, /* 0xAF  CYRILLIC SMALL LETTER PE */
  0x2591, /* 0xB0  LIGHT SHADE */
  0x2592, /* 0xB1  MEDIUM SHADE */
  0x2593, /* 0xB2  DARK SHADE */
  0x2502, /* 0xB3  BOX DRAWINGS LIGHT VERTICAL */
  0x2524, /* 0xB4  BOX DRAWINGS LIGHT VERTICAL AND LEFT */
  0x2561, /* 0xB5  BOX DRAWINGS VERTICAL SINGLE AND LEFT DOUBLE */
  0x2562, /* 0xB6  BOX DRAWINGS VERTICAL DOUBLE AND LEFT SINGLE */
  0x2556, /* 0xB7  BOX DRAWINGS DOWN DOUBLE AND LEFT SINGLE */
  0x2555, /* 0xB8  BOX DRAWINGS DOWN SINGLE AND LEFT DOUBLE */
  0x2563, /* 0xB9  BOX DRAWINGS DOUBLE VERTICAL AND LEFT */
  0x2551, /* 0xBA  BOX DRAWINGS DOUBLE VERTICAL */
  0x2557, /* 0xBB  BOX DRAWINGS DOUBLE DOWN AND LEFT */
  0x255d, /* 0xBC  BOX DRAWINGS DOUBLE UP AND LEFT */
  0x255c, /* 0xBD  BOX DRAWINGS UP DOUBLE AND LEFT SINGLE */
  0x255b, /* 0xBE  BOX DRAWINGS UP SINGLE AND LEFT DOUBLE */
  0x2510, /* 0xBF  BOX DRAWINGS LIGHT DOWN AND LEFT */
  0x2514, /* 0xC0  BOX DRAWINGS LIGHT UP AND RIGHT */
  0x2534, /* 0xC1  BOX DRAWINGS LIGHT UP AND HORIZONTAL */
  0x252c, /* 0xC2  BOX DRAWINGS LIGHT DOWN AND HORIZONTAL */
  0x251c, /* 0xC3  BOX DRAWINGS LIGHT VERTICAL AND RIGHT */
  0x2500, /* 0xC4  BOX DRAWINGS LIGHT HORIZONTAL */
  0x253c, /* 0xC5  BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL */
  0x255e, /* 0xC6  BOX DRAWINGS VERTICAL SINGLE AND RIGHT DOUBLE */
  0x255f, /* 0xC7  BOX DRAWINGS VERTICAL DOUBLE AND RIGHT SINGLE */
  0x255a, /* 0xC8  BOX DRAWINGS DOUBLE UP AND RIGHT */
  0x2554, /* 0xC9  BOX DRAWINGS DOUBLE DOWN AND RIGHT */
  0x2569, /* 0xCA  BOX DRAWINGS DOUBLE UP AND HORIZONTAL */
  0x2566, /* 0xCB  BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL */
  0x2560, /* 0xCC  BOX DRAWINGS DOUBLE VERTICAL AND RIGHT */
  0x2550, /* 0xCD  BOX DRAWINGS DOUBLE HORIZONTAL */
  0x256c, /* 0xCE  BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL */
  0x2567, /* 0xCF  BOX DRAWINGS UP SINGLE AND HORIZONTAL DOUBLE */
  0x2568, /* 0xD0  BOX DRAWINGS UP DOUBLE AND HORIZONTAL SINGLE */
  0x2564, /* 0xD1  BOX DRAWINGS DOWN SINGLE AND HORIZONTAL DOUBLE */
  0x2565, /* 0xD2  BOX DRAWINGS DOWN DOUBLE AND HORIZONTAL SINGLE */
  0x2559, /* 0xD3  BOX DRAWINGS UP DOUBLE AND RIGHT SINGLE */
  0x2558, /* 0xD4  BOX DRAWINGS UP SINGLE AND RIGHT DOUBLE */
  0x2552, /* 0xD5  BOX DRAWINGS DOWN SINGLE AND RIGHT DOUBLE */
  0x2553, /* 0xD6  BOX DRAWINGS DOWN DOUBLE AND RIGHT SINGLE */
  0x256b, /* 0xD7  BOX DRAWINGS VERTICAL DOUBLE AND HORIZONTAL SINGLE */
  0x256a, /* 0xD8  BOX DRAWINGS VERTICAL SINGLE AND HORIZONTAL DOUBLE */
  0x2518, /* 0xD9  BOX DRAWINGS LIGHT UP AND LEFT */
  0x250c, /* 0xDA  BOX DRAWINGS LIGHT DOWN AND RIGHT */
  0x2588, /* 0xDB  FULL BLOCK */
  0x2584, /* 0xDC  LOWER HALF BLOCK */
  0x258c, /* 0xDD  LEFT HALF BLOCK */
  0x2590, /* 0xDE  RIGHT HALF BLOCK */
  0x2580, /* 0xDF  UPPER HALF BLOCK */
  0x0440, /* 0xE0  CYRILLIC SMALL LETTER ER */
  0x0441, /* 0xE1  CYRILLIC SMALL LETTER ES */
  0x0442, /* 0xE2  CYRILLIC SMALL LETTER TE */
  0x0443, /* 0xE3  CYRILLIC SMALL LETTER U */
  0x0444, /* 0xE4  CYRILLIC SMALL LETTER EF */
  0x0445, /* 0xE5  CYRILLIC SMALL LETTER HA */
  0x0446, /* 0xE6  CYRILLIC SMALL LETTER TSE */
  0x0447, /* 0xE7  CYRILLIC SMALL LETTER CHE */
  0x0448, /* 0xE8  CYRILLIC SMALL LETTER SHA */
  0x0449, /* 0xE9  CYRILLIC SMALL LETTER SHCHA */
  0x044a, /* 0xEA  CYRILLIC SMALL LETTER HARD SIGN */
  0x044b, /* 0xEB  CYRILLIC SMALL LETTER YERU */
  0x044c, /* 0xEC  CYRILLIC SMALL LETTER SOFT SIGN */
  0x044d, /* 0xED  CYRILLIC SMALL LETTER E */
  0x044e, /* 0xEE  CYRILLIC SMALL LETTER YU */
  0x044f, /* 0xEF  CYRILLIC SMALL LETTER YA */
  0x0401, /* 0xF0  CYRILLIC CAPITAL LETTER IO */
  0x0451, /* 0xF1  CYRILLIC SMALL LETTER IO */
  0x0404, /* 0xF2  CYRILLIC CAPITAL LETTER UKRAINIAN IE */
  0x0454, /* 0xF3  CYRILLIC SMALL LETTER UKRAINIAN IE */
  0x0407, /* 0xF4  CYRILLIC CAPITAL LETTER YI */
  0x0457, /* 0xF5  CYRILLIC SMALL LETTER YI */
  0x040e, /* 0xF6  CYRILLIC CAPITAL LETTER SHORT U */
  0x045e, /* 0xF7  CYRILLIC SMALL LETTER SHORT U */
  0x00b0, /* 0xF8  DEGREE SIGN */
  0x2219, /* 0xF9  BULLET OPERATOR */
  0x00b7, /* 0xFA  MIDDLE DOT */
  0x221a, /* 0xFB  SQUARE ROOT */
  0x2116, /* 0xFC  NUMERO SIGN */
  0x00a4, /* 0xFD  CURRENCY SIGN */
  0x25a0, /* 0xFE  BLACK SQUARE */
  0x00a0  /* 0xFF  NO-BREAK SPACE */
  };

