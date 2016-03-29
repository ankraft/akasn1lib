/*
 * enumrd.c
 *
 * written 1993 by Andreas Kraft
 */


# include	<string.h>
# include	"akasn1.h"


/**
 *	\brief		Read an enumeration value from an ASN.1-File (with tag and length)
 *
 *	\details 	Read an enumeration value from the opened ASN.1 file, including
 *				the tag	and the length of the encoding. \p value is the 
 *				variable to fill with the result.
 *
 *	\return 	If an error occures, the function returns -1. -2 is returned 
 *				if the value read is not of type enumeration. 0 is return if
 *				no error occured.
 *
 *	\see 		asnDecodeEnum, asnEncodeEnum, asnWriteEnum, asnReadEnumL
 */

int asnReadEnumTL (long *value) {
	int		 taglen;			/* length of tag							*/
	byte	 buffer[256],		/* buffer									*/
			 cl,				/* tagclass									*/
			 pc,				/* primitive or constructed					*/
			 tag;				/* the tag itself							*/

	/* read and decode the tag. Is it an enum-value value ? */

	if ((taglen= asnReadTag (buffer)) == -1) 
		return -1;
	asnDecodeTag (&cl, &pc, &tag, buffer);

	if (cl != asnUNIVERSAL || tag != asnENUMERATED) {
		asnSkipFile (-taglen);		/* skip backwards  !					*/
		return -2;
	}

	/* Get the enum-value */

	return asnReadEnumL (value);
}


/**
 *	\brief 		Read an enumeration value including the length from an ASN.1-File
 *
 *	\details 	Read an enumeration value from the opened ASN.1 file, including
 *				the length.	The type tag may have been read prior. \p value is
 *				the variable to fill with the result.
 *
 *	\return 	If an error occures, the function returns -1, or 0 otherwise.
 *
 *	\see 		asnDecodeEnum, asnEncodeEnum, asnWriteEnum, asnReadEnum, sasnReadEnumTL
 */

int asnReadEnumL (long *value) {
	long	 length;			/* length of the enum-value					*/

	/* Get the length of the enum-value */

	if (asnReadLength (&length) == -1)
		return -1;	/* error */

	/* Read the enum and decode it */

	return asnReadEnum (value, (int)length);
}



/**
 *	\brief 		Read only the enumeration value w/o the tag and length
 *
 *	\details 	Read only the enumeration value from the opened ASN.1 file, 
 *				without the tag and the length. These had to be read prior.
 *				\p value is a pointer to the buffer to encode the value in.
 *				\p length is the number of bytes to read from the file.
 *
 *	\return 	If an error occures, the function returns -1, or the length
 *				of the encoded enumeration value otherwise.
 *
 *	\see 		asnDecodeEnum, asnEncodeEnum, asnWriteEnum, asnReadEnumL, asnReadEnumTL
 */

int asnReadEnum (long *value, int length) {
	byte	 buffer[256];		/* buffer									*/

	if (length<1 || length>=256)
		return -1;

	/* Read the enum-value and decode it */

	if (asnRead (buffer, (uint)length) != length)
		return -1;	/* error */

	asnDecodeEnum (buffer, length, value);

	return length;		/* OK */
}


