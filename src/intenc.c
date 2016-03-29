/*
 * intenc.c
 *
 * written 1993 by Andreas Kraft
 */


# include	"akasn1.h"

static int	_asnEncodeIntegerValue(byte *, long, int);

# define	IGNORE_VALUE	0
# define	NULL_VALUE		1
# define	FF_VALUE		2

/**
 *	\brief 		Encode an integer value with tag and length
 *
 *	\details	Encode an Integer (C-type long) with tag and length into a
 *				buffer. \p buffer is the buffer to fill with the resulting
 *				encoding, \p value is the integer value to encode.
 *
 *	\return 	If an error occures, the function returns -1, or the length
 *				of the result in \p buffer otherwise.
 *
 *	\note		Restriction: The Integer has to be less than 2^31.
 *
 *	\see 		asnDecodeInteger, asnReadInteger, asnWriteInteger
 */

int asnEncodeInteger (byte *buffer, long value) {

	int	l;

	/* Encode tag */

	if ((l= asnEncodeTag (buffer,asnUNIVERSAL,asnPRIMITIVE,asnINTEGER)) == -1) 
		return -1;		/* error */

	return _asnEncodeIntegerValue(buffer, value, l);
}


/**
 *	\brief 		Encode an integer value with tag (no length!)
 *
 *	\details	Encode an Integer (C-type long) with tag but without the length into a
 *				buffer. \p buffer is the buffer to fill with the resulting
 *				encoding, \p value is the integer value to encode.
 *
 *	\return 	If an error occures, the function returns -1, or the length
 *				of the result in \p buffer otherwise.
 *
 *	\note		Restriction: The Integer has to be less than 2^31.
 *
 *	\see 		asnDecodeInteger, asnReadInteger, asnWriteInteger
 */

int asnEncodeIntegerValue (byte *buffer, long value) {
	return _asnEncodeIntegerValue(buffer, value, 0);
}


static int
_asnEncodeIntegerValue(byte * buffer, long value, int enclen) {

	byte	v, vb[4];
	int		l, i, al, size, pre;
	int		offset = 0;

	/* Encode tag */

	if ((l= asnEncodeTag (buffer,asnUNIVERSAL,asnPRIMITIVE,asnINTEGER)) == -1) 
		return -1;		/* error */


	/* Encode value without leading 0's and 0xff,  get length */

	size= 0;
	v= value >> 24;
	if (size || (v & 0xff)) vb[size++]= v & 0xff;
	v= value >> 16;
	if (size || (v & 0xff)) vb[size++]= v & 0xff;
	v= value >> 8;
	if (size || (v & 0xff)) vb[size++]= v & 0xff;
	vb[size++]= value & 0xff;

	/*fprintf(stderr, "(1) size = %d\n", size);*/
	if (value < 0) {
		for (offset = 0; offset < size; offset++)
			if (vb[offset] != 0xff)
				break;
	}

	if (offset == size) 
		offset--;

	/* If the first byte of the encoded value has the 8'st bit set and 
	   the value is a positiv number than we must insert a 0x00 before 
	   the encoding. If the original value is a negativ number and the
	   first byte has *not* set the highest bit then a 0xFF-byte must be
	   inserted before the encoding. */

	/* fprintf(stderr, "(2) vb[offset]        = %d\n", vb[offset]);
	fprintf(stderr, "(3) vb[offset] & 0x80 = %d\n", vb[offset] & 0x80); */

	pre= IGNORE_VALUE;
	if (value>0 && (vb[offset] & 0x80)) {
		pre= NULL_VALUE;
		size++;
	}
	if (value<0 && !(vb[offset] & 0x80)) {
		pre= FF_VALUE;
		size++;
	}

	/* fprintf(stderr, "size = %d, offset = %d, enclen = %d, ", size, offset,enclen); */
	/* Encode length */

	al = 0;
	if (enclen > 0) {
		al= enclen;
		if ((l= asnEncodeLength (&buffer[l], (long)size-offset)) == -1)
			return -1;		/* error */
		al+= l;

	} 

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
	for (i= offset; i<size; i++)
		buffer[al++]= vb[i];

	/* fprintf(stderr, "value = %ld, al=%d\n", value, al); */


	return al;
}
