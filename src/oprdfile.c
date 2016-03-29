/*
 * oprdfile.c
 *
 * written 1993 by Andreas Kraft
 */

# ifdef		__TURBOC__
# include	<io.h>
# endif		/* __TURBOC__ */

# include	<sys/stat.h>
# include	<fcntl.h>
# include	"akasn1.h"

/**
 *	\brief 		Open an ASN.1 file for reading
 *
 *	\details 	Open an ASN.1 file for reading. \p fn is the file name of the file.
 *
 *	\return 	If an error occures, the function returns -1, or the internal
 *				file descriptor \ref asnfd otherwise.
 *
 *	\see 		asnOpenWriteFile, asnCloseFile, asnRead
 */

int asnOpenReadFile (char *fn) {
	int mode;

# if defined(__MSDOS__) | defined(__WATCOMC__) | defined(_MSC_VER)
	mode= O_RDWR|O_BINARY;
# else
	mode= O_RDWR;
# endif

	if (asnfd != -1)
		asnCloseFile ();
	return (asnfd= open (fn, mode, O_RDWR));
}


