#include "hash_utils.h"
#include "usage.h"
#include "bcrypt.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "sha512.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

hash_type_t hash_type_from_string(const char *hash_type){

   if(!hash_type){
      fprintf(stderr, "Cannot leave the hash mode empty!\n");
      return UNKNOWN_HASH;
   }

   if(isdigit((unsigned char)hash_type[0])) { // If user enters the numeric code for the mode it checks with this
      int mode = atoi(hash_type);

      switch (mode)
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
         return UNKNOWN_HASH;
         break;
      }
   }

   //Case 2: if user enters the name (md5, argon2, bcrypt...)
   char mode_string[32];
   int i;
   for (i = 0; hash_type[i] && i < (int)sizeof(mode_string) - 1; i++) {
      mode_string[i] = tolower((unsigned char)hash_type[i]);
   }
   mode_string[i] = '\0';

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

bool is_valid_hash(hash_type_t type, const char *hash){

   switch (type)
   {
   case HASH_MD5:
      return is_valid_md5_hash(hash);
      break;
   case HASH_SHA1:
      return is_valid_sha1_hash(hash);
      break;
   case HASH_SHA256:
      return is_valid_sha256_hash(hash);
      break;
   case HASH_SHA512:
      return is_valid_sha512_hash(hash);
      break;
   case HASH_BCRYPT:
      return is_valid_bcrypt_hash(hash);
      break;
   case HASH_ARGON2: 
      return (strncmp(hash, "$argon2", 7) == 0);
      default:
         fprintf(stderr, "Invalid hash type!\n");
         return false;
   }

}



int hash_compute_hex(hash_type_t type, const char *candidate, char *out_hex, size_t out_hex_len){

   switch (type)
   {
   case HASH_MD5:
      return md5_compute_hex(candidate, out_hex, out_hex_len);
      break;
   case HASH_SHA1:
      return sha1_compute_hex(candidate, out_hex, out_hex_len);
      break;
   case HASH_SHA256:
      return sha256_compute_hex(candidate, out_hex, out_hex_len);
      break;
   case HASH_SHA512:
      return sha512_compute_hex(candidate, out_hex, out_hex_len);
      break;
   default:
      fprintf(stderr, "Invalid hash type!\n");
      return -1;
      break;
   }

}



bool hash_verify(hash_type_t type, const char *candidate, const char *target_hash){

   switch(type){
   case HASH_MD5:
      return md5_verify(candidate, target_hash);
      break;
   case HASH_SHA1:
      return sha1_verify(candidate, target_hash);
      break;
   case HASH_SHA256:
      return sha256_verify(candidate, target_hash);
      break;
   case HASH_SHA512:
      return sha512_verify(candidate, target_hash);
      break;
   case HASH_BCRYPT:
      return bcrypt_verify(candidate, target_hash);
      break;
   case HASH_ARGON2:
      // Assuming the standard argon2 library interface
      return (argon2_verify(target_hash, candidate, strlen(candidate)) == 0);
      default:
         fprintf(stderr, "Error: Unsupported or invalid hash type!\n");
         return false; // Return false for security
   }

}