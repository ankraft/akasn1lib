/*
 * oiddec.c
 *
 * written 1993 by Andreas Kraft
 */

# include	<string.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	"akasn1.h"

/**
 *	\brief 		Decode an object identifier from a buffer into a string
 *
 *	\details 	Decode an object identifier from buffer and return it in the
 *				format "a b c ...". \p buffer contains the encoded object 
 *				identifier. \p length is the length of the encoding in \p buffer.
 *				\p id is a pointer for the resulting string.
 *
 *	\return 	The length of the result string \p id is returned.
 *
 *	\note 		Restriction: Supports only subid's less or equal 16383.
 * 
 *	\see 		asnEncodeOID, asnReadOID, asnWriteOID
 */

int asnDecodeOid (byte *buffer, int len, char *id) {
	int		i,
			val1,
			val2;
	char	sbuf[25];					/* buffer for itoa()				*/

	/* decode the first two subidentifier */

	val1= buffer[0]/40;
	val2= buffer[0]-(val1*40);
	sprintf (id, "%d %d", val1, val2);

	/* decode the rest of the oid */

	for (i=1; i<len; i++) {
		if (buffer[i] & 0x80) 			/* > 127							*/
			val1= (buffer[i++] & 0x7F) << 7;
		else
			val1= 0;
		val1+= buffer[i] & 0x7F;
		strcat (id, " ");

# ifdef		 MSDOS 
		itoa (val1, sbuf, 10);
# else
		sprintf (sbuf, "%d", val1);
# endif

		strcat (id, sbuf);
	}

	return strlen (id);
}

