#ifndef _MARS_UTILS_H
#define _MARS_UTILS_H

#include "mars.h"

size_t mars_ecb_encrypt_text(const char *plain_text, char **encrypted_text_ptr);
char* mars_ecb_decrypt_text(const char *encrypted_text, size_t encrypted_text_len) ;
size_t mars_cfb_encrypt_text(const char *plain_text, char **encrypted_text_ptr);
char* mars_cfb_decrypt_text(const char *encrypted_text, size_t encrypted_text_len);


#endif /* _MARS_UTILS_H */