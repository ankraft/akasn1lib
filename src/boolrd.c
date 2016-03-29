/*
 * boolrd.c
 *
 * written 1993 by Andreas Kraft
 */


# include	"akasn1.h"

/**
 *	\brief Read a boolean value from an ASN.1-File (with tag and length)
 *
 *	\details	Read a boolean value from the opened ASN.1 file, including 
 *				the tag and the length of the encoding. `value` is the 
 *				variable to fill with the result.
 *
 *	\return 	If an error occures, the function returns -1. -2 is returned
 *				if the value read is not of type boolean. 0 is return if no
 *				error occured.
 *
 *	\see 		asnDecodeBoolean, asnReadBoolean, asnReadBooleanL
 */

int asnReadBooleanTL (byte *value) {
	int		 taglen;			/* length of tag							*/
	byte	 buffer[256],		/* buffer									*/
			 cl,				/* tagclass									*/
			 pc,				/* primitive or constructed					*/
			 tag;				/* the tag itself							*/

	/* read and decode the tag. Is it a boolean ? */

	if ((taglen= asnReadTag (buffer)) == -1) 
		return -1;
	asnDecodeTag (&cl, &pc, &tag, buffer);

	if (cl != asnUNIVERSAL || tag != asnBOOLEAN) {
		asnSkipFile (-taglen);		/* skip backwards  !					*/
		return -2;
	}

	/* Get the boolean */

	return asnReadBooleanL (value);
}


/**
 *	\brief Read a boolean value including the length from an ASN.1-File.
 *
 *	\details 	Read a boolean value from the opened ASN.1 file, including
 *				the length.	The type tag may have been read prior. \p value 
 *				is the variable to fill with the result.
 *
 *	\return 	If an error occures, the function returns -1, or 0 otherwise.
 *
 *	\see 		asnDecodeBoolean, asnReadBoolean, asnReadBooleanTL
 */

int asnReadBooleanL (byte *value) {
	long	 length;			/* length of the integer value				*/

	/* Get the length of the boolean. Should be 1 */

	if (asnReadLength (&length) == -1 && length != 1)
		return -1;	/* error */

	/* Read the boolean and decode it */

	return asnReadBoolean (value, length);
}


/**
 *	\brief Read only the boolean value w/o the tag and length
 *
 *	\details 	Read only the boolean value from the opened ASN.1 file, without
 *				the tag	and the length. These had to be read prior. \p value is
 *				a pointer to the buffer to encode the value in. \p length is
 *				the number of bytes to read	from the file.
 *
 *	\return 	If an error occures, the function returns -1, or 0 otherwise.
 *
 *	\see 		asnDecodeBoolean, asnReadBooleanL, asnReadBooleanTL
 */

int asnReadBoolean (byte *value, long length) {
	byte	 buffer[10];		/* buffer									*/

	if (length<1l || length>=10l)
		return -1;

	/* Read the boolean and decode it */

	if (asnRead (buffer, (uint)length) != length)
		return -1;	/* error */

	return asnDecodeBoolean (buffer, value);
}


