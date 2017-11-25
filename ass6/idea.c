/* Simplified IDEA algorithm
   MIS : 111403049
   Name : Purva Tendulkar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char key_set[112];
char key_set_decrypt[112];

/*....................................................................................................*/
/* MATH FUNCTIONS */

int getnum(char *x) {
	/* Returns decimal equivalent of binary string */
	int i, sum = 0;
	for (i = 0; i < 4; i++)
		sum += (x[3-i] - '0') * pow(2, i);
	return sum;
}

void getbinary(char *a, int x) {
	/* Stores 4-bit equivalent binary of decimal x in a */
	int i;
	for (i = 0; i < 4; i++) {
		a[3-i] = (x % 2) + '0';
		x /= 2;
	}
}

void mul_rev(char *a) {
	/* Store reverse of a in a */
	int x = getnum(a), y = 0;
	switch(x) {
		case 1 : y = 1; break;
		case 2 : y = 9; break;
		case 3 : y = 6; break;
		case 4 : y = 13; break;
		case 5 : y = 7; break;
		case 6 : y = 3; break;
		case 7 : y = 5; break;
		case 8 : y = 15; break;
		case 9 : y = 2; break;
		case 10 : y = 12; break;
		case 11: y = 14; break;
		case 12 : y = 10; break;
		case 13 : y = 4; break;
		case 14 : y = 11; break;
		case 15 : y = 8; break;
	}
	getbinary(a, y);
}

void add_rev(char *a) {
	/* Store reverse of a in a - 2s complement */
	int i;
	for (i = 0; i < 4; i++) {
		if (a[i] == '0')	a[i] = '1';
		else a[i] = '0';
	}
	if (a[3] == '0') {
		a[3] = '1';
		return;
	}

	a[3] = '0';
	if (a[2] == '0') {
		a[2] = '1';
		return;
	}
	a[2] = '0';
	if (a[1] == '0') {
		a[1] = '1';
		return;
	}
	a[1] = '0';
	if (a[0] == '0') {
		a[0] = '1';
		return;
	}
	a[0] = '0';
}

void mul(char *a, char *b, char *c) {
	/* Multiply b and c modulo 17, store in a */
	int x = getnum(b);
	int y = getnum(c);
	if (x == 0)
		x = 16;
	if (y == 0)
		y = 16;
	int z = (x * y) % 17;
	getbinary(a, z);
}

void add(char *a, char *b, char *c) {
	/* Add b and c modulo 16, store in a */
	int x = getnum(b);
	int y = getnum(c);
	int z = (x + y) % 16;
	getbinary(a, z);
}

void xor(char *a, char *b, char *c) {
	/* XOR b and c */
	int i;
	for (i = 0; i < 4; i++) {
		if (b[i] == c[i])
			a[i] = '0';
		else
			a[i] = '1';
	}
}

/*....................................................................................................*/
/* KEY GENERATION */

void key_generate_encrypt(char *key) {
	/* Generate the 28 encryption keys */
	int i;

	for (i = 0; i < 32; i++)
		key_set[i] = key[i];
	for (i = 0; i < 32; i++)
		key_set[i+32] = key_set[(i+6)%32];
	for (i = 0; i < 26; i++)
		key_set[i+64] = key_set[(i+38)%64];
	for (i = 0; i < 6; i++)
		key_set[i+90] = key_set[(i+32)];
	for (i = 0; i < 16; i++)
		key_set[i+96] = key_set[(i+70)];
}

void get_key(char *round_key, int r) {
	int i, n = 24;
	if (r == 4) n = 16;
	for (i = 0; i < n; i++)
		round_key[i] = key_set[(24*r) + i];
}

void get_decrypt_key(char *round_key, int r) {
	int i, j, from, to;
	switch(r) {
		case 0 :
			from = 88;
			to = 112;
			break;
		case 1 :
			from = 64;
			to = 88;
			break;
		case 2 :
			from = 40;
			to = 64;
			break;
		case 3 :
			from = 16;
			to = 40;
			break;
	}

	j = 0;
	for (i = from; i < to; i++) {
		round_key[j] = key_set[i];
		j++;
	}
}

void key_generate_decrypt() {
	/* Generate the 28 decryption keys */
	char round_key[24], a[5], b[5], c[5], d[5], e[5], f[5];
	int i, j, x = 0;

	/* Formating for string printing purposes */
	a[4] = b[4] = c[4] = d[4] = e[4] = f[4] = '\0';

	for (i = 0; i < 4; i++) {
		get_decrypt_key(round_key, i);

		for (j = 0; j < 4; j++) {
			e[j] = round_key[j];
			f[j] = round_key[4+j];
			a[j] = round_key[8+j];
			b[j] = round_key[12+j];
			c[j] = round_key[16+j];
			d[j] = round_key[20+j];
		}

		mul_rev(a);
		add_rev(b);
		add_rev(c);
		mul_rev(d);

		for (j = 0; j < 4; j++) {
			key_set_decrypt[i*24 + j] = a[j];
			key_set_decrypt[i*24 + j + 4] = b[j];
			key_set_decrypt[i*24 + j + 8] = c[j];
			key_set_decrypt[i*24 + j + 12] = d[j];
			key_set_decrypt[i*24 + j + 16] = e[j];
			key_set_decrypt[i*24 + j + 20] = f[j];
		}
	}

	// Round 5
	for (i = 0; i < 4; i++) {
		a[i] = key_set[i];
		b[i] = key_set[4+i];
		c[i] = key_set[8+i];
		d[i] = key_set[12+i];
	}

	mul_rev(a);
	add_rev(b);
	add_rev(c);
	mul_rev(d);

	for (i = 0; i < 4; i++) {
		key_set_decrypt[96+i] = a[i];
		key_set_decrypt[100+i] = b[i];
		key_set_decrypt[104+i] = c[i];
		key_set_decrypt[108+i] = d[i];
	}


	// transfer
	for (i = 0; i < 112; i++)
		key_set[i] = key_set_decrypt[i];
}

/*....................................................................................................*/
/* ENCRYPTION - DECRYPTION */

void idea_round(char *msg, char *result, char *round_key, int r) {
	char key[6][5], message[4][5];
	char a[5], b[5], c[5], d[5], e[5], f[5];
	int i, j, k;

	k = 0;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 4; j++) {
			key[i][j] = round_key[k];
			k++;
		}
	}

	k = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			message[i][j] = msg[k];
			k++;
		}
	}

	/* Formating for string printing purposes */
	a[4] = b[4] = c[4] = d[4] = e[4] = f[4] = '\0';
	key[0][4] = key[1][4] = key[2][4] = key[3][4] = key[4][4] = key[5][4] = '\0';
	message[0][4] = message[1][4] = message[2][4] = message[3][4] = '\0';

	mul(a, message[0], key[0]);
	add(b, message[1], key[1]);
	add(c, message[2], key[2]);
	mul(d, message[3], key[3]);

	if (r == 5) {
		for (i = 0; i < 4; i++) {
			result[i] = a[i];
			result[i+4] = b[i];
			result[i+8] = c[i];
			result[i+12] = d[i];
		}
		return;
	}

	xor(e, a, c);
	xor(f, b, d);

	mul(e, e, key[4]);
	add(f, f, e);

	mul(f, f, key[5]);
	add(e, e, f);

	xor(a, a, f);
	xor(b, b, e);
	xor(c, c, f);
	xor(d, d, e);

	// Transfer back
	for (i = 0; i < 4; i++) {
		result[i] = a[i];
		result[i+4] = b[i];
		result[i+8] = c[i];
		result[i+12] = d[i];
	}
}

void encrypt(char *msg, char *cipher) {
	char result[17], round_key[25];
	int i;

	result[16] = '\0';
	round_key[24] = '\0';
	for (i = 0; i < 5; i++) {
		get_key(round_key, i);
		printf("\nROUND %d\n", i+1);
		printf("Message : %s\n", msg);

		idea_round(msg, result, round_key, i+1);
		strcpy(msg, result);

		printf("Result : %s\n", msg);
		printf("\n");
	}
	strcpy(cipher, msg);
}

/*....................................................................................................*/
/* MAIN */

int main() {
	int i;
	char key[32], *msg = (char *)malloc(sizeof(char)), *cipher = (char *)malloc(sizeof(char));

	/* KEY GENERATION */
	printf("Enter the 32 bit key in binary format\n");
	for (i = 0; i < 32; i++)
		scanf("%c", &key[i]);
	key_generate_encrypt(key);

	printf("Enter the 16 bit plaintext to be encrypted\n");
	scanf("%s", msg);

	// Encryption
	encrypt(msg, cipher);

	printf("************************************************************************************\n");
	printf("Encrypted message is %s\n", cipher);
	printf("************************************************************************************\n");

	// Decryption
	key_generate_decrypt(); 		// generate new set of keys for decryption
	encrypt(cipher, msg);
	printf("************************************************************************************\n");
	printf("Decrypted message is %s\n", msg);
	printf("************************************************************************************\n");

	return 0;
}

/*....................................................................................................*/
