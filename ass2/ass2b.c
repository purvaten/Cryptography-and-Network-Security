/* Hill Cipher - Dencryption Algorithm */
/* Ciphertext and k value are known */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

/*................................................................................................*/

int *matrix_mul(int key[3][3], int msg[3]) {
	int *res = (int *)malloc(sizeof(int) * 3);
	int i, j;

	/* Perform matrix multiplication */
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			res[i] += msg[j] * key[i][j];
		}
	}

	return res;
}

void inverse(int key[3][3]) {
	int val = 0; 			//determinant
	int i, j;
	int new_matrix[3][3];

	/* Calculate determinant */
	for (i = 0; i < 3; i++)
		val += key[0][i] * (key[1][(i+1)%3]*key[2][(i+2)%3] - key[1][(i+2)%3]*key[2][(i+1)%3]);

	/* Caclulate inverse */
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			new_matrix[i][j] = ((key[(i+1)%3][(j+1)%3] * key[(i+2)%3][(j+2)%3]) - (key[(i+1)%3][(j+2)%3]*key[(i+2)%3][(j+1)%3]));

	/* Put it back in original */
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			key[i][j] = new_matrix[i][j];

}

void hill_decrypt(int key[3][3], int msg[3]) {
	int *res = (int *)malloc(sizeof(int) * 3);
	int i;

	/* Find key matrix inverse */
	inverse(key);

	/* Matrix multiplication */
	res = matrix_mul(key, msg);

	/* Perform modulo on matrix multiplication */
	for (i = 0; i < 3; i++)
		res[i] = (int)res[i] % 26;

	/* convert back into characters and print */
	for (i = 0; i < 3; i++)
		printf("%c", 'a'+res[i]);
	printf(" ");
}

/*................................................................................................*/

int main() {
	int i, j, count = 0, len;
	char message[MAX], ch;
	int key[3][3], msg[3];

	/* Assume key contains all lowercase alphabets */
	printf("Enter the key\n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			scanf("%c", &ch);
			key[i][j] = ch - 'a';
		}
	}

	printf("The key is...\n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", key[i][j]);
		}
		printf("\n");
	}

	scanf("%c", &ch); //new line
	printf("Enter the Ciphertext available\n");
	scanf("%[^\n]s", message);
	len = strlen(message);

	j = 0;
	/* Assuming alphabets are all in lowercase AND length is multiple of 3 */
	for (i = 0; i < len; i++) {
		if (isalpha(message[i])) {
			msg[j++] = message[i] - 'a';
			count++;
			if (count%3 == 0) {
				hill_decrypt(key, msg);
				j = 0;
			}
		}
	}
	printf("\n");

	return 0;
}
