/*
 * intwr.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Write an integer value into an ASN.1 file
 *
 *	\details 	Write an integer value into an opened ASN.1 file. \p value
 *				is the integer value to be encoded.
 *
 *	\return 	If an error occures, the function returns -1, or the number
 *				of bytes written to the file otherwise.
 *
 *	\see 		asnReadInteger
 */

int asnWriteInteger (long value) {
	byte	 buffer[256];			/* Buffer to encode the value			*/
	int		 length= 0;				/* Length of the encoding				*/

	/* Encode the value */

	if ((length= asnEncodeInteger (buffer, value)) == -1)
		return -1;

	/* Write buffer to file */

	return asnWrite (buffer, length);
}

