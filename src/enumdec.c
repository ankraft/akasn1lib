/*
 * enumdec.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Decode an enumeration value
 *
 *	\details  	Decode an enumeration value (C-type long) from a buffer 
 *				\p buffer. \p length is the length of the encoding in 
 *				\p buffer, \p value is a	pointer to the result variable.
 *
 *	\return 	This function always returns `0`.
 *
 *	\see 		asnEncodeEnum, asnReadEnum, asnWriteEnum
 */

int asnDecodeEnum (byte *buffer, int length, long *value) {
	
	/* Call asnDecodeInteger() because an enumaration value is encoded
	   as an integer value */

	return asnDecodeInteger (buffer, length, value);
}
