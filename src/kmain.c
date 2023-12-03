#include <limine.h>
#include <stdbool.h>
#include <stddef.h>
#include <panic.h>
#include <terminal.h>
#include <log.h>
#include <utils.h>

static void kmain(void);

LIMINE_BASE_REVISION(1)

struct limine_entry_point_request entry_point_request = {
    .id = LIMINE_ENTRY_POINT_REQUEST,
    .revision = 0, .response = NULL,

    .entry = kmain
};

struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0, .response = NULL
};

struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0, .response = NULL
};

struct limine_bootloader_info_request bootloader_info = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0, .response = NULL
};

struct limine_stack_size_request _stack = {
    .id = LIMINE_STACK_SIZE_REQUEST,
    .revision = 0, .response = NULL,

    .stack_size = 128*1024 // 128 kb
};

static void kmain() {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        early_panic();
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        early_panic();
    }

    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];

    terminal_init(fb);

    tprintf("Booted via %s (version: %s)\n", bootloader_info.response->name, bootloader_info.response->version);

    struct limine_memmap_response *memmap_response = memmap_request.response;
    
    for (size_t i = 0; i < memmap_response->entry_count; i++) {
        struct limine_memmap_entry *e = memmap_response->entries[i];
        tprintf("%x->%x %s\n", e->base, e->base + e->length, get_memmap_type(e->type));
    }

    log_info("pre init ok");

    log_info("OK");

    for (;;);
}

