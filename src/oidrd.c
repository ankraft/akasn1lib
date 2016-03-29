/*
 * oidrd.c
 *
 * written 1993 by Andreas Kraft
 */

# include	<string.h>
# include	"akasn1.h"


/**
 *	\brief 		Read an object identifier from an ASN.1-File (with tag and length)
 *
 *	\details 	Read an object identifier from the opened ASN.1 file, including
 *				the tag	and the length of the encoding. \p id is the variable
 *				to fill with the result.
 *
 *	\return 	If an error occures, the function returns -1. -2 is returned if
 *				the	value read is not an object identifier. Otherwise, the
 *				length of the resulting object identifier string is returned.
 *
 *	\note 		Restriction: The maximum length has to be less or equal 127 
 *				octets and the maximum number of subidentifiers is 10. The
 *				number of oid's has to be equal or greater than 2. Supports 
 *				only subid's less or equal 16383.
 *
 *	\see 		asnDecodeOID, asnEncodeOID, asnReadOIDL, asnWriteOID
 */

int asnReadOidTL (char *id) {
	int		 taglen;			/* length of tag							*/
	byte	 buffer[256],		/* buffer									*/
			 cl,				/* tagclass									*/
			 pc,				/* primitive or constructed					*/
			 tag;				/* the tag itself							*/

	/* read and decode the tag. Is it an object identifier ? */

	if ((taglen= asnReadTag (buffer)) == -1) 
		return -1;
	asnDecodeTag (&cl, &pc, &tag, buffer);

	if (cl != asnUNIVERSAL || tag != asnOBJECTID) {
		asnSkipFile (-taglen);		/* skip backwards  !					*/
		return -2;
	}

	/* Get the length of the oid and the oid */

	return asnReadOidL (id);
}


/**
 *	\brief 		Read an object identifier from an ASN.1-File (with length)
 *
 *	\details 	Read an object identifier from the opened ASN.1 file, including
 *				the length of the encoding. \p id is the variable to fill with
 *				the result.
 *
 *	\return 	If an error occures, the function returns -1. Otherwise, the
 *				length of the resulting object identifier string is returned.
 *
 *	\note 		Restriction: The maximum length has to be less or equal 127
 *				octets and the maximum number of subidentifiers is 10. The 
 *				number of oid's has to be equal or greater than 2. Supports 
 *				only subid's less or equal 16383.
 *
 *	\see 		asnDecodeOID, asnEncodeOID, asnReadOID, asnWriteOID
 */

int asnReadOidL (char *id) {
	long	 length;			/* length of the oid						*/

	/* Get the length of the oid */

	if (asnReadLength (&length) == -1)
		return -1;	/* error */

	/* Read the oid and decode it */

	return asnReadOid (id, (int)length);
}


/**
 *	\brief 		Read an object identifier from an ASN.1-File (w/o tag and length)
 *
 *	\details 	Read an object identifier from the opened ASN.1 file. \p length
 *				is the number of bytes to be read. \p id is the variable to 
 *				fill with the result.
 *
 *	\return 	If an error occures, the function returns -1. Otherwise, the
 *				length of the resulting object identifier string is returned.
 *
 *	\note 		Restriction: The maximum length has to be less or equal 127
 *				octets and the maximum number of subidentifiers is 10. The
 *				number of oid's has to be equal or greater than 2. Supports
 *				only subid's less or equal 16383.
 *
 *	\see 		asnDecodeOID, asnEncodeOID, asnReadOIDTL, asnWriteOID
 */

int asnReadOid (char *id, int length) {
	byte	 buffer[256];		/* buffer									*/

	if (length<1 || length>=256)
		return -1;

	/* Read the oid and decode it */

	if (asnRead (buffer, length) != length)
		return -1;
	asnDecodeOid (buffer, length, id);

	return strlen (id);
}


