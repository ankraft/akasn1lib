/*
 * 	oidenc.c
 *
 *	written 1993 by Andreas Kraft
 */

# include	<stdlib.h>
# include	<string.h>
# include	"akasn1.h"

/**
 *	\brief 		Encode an object identifier with the tag and length
 *
 *	\details 	Encode an object identifier from a string \p id into the buffer
 *				\p buffer including the tag and the length. The format of the 
 *				input must be "a b c ...".
 *
 *	\return 	The length of the encoding in \p buffer.
 *
 *	\note 		Restriction: The maximum length has to be less or equal 127 
 *				octets and the maximum number of subidentifiers is 10. The
 *				number of oid's has to be equal or greater than 2.Supports only 
 *				subid's less or equal 16383.
 *
 *	\see 		asnDecodeOID, asnReadOID, asnWriteOID
 */

int asnEncodeOid (byte *buffer, char *id) {
	int		 val[MAXOID],
			 nr_val= 0;
	int		 i,
			 bc;
	char	*c;

	/* extract values from 'id' */

	while (nr_val != MAXOID && (c= strchr (id, ' ')) != 0) {
		val[nr_val++]= atoi (id);
		id= ++c;
	} /* while */
	if (*id)
		val[nr_val++]= atoi (id);

	val[1]= val[0]*40 + val[1]; /* special treatment for the first two oid's */


	/* fill buffer */

	buffer[0]= asnOBJECTID;		/* Object identifier tag					*/

	for (i= 1, bc= 2; i<nr_val; i++) {
		if (val[i] > 0x7F)		/* 127 */
			buffer[bc++]= (0x80 | val[i]>>7) & 0xFF;
		buffer[bc++]= val[i] & 0x7F;
	} /* for */

	buffer[1]= bc-2;		/* encode length directly into the buffer		*/
	
	return bc;
}


