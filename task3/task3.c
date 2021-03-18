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


/* Sets r to a random GMP integer with the specified number of bits. */
void get_random_n_bits(mpz_t r, size_t bits) {
	size_t size = (size_t) ceilf(bits/8);
	char *buffer = (char*) malloc(sizeof(char)*size);
	int prg = open("/dev/urandom", O_RDONLY);
	read(prg, buffer, size);
	close(prg);
	mpz_import (r, size, 1, sizeof(char), 0, 0, buffer);
	free(buffer);
}

/* Sets r to a random GMP integer smaller than max. */
void get_random_n(mpz_t r, mpz_t max) {
	int cnt = 0;
	do {
		get_random_n_bits(r, mpz_sizeinbase(max, 2));
		cnt++;
	} while (mpz_cmp(r, max) >= 0);
	printf("cnt = %d\n", cnt);
}

char message[] = "Gimadutdinov Rustem Maratovich 09-712";

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
	printf("p length is %lu bits\n", mpz_sizeinbase(p, 2));

	mpz_t tmp; mpz_init(tmp);
	mpz_t res; mpz_init(res);
	mpz_sub_ui(tmp, p, 1);
	gmp_printf("p - 1 = %Zd\n", tmp);

	mpz_mod(res, tmp, q); // res = tmp % q;
	gmp_printf("(p - 1) mod q = %Zd\n", res);

	mpz_t g; mpz_init(g);
	get_random_n_bits(g, 128); 	// g = random 128 bit >= 1
	mpz_fdiv_q(res, tmp, q); // res = tmp / q  ; f means floor
	mpz_powm(g, g, res, p);
	gmp_printf("g = %Zd\n", g);
	//printf("g length is %lu bits\n", mpz_sizeinbase(g, 2));

	mpz_t x; mpz_init(x);
	get_random_n(x, q);
	gmp_printf("x = %Zd\n", x);

	mpz_t y; mpz_init(y);
	mpz_powm(y, g, x, p);
	gmp_printf("y = %Zd\n", y);
	//printf("y length is %lu bits\n", mpz_sizeinbase(y, 2));

	mpz_t k; mpz_init(k);
	get_random_n_bits(k, 128);

	mpz_t r; mpz_init(r);
	mpz_powm(r, g, k, p);
	gmp_printf("r = %Zd\n", r);
	printf("r length is %lu bits\n", mpz_sizeinbase(r, 2));

	mpz_t ro; mpz_init(ro);
	mpz_mod(ro, r, q);
	gmp_printf("ro = %Zd\n", ro);

	uint32_t hash_arr[4];
	hash_text(message, hash_arr);
	printf("hash is %x %x %x %x\n", hash_arr[0], hash_arr[1], hash_arr[2], hash_arr[3]);

	mpz_t h; mpz_init(h);
	mpz_import(h, 16/*bytes = 128bit*/, 1, sizeof(char), 0, 0, hash_arr);

	gmp_printf("h = %Zd\n", h);
	//printf("h length is %lu bits\n", mpz_sizeinbase(h, 2));

	mpz_t s; mpz_init(s);
	mpz_mul(s, ro, h);
	mpz_mul(s, s, k);
	mpz_sub(s, s, x);
	mpz_mod(s, s, q);
	gmp_printf("s = %Zd\n", s);
	printf("s length is %lu bits\n", mpz_sizeinbase(s, 2));

	// Checking:
	mpz_t left; mpz_init(left);
	mpz_mul(tmp, ro, h);
	mpz_powm(left, r, tmp, p);
	gmp_printf("left = %Zd\n", left);

	mpz_t right; mpz_init(right);
	mpz_powm(right, g, s, p);
	mpz_mod(tmp, y, p);
	mpz_mul(right, right, tmp);
	mpz_mod(right, right, p);
	gmp_printf("righ = %Zd\n", right);


}