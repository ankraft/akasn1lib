/*
 * nullrd.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Read a Null value with tag and length
 *
 *	\details 	Read a Null value from an opened ASN.1 file, including the tag
 *				and the	length.
 *
 *	\return 	If an error occures, the function returns -1, -2 if the value
 *				read is not	a Null value or the number of bytes read otherwise.
 *
 *	\see 		asnEncodeNull, asnReadNullL, asnWriteNull
 */

int asnReadNullTL (void) {
	int		 taglen;			/* length of tag							*/
	byte	 buffer[256],		/* buffer									*/
			 cl,				/* tagclass									*/
			 pc,				/* primitive or constructed					*/
			 tag;				/* the tag itself							*/

	/* read and decode the tag. Is it a Null-value ? */

	if ((taglen= asnReadTag (buffer)) == -1) 
		return -1;
	asnDecodeTag (&cl, &pc, &tag, buffer);

	if (cl != asnUNIVERSAL || tag != asnNULLVALUE) {
		asnSkipFile (-taglen);		/* skip backwards  !					*/
		return -2;
	}

	/* Get the length of the Null Value */

	return asnReadNullL ();
}


/**
 *	\brief 		Read a Null value with length field
 *
 *	\details 	Read a Null-value (with length) from the opened ASN.1 file 
 *				without the tag. This function does nothing more than read one
 *				byte of the input stream and ignore the length-field which 
 *				should be 0.
 *
 *	\return 	If an error occures, the function returns -1, or the number
 *				of bytes read otherwise.
 *
 *	\see 		asnEncodeNull, asnReadNullTL, asnWriteNull
 */

int asnReadNullL (void) {
	return asnSkipFile (1);
}
