#include "attack.h"
#include "wordlist.h"
#include "hash_utils.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Thread argument structure for the wordlist
typedef struct
{
    char **words;
    size_t start_idx;
    size_t end_idx;
    const char *target_hash;
    hash_type_t hash_type;
    bool *found;
    char *result;
    size_t result_size;
    pthread_mutex_t *mutex;
    int thread_id;
}thread_args_t;

void *wordlist_worker_thread(void *arg){
    thread_args_t *args = (thread_args_t*)arg;
    size_t attempts = 0;

    for(size_t i = args->start_idx; i < args->end_idx; i++){
        //Checking if another thread found it
        pthread_mutex_lock(args->mutex);
        bool already_found = *args->found;
        pthread_mutex_unlock(args->mutex);

        if(already_found){
            printf("Thread %d stopping (password found by another thread)\n", args->thread_id);
            return NULL;
        }

        attempts++;

        if(hash_verify(args->hash_type, args->words[i], args->target_hash)){
            pthread_mutex_lock(args->mutex);
            if(!*args->found){
                *args->found = true;
                strncpy(args->result, args->words[i], args->result_size - 1);
                args->result[args->result_size - 1] = '\0';
                printf("\n[SUCCESS]\n");
                printf("Password found: %s\n", args->words[i]);
                printf("Attempts: %zu\n", attempts);
            }
            pthread_mutex_unlock(args->mutex);
            return NULL;
        }

        // Progress indicator 

        if(attempts % 100000 == 0){
            printf("Attempts: %zu\n", attempts);
        } 
    }

    printf("Work finished. No match!\n");
    return NULL;
}

void wordlist_attack_mt(const char *wordlist_path, const char *target_hash, hash_type_t hash_type, int num_threads){

    if(num_threads < 1) num_threads = 1;
    if(num_threads > 16) num_threads = 16;

    printf("\n === Starting Multithreaded Wordlist Attack ===\n");
    printf("Threads: %d\n", num_threads);
    printf("Target Hash: %s", target_hash);

    clock_t start = clock();

    // Loading the entire wordlist into memory
    size_t word_count;
    char **words = wordlist_load_all(wordlist_path, &word_count);
    if(!words){
        fprintf(stderr, "Failed to load wordlist\n");
        return;
    }

    bool found = false;
    char result[256] = {0};
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_t threads[num_threads];
    thread_args_t args[num_threads];
    size_t words_per_thread = word_count / num_threads;

    printf("Starting %d worker threads...\n\n", num_threads);

    //Create the worker threads
    for(int i = 0; i < num_threads; i++){
        args[i].words = words;
        args[i].start_idx = i * words_per_thread;
        args[i].end_idx = (i == num_threads - 1) ? word_count : (i + 1) * words_per_thread;
        args[i].target_hash = target_hash;
        args[i].hash_type = hash_type;
        args[i].found = &found;
        args[i].result = result;
        args[i].result_size = sizeof(result);
        args[i].mutex = &mutex;
        args[i].thread_id = i;

        pthread_create(&threads[i], NULL, wordlist_worker_thread, &args[i]);
    }

    printf("\n");

    //Wait for all the threads to complete
    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("=== Attack Complete === \n\n");

    if(found){
        printf("Password found: %s\n", result);
    }
    else{
        printf("Password not found in the wordlist!\n");
    }
    printf("Time elapsed: %.2f sec\n", time_spent);
    printf("Total attempts: %zu\n", word_count);
    printf("Speed: %.0f password/second", word_count / time_spent);

    pthread_mutex_destroy(&mutex);
    wordlist_free_all(words, word_count);
    
}

void wordlist_attack_st(const char *wordlist_path, const char *target_hash, hash_type_t hash_type){

    printf("\n === Starting Single-Threaded Wordlist Attack === \n");
    printf("Target Hash: %s \n\n", target_hash);

    clock_t start = clock();

    wordlist_t *wl = wordlist_open(wordlist_path);
    if(!wl){
        fprintf(stderr, "Failed to open wordlist!\n");
        return;
    }

    char buffer[256];
    size_t attempts = 0;

    while(wordlist_next_to_buffer(wl, buffer, sizeof(buffer))) {
        attempts++;

        if(hash_verify(hash_type, buffer, target_hash)){
            clock_t end = clock();
            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

            printf("\n=== Attack Completed ===\n");
            printf("Password found: %s\n",buffer);
            printf("Time Elapsed: %.2f\n", time_spent);
            printf("Attempts: %zu\n", attempts);

            wordlist_close(wl);
            return;
        }

        if(attempts % 10000 == 0){
            printf("Attempted %zu passwords", attempts);
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n === Attack Completed ===\n");
    printf("Password not found in wordlist!\n");
    printf("Time Elapsed: %.2f", time_spent);
    printf("Password Tried: %zu", attempts);

    wordlist_close(wl);
    
}
