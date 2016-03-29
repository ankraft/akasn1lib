/*
 *	iseoc.c
 *
 *	written by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Check for End-Of-Contents in the opened ASN.1 file
 *
 *	\details 	This function provides a way to check whether the next token
 *				in the opened ASN.1 file is an End-Of-Contents token EOC.
 *
 *	\return 	If an EOC token is the next in the file, 1 is returned,
 *				0 otherwise.
 *
 *	\see 		asnFtell, asnFseek, asnOpenReadFile, asnOpenWriteFile
 */

int asnIsEOC (void) {
	byte	buffer[4];
	
	long	oldpos= asnFtell ();

	if (asnRead (buffer, 3) == 3 &&
		buffer[0]=='\0' && buffer[1]=='\0' && buffer[2]=='\0')
			return 1;

	asnFseek (oldpos);
	return 0;
}
