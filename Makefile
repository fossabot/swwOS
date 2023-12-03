OBJECTS = $(patsubst %.c,%.o,$(shell find src -name "*.c"))

#OBJECTS := $(OBJECTS:.s=.o)

%.o: %.c
	aarch64-linux-gnu-gcc -ffreestanding -Iinclude -Iflanterm -c $< -o $@

%.o: %.s
	aarch64-linux-gnu-as $< -o $@

k.elf: $(OBJECTS) $(LIBFDT_OBJS) flanterm/flanterm.o flanterm/backends/fb.o
	aarch64-linux-gnu-ld -nostdlib -Tsrc/link.ld --no-warn-rwx-segments $(OBJECTS) flanterm/flanterm.o flanterm/backends/fb.o -o swk.elf

run:
	-mv swk.elf ./vfs/
	./run.sh

.PHONY: k.elf


