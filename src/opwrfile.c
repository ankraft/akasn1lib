/*
 * opwrfile.c
 *
 * written 1993 by Andreas Kraft
 */

# ifdef		__TURBOC__
# include	<io.h>
# endif		/* __TURBOC__ */

# include	<fcntl.h>
# include	<sys/stat.h>
# include	"akasn1.h"

/**
 *	\brief 		Open an ASN.1 file for writing
 *
 *	\details 	Open an ASN.1 file for writing. \p fn is the file name of the file.
 *
 *	\return 	If an error occures, the function returns -1, or the internal
 *				file descriptor \ref asnfd otherwise.
 *
 *	\see 		asnOpenWriteFile, asnCloseFile, asnWrite
 */

int asnOpenWriteFile (char *fn) {
	int mode;

# if defined(__MSDOS__) | defined(__WATCOMC__) | defined(_MSC_VER)
	mode= O_CREAT|O_TRUNC|O_RDWR|O_BINARY;
# else
	mode= O_CREAT|O_TRUNC|O_RDWR;
# endif

	if (asnfd != -1)
		asnCloseFile ();
	return (asnfd= open (fn, mode, O_RDWR));
}


