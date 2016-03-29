/*
 * readbuf.c
 *
 * written 1993 by Andreas Kraft
 */

# if defined(__TURBOC__) | defined(_MSC_VER)
# include	<io.h>
# endif		/* __TURBOC __ */

# ifndef	_MSC_VER
# include	<unistd.h>
# endif
# include	"akasn1.h"

/**
 *	\brief 		Read some data from the ASN.1 file
 *
 *	\details 	Read some data from the opened ASN.1 file. \p buffer is the
 *				buffer to be filled with the data, \p length is the number of
 *				bytes to be read.
 * 
 *	\return 	If an error occures, the function returns -1, 0 at EOF, or the
 *				number of bytes read otherwise.
 *
 *	\see 		asnOpenReadFile, asnWrite
 */

int asnRead (byte *buffer, uint length) {
	if (asnfd == -1)
		return -1;		/* error */
	return read (asnfd, (void *)buffer, length);
}

