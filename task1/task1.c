#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "mars.h"

#define BLK_BYTES 16

int round_up_to(int num, int multiple) {
    assert(multiple);
    return ((num + multiple - 1) / multiple) * multiple;
}

size_t mars_encrypt_text(const char *plain_text, char **encrypted_text_ptr) {
    size_t plain_text_len = strlen(plain_text);
    size_t encrypted_text_len = round_up_to(plain_text_len, BLK_BYTES);
    *encrypted_text_ptr = (char*)malloc(encrypted_text_len);
    size_t full_blocks = plain_text_len / BLK_BYTES;
    size_t remainder_len = plain_text_len % BLK_BYTES;

    for (size_t i = 0; i < full_blocks; i++) {
        encrypt((uint32_t*)(plain_text + i*BLK_BYTES), (uint32_t*)(*encrypted_text_ptr + i*BLK_BYTES));
    }
    if (remainder_len == 0) { return encrypted_text_len; }
    char remainder[BLK_BYTES] = {0};
    for (size_t i = 0; i < remainder_len; i++) {
        remainder[i] = plain_text[full_blocks*BLK_BYTES + i];
    }

    encrypt((uint32_t*)remainder, (uint32_t*)(*encrypted_text_ptr + full_blocks*BLK_BYTES));

    return encrypted_text_len;
}

char* mars_decrypt_text(const char *encrypted_text, size_t encrypted_text_len) {
    char *decryped_text = (char*)malloc(encrypted_text_len);
    size_t blocks = encrypted_text_len / BLK_BYTES;

    for (size_t i = 0; i < blocks; i++) {
        decrypt((uint32_t*)(encrypted_text + i*BLK_BYTES), (uint32_t*)(decryped_text + i*BLK_BYTES));
    }
    return decryped_text;
}

int main(int argc, char **argv) {
    char text[] = "Hello world! Mars cipher! Lorem ipsum lorem ipsum veni vidi vici linux ubuntu top !";

    set_key((uint32_t[]){0x12345678, 0x23456789, 0x3456789A, 0x456789AB}, 128);

    char *enc;
    int enc_len = mars_encrypt_text(text, &enc);

    char *dec = mars_decrypt_text(enc, enc_len);
    printf("dec = '%s'\n", dec);

    free(enc);
    free(dec);
}