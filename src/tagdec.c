/*
 * tagdec.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Decode an ASN.1 tag
 *
 *	\details 	Decode an ASN.1 tag value. \p class is a pointer to a variable
 *				to store the class value (\ref asnUNIVERSAL , 
 *				\ref asnAPPLICATION , \ref asnCONTEXT, \ref asnPRIVATE ) in.
 *				\p pc is a pointer to a variable to indicate wether the data
 *				following the tag is constructed or primitive 
 *				(\ref asnPRIMITIVE , \ref asnCONSTRUCTED ). \p tagnum is a
 * 				pointer to a variable to store the tag number in. \p buffer is
 *				the buffer which contains the tag to decode.
 * 
 *	\return 	If an error occures, the function returns -1, or the number	of
 *				decoded bytes otherwise.
 *
 *	\see 		asnEncodeTag, asnReadTag, asnReadTagAndLength, asnWriteTag
 */

int asnDecodeTag (byte *clasS, byte *pc, byte *tagnum, byte *buf) {
	int idx = 1;
	byte b;

	*tagnum = 0;
	*clasS= buf[0] & 0xC0;			/* get class							*/
	*pc=    buf[0] & 0x20;			/* get primitive or constructed			*/
	if ((buf[0] & 0x1F) == 0x1F) {	/* tagnumbers >= 31						*/
		do {
			b = buf[idx] & 0x7F;
			*tagnum = (*tagnum << 7) | b;
		} while ((buf[idx++] & 0x80) != 0);
		/* *tagnum= buf[1]; */
	} else
		*tagnum= buf[0] & 0x1F;

	return idx;
}
