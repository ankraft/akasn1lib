/*
 * extwr.c
 *
 * written 1994 by Andreas Kraft
 */

# include	<stdio.h>
# include	<assert.h>

# ifndef	_MSC_VER
# include	<unistd.h>
# endif
# include	"akasn1.h"

static long _encodeheader (byte *, int *, byte *, int *, char *,
						   byte *, int *, byte, byte, long);

/**
 *	\brief 		Write an X.400 EXTERNAL body part to a file.
 *
 *	\details 	Write an X.400 EXTERNAL body part to a file. Only
 *				direct-reference (oid) and encoding (0, 1, 2) are supported.
 *				\p param is a pointer to the encoded (!) parameter part or 0.
 *				\p parlen is the length of the data in \p param or 0. \p poid
 *				is the OID of the parameter	part or 0. \p pet is the type for
 *				the CHOICE-Tag (0,1,2) of the parameter	part. \p pcon is a flag
 *				whether the parameters are constructed or not. \p infd is the
 *				File descriptor to the (encoded) data. \p doid is the OID of
 *				the data part. \p det is the type for the CHOICE-Tag (0,1,2)
 *				of the data part. \p dcon is a flag whether the parameters are 
 *				constructed or primitive.
 *
 *	\return 	If an error occures, the function returns -1, or the length
 *				of theencoding otherwise.
 *
 *	\see 		asnReadExternalBPFile
 */

long asnWriteExternalBPFile (byte *param, long parlen, char *poid, 
							 byte pet, byte pcon,
							 int infd, char *doid, byte det, byte dcon) {
	
	long	allen= 0;
	long	datalen;
	long	sizep;
	int		penclen= 0, denclen= 0;
	int		poidlen= 0, doidlen= 0;
	int		pextlen= 0, dextlen= 0;
	int		seqlen= 0;
	int		l;
	byte	pencbuf[20], dencbuf[20];
	byte	poidbuf[20], doidbuf[20];
	byte	pextbuf[20], dextbuf[20];
	byte	seqbuf[20];
	byte	buffer[1024];
	long	altpos;
	
	assert (infd>=0);
	assert (doid);
	assert (det==1 || det==2 || det==3);

	/********************************************************************
	 *	Encode the data part
	 */

	/* 
	 *	Get size of the input-file 
	 */

	/*altpos= tell (infd);*/
	altpos= lseek(infd, 0, SEEK_CUR);

	lseek (infd, 0, SEEK_END);
	/*datalen= tell (infd);*/
	datalen= lseek(infd, 0, SEEK_CUR);
	lseek (infd, altpos, SEEK_SET);

	allen= _encodeheader (dextbuf, &dextlen, 
						  doidbuf, &doidlen, doid, 
						  dencbuf, &denclen, det, 
						  dcon,
						  datalen);

	/********************************************************************
	 *	Encode the parameter part
	 */

	if (param) {
		assert (poid);
		assert (pet==1 || pet==2 || pet==3);

		sizep= _encodeheader (pextbuf, &pextlen, 
							  poidbuf, &poidlen, poid, 
							  pencbuf, &penclen, pet, 
							  pcon,
							  parlen);
		/*
		 *	Substract the length of the EXTERNAL-tag because there is
		 *	none. Instead there is a CHOICE[0]-tag which must be encoded.
		 */

		sizep-=   pextlen; 
		pextlen=  asnEncodeTag (pextbuf, asnCONTEXT, asnCONSTRUCTED, 0);
		pextlen+= asnEncodeLength (&pextbuf[pextlen], sizep);
		sizep+=   (long)pextlen;

		allen+= sizep;

	} /* if param */

	/***********************************************************************
	 *
	 *	Encode the enclosing SEQUENCE-tag
	 */

	seqlen=  asnEncodeTag (seqbuf, asnUNIVERSAL, asnCONSTRUCTED, asnSEQUENCE);
	seqlen+= asnEncodeLength (&seqbuf[seqlen], allen);
	allen+= (long)seqlen;


	/***********************************************************************
	 *
	 *	Copy the single buffers to the outfile
	 */
	
	if (asnWrite (seqbuf, (uint)seqlen) == -1)
		return -1;

	if (param) {
		if (asnWrite (pextbuf, (uint)pextlen) == -1)	/* actual a [0]-tag */
			return -1;
		if (asnWrite (poidbuf, (uint)poidlen) == -1)
			return -1;
		if (asnWrite (pencbuf, (uint)penclen) == -1)
			return -1;
		if (asnWrite (param, (uint)parlen) == -1)
			return -1;
	} /* if param */

	if (asnWrite (dextbuf, (uint)dextlen) == -1)
		return -1;
	if (asnWrite (doidbuf, (uint)doidlen) == -1)
		return -1;
	if (asnWrite (dencbuf, (uint)denclen) == -1)
		return -1;

	/* write buffer */

	while ((l=read (infd, buffer, sizeof(buffer))) != 0)
		if (asnWrite (buffer, (uint)l) == -1) 
			return -1;
	
	return allen;
}



static long _encodeheader (byte *extbuf, int *extlen,
						   byte *oidbuf, int *oidlen, char *oid,
						   byte *encbuf, int *enclen, byte enctype,
						   byte constructed,
						   long datalength ) {

	long	allen= datalength;

	/* 
	 *	Encode tag and size of the data choice[n] -part 
	 */  

	*enclen=  asnEncodeTag (encbuf, 
							asnCONTEXT, 
							constructed ? asnCONSTRUCTED : asnPRIMITIVE, 
							enctype);  
	*enclen+= asnEncodeLength (&encbuf[*enclen], datalength);
	allen+= (long)*enclen;

	/* 
	 *	Encode object id 
	 */

	*oidlen= asnEncodeOid (oidbuf, oid); 
	allen+= (long)*oidlen;
	
	/* 
	 *	Encode tag and size of the external-part 
	 */

	*extlen=  asnEncodeTag (extbuf,asnUNIVERSAL, asnCONSTRUCTED, asnEXTERNAL);
	*extlen+= asnEncodeLength (&extbuf[*extlen], allen);
	allen+= (long)*extlen;

	return allen;
}
