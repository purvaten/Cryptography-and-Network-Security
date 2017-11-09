/* Transposition cipher - Encryption and Decryption */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 	100

/*................................................................................................*/
/* SUPPORTING FUNCTIONS */

void encipher(char **array, int x, int y, int *order, char *cipher) {
	int i, j, k, l = 0;

	for (i = 0; i < y; i++) {
		for (j = 0; j < y; j++) {
			if (order[j] == i+1) {
				for (k = 0; k < x; k++)
					cipher[l++] = array[k][j];
				break;
			}
		}
	}
	printf("\n");
}

void decipher(int *order, char *ciphertxt, int x, int y, char *plaintxt) {
	int i, j = 0, k = 1, index;
	char **array, *temp;

	temp = (char *)malloc(sizeof(char) * x);
	array = (char **)malloc(sizeof(char *) * x);
	for (i = 0; i < y; i++)
		array[i] = (char *)malloc(sizeof(char));

	/* Split ciphertxt into groups of 'y' and find the array index where to insert */
	for (i = 0; i < x*y; i+=x) {
		for (j = 0; j < x; j++)
			temp[j] = ciphertxt[i+j];

		for (j = 0; j < y; j++) {
			if (order[j] == k) {
				index = j;
				break;
			}
		}
		k++;

		for (j = 0; j < x; j++)
			array[j][index] = temp[j];
	}

	k = 0;
	for (i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			plaintxt[k++] = array[i][j];
}

/*................................................................................................*/
/* MAIN FUNCTION */

int main() {
	int i, j, k, mslen, len, order[MAX], x;
	char **array, msg[MAX], *ciphertxt, *plaintxt;

	printf("Enter the length of the key\n");
	scanf("%d", &len);
	printf("Enter the key of %d integers from 1 till %d\n", len, len);
	for (i = 0; i < len; i++)
		scanf("%d", &order[i]);
	printf("Enter the message of lowercase alphabets only without spaces\n");
	scanf("%s", msg);
	mslen = strlen(msg);

	array = (char **)malloc(sizeof(char *) * len);
	x = mslen/len;
	if (mslen%len != 0)
		x++;
	for (i = 0; i < x; i++)
		array[i] = (char *)malloc(sizeof(char));

	k = 0;
	for (i = 0; i < x; i++) {
		for (j = 0; j < len; j++)
			array[i][j] = msg[k++];
	}

	if (mslen%len != 0) {
		for (i = 0; i < len - mslen%len; i++)
			array[x-1][len-1-i] = 'a';
	}

	/* Printing stuff */
	printf("\nPlaintext array is -\n");
	for (i = 0; i < len; i++)
		printf("%d ", order[i]);
	printf("\n");
	for (i = 0; i < len; i++)
		printf("- ");
	printf("\n");
	for (i = 0; i < x; i++) {
		for (j = 0; j < len; j++)
			printf("%c ", array[i][j]);
		printf("\n");
	}

	ciphertxt = (char *)malloc(sizeof(char) * x * len);
	plaintxt = (char *)malloc(sizeof(char) * x * len);
	encipher(array, x, len, order, ciphertxt);
	printf("\nEnciphered message is - %s\n", ciphertxt);

	decipher(order, ciphertxt, x, len, plaintxt);
	printf("\nDeciphered message is - %s\n\n", plaintxt);

	return 0;
}

/*................................................................................................*/
