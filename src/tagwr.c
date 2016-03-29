/*
 * tagwr.c
 *
 * written 1993 by Andreas Kraft
 */

# include	"akasn1.h"

/**
 *	\brief 		Encode and write a tag to an ASN.1 file
 *
 *	\details 	Encode and write a tag to the opened ASN.1 file. \p clasS is
 *				the class of the tag (\ref asnUNIVERSAL , \ref asnAPPLICATION ,
 *				\ref asnCONTEXT , \ref asnPRIVATE ). \p pc is a flag to 
 *				indicate wether the data following the tag is constructed or
 *				primitive (\ref asnPRIMITIVE , \ref asnCONSTRUCTED ). \p tag
 *				is the number of the tag. 
 *
 *	\return 	If an error occures, the function returns -1, or the size of
 *				the	encoded tag otherwise.
 *
 *	\see 		asnWrite, asnEncodeTag
 */ 

int asnWriteTag (byte clasS, byte pc, byte tag) {
	int		 size= 0;
	byte	 buffer[10];

	if ((size= asnEncodeTag (buffer, clasS, pc, tag)) == -1)
		return -1;
	return asnWrite (buffer, (uint)size);
}


