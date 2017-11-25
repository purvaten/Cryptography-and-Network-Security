/* RSA Algorithm
   MIS : 111403049
   Name : Purva Tendulkar
*/

#include <stdio.h>
#include <math.h>
#define MAX 	100

int gcd(int a, int b) {
	/* Returns gcd of a and b */
    int temp;
    while (1) {
        temp = a%b;
        if (temp == 0)
          return b;
        a = b;
        b = temp;
    }
}

int inverse(e, y) {
	/* Returns the inverse of e modulo y */
	int d = 1;
	while(1) {
		if ((e*d) % y == 1)
			return d;
		d++;
	}
}

int main() {
	int i, n, array[MAX], ciphertext[MAX];
	long long int p, q, x, y, temp, e, d;

	printf("Enter the size of the plaintext list\n");
	scanf("%d", &n);
	printf("Enter the plaintext numbers in decimal\n");
	for (i = 0; i < n; i++)
		scanf("%d", &array[i]);
	printf("Enter the 2 prime numbers\n");
	scanf("%lld %lld", &p, &q);
	x = p * q;
	y = (p-1) * (q-1);

	/* ENCRYPTION */
	/* STEP 1 - Finding e :- relatively prime number to y */
	e = 2;
	while(e < y) {
		if (gcd(e, y) == 1)
            break;
        else
            e++;
	}

	/* STEP 2 - Generating ciphertext */
	printf("\nCiphertext : { ");
	for (i = 0; i < n; i++) {
		temp = (long long int)pow(array[i], e) % x;
		ciphertext[i] = temp;
		printf("%lld ", temp);
	}
	printf("}\n\n");


	/* DECRYPTION */
	/* STEP 1 - Calculate d :- Inverse of e modulo y */
	d = inverse(e, y);

	/* STEP 2 - Generating plaintext */
	printf("Plaintext : { ");
	for (i = 0; i < n; i++) {
		temp = (long long int)pow(ciphertext[i], d) % x;
		printf("%lld ", temp);
	}
	printf("}\n\n");

	return 0;
}