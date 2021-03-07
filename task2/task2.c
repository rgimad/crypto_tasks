#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../mars.h"

#define BLK_BYTES 16

int round_up_to(int num, int multiple) {
    assert(multiple);
    return ((num + multiple - 1) / multiple) * multiple;
}

// TODO xor_block function

size_t get_hash(const char *plain_text, char **hash_text_ptr) {
    size_t plain_text_len = strlen(plain_text);
    //
    return hash_text_len;
}