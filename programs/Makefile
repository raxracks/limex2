ifeq ($(origin CC), default)
CC := cc
endif

ifeq ($(origin LD), default)
LD := ld
endif

CFLAGS ?= -O1 -g -Wall -Wextra -Wpedantic -pipe

LDFLAGS ?=

override INTERNALCFLAGS :=   \
	-Iinclude            \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-stack-check     \
	-fno-pic             \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-MMD
 
override INTERNALLDFLAGS :=    \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static
 
override CFILES := $(shell find ./apps -type f -name '*.c')
override OBJ := $(CFILES:.c=.o)
override HEADER_DEPS := $(CFILES:.c=.d)
 
.PHONY: all
all: compile convert
 
compile: $(OBJ)
	objcopy -O binary -j .text apps/test.o binfile
 
-include $(HEADER_DEPS)
%.o: %.c
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

convert:
	bin2c/bin2c binfile program.h test