#include "usage.h"

#include <stdio.h>

static const char *const USAGE_MINI[] = {
"Usage: ./hash_cracker --hash=[hash|hashfile] --hash-type=001 --wordlist=[wordlist|directory]",
"Usage: ./hash_cracker -H [hash|hashfile] -m MD5 -w [wordlist|directory]",
"Help: ./hash_cracker --help or ./hash_cracker -help or ./hash_cracker -h"
};

static const char *const USAGE_BIG_OPTIONS[] = {
"Usage: ./hash_cracker --hash=[hash|hashfile] --hash-type=MD5 --wordlist=[wordlist|directory]",
"Usage: ./hash_cracker -H [hash|hashfile] -m 001 -w [wordlist|directory]",
"",
"",
"Options short/long          |     Type      |           Description              | Example",
"============================+===============+====================================+=========",
"-m, --hash-type=            |    String     | Hash type, ex. MD5 SHA1 SHA256     | -m MD5",
"-H, --hash=                 |  Path/String  | Hash File path or hash itself      | -H /path/to/hash.txt",
"-w, --wordlist=             |     File      | Wordlist file                      | -w /path/to/rockyou.txt",
"-a, --mode                  |     Num       | The mode you want to execute       | -a 0 (dictionary attack)",
"-t, --threads=              |     Num       | Number of threads (1-16, default 4)| -t 8",
"    --types                 |     Menu      | Hash types supported               |",
"-h, --help                  |   Help Menu   | Help Menu (This Menu)              |"
};

static const char *const USAGE_BIG_HASHMODES[] = {
"- [ Attack Modes ] -",
"",
" # | Mode",
"===+============",
"0  | Dictionary",
"1  | Bruteforce",
"",
"",
"- [ Hash Types ] -",
"",
" # | Hash Type  | Hash Length (hex) | Status",
"===+============+===================+===========",
"001| MD5        | 32 characters     | ✓ Ready",
"002| SHA1       | 40 characters     | ✓ Ready",
"003| SHA256     | 64 characters     | ✓ Ready",
"004| SHA512     | 128 characters    | ✓ Ready",
"005| Bcrypt     | 60 characters     | ✓ Ready",
"006| Argon2     | Variable          | ⚠ Coming Soon",
"",
"",
"- [ Examples ] -",
"",
"# Crack MD5 hash with 4 threads (default)",
"./hash_cracker -H 5d41402abc4b2a76b9719d911017c592 -m MD5 -w rockyou.txt",
"",
"# Crack SHA256 hash with 8 threads",
"./hash_cracker -H e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855 \\",
"               -m SHA256 -w wordlist.txt -t 8",
"",
"# Using numeric hash type codes",
"./hash_cracker -H 5d41402abc4b2a76b9719d911017c592 -m 001 -w rockyou.txt -t 4"
};


void usage_big_print(){
    int len = sizeof(USAGE_BIG_OPTIONS) / sizeof(USAGE_BIG_OPTIONS[0]);

    for(int i = 0; i < len; i++){
        printf("%s\n", USAGE_BIG_OPTIONS[i]);
    }
}

void usage_mini_print(){
    int len = sizeof(USAGE_MINI) / sizeof(USAGE_MINI[0]);   

    for(int i = 0; i < len; i++){
        printf("%s\n", USAGE_MINI[i]);
    }
}

void usage_big_hashmodes(){
    int len = sizeof(USAGE_BIG_HASHMODES) / sizeof(USAGE_BIG_HASHMODES[0]);

    for(int i = 0; i < len; i++){
        printf("%s\n", USAGE_BIG_HASHMODES[i]);
    }
}