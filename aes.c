#include "aes.h"

void copy_block(uint8_t src[BLOCK_SIZE], uint8_t dest[BLOCK_COLS])
{
  for (uint8_t i = 0; i < BLOCK_SIZE; i++)
    dest[i] = src[i];
}

void sbox_round(uint8_t block[BLOCK_SIZE])
{
  unsigned char i;

  for (i = 0; i < BLOCK_SIZE; i++)
    block[i] = sbox[block[i]];
}

void shift_rows(uint8_t block[BLOCK_SIZE])
{
  uint8_t i, j, x;

  for (i = 1; i < BLOCK_ROWS; i++) {
    // Shift i times
    for (j = 0; j < i; j++) {
      x = block[I(i, 0)];
      block[I(i, 0)] = block[I(i, 1)];
      block[I(i, 1)] = block[I(i, 2)];
      block[I(i, 2)] = block[I(i, 3)];
      block[I(i, 3)] = x;
    }
  }
}

void mix_cols(uint8_t block[BLOCK_SIZE])
{
  uint8_t i, j, temp[BLOCK_SIZE];

  copy_block(block, temp);

  // Mat Mul
  for (i = 0; i < BLOCK_ROWS; i++) {
    for (j = 0; j < BLOCK_COLS; j++) {
      block[I(j, i)] =
        column_mix[I(j, 0)] * temp[I(0, i)] +
        column_mix[I(j, 1)] * temp[I(1, i)] +
        column_mix[I(j, 2)] * temp[I(2, i)] +
        column_mix[I(j, 3)] * temp[I(3, i)];
    }
  }
}

void add_subkey(uint8_t blk[BLOCK_SIZE], uint8_t key[BLOCK_SIZE])
{
  for (uint8_t i = 0; i < BLOCK_SIZE; i++)
    blk[i] ^= key[i];
}

#ifdef DEBUG
void print_block(const uint8_t block[BLOCK_SIZE])
{
  uint8_t i, j;

  for (i = 0; i < BLOCK_ROWS; i++) {
    for (j = 0; j < BLOCK_COLS; j++) {
      printf(" %2d ", block[I(i, j)]);
    }
    printf("\n");
  }
}
#endif // DEBUG
