/*
 * intdec.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Decode an integer value
 *
 *	\details	Decode an integer value (C-type long) from a buffer \p buffer.
 *				\p length is the length of the encoding in \p buffer, \p value
 *				is a pointer to the result variable.
 *
 *	\return 	This function always returns `0`.
 *
 *	\note 		Restriction: The Integer has to be less than 2^31.
 *
 *	\see 		asnEncodeInteger, asnReadInteger, asnWriteInteger, 
 */

int asnDecodeInteger (byte *buffer, int length, long *value) {
	int		 l= 0;			/* buffer-pointer								*/

	/* Analyse the first byte which has a special meaning under some special
	   circumstances, see comment in asnEncodeInteger() */
	
	*value= buffer[l++];
	if (*value & 0x80) {
		switch (sizeof(long)) {			/* Sign extension					*/
			case 4: *value |= 0xffffff00;
					break;
			case 8: *value |= 0xffffffffffffff00;
		}
	}

	/* Decode the value */

	for ( /**/ ; l<length; l++)
		*value = ((*value << 8) | buffer[l]);
	
	return 0;
}
