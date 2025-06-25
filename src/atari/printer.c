#include <stdio.h>
#include <stdint.h>

#include "printer.h"

#define ESC "\x1B"

const char graphics_data[] = {
  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,
  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,
  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,
  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,
  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,
  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,
  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,
  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,  0xEE,0xDD,0xBB,0x77,
};

void print_sample_plaintext()
{
  FILE *printer;

  printf("Printing Epson sample...");

  printer = fopen("P1:", "w");

  fprintf(printer, "\n\n==============\nPRINTER SAMPLE\n==============\n\n");
  fprintf(printer, "Plaintext\n\n");
  fprintf(printer, "This is an example of printing a plain text document to the printer. It contains"
                   " only basic ASCII characters and newlines. This line is long enough that it"
                   " should demonstrate automated linewrapping.\n\n");
  fprintf(printer, "\n\n\n\n\n\n\n\n\n\n");

  fclose(printer);

  printf("DONE\n");
}

void print_sample_epson()
{
  FILE *p;
  int i;
  uint16_t len;
  uint8_t hi;
  uint8_t lo;

  printf("Printing Epson sample...");

  p = fopen("P1:", "w");

  fputs("===================================\n", p);
  fputs("PRINTER SAMPLE\n\n", p);
  fputs("Epson Graphics & Text Styles\n\n\n", p);

  fputs("------------------------------------\n", p);
  fputs("PITCH\n\n", p);
  fputs("Normal text\n", p);
  fputc(15, p); fputs("Compressed", p); fputc(18, p); fputc('\n', p);
  fputs(ESC"W\1"     "Expanded"     ESC"W", p); fputc(0, p); fputc('\n', p);
  fputs(ESC"M"       "Elite"        ESC"P\n", p);
  fputs(ESC"p\1"     "Proportional" ESC"p", p); fputc(0, p); fputc('\n', p);
  fputs("\n\n", p);

  fputs("------------------------------------\n", p);
  fputs("ENHANCEMENTS\n\n", p);
  fputs(ESC"E""Emphasized"ESC"F\n", p);
  fputs(ESC"G""Double stroke"ESC"H\n", p);
  fputs(ESC"-\1""Underline"ESC"-",p); fputc(0, p); fputc('\n', p);
  fputs("\n\n", p);

  fputs("------------------------------------\n", p);
  fputs("GRAPHICS\n\n", p);
  len = sizeof(graphics_data) / sizeof(graphics_data[0]);
  lo = len;
  hi = len >> 8;

  fputs("Single density:\n", p);
  fputs(ESC"A", p); fputc(8, p); // 8/72 in line spacing
  for (i = 0; i < 3; i++) {
    fputs(ESC"K", p); fputc(lo, p); fputc(hi, p);
    fwrite(graphics_data, sizeof(graphics_data[0]), len, p);
    fputc('\n', p);
  }
  fputs(ESC"2", p); // 6 lines per inch (default?)
  fputs("\n", p);

  fputs("Double density:\n", p);
  fputs(ESC"A", p); fputc(8, p); // 8/72 in line spacing
  for (i = 0; i < 3; i++) {
    fputs(ESC"L", p); fputc(lo, p); fputc(hi, p);
    fwrite(graphics_data, sizeof(graphics_data[0]), len, p);
    fputc('\n', p);
  }
  fputs(ESC"2", p); // 6 lines per inch (default?)
  fputs("\n", p);

  fputs("\n\n\n\n\n\n\n\n\n\n", p);

  fclose(p);

  printf("DONE\n");
}
