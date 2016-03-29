/*
 * lendec.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Decode a "length" field
 *
 *	\details 	This function decodes a "length" field of an ASN.1 value. 
 *				\p buffer contains the encoded length, \p length is a pointer
 *				to a long variable which should	get the result.
 *
 *	\return 	The function returns the length of the encoding in \p buffer.
 *
 *	\note 		Restriction: supports only length between 0 and MAXLONG.
 *
 *	\see 		asnEncodeLength, asnReadLength, asnWriteLength
 */

int asnDecodeLength (byte *buffer, long *length) {
	int		 size= 0, i;
	byte	 b;

	*length= 0;
	if (buffer[0] == 0x80) {
		*length= asnINDEFINITE;
		return 1;
	}
	if (buffer[0] == 0x00 && buffer[1] == 0x00) {
		*length= asnENDCONTENTS;
		return 1;
	}

	if (buffer[0] <= 0x7F) {
		b= buffer[0];
		*length= (long)b;
		return 1;
	}
	
	size= buffer[0] & 0x7F;
	for (i= 1; i <= size; i++) {
		b= buffer[i];
		*length+= (long)b << ((size-i)*8);
	}

	return size+1;
}
