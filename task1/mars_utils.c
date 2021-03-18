#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "mars_utils.h"

static int round_up_to(int num, int multiple) {
    assert(multiple);
    return ((num + multiple - 1) / multiple) * multiple;
}

static void xor_block(uint8_t *dst, uint8_t *src, size_t len) {
    for (size_t i = 0; i < len; i++) {
        *(dst + i) ^= *(src + i);
    }
}

size_t mars_ecb_encrypt_text(const char *plain_text, char **encrypted_text_ptr) {
    size_t plain_text_len = strlen(plain_text);
    size_t encrypted_text_len = round_up_to(plain_text_len, 16);
    *encrypted_text_ptr = (char*)malloc(encrypted_text_len);
    size_t full_blocks = plain_text_len / 16;
    size_t remainder_len = plain_text_len % 16;
    for (size_t i = 0; i < full_blocks; i++) {
        encrypt((uint32_t*)(plain_text + i*16), (uint32_t*)(*encrypted_text_ptr + i*16));
    }
    if (remainder_len == 0) { return encrypted_text_len; }
    char remainder[16] = {0};
    for (size_t i = 0; i < remainder_len; i++) {
        remainder[i] = plain_text[full_blocks*16 + i];
    }
    encrypt((uint32_t*)remainder, (uint32_t*)(*encrypted_text_ptr + full_blocks*16));
    return encrypted_text_len;
}

char* mars_ecb_decrypt_text(const char *encrypted_text, size_t encrypted_text_len) {
    char *decryped_text = (char*)malloc(encrypted_text_len);
    size_t blocks = encrypted_text_len / 16;
    for (size_t i = 0; i < blocks; i++) {
        decrypt((uint32_t*)(encrypted_text + i*16), (uint32_t*)(decryped_text + i*16));
    }
    return decryped_text;
}

size_t mars_cfb_encrypt_text(const char *plain_text, char **encrypted_text_ptr) {
    size_t plain_text_len = strlen(plain_text);
    size_t encrypted_text_len = round_up_to(plain_text_len, 16);
    *encrypted_text_ptr = (char*)malloc(encrypted_text_len);
    size_t full_blocks = plain_text_len / 16;
    size_t remainder_len = plain_text_len % 16;
    uint32_t c_iv[4] = {0};
    if (full_blocks == 0) goto enc_rem;

    /* enc[i] = E(enc[i - 1]) ^ plain[i] */
    encrypt(c_iv, (uint32_t*)*encrypted_text_ptr);
    xor_block((uint8_t*)*encrypted_text_ptr, (uint8_t*)plain_text, 16);
    for (size_t i = 1; i < full_blocks; i++) {
        encrypt((uint32_t*)(*encrypted_text_ptr + (i - 1)*16), (uint32_t*)(*encrypted_text_ptr + i*16));
        xor_block((uint8_t*)(*encrypted_text_ptr + i*16), (uint8_t*)(plain_text + i*16), 16);
    }

enc_rem:
    if (remainder_len == 0) { return encrypted_text_len; }
    char remainder[16] = {0};
    for (size_t i = 0; i < remainder_len; i++) {
        remainder[i] = plain_text[full_blocks*16 + i];
    }
    encrypt( full_blocks == 0 ? c_iv : (uint32_t*)(*encrypted_text_ptr + (full_blocks - 1)*16), (uint32_t*)(*encrypted_text_ptr + full_blocks*16));
    xor_block((uint8_t*)(*encrypted_text_ptr + full_blocks*16), (uint8_t*)remainder, 16);
    return encrypted_text_len;
}

char* mars_cfb_decrypt_text(const char *encrypted_text, size_t encrypted_text_len) {
    char *decryped_text = (char*)malloc(encrypted_text_len);
    size_t blocks = encrypted_text_len / 16;
    uint32_t c_iv[4] = {0};
    /* dec[i] = D(enc[i - 1]) ^ enc[i] */
    encrypt(c_iv, (uint32_t*)decryped_text);
    xor_block((uint8_t*)decryped_text, (uint8_t*)encrypted_text, 16);
    for (size_t i = 1; i < blocks; i++) {
        encrypt((uint32_t*)(encrypted_text + (i - 1)*16), (uint32_t*)(decryped_text + i*16));
        xor_block((uint8_t*)(decryped_text + i*16), (uint8_t*)(encrypted_text + i*16), 16);
    }
    return decryped_text;
}
