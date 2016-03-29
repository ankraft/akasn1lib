/*
 * octdec.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

# ifdef __TURBOC__
# pragma argsused
# endif	/* __TURBOC__ */

/**
 *	\brief 		Decode an octet string from a buffer
 *
 *	\details 	Decode an octet string from a buffer. This function realy does
 *				nothing	because there is not much to do at the moment. \p value
 *				is the pointer to the buffer which contains the data to be
 *				decoded, \p length is the length of the data.
 *
 *	\return 	If an error occures, the function returns -1, or the number of
 *				bytes decoded otherwise.
 *
 *	\note 		The encoding has to be primitive. The constructed encoding is
 *				not supported yet. The maximum number of bytes has to be less
 *				than MAXINT.
 *
 *	\see 		asnEncodeOctet, asnWriteOctet, asnReadOctet
 */

int asnDecodeOctet (byte *value, int length) {
	return length;
}
