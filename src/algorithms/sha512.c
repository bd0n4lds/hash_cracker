#define _GNU_SOURCE

#include "sha512.h"
#include <openssl/evp.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

bool is_valid_sha512_hash(const char *hash) {
    if (!hash) return false;
    if (strlen(hash) != 128) return false;
    
    for (int i = 0; i < 128; i++) {
        if (!isxdigit(hash[i])) return false;
    }
    return true;
}

int sha512_compute_hex(const char *candidate, char *out_hex, size_t out_hex_len) {
    if (!candidate || !out_hex || out_hex_len < 129) return -1;
    
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if(!ctx){
        return -1;
    }
    
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    if (!EVP_DigestInit_ex(ctx, EVP_sha512(), NULL) || !EVP_DigestUpdate(ctx, candidate, strlen(candidate)) || !EVP_DigestFinal_ex(ctx, hash, &hash_len)) {
        EVP_MD_CTX_free(ctx);
        return -1;
    }

    EVP_MD_CTX_free(ctx);

    // Converting to hex
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(&out_hex[i*2], "%02x", hash[i]);
    }
    out_hex[128] = '\0';
    
    return 0;
}

bool sha512_verify(const char *candidate, const char *target_hash) {
    char computed[129];
    
    if (sha512_compute_hex(candidate, computed, sizeof(computed)) != 0) {
        return false;
    }
    
    return strcasecmp(computed, target_hash) == 0;
}