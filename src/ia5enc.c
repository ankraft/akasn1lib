/*
 * ia5enc.c
 *
 * written 1993 by Andreas Kraft
 */


# include	<string.h>
# include	<ctype.h>
# include	"akasn1.h"

/**
 *	\brief 		Encode an IA5-String with tag and length
 *
 *	\details 	Encode an IA5-String with tag and length into a buffer. \p value
 *				is a 0-terminated C-string. \p buffer is a buffer in which the
 *				encoding of	the tag and the length will be done. The length of
 *				the encoding in	\p buffer will be returned in \p length.
 *
 *	\return 	If an error occures, the function returns -1, -2 of the value
 *				is not a legal IA5-String or the length of the result in
 *				\p buffer otherwise.
 *
 *	\note		Restriction: The length of the string has to be less than MAXINT.
 *
 *	\see 		asnDecodeIA5, asnReadIA5, asnWriteIA5
 */

int asnEncodeIA5 (char *value, byte *buffer, int *length) {
	int		size, i;

	/* Encode tag */

	if ((*length=
			asnEncodeTag (buffer,asnUNIVERSAL,asnPRIMITIVE,asnIA5STRING))==-1) 
		return -1;		/* error */

	size= strlen (value);	/* get length of the string						*/


	/* Check string */

	for (i= 0; i<size; i++)
		if (!isascii (value[i]))
			return -2;


	/* Encode length */

	if ((*length += asnEncodeLength(&buffer[*length], (long)size)) == -1)
		return -1;		/* error */

	/* an ia5-string doesn't need further conversation */

	return size;			/* OK */
}

