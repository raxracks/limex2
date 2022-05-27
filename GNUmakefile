override KERNEL := limex.elf
override ISO := output/limex.iso
 
ifeq ($(origin CC), default)
CC := cc
endif

ifeq ($(origin LD), default)
LD := ld
endif

ASM := nasm

CFLAGS ?= -O2 -g -Wall -Wextra -Wpedantic -pipe
ASMFLAGS ?= -felf64

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
 
override CFILES := $(shell find ./src -type f -name '*.c')
override ASMFILES := $(shell find ./src -type f -name '*.s')
override OBJ := $(CFILES:.c=.o)
override ASMOBJ := $(ASMFILES:.s=.o)
override HEADER_DEPS := $(CFILES:.c=.d)
 
.PHONY: all
all: clean apps $(KERNEL) iso
 
$(KERNEL): $(OBJ) $(ASMOBJ)
	$(LD) $(OBJ) $(ASMOBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@
 
-include $(HEADER_DEPS)
%.o: %.c
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

iso: clean
	if [ ! -d "./limine" ]; then git clone https://github.com/limine-bootloader/limine.git --branch=v3.0-branch-binary --depth=1 && make -C limine; fi
	
	mkdir -p output/iso_root
	
	cp -v $(KERNEL) misc/limine.cfg misc/unifont.bin misc/unifont.sfn limine/limine.sys \
		limine/limine-cd.bin limine/limine-cd-efi.bin output/iso_root/
	
	xorriso -as mkisofs -b limine-cd.bin \
			-no-emul-boot -boot-load-size 4 -boot-info-table \
			--efi-boot limine-cd-efi.bin \
			-efi-boot-part --efi-boot-image --protective-msdos-label \
			output/iso_root -o $(ISO)
	
	./limine/limine-deploy $(ISO)

	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)

run:
	qemu-system-x86_64 -cdrom $(ISO)
 
.PHONY:
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS) $(ISO) output/*

apps:
	make -C programs