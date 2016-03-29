/*
 * ia5rd.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Read an IA5-String from the opened ASN.1 file (with tag and length)
 *
 *	\details 	Read an IA5-String from the opened ASN.1 file, including the
 *				tag	and the length of the encoding. \p value is the variable to
 *				fill with the result, \p maxlen is the maximum number of
 *				characters to be read (mostly the size of \p value).
 *
 *	\return 	If an error occures, the function returns -1. -2 is returned
 *				if the value read is not of type IA5-String. Otherwise, the
 *				number of characters read is returned.
 *
 *	\note		Restriction: The length of the string has to be less than MAXINT.
 *
 *	\see 		asnDecodeIA5, asnEncodeIA5, asnWriteIA5, asnReadIA5L
 */

int asnReadIA5TL (char *value, int maxlen) {
	int		 taglen;			/* length of tag							*/
	byte	 buffer[256],		/* buffer									*/
			 cl,				/* tagclass									*/
			 pc,				/* primitive or constructed					*/
			 tag;				/* the tag itself							*/

	/* read and decode the tag. Is it an IA5-string ? */

	if ((taglen= asnReadTag (buffer)) == -1) 
		return -1;
	asnDecodeTag (&cl, &pc, &tag, buffer);

	if (cl != asnUNIVERSAL || tag != asnIA5STRING) {
		asnSkipFile (-taglen);		/* skip backwards  !					*/
		return -2;
	}

	/* Get the length of the IA5-String and the IA5-String */

	return asnReadIA5L (value, maxlen);
}


/**
 *	\brief 		Read an IA5-String including the length from an ASN.1-File
 *
 *	\details 	Read an IA5-String from the opened ASN.1 file, including the
 *				length.	The type tag may have been read prior. \p value is the 
 *				variable to fill with the result. \p maxlen is maximum number 
 *				of characters to be read.
 *
 *	\return 	If an error occures, the function returns -1. Otherwise, the
 *				number of characters read is returned.
 *
 *	\note		Restriction: The length of the string has to be less than MAXINT.
 *
 *	\see 		asnDecodeIA5, asnEncodeIA5, asnWriteIA5, asnReadIA5, asnReadIA5TL
 */

int asnReadIA5L (char *value, int maxlen) {
	long	 length;			/* length of the string						*/

	/* Get the length of the IA5-String */

	if (asnReadLength (&length) == -1)
		return -1;	/* error */

	/* Read the IA5-String and decode it */

	return asnReadIA5 (value, (int)length, maxlen);
}


/**
 *	\brief 		Read only the IA5-String w/o the tag and length
 *
 *	\details 	Read only the IA5-String from the opened ASN.1 file, without 
 *				the tag	and the length. These had to be read prior. \p value is
 *				a pointer to the buffer to encode the string in. \p length is 
 *				the number of bytes to read	from the file. \p maxlen is maximum
 *				number of characters to be read.
 *
 *	\return 	If an error occures, the function returns -1. Otherwise, the 
 *				number of characters read is returned.
 *
 *	\note		Restriction: The length of the string has to be less than MAXINT.
 *
 *	\see 		asnDecodeIA5, asnEncodeIA5, asnWriteIA5, asnReadIA5L, asnReadIA5TL
 */

int asnReadIA5 (char *value, int length, int maxlen) {
	int	len;

	len= (length<maxlen) ? length : maxlen;

	/* Read the IA5-String and decode it */
	if (asnRead ((byte *)value, len) != len)
		return -1;
	asnDecodeIA5 ((byte *)value, len);

	/* Skip the difference of the real length of the IA5-String and the 
	   characters read. */

	if (len<length)
		asnSkipFile ((int)(length-len));

	value[len]= '\0';		/* ?? Is this necessary ?? */

	return len;
}


