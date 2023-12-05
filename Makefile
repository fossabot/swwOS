OBJECTS = $(patsubst %.c,%.o,$(shell find src -name "*.c"))
CCARGS = -ffreestanding -Iinclude -Iflanterm -std=gnu11 -Wall -Wextra -Wpedantic -Werror

#OBJECTS := $(OBJECTS:.s=.o)

%.o: %.c
	aarch64-linux-gnu-gcc $(CCARGS) -c $< -o $@

%.o: %.s
	aarch64-linux-gnu-as $< -o $@

k.elf: $(OBJECTS) $(LIBFDT_OBJS) flanterm/flanterm.o flanterm/backends/fb.o src/interrupts.o
	aarch64-linux-gnu-ld -nostdlib -Tsrc/link.ld --no-warn-rwx-segments $? -o swk.elf

run:
	-mv swk.elf ./vfs/
	./run.sh

.PHONY: k.elf


