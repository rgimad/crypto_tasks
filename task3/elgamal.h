#ifndef _ELGAMAL_H
#define _ELGAMAL_H

#include <gmp.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include "../task2/hash.h"

typedef struct elgamal_pub_t {
    mpz_t p, q, g, y;
} elgamal_pub_t;

typedef struct elgamal_ctx_t {
    elgamal_pub_t pub_key;
    mpz_t priv_key;
} elgamal_ctx_t;

typedef struct elgamal_sgn_t {
    mpz_t r, s;
} elgamal_sgn_t;

elgamal_ctx_t elgamal_create_context();
elgamal_sgn_t elgamal_sign_msg(elgamal_ctx_t ctx, char *message);
int elgamal_sign_check(elgamal_sgn_t sgn, elgamal_pub_t pub_key, char *message);


#endif /* _ELGAMAL_H */