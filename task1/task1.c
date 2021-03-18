#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mars_utils.h"

int main(int argc, char **argv) {
    char text[] = "Hello world! Mars cipher! Lorem ipsum lorem ipsum veni vidi vici linux ubuntu top !";

    set_key((uint32_t[]){0x12345678, 0x23456789, 0x3456789A, 0x456789AB}, 128);

    char *enc, *dec;
    int enc_len;

    //enc_len = mars_ecb_encrypt_text(text, &enc); dec = mars_ecb_decrypt_text(enc, enc_len); printf("dec (ecb) = '%s'\n", dec);

    enc_len = mars_cfb_encrypt_text(text, &enc); dec = mars_cfb_decrypt_text(enc, enc_len); printf("dec (cfb) = '%s'\n", dec);

    free(enc);
    free(dec);
}