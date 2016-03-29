/*
 * asnfseek.c
 *
 * written 1993 by Andreas Kraft
 */


# if defined(__TURBOC__) | defined(__WATCOMC__) | defined(_MSC_VER)
# include	<io.h>
# else
# include	<sys/file.h>
# include	<unistd.h>
# endif		/* __TURBOC__ */

# include	"akasn1.h"


/**
 *	\brief Seek to a position \p pos in the open ASN.1-file.
 *
 *	\return	If an error occures, the function returns -1, or 0 otherwise.
 *
 *	\see asnFtell, asnOpenReadFile, asnOpenWriteFile
 */

int asnFseek (long pos) {
	if (asnfd == -1)
		return -1;		/* error */

# if defined(__TURBOC__) | defined(__WATCOMC__) | defined(_MSC_VER)
	return (lseek (asnfd, pos, SEEK_SET) == 1l) ? -1 : 0;
# else
	return (lseek (asnfd, pos, L_SET) == -1l) ? -1 : 0;
# endif
}


