/*
 * booldec.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief Decode a boolean value from a buffer
 *
 *	\details This function decodes a boolean value from a buffer. \p buffer contains the encoded boolean 
 *	value, \p value is the variable to fill with the result. It is assumed that \p buffer contains only the value,
 *	not the tag and length.
 *
 *	\return	Allways return 0.
 *
 *	\see asnEncodeBoolean, asnReadBoolean, asnReadBooleanTL, asnReadBooleanL, asnWriteBoolean
 */

int asnDecodeBoolean (byte *buffer, byte *value) {
	*value= (buffer[0] == 0x00) ? asnFALSE : asnTRUE;
	return 0;
}
