/*
 * tagenc.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Encode an ASN.1 tag
 *
 *	\details 	Encode an ASN.1 tag value. \p class is the class of the tag
 *				(\ref asnUNIVERSAL , \ref asnAPPLICATION , \ref asnCONTEXT ,
 *				\ref asnPRIVATE ). \p pc is a flag to indicate wether the data
 *				following the tag is constructed or primitive 
 *				(\ref asnPRIMITIVE , \ref asnCONSTRUCTED ). \p tag is the
 *				number of the tag. \p buffer is the buffer which will get the
 *				resulting encoding.
 *
 *	\return 	If an error occures, the function returns -1, or the number of
 *				encoded bytes otherwise.
 *
 *	\see 		asnDecodeTag, asnReadTag, asnReadTagAndLength, asnWriteTag
 */

int asnEncodeTag (byte *buf, byte clasS, byte pc, byte tag) {
	if (tag < 31) {
		*buf= (clasS | pc | tag);
		return 1;
	} else { /* tag >= 31 */
		int i, n = 0;
		char result[10];

		while(tag > 0) {
			byte aByte = tag & 0x7F;
			result[n++] = aByte;
			tag = (tag >> 7);
		}

		buf[0] = (clasS | pc | 0x1F);

		for (i = 0; i < n; i++) {
			buf[i+1] = result[n-1-i];
			if (i < n-1)
				buf[i+1] |= 0x80;
		}
		return n+1;
	}
	return -1;		/* error */
}
