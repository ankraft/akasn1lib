/*
 * clfile.c
 *
 * written 1993 by Andreas Kraft
 */


# if defined(__TURBOC__) | defined(_MSC_VER)
# include	"io.h"
# else
# include	<unistd.h>
# endif
# include	"akasn1.h"

/**
 *	\brief 		Close the opened ASN.1 file
 *
 *	\details 	Close the ASN.1 file which prior must have been opened by 
 *				\ref asnOpenReadFile or \ref asnOpenWriteFile .
 *
 *	\see 		asnOpenReadFile, asnOpenWriteFile
 */

void asnCloseFile (void) {
	if (asnfd != -1) {
		close (asnfd);
		asnfd= -1;
	} 
}

