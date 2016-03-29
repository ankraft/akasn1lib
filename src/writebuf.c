/*
 * writebuf.c
 *
 * written 1993 by Andreas Kraft
 */

# ifdef		__TURBOC__
# include	<io.h>
# elif defined(solaris) || defined(linux)
# include	<unistd.h>
# else
# include	<unistd.h>
# endif		/* __TURBOC__ */

# include	"akasn1.h"

/**
 *	\brief 		Write a buffer to the opened ASN.1 file
 *
 *	\details 	Write a \p length bytes of the buffer \p buffer to the opened
 *				ASN.1 file.
 *
 *	\return 	If an error occures, the function returns -1, or the number of
 *				bytes written otherwise.
 *
 *	\see 		asnOpenReadFile, asnOpenWriteFile
 */

int asnWrite (byte *buffer, uint len) {
	if (asnfd == -1)
		return -1;		/* error */
	return write (asnfd, (void *)buffer, len);
}
