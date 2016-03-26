#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H 1

#if !defined(__cplusplus)
#include <stdbool.h>
#endif

#include <stddef.h>
#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

typedef struct {
    bool ctrl;
    bool shift;
    bool alt;
    bool press;
    char character;
} key;

typedef struct {
   uint16_t offset_1;
   uint16_t selector; // code segment selector in GDT or LDT
   uint8_t unused;
   uint8_t type_attr; // type and attributes - p, descriptor_privilege_level x 2, s, type x 4
   uint16_t offset_2;
} idt;

typedef enum {
    TASK_GATE_32      =  5,
    INTERRUPT_GATE_16 =  6,
    TRAP_GATE_16      =  7,
    INTERRUPT_GATE_32 = 14,
    TRAP_GATE_32      = 15
} gate_type;

void io_initialize(void);
char io_getscancode(void);
char io_getchar(void);
key io_getkey(void);

void update_cursor(int, int);

#endif