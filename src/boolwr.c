/*
 * boolwr.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Write a boolean value into an ASN.1 file
 *
 *	\details 	Write a boolean value into an opened ASN.1 file. \p value is
 *				the boolean	value to be encoded. It must be either \ref asnFALSE 
 *				or \ref asnTRUE .
 *
 *	\return 	If an error occures, the function returns -1, or 0 otherwise.
 *
 *	\see 		asnReadBoolean
 */

int asnWriteBoolean (byte value) {
	byte	 buffer[256];			/* Buffer to encode the value			*/
	int		 length= 0;				/* Length of the encoding				*/

	/* Encode the value */

	if ((length= asnEncodeBoolean (buffer, value)) == -1)
		return -1;

	/* Write buffer to file */

	return asnWrite (buffer, (uint)length);
}

