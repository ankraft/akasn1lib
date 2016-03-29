/*
 * asnftell.c
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
 *	\brief	Get position in the opened ASN.1-File.
 *
 *	\details This function returns the current position of the internal file descriptor in the opened ASN.1 file.
 *
 *	\return	If an error occures, the function returns -1, or a value equal or greater than 0 (the position).
 *
 *	\see asnFseek, asnOpenReadFile, asnOpenWriteFile
 */

 long asnFtell (void) {
	if (asnfd == -1)
		return -1;		/* error */
	/* return tell (asnfd); */
	return lseek(asnfd, 0, SEEK_CUR); // in case tell is not available

}



