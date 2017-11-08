/* Cryptanalysis of Caesar cipher */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
	FILE *fin, *fout;
	int k, count1 = 0, count2 = 0, x;
	char infile[15], outfile[15], ch;

	printf("Enter the filename to be read\n");
	scanf("%s", infile);
	printf("Enter the filename to write\n");
	scanf("%s", outfile);

	fin = fopen(infile, "r");
	if (fin == NULL) {
		printf("Cannot open file.. Exiting!\n");
		return 1;
	}

	fout = fopen(outfile, "w+");
	if (fout == NULL) {
		printf("Cannot open file.. Exiting!\n");
		return 1;
	}

	for (k = 0; k < 26; k++) {
		ch = fgetc(fin);
		while(ch != EOF) {
			if (isalpha(ch)) {

				x = ch - k;

				/* Upper case -> convert to lowercase */
				if (ch >= 65 && ch <= 90)
					x += 32;

				/* Wrap lower case */
				while (x < 97)
					x += 26;

				fprintf(fout, "%c", x);
				count1++;
				if (count1 % 5 == 0) {
					count2++;
					if (count2 % 10 != 0)
						fprintf(fout, " ");
					else
						fprintf(fout, "\n");
				}
			}
			ch = fgetc(fin);
		}
		fprintf(fout, "\n\n");
		count1 = 0;
		count2 = 0;
		fin = fopen(infile, "r");
	}
	fclose(fin);
	fclose(fout);

	return 0;
}
