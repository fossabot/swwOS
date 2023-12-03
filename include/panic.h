#include <terminal.h>

#ifndef _PANIC_H_
#define _PANIC_H_

static inline void early_panic() {
    // 0xDEADBEEF
    
    asm("wfi");
    asm("wfe");
    for(;;)
        asm("nop");
}

static inline void panic(char* reason) {
    clear();
    tprintf("oh no. swwk moment!\n%s", reason);

    early_panic();
}
#endif