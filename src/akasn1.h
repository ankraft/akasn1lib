/*
 *	akasn1.h
 *
 *	Includefile for use with ASN.1-functions
 *
 *	(c) by Andreas Kraft, 1994-2016
 */

# ifndef	_AKASN1_H_
# define	_AKASN1_H_

# include "vlARGS.h"

# if defined(sun) | defined(__svr4__)
# include	<sys/types.h>
# endif		/* sun */

# ifdef		linux
# include	<sys/types.h>
# endif		/* linux */

/*
 * Types
 */

typedef unsigned char	byte;
typedef unsigned int	uint;


/*
 * Some other definements
 */

/** Maximum number of subid's in an oid */
#define	MAXOID	10

/** ASN.1 Boolean False */
#define	asnFALSE	0x00

 /** ASN.1 Boolean TRUE */
#define	asnTRUE		0xFF


/*
 * Tag-Classes
 */

/** Universal-Tag-Class */
#define	asnUNIVERSAL		0x00

/** Application-Tag-Class */
#define	asnAPPLICATION		0x40

/** Context-Tag-Class */
#define	asnCONTEXT			0x80

/** Private-Tag-Class */
#define	asnPRIVATE			0xC0


/** Primitive coding */
#define	asnPRIMITIVE		0x00	

/** Constructed coding */
#define	asnCONSTRUCTED		0x20	


/*
 * ASN.1-length encoding
 */

/** ASN.1 length encoding indefinite */
#define	asnINDEFINITE		-1l

/** ASN.1 length encoding end-of-contents */
#define	asnENDCONTENTS		-2l

/*
 * ASN.1-types
 */

/** ASN.1 type: No Tag */
#define	asnNOTHING			0x00	

/** ASN.1 type: Boolean */
#define	asnBOOLEAN			0x01	

/** ASN.1 type: Integer */
#define	asnINTEGER			0x02	

/** ASN.1 type: Byte-String	*/
#define	asnOCTETSTRING		0x04

/** ASN.1 type: Empty, NULL-Value */	
#define	asnNULLVALUE		0x05

/** ASN.1 type: object identifier */
#define	asnOBJECTID			0x06

/** ASN.1 type: External */
#define	asnEXTERNAL			0x08

/** ASN.1 type: Enumerated */
#define	asnENUMERATED		0x0A

/** ASN.1 type: Sequence, Sequence of */	
#define	asnSEQUENCE			0x10

/** ASN.1 type: Set, Set of	*/
#define	asnSET				0x11

/** ASN.1 type: Numeric String */
#define	asnNUMERICSTRING	0x12

/** ASN.1 type: Printable String */	
#define	asnPRINTABLESTRING	0x13

/** ASN.1 type: Teletex */
#define	asnTELETEXSTRING	0x14

/** ASN.1 type: Videotex String	*/
#define	asnVIDEOTEXSTRING	0x15

/** ASN.1 type: ia5 (ASCII) -String	*/	
#define	asnIA5STRING		0x16

/** ASN.1 type: Graphic String */
#define	asnGRAPHICSTRING	0x19

/** ASN.1 type: Visible String */
#define	asnVISIBLESTRING	0x1A

/** General String */
#define	asnGENERALSTRING	0x1B

/*****************************************************************************
 *
 *	Map the functions for the string types to the functions for octet string.
 *	This can be done because:
 *
 *		[UNIVERSAL x] IMPLICIT OCTETSTRING
 *
 *	where x is one of {18, 19, 20, 21, 22, 25, 26, 27}.
 *
 */

/* Numeric String */

#define	asnDecodeNumericString				asnDecodeOctetString
#define	asnEncodeNumericString(v,l,tl,tll)	asnEncodeOctetString(v,l,tl,tll,asnNUMERICSTRING)
#define	asnReadNumericString				asnReadOctet
#define	asnReadNumericStringL				asnReadOctetL
#define	asnReadNumericStringTL				asnReadOctetTL
#define	asnReadNumericStringFile			asnReadOctetFile
#define	asnReadNumericStringFileL			asnReadOctetFileL
#define	asnReadNumericStringFileTL			asnReadOctetFileTL
#define	asnWriteNumericString(v)			_asnWriteOctet(v,strlen(v),asnNUMERICSTRING)
#define	asnWriteNumericStringFile(f,l) 		_asnWriteOctetFile(f,l,asnNUMERICSTRING)


/* Printable String */

#define	asnDecodePrintableString			asnDecodeOctetString
#define	asnEncodePrintableString(v,l,tl,tll) asnEncodeOctetString(v,l,tl,tll,asnPRINTABLESTRING)
#define	asnReadPrintableString				asnReadOctet
#define	asnReadPrintableStringL				asnReadOctetL
#define	asnReadPrintableStringTL			asnReadOctetTL
#define	asnReadPrintableStringFile			asnReadOctetFile
#define	asnReadPrintableStringFileL			asnReadOctetFileL
#define	asnReadPrintableStringFileTL		asnReadOctetFileTL
#define	asnWritePrintableString(v)			_asnWriteOctet(v,strlen(v),asnPRINTABLESTRING)
#define	asnWritePrintableStringFile(f,l) 	_asnWriteOctetFile(f,l,asnPRINTABLESTRING)


/* Teletex String */

#define	asnDecodeTeletexString				asnDecodeOctetString
#define	asnEncodeTeletexString(v,l,tl,tll)	asnEncodeOctetString(v,l,tl,tll,asnTELETEXSTRING)
#define	asnReadTeletexString				asnReadOctet
#define	asnReadTeletexStringL				asnReadOctetL
#define	asnReadTeletexStringTL				asnReadOctetTL
#define	asnReadTeletexStringFile			asnReadOctetFile
#define	asnReadTeletexStringFileL			asnReadOctetFileL
#define	asnReadTeletexStringFileTL			asnReadOctetFileTL
#define	asnWriteTeletexString(v)			_asnWriteOctet(v,strlen(v),asnTELETEXSTRING)
#define	asnWriteTeletexStringFile(f,l) 		_asnWriteOctetFile(f,l,asnTELETEXSTRING)


/* Videotex String */

#define	asnDecodeVideotexString				asnDecodeOctetString
#define	asnEncodeVideotexString(v,l,tl,tll)	asnEncodeOctetString(v,l,tl,tll,asnVIDEOTEXSTRING)
#define	asnReadVideotexString				asnReadOctet
#define	asnReadVideotexStringL				asnReadOctetL
#define	asnReadVideotexStringTL				asnReadOctetTL
#define	asnReadVideotexStringFile			asnReadOctetFile
#define	asnReadVideotexStringFileL			asnReadOctetFileL
#define	asnReadVideotexStringFileTL			asnReadOctetFileTL
#define	asnWriteVideotexString(v)			_asnWriteOctet(v,strlen(v),asnVIDEOTEXSTRING)
#define	asnWriteVideotexStringFile(f,l)		_asnWriteOctetFile(f,l,asnVIDEOTEXSTRING)


/* Graphic String */

#define	asnDecodeGraphicString				asnDecodeOctetString
#define	asnEncodeGraphicString(v,l,tl,tll)	asnEncodeOctetString(v,l,tl,tll,asnGRAPHICSTRING)
#define	asnReadGraphicString				asnReadOctet
#define	asnReadGraphicStringL				asnReadOctetL
#define	asnReadGraphicStringTL				asnReadOctetTL
#define	asnReadGraphicStringFile			asnReadOctetFile
#define	asnReadGraphicStringFileL			asnReadOctetFileL
#define	asnReadGraphicStringFileTL			asnReadOctetFileTL
#define	asnWriteGraphicString(v)			_asnWriteOctet(v,strlen(v),asnGRAPHICSTRING)
#define	asnWriteGraphicStringFile(f,l) 		_asnWriteOctetFile(f,l,asnGRAPHICSTRING)


/* Visible String */

#define	asnDecodeVisibleString				asnDecodeOctetString
#define	asnEncodeVisibleString(v,l,tl,tll)	asnEncodeOctetString(v,l,tl,tll,asnVISIBLESTRING)
#define	asnReadVisibleString				asnReadOctet
#define	asnReadVisibleStringL				asnReadOctetL
#define	asnReadVisibleStringTL				asnReadOctetTL
#define	asnReadVisibleStringFile			asnReadOctetFile
#define	asnReadVisibleStringFileL			asnReadOctetFileL
#define	asnReadVisibleStringFileTL			asnReadOctetFileTL
#define	asnWriteVisibleString(v)			_asnWriteOctet(v,strlen(v),asnVISIBLESTRING)
#define	asnWriteVisibleStringFile(f,l) 		_asnWriteOctetFile(f,l,asnVISIBLESTRING)


/* General String */

#define	asnDecodeGeneralString				asnDecodeOctetString
#define	asnEncodeGeneralString(v,l,tl,tll)	asnEncodeOctetString(v,l,tl,tll,asnGENERALSTRING)
#define	asnReadGeneralString				asnReadOctet
#define	asnReadGeneralStringL				asnReadOctetL
#define	asnReadGeneralStringTL				asnReadOctetTL
#define	asnReadGeneralStringFile			asnReadOctetFile
#define	asnReadGeneralStringFileL			asnReadOctetFileL
#define	asnReadGeneralStringFileTL			asnReadOctetFileTL
#define	asnWriteGeneralString(v)			_asnWriteOctet(v,strlen(v),asnGENERALSTRING)
#define	asnWriteGeneralStringFile(f,l) 		_asnWriteOctetFile(f,l,asnGENERALSTRING)


/* IA5 String */

#define	asnDecodeIA5String					asnDecodeOctetString
#define	asnEncodeIA5String(v,l,tl,tll)		asnEncodeOctetString(v,l,tl,tll,asnIA5STRING)
#define	asnReadIA5String					asnReadOctet
#define	asnReadIA5StringL					asnReadOctetL
#define	asnReadIA5StringTL					asnReadOctetTL
#define	asnReadIA5StringFile				asnReadOctetFile
#define	asnReadIA5StringFileL				asnReadOctetFileL
#define	asnReadIA5StringFileTL				asnReadOctetFileTL
#define	asnWriteIA5String(v)				_asnWriteOctet(v,strlen(v),asnIA5STRING)
#define	asnWriteIA5StringFile(f,l) 			_asnWriteOctetFile(f,l,asnIA5STRING)


/* Octet String */

#define	asnWriteOctet(v,l)		_asnWriteOctet (v,l,asnOCTETSTRING)
#define	asnWriteOctetFile(f,l) 	_asnWriteOctetFile(f,l,asnOCTETSTRING)


/*****************************************************************************
 *****************************************************************************
 *
 * externals
 */

/** Globally used file descriptor. */
extern	int		asnfd;


/*
 * Prototypes
 */


EXTERN void	 asnCloseFile (void);
EXTERN int	 asnDecodeBoolean (byte *buffer, byte *value);
EXTERN int	 asnDecodeEnum (byte *buffer, int length, long *value);
EXTERN int	 asnDecodeLength (byte *buffer, long *length);
EXTERN int	 asnDecodeIA5 (byte *value, int length);
EXTERN int	 asnDecodeInteger (byte *buffer, int length, long *value);
EXTERN int	 asnDecodeOctet (byte *value, int length);
EXTERN int	 asnDecodeOid (byte *buffer, int len, char *id);
EXTERN int	 asnDecodeTag (byte *clasS, byte *pc, byte *tagnum, byte *buf);
EXTERN int	 asnEncodeBoolean (byte *buffer, byte value);
EXTERN int	 asnEncodeBooleanValue (byte *buffer, byte value);
EXTERN int	 asnEncodeEnum (byte * buffer, long value);
EXTERN int	 asnEncodeEnumValue (byte *buffer, long value);
EXTERN int	 asnEncodeIA5 (char *value, byte *buffer, int *length);
EXTERN int	 asnEncodeInteger (byte *buffer, long value);
EXTERN int	 asnEncodeIntegerValue (byte *buffer, long value);
EXTERN int	 asnEncodeLength (byte *buffer, long length);
EXTERN int	 asnEncodeNull (byte *buffer);
EXTERN int	 asnEncodeOctet (byte *value, int length, byte *tag_len, int *tl_length, byte tag);
EXTERN int	 asnEncodeOid (byte *buffer, char *id);
EXTERN int	 asnEncodeTag (byte *buf, byte clasS, byte pc, byte tag);
EXTERN int	 asnFseek (long pos);
EXTERN long	 asnFtell (void);
EXTERN int	 asnIsEOC (void);
EXTERN int	 asnOpenReadFile (char *fn);
EXTERN int	 asnOpenWriteFile (char *fn);
EXTERN int	 asnRead (byte *buffer, uint length);
EXTERN int	 asnReadBoolean (byte *value, long length);
EXTERN int	 asnReadBooleanL (byte *value);
EXTERN int	 asnReadBooleanTL (byte *value);
EXTERN int	 asnReadEnum (long *value, int length);
EXTERN int	 asnReadEnumL (long *value);
EXTERN int	 asnReadEnumTL (long *value);
EXTERN int	 asnReadIA5 (char *value, int len, int maxlen);
EXTERN int	 asnReadIA5L (char *value, int maxlen);
EXTERN int	 asnReadIA5TL (char *value, int maxlen);
EXTERN int	 asnReadInteger (long *value, int length);
EXTERN int	 asnReadIntegerL (long *value);
EXTERN int	 asnReadIntegerTL (long *value);
EXTERN int	 asnReadLength (long *length);
EXTERN int	 asnReadNullL (void);
EXTERN int	 asnReadNullTL (void);
EXTERN int	 asnReadOctet (byte *value, int length, int maxlen, byte pc);
EXTERN long	 asnReadOctetFile (int outfile, byte pc, long length);
EXTERN long	 asnReadOctetFileL (int outfile, byte pc);
EXTERN long	 asnReadOctetFileTL (int outfile);
EXTERN int	 asnReadOctetL (byte *value, int maxlen, byte pc);
EXTERN int	 asnReadOctetTL (byte *value, int maxlen);
EXTERN int	 asnReadOid (char *id, int length);
EXTERN int	 asnReadOidL (char *id);
EXTERN int	 asnReadOidTL (char *id);
EXTERN int	 asnReadTag (byte *buffer);
EXTERN long	 asnReadTagAndLength (byte *buffer, long *length);
EXTERN int	 asnSkipFile (long length);
EXTERN int	 asnWrite (byte *buffer, uint length);
EXTERN int	 asnWriteBoolean (byte value);
EXTERN int	 asnWriteEnum (long value);
EXTERN int 	 asnWriteIA5 (char *value);
EXTERN int	 asnWriteInteger (long value);
EXTERN int	 asnWriteLength (long length);
EXTERN int	 asnWriteNull (void);
EXTERN int	 asnWriteOid (char *id);
EXTERN int	 asnWriteTag (byte clasS, byte pc, byte tag);
EXTERN int	 _asnWriteOctet (byte *value, int length, byte tag);
EXTERN int	 _asnWriteOctetFile (int infd, long length, byte tag);

/*
 *	More complex functions
 */

/* Write an externally defined BP to a file  */


EXTERN long	 asnWriteExternalBPFile (byte *param, long parlen, char *poid, byte pet, byte pcon, int infd, char *doid, byte det, byte dcon);
EXTERN long	 asnReadExternalBPFile (byte *param, long *parlen, long maxplen, char *poid, int outfd, long *datalen, char *doid, byte *dpc);

# endif		/* _AKASN1_H_ */
