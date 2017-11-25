/* Diffie-Hellman KeyExchange algorithm
   MIS : 111403049
   Name : Purva Tendulkar */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int Diffie_Hellman(int p, int g, int a, int b) {
	/* Returns shared session key */
	long long int A, B, s;
	A = (long long int)pow(g, a) % p;
	B = (long long int)pow(g, b) % p;

	printf("Internal keys : A = %lld, B = %lld\n", A, B);

	s = (long long int)pow(A, b) % p;
	return s;
}

/*......................................................................................*/

int main() {
	long long int p, g, a, b, s;

	printf("Enter prime number p and base value g :\n");
	scanf("%lld %lld", &p, &g);
	printf("Enter private keys of Alice and Bob :\n");
	scanf("%lld %lld", &a, &b);

	s = Diffie_Hellman(p, g, a, b);
	printf("The shared session key : %lld\n", s);

	return 0;
}