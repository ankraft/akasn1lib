/*
 * oidwr.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief		Write an object identifier into an ASN.1 file
 *
 *	\details 	Write an object identifier into an opened ASN.1 file. \p id is
 *				the enum value to be encoded. The format of the input must be
 *				"a b c ...".
 *
 *	\return 	If an error occures, the function returns -1, or the number of
 *				bytes written to the file otherwise.
 *
 *	\note 		Restriction: Supports only subid's less or equal 16383.
 *
 *	\see 		asnReadOID, asnEncodeOID
 */

int asnWriteOid (char *id) {
	byte	 buffer[256];		/* Buffer to fill							*/
	int		 len;				/* Length of OID						 	*/

	len= asnEncodeOid (buffer, id);
	return asnWrite (buffer, (uint)len);
}

