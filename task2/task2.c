#include <stdio.h>
#include <string.h>
#include "hash.h"

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
