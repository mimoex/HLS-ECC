#ifndef __CHACHA20_H
#define __CHACHA20_H
#include <stdint.h>

void ChaCha20XOR(const uint8_t key[32], const uint32_t counter, const uint8_t nonce[12], const uint8_t* in, uint8_t* out, const int inlen);

#endif