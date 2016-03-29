/*
 * skipfile.c
 *
 * written 1993 by Andreas Kraft
 */

# if defined(__TURBOC__) | defined(__WATCOMC__) | defined(_MSC_VER)
# include	<io.h>
# elif		solaris
# include	<sys/types.h>
# include	<unistd.h>
# elif		linux
# include	<sys/types.h>
# include	<unistd.h>
# elif		__svr4__
# include	<sys/types.h>
# include	<unistd.h>
# else
# include	<sys/file.h>
# include	<unistd.h>
# endif		/* __TURBOC__ */

# include	"akasn1.h"

/**
 *	\brief 		Skip a portion of the opened ASN.1 file
 *
 *	\details 	This function skips `length` bytes of the data in the opened
 *				ASN.1 file.
 *
 *	\return 	If an error occures, the function returns -1, or 0 otherwise.
 *
 *	\see 		asnFtell, asnFSeek, asnOpenReadFile, asnOpenWriteFile
 */

int asnSkipFile (long length) {
	if (asnfd == -1)
		return -1;		/* error */
	if (!length)
		return 0;

# if defined(__TURBOC__) | defined(__WATCOMC__) | defined(_MSC_VER)
	return (lseek (asnfd, length, SEEK_CUR) == 1l) ? -1 : 0;
# elif solaris
	return (lseek (asnfd, length, SEEK_CUR) == 1l) ? -1 : 0;
# elif linux
	return (lseek (asnfd, length, SEEK_CUR) == 1l) ? -1 : 0;
# elif __svr4__
	return (lseek (asnfd, length, SEEK_CUR) == 1l) ? -1 : 0;
# else
	return (lseek (asnfd, length, L_INCR) == -1l) ? -1 : 0;
# endif
}


