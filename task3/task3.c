#include <gmp.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>


/* Sets r to a random GMP integer with the specified number of bits. */
void get_random_n_bits(mpz_t r, size_t bits)
{
	size_t size = (size_t) ceilf(bits/8);
	char *buffer = (char*) malloc(sizeof(char)*size);
	int prg = open("/dev/random", O_RDONLY);
	read(prg, buffer, size);
	close(prg);
	mpz_import (r, size, 1, sizeof(char), 0, 0, buffer);
	free(buffer);
}

int main() {
	mpz_t q;
	mpz_init(q);
	get_random_n_bits(q, 128);
	gmp_printf("q = %Zd\n", q);
	// p = q*2^128 + 1
	mpz_t p;
	mpz_init(p);
	mpz_ui_pow_ui(p, 2, 128);
	mpz_mul(p, p, q);
	mpz_add_ui(p, p, 1);
	gmp_printf("initial p = %Zd\n", p);
	while (mpz_probab_prime_p(p, 20) == 0) {
		mpz_add(p, p, q);
		mpz_add(p, p, q);
	}
	gmp_printf("p = %Zd\n", p);

	mpz_t tmp; mpz_init(tmp);
	mpz_t res; mpz_init(res);
	mpz_set(tmp, p);
	mpz_sub_ui(tmp, tmp, 1);
	gmp_printf("p - 1 = %Zd\n", tmp);

	mpz_mod(res, tmp, q);
	gmp_printf("(p - 1) mod q = %Zd\n", res);

	// TODO check is g generated correctly?
	mpz_t g; mpz_init(g);
	get_random_n_bits(g, 128); 	// g = random 128 bit >= 1
	mpz_fdiv_q(res, tmp, q); // res = tmp / q  ; f means floor
	mpz_powm(g, g, res, p);
	gmp_printf("g = %Zd\n", g);

}