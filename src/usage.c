#include <stdio.h>
#include "usage.h"

static const char *const USAGE_MINI[] = {
"Usage: ./hash_cracker --hash=[ 'hash' |hashfile] --hash-type=001 --wordlist=[wordlist|directory]",
"Usage: ./hash_cracker -H [ 'hash' |hashfile] -m |MD5| -w [wordlist|directory]",
"Help: ./hash_cracker --help or ./hash_cracker -help or ./hash_cracker -h"
};

static const char *const USAGE_BIG_OPTIONS[] = {
"Usage: ./hash_cracker --hash=[hash|hashfile] --hash-type=|MD5| --wordlist=[wordlist|directory]",
"Usage: ./hash_cracker -h [hash|hashfile] -m |001| -w [wordlist|directory]",
"",
"",
"Options short/long          |     Type      |           Description          | Example",
"============================+===============+================================+=========",
"-m, --hash-type=            |    String     | Hash type, ex. MD5 SHA1 SHA256 | -m MD5",
"-H, --hash=                 |  Path/String  | Hash File path or hash itself  | -h /path/to/hash.txt",
"-w, --wordlist=             |     File      | Wordlist file                  | -w /path/to/rockyou.txt",
"-a, --mode                  |     Num       | The mode you want to execute   | -a 1 (dictionary attack)",
"-t, --types                 |     Menu      | Hash types supported           |",
"-h, --help                  |   Help Menu   | Help Menu (This Menu)          |"
};

static const char *const USAGE_BIG_HASHMODES[] = {
"- [ Attack Modes ] -",
"",
" # | Mode",
"===+======",
"0  | Dictionary",
"1  | Bruteforce",
"",
"",
"- [ Hash Type ] -",
"",
" # | Hash Type",
"===+============",
"001| MD5",
"002| SHA1",
"003| SHA256",
"004| SHA512",
"005| Bcrypt"
};


void usage_big_print(){
    int len = sizeof(USAGE_BIG_OPTIONS) / sizeof(USAGE_BIG_OPTIONS[0]);

    for(int i = 0; i <= len; i++){
        printf("%s\n", USAGE_BIG_OPTIONS[i]);
    }
}

void usage_mini_print(){
    int len = sizeof(USAGE_MINI) / sizeof(USAGE_MINI[0]);   

    for(int i = 0; i <= len; i++){
        printf("%s\n", USAGE_MINI[i]);
    }
}

void usage_big_hashmodes(){
    int len = sizeof(USAGE_BIG_HASHMODES) / sizeof(USAGE_BIG_HASHMODES[0]);

    for(int i = 0; i <= len; i++){
        printf("%s\n", USAGE_BIG_HASHMODES[i]);
    }
}