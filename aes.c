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
  uint8_t i;

  for (i = 1; i < BLOCK_ROWS; i++) {
    // Circular Shift i times
    crot32((uint32_t *)(block + i*4), i);
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
  uint8_t i, nwords = size / 32, rounds = nwords + 7;
  uint32_t
    *prevkey,
    *kw,
    curw = 0,
    round_constant,
    tempword[4],
    whole[4 * AES_ROUNDS_256]; // Worst case

  for (i = 0; i < 4*rounds; i++) {
    prevkey = whole + i - 1;
    curw = *(whole + i - nwords);
    round_constant = rcon[i / nwords - 1];

    if (i < nwords) {
      kw = (uint32_t*) key;
      whole[i] = *(kw + i);
    } else if (i >= nwords && (i % nwords == 0)) {
      memcpy(tempword, prevkey, sizeof(uint32_t));
      sbox32(tempword);
      crot32(tempword, 1);
      whole[i] = curw ^ *tempword ^ round_constant;
    } else if (i >= nwords && nwords > 6 && ((i - 4) % nwords == 0)) {
      memcpy(tempword, prevkey, sizeof(uint32_t));
      sbox32(tempword);
      whole[i] = curw ^ *tempword;
    } else {
      whole[i] = curw ^ *(whole + i - 1);
    }
  }

#ifdef DEBUG
  printf("EXPANSION:\n");

  for (i = 0; i < rounds; i++) {
    printf("%02d:", i);
    print_key_round((uint8_t *) whole + i*16);
  }
#endif
}

#ifdef DEBUG
void print_block_inline(const uint8_t block[BLOCK_SIZE])
{
  uint8_t i, j;

  for (i = 0; i < BLOCK_ROWS; i++) {
    for (j = 0; j < BLOCK_COLS; j++) {
      printf(" %2d ", block[I(i, j)]);
    }
  }
}

void print_block(const uint8_t block[BLOCK_SIZE])
{
  print_block_inline(block);
  printf("\n");
}

void print_key(const uint8_t *block, size_t size)
{
  uint8_t i, len = size / 8;

  printf("{");

  for (i = 0; i < len; i++) {
    printf(" %4c ", block[i]);
  }

  printf("}\n{");

  for (i = 0; i < len; i++) {
    printf(" 0x%02x ", block[i]);
  }

  printf("}\n");
}

void print_word(const uint32_t* word)
{
  uint8_t *bytes = (uint8_t *) word;

  printf(" 0x%02x ", bytes[0]);
  printf(" 0x%02x ", bytes[1]);
  printf(" 0x%02x ", bytes[2]);
  printf(" 0x%02x \n", bytes[3]);
}

void print_key_round(const uint8_t* word)
{
  for (uint8_t i = 0; i < 16; i++) {
    printf(" %02X ", word[i]);
  }

  printf("\n");
}
#endif // DEBUG
