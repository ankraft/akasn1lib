/*
 *	taglenrd.c
 *
 *	written 1994 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Read a tag and a length from the opened ASN.1 file
 *
 *	\details 	Read a tag and a length from the opened ASN.1 file. \p buffer is
 *				a pointer to the buffer for the read tag. \p length is a
 *				pointer to a variable, which will get the decoded length.
 *
 *	\return 	If an error occures, the function returns -1, or 0 otherwise.
 *
 *	\see 		asnReadTag, asnReadLength
 */

long asnReadTagAndLength (byte *buffer, long *length) {
	if (asnReadTag (buffer) == -1) 
		return -1;
	return asnReadLength (length);
}
