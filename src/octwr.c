/*
 * otcwr.c
 *
 * written 1993 by Andreas Kraft
 */

# ifndef	_MSC_VER
# include	<unistd.h>
# endif
# include	"akasn1.h"

/**
 *	\brief 		Write an octet string into an ASN.1 file
 * 
 *	\details 	Write an octet string into an opened ASN.1 file. \p value is
 *				the data value to be written. \p length is the number of bytes
 *				to be encoded. Macros for each individual octet or other string
 *				type actually map to this function which does the writing. 
 *				See \ref akasn1.h for further details on writing of octet and
 *				other strings.
 *
 *	\return 	If an error occures, the function returns -1 or the number of
 *				bytes written to the file otherwise.
 *
 *	\note 		Restriction: The length of the data has to be less than MAXINT.
 *
 *	\see 		asnReadOctet, asnWriteOctetFile
 */

int _asnWriteOctet (byte *value, int length, byte tag) {
	byte	 tl_buffer[10];			/* Buffer for the tag+len-encoding		*/
	int		 tl_length,				/* Length of the tag+len-encoding		*/
			 olen;					/* Length of the encoded octetstring	*/

	if (tag!=asnOCTETSTRING && tag!=asnNUMERICSTRING && tag!=asnPRINTABLESTRING && 
		tag!=asnTELETEXSTRING && tag!=asnVIDEOTEXSTRING && tag!=asnIA5STRING &&
		tag!=asnGRAPHICSTRING && tag!=asnVISIBLESTRING && tag!=asnGENERALSTRING)
			return -1;

	if ((olen= asnEncodeOctet (value, length, tl_buffer, &tl_length, tag)) == -1)
		return -1;	/* error */
	
	/* write tag + length */

	if (asnWrite (tl_buffer, (uint)tl_length) == -1)
		return -1;	/* error */
	
	/* write octetstring */

	if (asnWrite (value, (uint)olen) == -1)
		return -1;	/* error */

	return tl_length+length;	/* OK */
}


/**
 *	\brief 		Read data from a file and write it as an octet string into an ASN.1 file
 *
 *	\details 	Read data from an open file \p infd and write it as an octet
 *				string to an opened ASN.1 file. \p length is the number of
 *				bytes to encode from the original file. Macros for each 
 *				individual octet or other string type actually map to this
 *				function, which does the writing. See \ref akasn1.h for further
 *				details	on writing of octet and other strings.
 *
 *	\return 	If an error occures, the function returns -1 or the number of 
 *				bytes written to the file otherwise.
 *
 *	\note 		Restriction: The length of the data has to be less than MAXINT.
 *
 *	\see 		asnReadOctet, asnWriteOctetFile
 */


int _asnWriteOctetFile (int infd, long length, byte tag) {
	byte	 tl_buffer[10];			/* Buffer for the tag+len-encoding		*/
	int		 tl_length;				/* Length of the tag+len-encoding		*/
	byte	 buffer[1024];
	int		 l;

	if (tag!=asnOCTETSTRING && tag!=asnNUMERICSTRING && tag!=asnPRINTABLESTRING && 
		tag!=asnTELETEXSTRING && tag!=asnVIDEOTEXSTRING && tag!=asnIA5STRING &&
		tag!=asnGRAPHICSTRING && tag!=asnVISIBLESTRING && tag!=asnGENERALSTRING)
			return -1;

	/* Encode tag */

	if ((tl_length= asnEncodeTag (tl_buffer,asnUNIVERSAL, asnPRIMITIVE, tag))==-1) 
		return -1;		/* error */

	/* Encode length */

	if ((tl_length += asnEncodeLength(&tl_buffer[tl_length],length))==-1)
		return -1;		/* error */

	/* write tag + length */

	if (asnWrite (tl_buffer, (uint)tl_length) == -1)
		return -1;	/* error */

	/* write buffer */

	while ((l=read (infd, buffer, sizeof(buffer))) != 0)
		if (asnWrite (buffer, (uint)l) == -1) 
			return -1;

	return 0;
}
