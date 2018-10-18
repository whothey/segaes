#include "aes.h"

void copy_block(uint8_t src[BLOCK_SIZE], uint8_t dest[BLOCK_COLS])
{
  for (uint8_t i = 0; i < BLOCK_SIZE; i++)
    dest[i] = src[i];
}

void sbox32(uint32_t *blk)
{
  uint8_t i, *block = (uint8_t *)blk;

  for (i = 0; i < 4; i++)
    block[i] = sbox[block[i]];
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
    // Circular Shift i times
    crot32(block + i*4, i);
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

void expand(uint8_t *key, size_t size)
{
  uint8_t i, nwords = size / 32, prevkey = malloc(sizeof(uint32_t));

  for (i = 0; i < nwords; i++) {
    prevkey = (uint32_t *) (key + i - 1);

    if (i < nwords) {
      // let as it is
    } else if (i >= nwords && (i % nwords == 0)) {
      key[i] = key[i - nwords] ^ crot32(sbox32(prevkey)) ^ rcon[i / nwords];
    } else if (i >= nwords && nwords > 6 && ((i - 4) % nwords == 0)) {
      key[i] = key[i - nwords] ^ sbox32(prevkey);
    } else {
      key[i] = key[i - nwords] ^ (key + i - 1);
    }
  }
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
