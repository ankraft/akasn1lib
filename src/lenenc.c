/*
 * lenenc.c
 *
 * written 1993 by Andreas Kraft
 *
 */

# include	<stdio.h>
# include	"akasn1.h"

/**
 *	\brief 		Encode a "length" field
 *
 *	\details 	Encode a length field \p length into the \p buffer.
 *
 *	\return 	If an error occures, the function returns -1, or the length 
 *				of the encoding in \p buffer otherwise.
 *
 *	\note 		Restriction: supports only length between 0 and MAXLONG.
 *
 *	\see 		asnDecodeLength, asnReadLength, asnWriteLength
 */

int asnEncodeLength (byte *buffer, long length) {

	if (length == asnINDEFINITE) {
		*buffer= 0x80;
		return 1;

	} else if (length == asnENDCONTENTS) {
		*(buffer++)= 0;
		*buffer=     0;
		return 2;

	} else if (length <= 0x0000007F) {
		*buffer= (byte)length;
		return 1;

	} else if (length <= 0x00000FF) {
		*(buffer++)= 0x81;
		*buffer= (byte)length;
		return 2;

	} else if (length <= 0x0000FFFF) {
		*(buffer++)= 0x82;
		*(buffer++)= (byte)(length >> 8l);
		*buffer=     (byte)(length & 0xff);
		return 3;

	} else if (length <= 0x00FFFFFF) {
		*(buffer++)= 0x83;
		*(buffer++)= (byte)(length >> 16l);
		*(buffer++)= (byte)((length >> 8l) & 0xFF);
		*buffer=     (byte)(length & 0xFF);
		return 4;

	} else if (length <= 0x7FFFFFFF) {
		*(buffer++)= 0x84;
		*(buffer++)= (byte)(length >> 24l);
		*(buffer++)= (byte)((length >> 16l) & 0xFF);
		*(buffer++)= (byte)((length >> 8l)  & 0xFF);
		*buffer=     (byte)(length & 0xFF);
		return 5;
	}
	return -1;  /* error */
}

