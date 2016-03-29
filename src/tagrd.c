/*
 * tagrd.c
 *
 * written 1993 by Andreas Kraft
 */


# include	"akasn1.h"

/**
 *	\brief 		Read a tag from the opened ASN.1 file
 *
 *	\details 	Read a tag from the opened ASN.1 file. \p buffer is a pointer
 *				to the buffer which will get the resulting tag encoding.
 *
 *	\return 	If an error occures, the function returns -1, or the size of
 *				the	tag in \p buffer otherwise.
 *
 *	\see 		asnOpenReadFile, asnRead, asnDecodeTag
 */

int asnReadTag (byte *buffer) {
	int	size= 0;

	if (asnRead (&buffer[size++], 1) != 1)
		return -1;
	if ((buffer[0] & 0x1F) == 0x1F)	{	/* Tag > 31							*/
		if (asnRead (&buffer[size++], 1) != 1)
			return -1;
		while (buffer[size-1] > 0x7F)
			if (asnRead (&buffer[size++], 1) != 1)
				return -1;
	}

	return size;
}
