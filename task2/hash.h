#ifndef _HASH_H
#define _HASH_H

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../task1/mars.h"

void hash_block(const uint32_t M[4], uint32_t h[4]);
void hash_text(const char *plain_text, uint32_t hash[4]);


#endif /* _HASH_H */