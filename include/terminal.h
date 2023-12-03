#include <limine.h>

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

int terminal_init(struct limine_framebuffer *fb);
int tprintf(const char* __restrict, ...);
void clear();

#endif