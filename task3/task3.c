#include <stdio.h>
#include <string.h>
#include "elgamal.h"

int main() {
	char msg1[] = "Gimadutdinov Rustem Maratovich 09-712";
	char msg1_[] = "Gimadutdinov Rustem Maratovich 09-712 .";
	elgamal_ctx_t ctx1 = elgamal_create_context();
	elgamal_sgn_t sgn1 = elgamal_sign_msg(ctx1, msg1);
	printf("\n\n\nmsg1 was signed\n");

	int check_res1 = elgamal_sign_check(sgn1, ctx1.pub_key, msg1);
	printf("  check result for msg1 with DS of msg1 = %s\n", check_res1 == 0 ? "FAKE" : "REAL");

	int check_res2 = elgamal_sign_check(sgn1, ctx1.pub_key, msg1_);
	printf("  check result for msg1_ with DS of msg1 = %s\n", check_res2 == 0 ? "FAKE" : "REAL");
}