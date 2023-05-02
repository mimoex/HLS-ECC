#include <stdint.h>
#include <string.h>

static inline void u32t8le(const uint32_t v, uint8_t p[4]) {
#pragma HLS INLINE
    p[0] = v & 0xff;
    p[1] = (v >> 8) & 0xff;
    p[2] = (v >> 16) & 0xff;
    p[3] = (v >> 24) & 0xff;
}

static inline uint32_t u8t32le(const uint8_t p[4]) {
#pragma HLS INLINE
    uint32_t value = p[3];

    value = (value << 8) | p[2];
    value = (value << 8) | p[1];
    value = (value << 8) | p[0];

    return value;
}

static inline uint32_t rotl32(const uint32_t x, const int n) {
#pragma HLS INLINE
    // http://blog.regehr.org/archives/1063
    //return x << n | (x >> (-n & 31));
	return (x << n) ^ (x >> (32 - n));
}

// https://tools.ietf.org/html/rfc7539#section-2.1
static inline void chacha20_quarterround(uint32_t* x, const int a, const int b, const int c, const int d) {
#pragma HLS INLINE
    uint32_t t1 = x[a];
    uint32_t t2 = x[b];
    uint32_t t3 = x[c];
    uint32_t t4 = x[d];

    t1 += t2;
    t4 ^= t1;
    t4 = rotl32(t4, 16);

    t3 += t4;
    t2 ^= t3;
    t2 = rotl32(t2, 12);

    t1 += t2;
    t4 ^= t1;
    t4 = rotl32(t4, 8);

    t3 += t4;
    t2 ^= t3;
    x[b] = rotl32(t2, 7);

    x[a] = t1;
    x[c] = t3;
    x[d] = t4;
}

static inline void chacha20_serialize(const uint32_t in[16], uint8_t output[64]) {
#pragma HLS INLINE
    serialize_loop:for (int i = 0; i < 16; i++) {
#pragma HLS UNROLL factor=4
        u32t8le(in[i], output + (i << 2));
    }
}

static void chacha20_block(const uint32_t in[16], uint8_t out[64]) {
    int i;
    const int num_rounds = 20;
    uint32_t x[16];

    //memcpy(x, in, sizeof(uint32_t) * 16);
    copy:for(i=0;i<16;i++){
#pragma HLS UNROLL
    	x[i]=in[i];
    }


    chacha_loop:for (i = num_rounds; i > 0; i -= 2) {
#pragma HLS PIPELINE off
        chacha20_quarterround(x, 0, 4, 8, 12);
        chacha20_quarterround(x, 1, 5, 9, 13);
        chacha20_quarterround(x, 2, 6, 10, 14);
        chacha20_quarterround(x, 3, 7, 11, 15);
        chacha20_quarterround(x, 0, 5, 10, 15);
        chacha20_quarterround(x, 1, 6, 11, 12);
        chacha20_quarterround(x, 2, 7, 8, 13);
        chacha20_quarterround(x, 3, 4, 9, 14);
    }

    add_loop:for (i = 0; i < 16; i++) {
#pragma HLS UNROLL
        x[i] += in[i];
    }

    chacha20_serialize(x, out);
}

// https://tools.ietf.org/html/rfc7539#section-2.3
static void chacha20_init_state(uint32_t s[16], const uint8_t key[32], const uint32_t counter, const uint8_t nonce[12]) {
	int i;
	uint8_t kv[32];
	uint8_t nv[12];

	key_copy:for(i=0;i<32;i++){
#pragma HLS UNROLL
		kv[i]=key[i];
	}
	nonce_copy:for(i=0;i<12;i++){
#pragma HLS UNROLL
			nv[i]=nonce[i];
		}

    // refer: https://dxr.mozilla.org/mozilla-beta/source/security/nss/lib/freebl/chacha20.c
    // convert magic number to string: "expand 32-byte k"
    s[0] = 0x61707865;
    s[1] = 0x3320646e;
    s[2] = 0x79622d32;
    s[3] = 0x6b206574;

    uint8_t t[4];

    init_first:for (i = 0; i < 8; i++) {
#pragma HLS PIPELINE off
        t[0] = kv[i * 4];
        t[1] = kv[i * 4 + 1];
        t[2] = kv[i * 4 + 2];
        t[3] = kv[i * 4 + 3];
        s[4 + i] = u8t32le(t);
    }

    s[12] = counter;

    init_second:for (i = 0; i < 3; i++) {
#pragma HLS PIPELINE
        t[0] = nv[i * 4];
        t[1] = nv[i * 4 + 1];
        t[2] = nv[i * 4 + 2];
        t[3] = nv[i * 4 + 3];
        s[13 + i] = u8t32le(t);
    }
}
void ChaCha20XOR(const uint8_t key[32], const uint32_t counter, const uint8_t nonce[12], const uint8_t in[114], uint8_t out[114], const int inlen)
{
#pragma HLS INTERFACE mode=s_axilite port=inlen
#pragma HLS INTERFACE mode=s_axilite port=out
#pragma HLS INTERFACE mode=s_axilite port=in
#pragma HLS INTERFACE mode=s_axilite port=nonce
#pragma HLS INTERFACE mode=s_axilite port=counter
#pragma HLS INTERFACE mode=s_axilite port=key
#pragma HLS INTERFACE mode=s_axilite port=return
    uint32_t s[16];
    uint8_t block[64];

    chacha20_init_state(s, key, counter, nonce);

    outer:for (int i = 0; i < inlen; i += 64) {
#pragma HLS PIPELINE off
        chacha20_block(s, block);
        s[12]++;

        inner:for (int j = i; j < i + 64; j++) {
#pragma HLS PIPELINE off
            if (j >= inlen) {
                break;
            }
            out[j] = in[j] ^ block[j - i];
        }
    }
}
