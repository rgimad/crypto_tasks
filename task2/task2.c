#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../task1/mars.h"

int round_up_to(int num, int multiple) {
    assert(multiple);
    return ((num + multiple - 1) / multiple) * multiple;
}

void xor_block(uint8_t *dst, uint8_t *src, size_t len) {
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

int main(int argc, char **argv) {
    //char text1[] = "privet kak dela u menya vse super klassno";
    //char text2[] = "privet kak dela u menya vse super klassno";
    char text1[128], text2[128];
    puts("Enter text1: ");fgets(text1, sizeof(text1), stdin);
    puts("Enter text2: ");fgets(text2, sizeof(text2), stdin);
    uint32_t hash_text1[4];
    uint32_t hash_text2[4];
    hash_text(text1, hash_text1);
    hash_text(text2, hash_text2);
    if (memcmp(hash_text1, hash_text2, 16) == 0) {
        puts("Strings are equal\n");
    } else {
        puts("Strings are different\n");
    }
}
