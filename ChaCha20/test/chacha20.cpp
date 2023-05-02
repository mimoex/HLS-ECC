#include <stdint.h>
#include <string.h>
#include "chacha20.h"

#include <iostream>

static inline void u32t8le(const uint32_t v, uint8_t p[4]) {
    p[0] = v & 0xff;
    p[1] = (v >> 8) & 0xff;
    p[2] = (v >> 16) & 0xff;
    p[3] = (v >> 24) & 0xff;
}

static inline uint32_t u8t32le(const uint8_t p[4]) {
    uint32_t value = p[3];

    value = (value << 8) | p[2];
    value = (value << 8) | p[1];
    value = (value << 8) | p[0];

    return value;
}

static inline uint32_t rotl32(const uint32_t x, const int n) {
    // http://blog.regehr.org/archives/1063
    //return x << n | (x >> (-n & 31));
    return (x << n) ^ (x >> (32 - n));
}

// https://tools.ietf.org/html/rfc7539#section-2.1
static inline void chacha20_quarterround(uint32_t* x, const int a, const int b, const int c, const int d) {
    x[a] += x[b]; x[d] = rotl32(x[d] ^ x[a], 16);
    x[c] += x[d]; x[b] = rotl32(x[b] ^ x[c], 12);
    x[a] += x[b]; x[d] = rotl32(x[d] ^ x[a], 8);

    x[c] += x[d]; x[b] = rotl32(x[b] ^ x[c], 7);
}

static void chacha20_serialize(const uint32_t in[16], uint8_t output[64]) {
    int i;
    for (i = 0; i < 16; i++) {
        u32t8le(in[i], output + (i << 2));
    }
}

static void chacha20_block(const uint32_t in[16], uint8_t out[64], const int num_rounds) {
    int i;
    uint32_t x[16];

    memcpy(x, in, sizeof(uint32_t) * 16);

    for (i = num_rounds; i > 0; i -= 2) {
        chacha20_quarterround(x, 0, 4, 8, 12);
        chacha20_quarterround(x, 1, 5, 9, 13);
        chacha20_quarterround(x, 2, 6, 10, 14);
        chacha20_quarterround(x, 3, 7, 11, 15);
        chacha20_quarterround(x, 0, 5, 10, 15);
        chacha20_quarterround(x, 1, 6, 11, 12);
        chacha20_quarterround(x, 2, 7, 8, 13);
        chacha20_quarterround(x, 3, 4, 9, 14);
    }

    for (i = 0; i < 16; i++) {
        x[i] += in[i];
    }

    chacha20_serialize(x, out);
}

// https://tools.ietf.org/html/rfc7539#section-2.3
static void chacha20_init_state(uint32_t s[16], const uint8_t key[32], const uint32_t counter, const uint8_t nonce[12]) {
    int i;

    // refer: https://dxr.mozilla.org/mozilla-beta/source/security/nss/lib/freebl/chacha20.c
    // convert magic number to string: "expand 32-byte k"
    s[0] = 0x61707865;
    s[1] = 0x3320646e;
    s[2] = 0x79622d32;
    s[3] = 0x6b206574;

    for (i = 0; i < 8; i++) {
        s[4 + i] = u8t32le(key + i * 4);
    }

    s[12] = counter;

    for (i = 0; i < 3; i++) {
        s[13 + i] = u8t32le(nonce + i * 4);
    }
}

void ChaCha20XOR(const uint8_t* key, const uint32_t counter, const uint8_t* nonce, const uint8_t* in, uint8_t* out, const int inlen) {

    uint32_t s[16];
    uint8_t block[64];

    chacha20_init_state(s, key, counter, nonce);

    for (int i = 0; i < inlen; i += 64) {
        chacha20_block(s, block, 20);
        s[12]++;

        for (int j = i; j < i + 64; j++) {
            printf("%d: %d\n", j, in[j]);
            if (j >= inlen) {
                break;
            }
            out[j] = in[j] ^ block[j - i];
        }
    }
}