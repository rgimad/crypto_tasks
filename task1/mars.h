#ifndef _MARS_H
#define _MARS_H

#include "stdint.h"

/*uint32_t gen_mask(uint32_t x);*/
uint32_t *set_key(const uint32_t in_key[], const uint32_t key_len);
void encrypt(const uint32_t in_blk[4], uint32_t out_blk[4]);
void decrypt(const uint32_t in_blk[4], uint32_t out_blk[4]);


#endif /* _MARS_H */