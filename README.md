
# hash-cracker

`hash-cracker` is a small, fast password hash cracking tool written in C. It takes a target hash (or file with the hash), the hash type, and a wordlist, then attempts to find the original password by testing candidates from the wordlist. (Brute-force mode is a work-in-progress.)

> **Warning / Ethics:** This tool is intended for learning, research, and recovery of **your** own passwords or with explicit permission. Do **not** use it to attack systems you do not own or have authorization to test. The author assumes no responsibility for misuse.

----------

## Features

-   Wordlist-based cracking for common hash types (MD5 / SHA-family via OpenSSL).
    
-   bcrypt support via `crypt.h` / `libbcrypt`.
    
-   Multi-threaded cracking (threading implemented; tune with `-t` or `--threads`).
    
-   Minimal, dependency-light C implementation to practice systems programming.
    

----------

## Requirements

-   A C compiler (GCC recommended)
    
-   GNU Make
    
-   OpenSSL development headers and library (for MD5 / SHA)
    
-   A bcrypt library or `crypt` implementation supporting `$2` variants
    
-   pthreads (usually built into the system)

----------
## Install
```bash
git clone https://github.com/aavnie/hash_cracker.git
cd hash-cracker
make
sudo make install
```
    

----------

## Build

The provided Makefile is used here:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread -std=c11
INCLUDES = -I./modules
LIBS = -lssl -lcrypto -lcrypt

TARGET = hash-cracker

SRCS = src/main.c \
			 src/attack.c \
			 src/hash_utils.c \
			 src/wordlist.c \
			 src/usage.c \
			 src/algorithms/md5.c \
			 src/algorithms/sha1.c \
			 src/algorithms/sha256.c \
			 src/algorithms/sha512.c \
			 src/algorithms/bcrypt.c

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

all: $(TARGET)
			 @echo "✓ Build complete: $(TARGET)"

$(TARGET): $(SRCS)
			 $(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $@ $(LIBS)

install: $(TARGET)
			 install -d $(BINDIR)
			 install -m 0755 $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
			 rm -f $(BINDIR)/$(TARGET)

clean:
			 rm -f $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild install uninstall
```
----------

### Build commands

```bash
make        # build
make clean  # remove binary
sudo make install # install the program globaly
sudo make uninstall # uninstall the program globaly
make rebuild # clean all
```

----------

## Usage

Example invocation:

```bash
hash-cracker --hash=path/to/hash.txt --hash-type=md5 --t 4 --wordlist=path/to/wordlist.txt
```

### Arguments

-   `--hash=FILE` — file containing one or more hashes
    
-   `--hash-type=TYPE` — md5 | sha1 | sha256 | sha512 | bcrypt
    
-   `-t`, `--threads` — number of worker threads
    
-   `--wordlist=FILE` — path to dictionary file
    

> Note: bcrypt uses `crypt()` / libbcrypt-style verification. Passwords longer than 72 characters may be truncated.

----------

## Wordlist format

A plain text file with **one candidate password per line**.

----------

## Testing

You can create a `tests/` folder with known hash pairs, for example:

-   `echo -n "password" | md5sum`
    
-   A bcrypt hash generated on your machine
    

----------

## Security & Responsible Use

Use only on systems and data you own or have explicit permission to test, do **not** try to use it on machines you don't own and don't have explicit permission to test.

----------

## Contributing

Open to improvements: brute-force mode, optimization, rulesets, etc.

----------

## License

This project is licensed under the MIT License.  
See the [LICENSE](./LICENSE) file for details.

----------

## Author

Avni E.
