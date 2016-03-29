/*
 * nullwr.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Write a Null value into a file
 *
 *	\details 	Write a Null value into the opened ASN.1 file.
 *
 *	\return 	If an error occures, the function returns -1, or the number
 *				of bytes written otherwise.
 *
 *	\see 		asnEncodeNull, asnReadNullTL, asnReadNullL
 */

int asnWriteNull (void) {
	byte	 buffer[10];			/* Buffer for the tag+len-encoding		*/
	int		 length;				/* Length of the encoding				*/

	if ((length= asnEncodeNull (buffer)) == -1)
		return -1;	/* error */
	return asnWrite (buffer, (uint)length);
}

