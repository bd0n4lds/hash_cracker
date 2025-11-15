# Hash Cracker - Single Compilation (src/ only)
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
