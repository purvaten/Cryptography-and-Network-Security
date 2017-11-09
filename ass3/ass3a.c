/* Hill Cipher - Decryption Algorithm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 	100
#define N 	29

/*................................................................................................*/
/* SUPPORTING FUNCTIONS */

int inverse(int x, int y) {
	/* Finds multiplicative inverse of x modulo y */
	int temp, i, p[MAX], a[3] = {0}, yinit = y;
	p[0] = 0, p[1] = 1;
	i = 0;

	while (x != 0) {
		temp = x;
		x = y%x;
		a[2]= a[1];
		a[1] = a[0];
		a[0] = y/temp;
		if (i > 1) {
			p[i] = (p[i-2] - (p[i-1]*a[2])%yinit) % yinit;
			if (p[i] < 0)
				p[i] = yinit - ((p[i] * -1) % yinit);
		}
		y = temp;
		i++;
	}

	a[2]= a[1];
	p[i] = (p[i-2] - (p[i-1]*a[2])%yinit) % yinit;
	if (p[i] < 0)
		p[i] = yinit - ((p[i] * -1) % yinit);

	return p[i];
}

void getCofactor(int A[3][3], int temp[3][3], int p, int q, int n) {
    int i = 0, j = 0, row, col;

    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(int A[3][3], int n) {
    int D = 0, temp[3][3], sign = 1, f;

    if (n == 1)
        return A[0][0];

    for (f = 0; f < n; f++) {
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }

    return D;
}

void adjoint(int A[3][3],int adj[3][3]) {
    int sign = 1, temp[3][3], i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            getCofactor(A, temp, i, j, 3);
            sign = ((i+j)%2 == 0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, 2));
        }
    }
}

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

void decipher(int key[3][3], int msg[3]) {
	int i, j, d, val, adj[3][3], *res;
	res = (int *)malloc(sizeof(int) * 3);

	/* Finding inverse of determinant */
	d = determinant(key, 3);
	val = inverse(d%N, N);

	/* Finding adjucate matrix */
	adjoint(key, adj);

	/* Mulitiply every term of matrix with val & take modulo N */
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			adj[i][j] = (adj[i][j] * val) % N;
			if (adj[i][j] < 0)
				adj[i][j] = N - ((adj[i][j]*-1)%N);
		}
	}

	/* Mulitply msg with this, take mod */
	res = matrix_mul(adj, msg);

	for (i = 0; i < 3; i++)
		res[i] = res[i] % N;

	/* Generate plaintext */
	for (i = 0; i < 3; i++) {
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
	int i, j, len;
	char c[MAX], ch;
	int key[3][3], cipher[3];

	printf("Enter the cipher text\n");
	scanf("%s", c);

	/* Make input multiple of 3 - append the string with character 'a' */
	len = strlen(c);
	if (len % 3 != 0) {
		for (i = 0; i < 3-(len%3); i++) {
			c[i] = 'a';
			len++;
		}
	}

	scanf("%c", &ch); 	// scanning newline
	/* Assume key is of length 9 */
	printf("Enter the key\n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			scanf("%c", &ch);
			if (isalpha(ch))
				key[i][j] = ch - 'a';
			else if (ch == '.')
				key[i][j] = 26;
			else if (ch == ',')
				key[i][j] = 27;
			else
				key[i][j] = 28;
		}
	}

	printf("\nThe Key is -\n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("%d ", key[i][j]);
		printf("\n");
	}

	printf("\nPlaintext is -\n");
	for (i = 0; i < len; i+=3) {
		for (j = 0; j < 3; j++) {
			if (isalpha(c[i+j]))
				cipher[j] = c[i+j] - 'a';
			else if (c[i+j] == '.')
				cipher[j] = 26;
			else if (c[i+j] == ',')
				cipher[j] = 27;
			else
				cipher[j] = 28;
		}

		decipher(key, cipher);
	}
	printf("\n");

	return 0;
}

/*................................................................................................*/
