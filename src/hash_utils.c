#include "hash_utils.h"
#include "usage.h"
#include "bcrypt.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <openssl/md5.h>
#include <openssl/sha.h>
#include <crypt.h>
#include <argon2.h>

/*
TODO List for hash_utils.c:

1. Core Hash Functions:
   - Implement for each type:
     * MD5_hash(input, output)
     * SHA1_hash(input, output)
     * SHA256_hash(input, output)
   - Use OpenSSL if available
   - Fall back to minimal impl if needed

2. Validation & Comparison:
   - Implement compare_hash():
     * Normalize case
     * Handle different lengths
     * Constant-time compare
   
   - Implement is_valid_hash():
     * Check length
     * Verify hex chars
     * Validate format

3. Helper Functions:
   - hex_to_bytes conversion
   - Case normalization
   - Length validation
   
4. Tests to Write:
- Known test vectors
- Case insensitive compare
- Invalid inputs
- Each hash type
*/


hash_type_t hash_type_from_string(const char *hash_type){

   if(!hash_type){
      fprintf(stderr, "Cannot leave the hash mode empty!\n");
      return 1;
   }

   if(isdigit((unsigned char)hash_type[0])) { // If user enters the numeric code for the mode it checks with this
      int mode = atoi(hash_type);

      switch (*hash_type)
      {
      case 1:
         return HASH_MD5;
         break;
      case 2:
         return HASH_SHA1;
         break;
      case 3:
         return HASH_SHA256;
         break;
      case 4:
         return HASH_SHA512;
         break;
      case 5:
         return HASH_BCRYPT;
         break;
      case 6:
         return HASH_ARGON2;
         break;
      default:
         fprintf(stderr, "Unknown hash type: %s\n", hash_type);
         fprintf(stderr, "Valid types:\n");
         usage_big_hashmodes();
         return 1;
         break;
      }
   }

   //Case 2: if user enters the name (md5, argon2, bcrypt...)
   char mode_string = tolower(hash_type);
   if(strcmp(mode_string, "md5") == 0) return HASH_MD5;
   if(strcmp(mode_string, "sha1") == 0) return HASH_SHA1;
   if(strcmp(mode_string, "sha256") == 0) return HASH_SHA256;
   if(strcmp(mode_string, "sha512") == 0) return HASH_SHA512;
   if(strcmp(mode_string, "bcrypt") == 0) return HASH_BCRYPT;
   if(strcmp(mode_string, "argon2") == 0) return HASH_ARGON2;

   // If the arg is not recognized
   fprintf(stderr, "Unknown hash type: %s\n", hash_type);
   fprintf(stderr, "Valid types:\n");
   usage_big_hashmodes();
   return UNKNOWN_HASH;
}


size_t get_hash_length(hash_type_t mode){
   //this function will return the hex length of the hashing algorithm except if they are argon2 or bcrypt cause they don't have fixed hex lengths
   switch (mode)
   {
   case HASH_MD5:
      return MD5_HEX_LENGTH;
      break;
   case HASH_SHA1:
      return SHA1_HEX_LENGTH;
      break;
   case HASH_SHA256:
      return SHA256_HEX_LENGTH;
      break;
   case HASH_SHA512:
      return SHA512_HEX_LENGTH;
      break;
   default:
      return 0;
   }
}