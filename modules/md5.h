#ifndef MD5_H
#define MD5_H

#include <stdbool.h>
#include <stddef.h>

// Validate MD5 hash format (32 hex chars)
bool is_valid_md5_hash(const char *hash);

// Compute MD5 hash of candidate and return as hex string
int md5_compute_hex(const char *candidate, char *out_hex, size_t out_hex_len);

// Verify if candidate matches target MD5 hash
bool md5_verify(const char *candidate, const char *target_hash);

#endif