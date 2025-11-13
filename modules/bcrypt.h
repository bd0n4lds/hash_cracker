#ifndef BCRYPT_H
#define BCRYPT_H

#include <stdbool.h>
#include <stddef.h>

// Core cracking function (REQUIRED)
bool is_valid_bcrypt_hash(const char *hash);
bool bcrypt_verify(const char *candidate, const char *target_hash);

// Utility functions (OPTIONAL - but are good for user feedback)
int bcrypt_get_cost(const char *hash);
void bcrypt_describe_hash(const char *hash, char *desc, size_t desc_len);

#endif