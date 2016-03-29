/*
 * lenwr.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Write an encoded ASN.1 length field to the open ASN.1 file
 *
 *	\details 	Encode and write an ASN.1 length field to the opened ASN.1 file.
 *				\p length is the length to be encoded.
 *
 *	\return 	If an error occures, the function returns -1, or the length of
 *				the	encoding otherwise.
 *
 *	\note 		Restriction: supports only length between 0 and MAXLONG.
 *
 *	\see 		asnOpenReadFile, asnOpenWriteFile, asnEncodeLength, asnDecodeLength, asnReadLength
 */

int asnWriteLength (long length) {
	int		 size= 0;
	byte	 buffer[10];

	if ((size= asnEncodeLength (buffer, length)) == -1)
		return -1;
	return asnWrite (buffer, (uint)size);
}

