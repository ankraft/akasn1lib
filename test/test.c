# include 	<stdio.h>
# include	"akasn1.h"

void printASN(int);
void printASNIA5(char *value);

int main() {
	printASN(20);
	printASN(340);
	printASN(128);
	printASN(-20);
	printASN(-340);
	printASN(-128);
	printASN(-1);
	printASN(1024);
	printASN(-296);
	printASN(-50000);

	printASNIA5("Hello, World");
	return 0;
}

void printASN(int value) {
	int		l, i;
	byte	buffer[100];
	long	val;

	l = asnEncodeInteger(buffer, value);
	printf("value = %d - encoded = ", value);
	for (i = 0; i < l; i++)
		printf("%02X", buffer[i]);

	l = asnEncodeIntegerValue(buffer, value);
	printf(" - valueencoded = ");
	for (i = 0; i < l; i++)
		printf("%02X", buffer[i]);

	asnDecodeInteger(buffer, l, &val);
	printf(" - decoded = %ld", val);

	printf("\n");
}

void printASNIA5(char *value) {
	int		l, i, bl;
	byte	buffer[100];

	l = asnEncodeIA5 (value, buffer, &bl);

	printf("value = %s - encoded = ", value);
	for (i = 0; i < bl; i++)
		printf("%02X", buffer[i]);
	printf(" + %s  strlength=%d ", value, l);

	printf("\n");
}
