#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <stdio.h>

char lower_character_brute(int min, int max, int threads);
char num_brute(int min, int max, int threads);
char upper_character_brute(int min, int max, int threads);
char mixed_character_brute(int min, int max, int threads);
char mixed_character_num_brute(int min, int max, int threads);
int total_combinations(size_t len); 

#endif