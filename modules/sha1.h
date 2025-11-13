#ifndef SHA1_H
#define SHA1_H

#include <stdbool.h>
#include <stddef.h>

bool is_valid_sha1_hash(const char *hash);
int sha1_compute_hex(const char *candidate, char *out_hex, size_t out_hex_len);
bool sha1_verify(const char *candidate, const char *target_hash);

#endif