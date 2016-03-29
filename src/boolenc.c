/*
 * boolenc.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief Encode a boolean value.
 *
 *	\details	Encode a boolean \p value into a \p buffer. 
 *				The type tag and length	is also encoded.
 *
 *	\return 	The function returns -1 in case of an error, or the length of the
 *				encoding in the \p buffer.
 *
 *	\see 		asnDecodeBoolean, asnReadBoolean, asnReadBooleanTL, asnReadBooleanL,
 *	 			asnWriteBoolean
 */

int asnEncodeBoolean (byte *buffer, byte value) {
	int		 l= 0;				/* length of encoding						*/

	/* Encode tag */

	if (value)
		value = asnTRUE;

	if (asnEncodeTag (&buffer[l++],asnUNIVERSAL,asnPRIMITIVE,asnBOOLEAN) == -1) 
		return -1;		/* error */


	/* Encode length */

	if (asnEncodeLength (&buffer[l++], 1l) == -1)
		return -1;		/* error */
	
	buffer[l++]= value;

	return l;			/* OK */
}

/**
 *	\brief 		Encode a boolean value.
 *
 *	\details	Encode a boolean \p value into a \p buffer. 
 *				The type tag and length	is NOT encoded, only the value
 *
 *	\return 	The function returns -1 in case of an error, or the length of the
 *				encoding in the \p buffer.
 *
 *	\see 		asnDecodeBoolean, asnReadBoolean, asnReadBooleanTL, asnReadBooleanL,
 *	 			asnWriteBoolean
 */

int asnEncodeBooleanValue (byte *buffer, byte value) {
	buffer[0] = value;
	return 1;
}
