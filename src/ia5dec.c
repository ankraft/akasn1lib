/*
 * ia5dec.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

# ifdef __TURBOC__
# pragma argsused
# endif	/* __TURBOC__ */

/**
 *	\brief 		Decode an IA5-String
 *
 *	\details	Decode an IA5-String into an ASCII-String from the buffer 
 *				\p value. Actually, there is nothing to do because an IA5-string
 *				is already an ASCII-String. This function exists merely for
 *				symmetry with other data types. \p length is the length of the
 *				encoding in \p value.
 *
 *	\return 	This function returns -1 in case of an error, or the number of
 *				characters decoded.
 *
 *	\note		Restriction: The length of the string has to be less than MAXINT.
 *
 *	\see 		asnEncodeIA5, asnReadIA5, asnWriteIA5
 */

int asnDecodeIA5 (byte *value, int length) {
	return length;
}
