/*
 * extrd.c
 *
 * written 1994 by Andreas Kraft
 */

/*:>*************************************************************************

Name
	asnReadExternalBPFile

Info
	Read an X.400 EXTERNAL body part from an ASN.1 file

Syntax
	long asnReadExternalBPFile(byte * param, long * parlen, long maxplen, char * poid, int outfd, long * datalen, char * doid, byte * dpc)

Include
	amasn1.h

Description
	Read an X.400 EXTERNAL body part from an ASN.1 file. Only direct-reference 
	(oid) and encoding (0, 1, 2) are supported.$
	(Sorry, no further description yet).

Return value
	If an error occures, the function returns -1, or the number of bytes
	read otherwise.

See also
	asnWriteExternalBPFile

Chapter
	ASN.1 Support

Author
	Andreas Kraft

Date
	1994

**************************************************************************<:*/

# include	<assert.h>
# include	<string.h>

# ifndef	_MSC_VER
# include	<unistd.h>
# endif
# include	"akasn1.h"


/**
 *	\brief 		Read an X.400 EXTERNAL body part from an ASN.1 file
 *
 *	\details	Read an X.400 EXTERNAL body part from an ASN.1 file. Only 
 *				direct-reference (oid) and encoding (0, 1, 2) are supported.
 *
 *	\return 	If an error occures, the function returns -1, or the number of
 *				bytes read otherwise.
 *
 *	\see 		asnWriteExternalBPFile
 */

long asnReadExternalBPFile (byte *param, long *parlen, long maxplen, char *poid,
						    int outfd, long *datalen, char *doid, byte *dpc) {
	byte	tbuf[20];
	long	length;
	long	all;
	int		l;
	byte	cl, pc, tag;
	char	buffer[1024];
	
	assert (datalen);

	/***********************************************************************
	 *
	 *	Read CHOICE- or SEQUENCE-Tag
	 */
	
	if (asnReadTagAndLength ((byte *)tbuf, &length) == -1) 
		return -1l;
	asnDecodeTag (&cl, &pc, &tag, tbuf);

	if (cl != asnCONTEXT) 
		if (cl != asnUNIVERSAL && tag != asnSEQUENCE) 
			return -1l;

	/***********************************************************************
	 *
	 *	Read Parameters
	 */

	if (asnReadTagAndLength ((byte *)tbuf, &length) == -1)	/* [0] or EXTERNAL */
		return -1l;
	asnDecodeTag (&cl, &pc, &tag, tbuf);
	
	if (cl == asnCONTEXT && tag == 0) {

		/*
 		 * Parameter part found !!!
 		 */

		/* skip optional EXTERNAL and read OID */

		if (asnReadTagAndLength ((byte *)tbuf, &length) == -1)	/* EXTERNAL or OID */
			return -1l;
		asnDecodeTag (&cl, &pc, &tag, tbuf);
		if (tag == asnEXTERNAL) 
			if (asnReadTagAndLength ((byte *)tbuf, &length) == -1)	/* OID */
				return -1l;
		

		/* read OID and check it */

		if (asnReadOid (buffer, length) == -1)
			return -1l;
		if (poid && *poid)
			if (strcmp (buffer, poid) != 0)
				return -1l;


		/* read CHOICE[0|1|2]-tag */

		if (asnReadTagAndLength ((byte *)tbuf, &length) == -1)
			return -1l;
		

		/* read data into the parameter buffer or skip */
		
		if (param) {
			*parlen= (length<=maxplen) ? length : maxplen;
			if (asnRead (param, (uint)*parlen) == -1l)
				return -1l;
		} else 
			asnSkipFile (length);
		

		/* read next EXTERNAL-tag */

		if (asnReadTagAndLength ((byte *)tbuf, &length) == -1)
			return -1l;
		asnDecodeTag (&cl, &pc, &tag, tbuf);

	} /* if (parameter found) */


	if (cl != asnUNIVERSAL && tag != asnEXTERNAL) 
		return -1l;

	
	/***********************************************************************
	 *
	 *	Read data
	 */

	/* read and compare the OID */

	if (asnReadTagAndLength ((byte *)tbuf, &length) == -1)
		return -1l;
	if (asnReadOid (buffer, length) == -1)
		return -1l;
	if (doid && *doid)
		if (strcmp (buffer, doid) != 0)
			return -1l;

	/* read CHOICE[0|1|2]-tag */

	if (asnReadTagAndLength ((byte *)tbuf, &length) == -1)
		return -1l;
	asnDecodeTag (&cl, dpc, &tag, tbuf);
	
	/* copy content to the open file 'infd' */

# ifdef ALT
	all= length;
	while (all!=0 && 
		   (l=read (asnfd, 
					(void *)buffer, 
					(all>sizeof(buffer)) ? sizeof(buffer) : all)) !=0) {

		if (write (outfd, (void *)buffer, l) != l) 
			return -1l;
		all-= (long)l;
	} /* while */
	*datalen= length;
	return length;
# endif

	all= 0;
	while ((l=read	(asnfd, (void *)buffer, sizeof(buffer))) !=0) {

		if (write (outfd, (void *)buffer, l) != l) 
			return -1l;
		all+= (long)l;
	} /* while */
	*datalen= all;

	return all;
}
