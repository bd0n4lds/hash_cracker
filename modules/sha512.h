#ifndef SHA512_H
#define SHA512_H

#include <stdbool.h>
#include <stddef.h>

bool is_valid_sha512_hash(const char *hash);
int sha512_compute_hex(const char *candidate, char *out_hex, size_t out_hex_len);
bool sha512_verify(const char *candidate, const char *target_hash);

#endif