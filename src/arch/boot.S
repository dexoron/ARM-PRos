// ==================================================================
// ARM-PRos - AArch64 boot stub for ARM-PRos kernel
// Copyright (C) 2026 PRoX2011
// ==================================================================

.section .text
.global _start
.global hang

_start:
    mrs x0, mpidr_el1
    and x0, x0, #0xff
    cbz x0, 1f
0:
    wfe
    b   0b
1:
    adr x0, _vectors
    msr vbar_el1, x0
    isb

    ldr x30, =stack_top
    mov sp, x30

    ldr x0, =__bss_start
    ldr x1, =__bss_end
2:
    cmp x0, x1
    b.hs 3f
    str xzr, [x0], #8
    b   2b
3:
    bl  main

hang:
    wfe
    b   hang

.balign 0x800
_vectors:
    b _exc_ignore
    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore

    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore

    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore

    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore
    .balign 0x80
    b _exc_ignore

_exc_ignore:
    eret