#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../task1/mars_utils.h"

int main(int argc, char **argv) {
    char text[] = "Gimadutdinov Rustem Maratovich 09-712";

    uint32_t key[] = {0x12345678, 0x23456789, 0x3456789A, 0x456789AB};
    set_key(key, 128);
    printf("key: %x %x %x %x\n", key[0], key[1], key[2], key[3]);

    char *enc, *dec;
    int enc_len;

    printf("plain text: '%s'\n", text);
    enc_len = mars_cfb_encrypt_text(text, &enc);
    puts("encrypted (cfb):");
    for (int i = 0; i < enc_len; i++) { putchar(enc[i]); }
    dec = mars_cfb_decrypt_text(enc, enc_len);
    printf("\ndecrypted (cfb): '%s'\n", dec);

    free(enc);
    free(dec);
}