/*
 * enumenc.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

# define	IGNORE_VALUE	0
# define	NULL_VALUE		1
# define	FF_VALUE		2


/**
 *	\brief 		Encode an enumeration value with tag and length.
 *
 *	\details	Encode an enumeration (C-type long) with tag and length into 
 *				a buffer. This function does the same as the function 
 *				\ref asnEncodeInteger except the encoding value of the tag.
 *				\p buffer is the buffer to fill with the resulting encoding,
 *				\p value is the enumeration value to encode.
 *
 *	\return 	If an error occures, the function returns -1, or the length
 *				of the result in \p buffer otherwise.
 *
 *	\see 		asnDecodeEnum, asnReadEnum, asnWriteEnum
 *
 *	\note		Restriction: The Integer has to be less than 2^31.
 */

int asnEncodeEnum (byte *buffer, long value) {

	byte	v, vb[4];
	int		l, i, al, size, pre;

	/* Encode tag */

	if ((l=asnEncodeTag(buffer,asnUNIVERSAL,asnPRIMITIVE,asnENUMERATED))==-1)
		return -1;		/* error */


	/* Encode value without leading 0's and 0xff,  get length */

	size= 0;
	v= value >> 24;
	if (v && (v & 0xff) != 0xff) vb[size++]= v;
	v= value >> 16;
	if (v && (v & 0xff) != 0xff) vb[size++]= v;
	v= value >> 8;
	if (v && (v & 0xff) != 0xff) vb[size++]= v;
	vb[size++]= value & 0xff;

	/* If the first byte of the encoded value has the 8'st bit set and 
	   the value is a positiv number than we must insert a 0x00 before 
	   the encoding. If the original value is a negativ number and the
	   first byte has *not* set the highest bit then a 0xFF-byte must be
	   inserted before the encoding. */

	pre= IGNORE_VALUE;
	if (value>0 && (vb[0] & 0x80)) {
		pre= NULL_VALUE;
		size++;
	}
	if (value<0 && !(vb[0] & 0x80)) {
		pre= FF_VALUE;
		size++;
	}

	/* Encode length */

	al= l;
	if ((l= asnEncodeLength (&buffer[l], (long)size)) == -1)
		return -1;		/* error */
	al+= l;

	/* Encode value into buffer */

	switch (pre) {
		case NULL_VALUE:	buffer[al++]= 0x00;
							size--;
							break;
		case FF_VALUE:		buffer[al++]= 0xFF;
							size--;
							break;
		case IGNORE_VALUE:
		default:			break;
	}
	for (i= 0; i<size; i++)
		buffer[al++]= vb[i];

	return al;			/* OK */
}


/**
 *	\brief 		Encode an enumeration value as an integer with tag and length.
 *
 *	\details	Encode an enumeration (C-type long) with tag and length into 
 *				a buffer. This function does the same as the function 
 *				\ref asnEncodeIntegerValue except the encoding value of the tag.
 *				\p buffer is the buffer to fill with the resulting encoding,
 *				\p value is the enumeration value to encode.
 *
 *	\return 	If an error occures, the function returns -1, or the length
 *				of the result in \p buffer otherwise.
 *
 *	\see 		asnDecodeEnum, asnReadEnum, asnWriteEnum
 */


int asnEncodeEnumValue (byte * buffer, long value) {
	return asnEncodeIntegerValue(buffer, value);
}


