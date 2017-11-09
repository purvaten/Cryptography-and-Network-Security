/* Hill Cipher - Encryption Algorithm */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX 100

/*................................................................................................*/
/* SUPPORTING FUNCTIONS */

int isPerfectSquare(int n) {
	int i, sum;
    for (sum = 0, i = 1; sum < n; i += 2) {
        sum += i;
        if (sum == n)
            return 1;
    }
    return 0;
}

int *matrix_mul(int **key, int *msg, int t) {
	int *res = (int *)malloc(sizeof(int) * t);
	int i, j;

	/* Perform matrix multiplication */
	for (i = 0; i < t; i++) {
		for (j = 0; j < t; j++) {
			res[i] += msg[j] * key[i][j];
		}
	}

	return res;
}

void hill(int **key, int *msg, int t) {
	int *res = (int *)malloc(sizeof(int) * t);
	int i;

	/* Matrix multiplication */
	res = matrix_mul(key, msg, t);

	/* Perform modulo on matrix multiplicatin */
	for (i = 0; i < t; i++)
		res[i] = res[i] % 29;

	/* convert back into characters and print */
	for (i = 0; i < t; i++) {
		if (res[i] < 26)
			printf("%c", 'a'+res[i]);
		else if (res[i] == 26)
			printf("%c", '.');
		else if (res[i] == 27)
			printf("%c", ',');
		else
			printf("%c", '!');
	}
}

/*................................................................................................*/
/* MAIN FUNCTION */

int main() {
	int i, j, count = 0, len, l = 0, keylen, t;
	char message[MAX], ch;
	int **key, *msg;

	printf("Enter the length of the key\n");
	scanf("%d", &keylen);
	if (isPerfectSquare(keylen))
		t = sqrt(keylen);
	else {
		printf("Keylength is not a perfect square\n");
		return 1;
	}

	msg = (int *)malloc(sizeof(int) * t);
	key = (int **)malloc(sizeof(int *) * t);
	for (i = 0; i < t; i++)
		key[i] = (int *)malloc(sizeof(int) * t);

	/* Assume key contains all lowercase alphabets */
	printf("Enter the key-\n");
	scanf("%c", &ch); // newline
	for (i = 0; i < t; i++) {
		for (j = 0; j < t; j++) {
			scanf("%c", &ch);
			key[i][j] = ch - 'a';
		}
	}

	scanf("%c", &ch); //new line
	printf("Enter the message to be encrypted\n");
	scanf("%[^\n]s", message);
	len = strlen(message);

	/* Calculate actual length (l) of message */
	for (i = 0; i < len; i++) {
		if (isalpha(message[i]) || message[i] == '.' || message[i] == ',' || message[i] == '!')
			l++;
	}

	/* If length is not a multiple of 3, pad it with some extra characters ('a's) */
	if (l%t != 0) {
		for (i = 0; i < t-(l%t); i++)
			message[len+i] = 'a';
		message[len+i] = '\0';
		len += t-(l%t);
	}

	printf("\nEncrypted message-\n");
	j = 0;
	for (i = 0; i < len; i++) {
		if (isalpha(message[i])) {
			if (message[i] >= 65 && message[i] <= 90)
				message[i] += 32;
			msg[j++] = message[i] - 'a';
		}
		else if (message[i] == '.')
			msg[j++] = 26;
		else if (message[i] == ',')
			msg[j++] = 27;
		else if (message[i] == '!')
			msg[j++] = 28;
		else
			continue;
		count++;
		if (count%t == 0) {
			hill(key, msg, t);
			j = 0;
		}
	}
	printf("\n");

	return 0;
}

/*................................................................................................*/
