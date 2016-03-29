/*
 * intrd.c
 *
 * written 1993 by Andreas Kraft
 */

# include	<string.h>
# include	"akasn1.h"

/**
 *	\brief 		Read an integer value from an ASN.1-File (with tag and length)
 *
 *	\details 	Read an integer value from the opened ASN.1 file, including
 *				the tag and the length of the encoding. \p value is the 
 *				variable to fill with the result.
 *
 *	\return 	If an error occures, the function returns -1. -2 is returned 
 *				if the value read is not of type integer. 0 is return if no 
 *				error occured.
 *
 *	\note 		Restriction: The Integer has to be less than 2^31.
 *
 *	\see 		asnDecodeInteger, asnEncodeInteger, asnWriteInteger, asnReadIntegerL
 */

int asnReadIntegerTL (long *value) {
	int		 taglen;			/* length of tag							*/
	byte	 buffer[256],		/* buffer									*/
			 cl,				/* tagclass									*/
			 pc,				/* primitive or constructed					*/
			 tag;				/* the tag itself							*/

	/* read and decode the tag. Is it an integer value ? */

	if ((taglen= asnReadTag (buffer)) == -1) 
		return -1;
	asnDecodeTag (&cl, &pc, &tag, buffer);

	if (cl != asnUNIVERSAL || tag != asnINTEGER) {
		asnSkipFile (-taglen);		/* skip backwards  !					*/
		return -2;
	}

	/* Get the integer */

	return asnReadIntegerL (value);
}


/**
 *	\brief 		Read an integer value including the length from an ASN.1-File
 *
 *	\details 	Read an integer value from the opened ASN.1 file, including the
 *				length.	The type tag must have been read prior. \p value is the
 *				variable to fill with the result.
 *
 *	\return 	If an error occures, the function returns -1, or 0 otherwise.
 *
 *	\note 		Restriction: The Integer has to be less than 2^31.
 *
 *	\see 		asnDecodeInteger, asnEncodeInteger, asnWriteInteger, asnReadInteger, asnReadIntegerTL
 */

int asnReadIntegerL (long *value) {
	long	 length;			/* length of the integer value				*/

	/* Get the length of the integer */

	if (asnReadLength (&length) == -1)
		return -1;	/* error */

	/* Read the integer and decode it */

	return asnReadInteger (value, (int)length);
}


/**
 *	\brief 		Read only a integer value w/o the tag and length
 *
 *	\details 	Read only an ineteger value from the opened ASN.1 file, without
 *				the tag and the length. These had to be read prior. \p value is
 *				a pointer to the buffer to encode the value in. \p length is
 *				the number of bytes to read	from the file.
 *
 *	\return 	If an error occures, the function returns -1, or the length of
 *				the	encoded integer value otherwise.
 *
 *	\note 		Restriction: The Integer has to be less than 2^31.
 *
 *	\see 		asnDecodeInteger, asnEncodeInteger, asnWriteInteger, asnReadIntegerL, asnReadIntegerTL
 */

int asnReadInteger (long *value, int length) {
	byte	 buffer[256];		/* buffer									*/

	if (length<1 || length>=256)
		return -1;

	/* Read the integer and decode it */

	if (asnRead (buffer, length) != length)
		return -1;	/* error */

	asnDecodeInteger (buffer, length, value);

	return length;		/* OK */
}


