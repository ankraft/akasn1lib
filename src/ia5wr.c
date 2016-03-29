/*
 * ia5wr.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Write an IA5-String into an ASN.1 file
 *
 *	\details 	Write an IA5-String into an opened ASN.1 file. \p value is the
 *				string value to be written.
 *
 *	\return 	If an error occures, the function returns -1, -2 if \p value 
 *				does not contain a legal IA5-String or the number of bytes 
 *				written to the file otherwise.
 *
 *	\see 		asnReadIA5
 */

int asnWriteIA5 (char *value) {
	byte	 tl_buffer[10];			/* Buffer for the tag+len-encoding		*/
	int		 tl_length,				/* Length of the tag+len-encoding		*/
			 length;				/* Length of the ia5-String				*/

	if ((length= asnEncodeIA5 (value, tl_buffer, &tl_length)) == -1)
		return -1;	/* error */
	
	/* write tag + length */

	if (asnWrite (tl_buffer, (uint)tl_length) == -1)
		return -1;	/* error */

	/* write string */

	if (asnWrite ((byte *)value, (uint)length) == -1)
		return -1;	/* error */

	return tl_length+length;	/* OK */
}

