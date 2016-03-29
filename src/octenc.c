/*
 * octenc.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

# ifdef __TURBOC__
# pragma argsused
# endif	/* __TURBOC__ */

/**
 *	\brief 		Encode an octet string with tag and length into a buffer
 *
 *	\details 	Encode an octet string with tag and length into a buffer.
 *				\p value is a pointer to the buffer to encode. \p length is the
 *				number of bytes in the \p value buffer to encode. \p tag_len
 *				is the buffer for the tag and the length of the encoding. 
 *				\p tl_length is a pointer to a variable for the resulting 
 *				length of \p tag_len.
 *
 *	\return 	If an error occures, the function returns -1, or the length of
 *				the	encoding (only the octet string, w/o \p tl_length) otherwise.
 *
 *	\note 		The encoding has to be ASN.1 primitive. The constructed encoding
 *				is not supported yet. The maximum number of bytes has to be
 *				less than MAXINT.
 *
 *	\see 		asnFtell, asnOpenReadFile, asnOpenQriteFile
 */

int asnEncodeOctet (byte *value, int length, byte *tag_len, int *tl_length, 
					byte tag) {

	/* Encode tag */

	if ((*tl_length=
		asnEncodeTag (tag_len, asnUNIVERSAL, asnPRIMITIVE, tag))==-1) 
		return -1;		/* error */

	/* Encode length */

	if ((*tl_length += asnEncodeLength(&tag_len[*tl_length],(long)length))==-1)
		return -1;		/* error */

	/* an octetstring doesn't need further conversation */

	return length;			/* OK */
}

