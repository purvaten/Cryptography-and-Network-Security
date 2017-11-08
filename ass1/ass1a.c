/* Caesar Cipher - Encryption Algorithm */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
	FILE *fp;
	int k, count1 = 0, count2 = 0, x;
	char filename[15], ch;

	printf("Enter the value of k\n");
	scanf("%d", &k);

	if ((k <= 0) || (k > 25)) {
		printf("Invalid value of k\n");
		return 1;
	}

	printf("Enter the filename to be read\n");
	scanf("%s", filename);

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Cannot open file.. Exiting!\n");
		return 1;
	}

	ch = fgetc(fp);
	while(ch != EOF) {
		if (isalpha(ch)) {

			x = ch + k;

			/* Upper case -> convert to lowercase */
			if (ch >= 65 && ch <= 90)
				x += 32;

			/* Wrap lower case */
			while (x > 122)
				x -= 26;

			printf("%c", x);
			count1++;
			if (count1 % 5 == 0) {
				count2++;
				if (count2 % 10 != 0)
					printf(" ");
				else
					printf("\n");
			}
		}
		ch = fgetc(fp);
	}
	printf("\n");
	fclose(fp);

	return 0;
}
