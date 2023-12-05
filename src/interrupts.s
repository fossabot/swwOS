// From ToaruOS

.extern kfault

.globl _exception_vector
.balign 0x800
_exception_vector:

/* AArch64 exception vectors are divided up;
 * our first set of vectors is for if we are using SP0
 * in EL1, which we don't currently do so these should
 * all probably just be loop branches to catch this. */
_exc_sp0_sync:
    b kfault
.balign 0x80
_exc_sp0_irq:
    b kfault
.balign 0x80
_exc_sp0_fiq:
    b kfault
.balign 0x80
_exc_sp0_serror:
    b kfault

/* These are EL1-EL1 fault handlers, for when we encounter
 * an exception in the kernel. We normally have interrupts
 * masked in the kernel so we should only see synchronous
 * exceptions - faults. */
.balign 0x80
_exc_spx_sync:
    b kfault
.balign 0x80
_exc_spx_irq:
    b kfault
.balign 0x80
_exc_spx_fiq:
    b kfault
.balign 0x80
_exc_spx_serror:
    b kfault

/* These are EL0-EL1 transition handlers. Synchronous is going
 * to be faults and system calls (SVC requests); */
.balign 0x80
_exc_lower_sync:
    b kfault

/* Actual interrupts */
.balign 0x80
_exc_lower_irq:
    b kfault

/* "Fast" interrupts. TODO */
.balign 0x80
_exc_lower_fiq:
    b kfault

.balign 0x80
_exc_lower_serror:
    b kfault
.balign 0x80

/* These are going to be calls from 32-bit userspace, which we're
 * not going to support, so just blank all of these out as well. */
_exc_lower_32_sync:
    b kfault
.balign 0x80
_exc_lower_32_irq:
    b kfault
.balign 0x80
_exc_lower_32_fiq:
    b kfault
.balign 0x80
_exc_lower_32_serror:
    b kfault

