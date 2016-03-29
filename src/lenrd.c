/*
 * lenrd.c
 *
 * written 1993 by Andreas Kraft
 *
 */

# include	"akasn1.h"

/**
 *	\brief 		Read a "length" field from the opened ASN.1 file
 *
 *	\details 	This function reads the ASN.1 length field from an opened file.
 *				\p length is a pointer to a long variable which will get the
 *				result.
 *
 *	\return 	If an error occures, the function returns -1, or the length of
 *				the encoding read from the file otherwise.
 *
 *	\note 		Restriction: supports only length between 0 and MAXLONG.
 *
 *	\see 		asnOpenReadFile, asnOpenWriteFile, asnEncodeLength, asnDecodeLength, asnWriteLength
 */

int asnReadLength (long *length) {
	byte	 buffer[10];
	int		 size= 0, i;
	byte	 b;

	*length= 0;
	if (asnRead (buffer, 1) != 1)
		return -1;
	if (buffer[0] == 0x80) {
		*length= asnINDEFINITE;
		return 1;
	}
	if (buffer[0] <= 0x7F) {
		b= buffer[0];
		*length= (long)b;
		return 1;
	}
	
	size= buffer[0] & 0x7F;

	if (size<0 || size >= 10)
		return 0;

	for (i= 1; i <= size; i++) {
		if (asnRead (&buffer[i], 1) != 1)
			return -1;
		b= buffer[i];
		*length+= (long)b << ((size-i)*8);
	}

	return size+1;
}

