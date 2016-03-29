/*
 * octrd.c
 *
 * written 1993 by Andreas Kraft
 */

# include	<assert.h>

# ifndef	_MSC_VER
# include	<unistd.h>
# endif
# include	"akasn1.h"


/**
 *	\brief 		Read an octet string from an ASN.1-File (with tag and length)
 *
 *	\details 	Read an octet string from the opened ASN.1 file, including the
 *				tag	and the length of the encoding. \p value is the variable to
 *				fill with the result. \p maxlen is the maximum number of bytes
 *				to be read.
 *
 *	\return 	If an error occures, the function returns -1. -2 is returned
 *				if the value read is not an octet string. Otherwise, the number
 *				of bytes read is returned.
 *
 *	\note 		The maximum number of bytes has to be less than MAXINT.
 *
 *	\see 		asnDecodeOctet, asnEncodeOctet, asnWriteOctet, asnReadOctetL, asnReadOctetFileTL
 */

int asnReadOctetTL (byte *value, int maxlen) {
	int		 taglen;			/* length of tag							*/
	byte	 buffer[256],		/* buffer									*/
			 cl,				/* tagclass									*/
			 pc,				/* primitive or constructed					*/
			 tag;				/* the tag itself							*/

	/* read and decode the tag. Is it an octetstring ? */

	if ((taglen= asnReadTag (buffer)) == -1) 
		return -1;
	asnDecodeTag (&cl, &pc, &tag, buffer);

	if (cl != asnUNIVERSAL || !(tag==asnOCTETSTRING || 
								tag==asnNUMERICSTRING ||
								tag==asnPRINTABLESTRING || 
								tag==asnTELETEXSTRING ||
								tag==asnVIDEOTEXSTRING ||
								tag==asnIA5STRING ||
								tag==asnGRAPHICSTRING ||
								tag==asnVISIBLESTRING ||
								tag==asnGENERALSTRING)) {
		asnSkipFile (-taglen);		/* skip backwards  !					*/
		return -2;
	}

	/* Get the length of the octetstring and the octetstring */

	return asnReadOctetL (value, maxlen, pc);
}


/**
 *	\brief 		Read an octet string from an ASN.1-File (with the length)
 *
 *	\details 	Read an octet string from the opened ASN.1 file, including the
 *				length of the encoding. The tag must have been read prior to
 *				the call of this function. \p value is the variable to fill 
 *				with the result. \p maxlen is the maximum number of bytes to
 *				be read. \p pc is a flag whether the encoding is primitive
 *				(\ref asnPRIMITIVE ) or constructed (\ref asnCONSTRUCTED ).
 *
 *	\return 	If an error occures, the function returns -1. Otherwise, the
 *				number of bytes read is returned.
 *
 *	\note 		The maximum number of bytes has to be less than MAXINT.
 *
 *	\see 		asnDecodeOctet, asnEncodeOctet, asnWriteOctet, asnReadOctet, asnReadOctetFileTL
 */

int asnReadOctetL (byte *value, int maxlen, byte pc) {
	long	 length;			/* length of the octetstring				*/

	/* Get the length of the octetstring */

	if (asnReadLength (&length) == -1)
		return -1;	/* error */

	/* Read the octetstring and decode it */

	return asnReadOctet (value, (int)length, maxlen, pc);
}


/**
 *	\brief 		Read an octet string from an ASN.1-File (w/o the tag and length)
 *
 *	\details 	Read an octet string from the opened ASN.1 file (only the data).
 *				The tag and the length must have been read prior to the call of
 *				this function. \p value is the variable to fill with the result.
 *				\p length is the length of the data to be read. \p maxlen is the
 *				maximum number of bytes to be read. \p pc is a flag whether the
 *				encoding is primitive (\ref asnPRIMITIVE ) or constructed 
 *				(\ref asnCONSTRUCTED ).
 *
 *	\return 	If an error occures, the function returns -1. Otherwise, the
 *				number of bytes read is returned.
 *
 *	\note		The maximum number of bytes has to be less than MAXINT.
 *
 *	\see 		asnDecodeOctet, asnEncodeOctet, asnWriteOctet, asnReadOctetTL, asnReadOctetFileTL
 */

int asnReadOctet (byte *value, int length, int maxlen, byte pc) {
	int		len, ret, rlen;
	long	nlength;
	byte	buffer[10], cl, pcn, tag;
	
	if (pc == asnCONSTRUCTED) {
		len= 0;
		rlen= 0;
		while (rlen<length) {

			if ((ret= asnReadTag (buffer)) == -1) 
				return -1;
			asnDecodeTag (&cl, &pcn, &tag, buffer);
			rlen+= ret;

			if ((ret= asnReadLength (&nlength)) == -1)
				return -1;	/* error */
			rlen+= ret;

			if ((ret= asnReadOctet (&value[len], nlength, maxlen-len, pcn)) < 0)
				return ret;
			len+= ret;
			rlen+= ret;
		}
	} else {
		len= (length<maxlen) ? length : maxlen;

		/* Read the octettring and decode it */

		if (asnRead (value, len) != len)
			return -1;
		asnDecodeOctet (value, len);

		/* Skip the difference of the real length of the octettring and the 
		   number of bytes read. */

		if (len<length)
			asnSkipFile ((int)(length-len));
		if (len<maxlen)
			value[len]= '\0';		/* for string values... */
	}

	return len;
}

/**
 *	\brief 		Read an octet string from an ASN.1-File and write it to another file
 *
 *	\details 	Read an octet string from the opened ASN.1 file (including the
 *				tag and	the length) and write it to another open file \p outfile.
 *
 *	\return 	If an error occures, the function returns -1. -2 is returned
 *				if the value read is not an octet string. Otherwise, the number
 *				of bytes read is returned.
 *
 *	\note 		The maximum number of bytes has to be less than MAXINT.
 *
 *	\see 		asnDecodeOctet, asnEncodeOctet, asnWriteOctet, asnReadOctetTL, asnReadOctetFile
 */

long asnReadOctetFileTL (int outfile) {
	int		 taglen;			/* length of tag							*/
	byte	 buffer[256],		/* buffer									*/
			 cl,				/* tagclass									*/
			 pc,				/* primitive or constructed					*/
			 tag;				/* the tag itself							*/
	
	assert (outfile);

	/* read and decode the tag. Is it an octetstring ? */

	if ((taglen= asnReadTag (buffer)) == -1) 
		return -1;
	asnDecodeTag (&cl, &pc, &tag, buffer);

	if (cl != asnUNIVERSAL || !(tag==asnOCTETSTRING || 
								tag==asnNUMERICSTRING ||
								tag==asnPRINTABLESTRING || 
								tag==asnTELETEXSTRING ||
								tag==asnVIDEOTEXSTRING ||
								tag==asnIA5STRING ||
								tag==asnGRAPHICSTRING ||
								tag==asnVISIBLESTRING ||
								tag==asnGENERALSTRING)) {
		asnSkipFile (-taglen);		/* skip backwards  !					*/
		return -2;
	}

	return asnReadOctetFileL (outfile, pc);
}


/**
 *	\brief 		Read an octet string from an ASN.1-File (with the tag) and write it to another file
 *
 *	\details 	Read an octet string from the opened ASN.1 file (and the length)
 *				and write it to another open file \p outfile. \p pc is a flag
 *				whether the encoding is primitive (\ref asnPRIMITIVE ) or
 *				constructed (\ref asnCONSTRUCTED ).
 *
 *	\return 	If an error occures, the function returns -1. Otherwise, the
 *				number of bytes read is returned.
 *
 *	\note 		The maximum number of bytes has to be less than MAXINT.
 *
 *	\see 		asnDecodeOctet, asnEncodeOctet, asnWriteOctet, asnReadOctetTL, asnReadOctetFile
 */

long asnReadOctetFileL (int outfile, byte pc) {
	long	 length;			/* length of the octetstring				*/

	assert (outfile);

	/* Get the length of the octetstring */

	if (asnReadLength (&length) == -1)
		return -1;	/* error */

	/* Read the octetstring and decode it */

	return asnReadOctetFile (outfile, pc, length);
}


/**
 *	\brief 		Read an octet string from an ASN.1-File (w/o the tag and the length) and write it to another file
 *
 *	\details 	Read an octet string from the opened ASN.1 file (without the
 *				tag and the length) and write it to another open file 
 *				\p outfile. \p pc is a flag whether the encoding is primitive
 *				(\ref asnPRIMITIVE ) or constructed (\ref asnCONSTRUCTED).
 *				\p length is the number of bytes to be read.
 *
 *	\return 	If an error occures, the function returns -1. Otherwise, the
 *				number of bytes read is returned.
 *
 *	\note 		The maximum number of bytes has to be less than MAXINT.
 *
 *	\see 		asnDecodeOctet, asnEncodeOctet, asnWriteOctet, asnReadOctetTL, asnReadOctetFile
 */

long asnReadOctetFile (int outfile, byte pc, long length) {
	long	all, rlen;
	long	ret, nlength;
	int		l;
	byte	buffer[1024], cl, pcn, tag;

	assert (outfile);

	if (pc == asnCONSTRUCTED) {
		all= 0;
		rlen= 0;
		while (rlen<length) {

			if ((ret= (long)asnReadTag (buffer)) == -1) 
				return -1;
			asnDecodeTag (&cl, &pcn, &tag, buffer);
			rlen+= ret;

			if ((ret= (long)asnReadLength (&nlength)) == -1)
				return -1;	/* error */
			rlen+= ret;

			if ((ret= asnReadOctetFile (outfile, pcn, nlength)) < 0)
				return ret;
			all+= ret;
			rlen+= ret;
		}
	} else {
		all= length;
		while (all!=0 && 
			   (l=read (asnfd, 
						(void *)buffer, 
						(all>sizeof(buffer)) ? sizeof(buffer) : all)) !=0) {

			if (write (outfile, (void *)buffer, l) != l) 
				return -1;
			all-= (long)l;
		} /* while */
	} /* else */
	return all;
}

