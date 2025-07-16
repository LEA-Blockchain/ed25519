# --- Configuration ---
ENABLE_UBSEN := 0
ENABLE_LEA_LOG := 0
ENABLE_LEA_FMT := 0

# --- Includes ---
include ../stdlea/stdlea.mk

# --- Compiler Flags ---
CFLAGS += -O3

# --- Include Paths ---
INCLUDE_PATHS := -I. -Isrc -Isrc/optional

# --- Header Files ---
ED25519_HDRS = src/monocypher.h src/optional/monocypher-ed25519.h randombytes.h
HDRS += $(ED25519_HDRS)

# --- Source Files ---
ED25519_SRCS = ed25519.c src/monocypher.c src/optional/monocypher-ed25519.c
SRCS += $(ED25519_SRCS)

# --- Target ---
TARGET := ed25519.wasm

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	@echo "Compiling and linking sources to $(TARGET)..."
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) \
	-Wl,--allow-undefined \
	$(SRCS) -o $@

	@echo "Stripping custom sections..."
	wasm-strip $@

clean:
	@echo "Removing build artifacts..."
	rm -f $(TARGET) *.o
