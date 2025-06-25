#include <conio.h>
#include <stdint.h>
#include <stdio.h>
#include "main.h"

int main() {
  char c;

	while (1) {
	  clrscr();
		printf("PRINTER TEST PROGRAM\n\n");
		printf("Choose a test:\n\n");
		printf("  T - Plain text\n\n");
		printf("  E - Epson text styles & graphics\n\n");

	  while (!kbhit());
		c = cgetc();

		switch (c) {
		case 'T':
		case 't':
		  print_sample_plaintext();
			cgetc();
			break;
		case 'E':
		case 'e':
		  print_sample_epson();
			cgetc();
			break;
		default:
		  break;
		}
	}

	return 0;
}
