#include "hash.h"

static void xor_block(uint8_t *dst, uint8_t *src, size_t len) {
    for (size_t i = 0; i < len; i++) {
        *(dst + i) ^= *(src + i);
    }
}

void hash_block(const uint32_t M[4], uint32_t h[4]) {
    uint32_t buf[4];
    set_key(h, 128);
    encrypt(M, buf);
    xor_block((uint8_t*)buf, (uint8_t*)M, 16); // 128 bits is 16 bytes
    xor_block((uint8_t*)buf, (uint8_t*)h, 16);
    memcpy((uint8_t*)h, (uint8_t*)buf, 16);
}

void hash_text(const char *plain_text, uint32_t hash[4]) {
    size_t plain_text_len = strlen(plain_text);
    size_t full_blocks = plain_text_len / 16;
    size_t remainder_len = plain_text_len % 16;
    memset(hash, 0, 16);
    for (size_t i = 0; i < full_blocks; i++) {
        hash_block((uint32_t*)(plain_text + i*16), hash);
    }
    if (remainder_len == 0) { return; }
    char remainder[16] = {0};
    for (size_t i = 0; i < remainder_len; i++) {
        remainder[i] = plain_text[full_blocks*16 + i];
    }
    hash_block((uint32_t*)remainder, hash);
}
