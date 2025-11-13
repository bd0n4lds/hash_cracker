#ifndef SHA256_H
#define SHA256_H

#include <stdbool.h>
#include <stddef.h>

bool is_valid_sha256_hash(const char *hash);
int sha256_compute_hex(const char *candidate, char *out_hex, size_t out_hex_len);
bool sha256_verify(const char *candidate, const char *target_hash);

#endif