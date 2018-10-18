#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "aes.h"

#ifdef DEBUG
void debug()
{
  uint8_t blk[BLOCK_SIZE] = { 1,  2,  3,  4,
                           5,  6,  7,  8,
                           9, 10, 11, 12,
                          13, 14, 15, 16 };

  printf("====\n");
  printf("== DEBUG FLAG ENABLED ==\n");
  printf("====\n\n");

  printf("Sizes:\n");
  printf(" > sizeof(char): %ld\n", sizeof(char));
  printf(" > sizeof(uint8_t): %ld\n", sizeof(uint8_t));
  printf(" > sizeof(uint16_t): %ld\n", sizeof(uint16_t));
  printf(" > sizeof(uint32_t): %ld\n", sizeof(uint32_t));
  printf(" > sizeof(unsigned char): %ld\n", sizeof(unsigned char));
  printf(" > sizeof(short): %ld\n", sizeof(short));
  printf(" > sizeof(int): %ld\n", sizeof(int));
  printf(" > BYTE_BITS: %ld\n", BYTE_BITS);

  printf("\nByte ops:\n");

  printf("inv(0x53) = 0x%02x\n", (uint8_t) ~0x53);
  printf("BYTE_CLSHIFT(00000001, 1) = "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(BYTE_CLSHIFT(1, 1)));
  printf("BYTE_CLSHIFT(00000001, 4) = "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(BYTE_CLSHIFT(1, 4)));
  printf("BYTE_CLSHIFT(00000001, 7) = "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(BYTE_CLSHIFT(1, 7)));
  printf("BYTE_CLSHIFT(00000001, 8) = "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(BYTE_CLSHIFT(1, 8)));
  printf("BYTE_CLSHIFT(00000001, 9) = "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(BYTE_CLSHIFT(1, 9)));

  printf("\nConsts:\n");

  printf(" > S-box:\n");

  for (unsigned short i = 0; i < 16; i++) {
    for (unsigned short j = 0; j < 16; j++) {
      printf(" 0x%02x ", sbox[16 * i + j]);
    }
    printf("\n");
  }

  printf(" > Column Mix:\n");
  print_block(column_mix);

  printf("\nBlock:\n");
  printf(" > Shifts:\n");
  print_block(blk);
  printf("===========\n");
  shift_rows(blk);
  print_block(blk);
  printf(" > MatMul:\n");
  mix_cols(blk);
  print_block(blk);
}
#endif

int main()
{
#ifdef DEBUG
  debug();
#endif

  printf("The CLI works!\n");

  return 0;
}
