# We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OSTYPE),cygwin)
    CLEANUP = rm -f
    MKDIR = mkdir -p
    TARGET_EXTENSION=.out
else ifeq ($(OS),Windows_NT)
    CLEANUP = del /F /Q
    MKDIR = mkdir
    TARGET_EXTENSION=.exe
else
    CLEANUP = rm -f
    MKDIR = mkdir -p
    TARGET_EXTENSION=.out
endif

# Path Definitions
PATHU = ../unity/
PATHS = src/
PATHT = test/
PATHI = inc/
PATHB = build/

# Zephyr Installation Path
ZEPHYR_BASE = c:/ncs/v2.4.1/zephyr  # Update this to your Zephyr installation path

# Determine our source files
SRCU = $(PATHU)unity.c
SRCS = $(wildcard $(PATHS)*.c)
SRCT = $(wildcard $(PATHT)*.c)
SRC = $(SRCU) $(SRCS) $(SRCT)

# Files We Are To Work With
OBJU = $(patsubst $(PATHU)%.c,$(PATHB)%.o,$(SRCU))
OBJS = $(patsubst $(PATHS)%.c,$(PATHB)%.o,$(SRCS))
OBJT = $(patsubst $(PATHT)%.c,$(PATHB)%.o,$(SRCT))
OBJ = $(OBJU) $(OBJS) $(OBJT)

# Other files we care about
DEP = $(PATHU)unity.h $(PATHU)unity_internals.h
TGT = $(PATHB)test$(TARGET_EXTENSION)

# Tool Definitions
CC=gcc
#CC = $(ZEPHYR_BASE)/zephyr/toolchain/gcc/bin/arm-zephyr-eabi-gcc  # Update this with the path to your Zephyr GCC toolchain
CFLAGS=-I. -I$(PATHU) -I$(PATHI) -I$(PATHS) -I$(ZEPHYR_BASE)/include -DTEST

# Add any necessary Zephyr libraries here if needed
# LDFLAGS=-L$(ZEPHYR_BASE)/lib -lzephyr

# Define the target board (replace with your specific board)
#BOARD = <YOUR_BOARD_NAME>

test: $(PATHB) $(TGT)
    ./$(TGT)

$(PATHB)%.o:: $(PATHS)%.c $(DEP)
    $(CC) -c $(CFLAGS) $< -o $@

$(PATHB)%.o:: $(PATHT)%.c $(DEP)
    $(CC) -c $(CFLAGS) $< -o $@

$(PATHB)%.o:: $(PATHU)%.c $(DEP)
    $(CC) -c $(CFLAGS) $< -o $@

$(TGT): $(OBJ)
    $(CC) -o $@ $^ $(LDFLAGS)

clean:
    $(CLEANUP) $(PATHB)*.o
    $(CLEANUP) $(TGT)

$(PATHB):
    $(MKDIR) $(PATHB)

all: clean test

.PHONY: all
.PHONY: clean
.PHONY: test
