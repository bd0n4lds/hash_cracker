#ifndef ATTACK_H
#define ATTACK_H

#include "hash_utils.h"
#include <stdbool.h>

// Multithreaded wordlist attack (mt = multithread)
void wordlist_attack_mt(const char *wordlist_path,
                        const char *target_hash,
                        hash_type_t compare_func,
                        int num_threads);

// Singlethreaded wordlist attack (st = singlethread)
void wordlist_attack_st(const char *wordlist_path,
                        const char *target_hash,
                        hash_type_t compare_func);

#endif