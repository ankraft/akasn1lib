/*
 * nullenc.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Encode a Null value
 *
 *	\details 	Encode a Null value. That is just the tag and the length field,
 *				no value. \p value is the buffer to be filled.
 *
 *	\return 	If an error occures, the function returns -1, or the length of
 *				the	encoding in \p value otherwise.
 *
 *	\see 		asnReadNullL, asnReadNullTL, asnWriteNull
 */

int asnEncodeNull (byte *value) {
	int		l;

	/* Encode the tag */

	if ((l= asnEncodeTag (value, asnUNIVERSAL,asnPRIMITIVE, asnNULLVALUE))==-1) 
		return -1;		/* error */

	/* Encode the length for the Null-"value" */

	value[l++]= 0;

	/* No content ! */

	return l;
}
