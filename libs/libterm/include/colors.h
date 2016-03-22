#ifndef _COLORS_H
#define _COLORS_H 1

#include <sys/termdefs.h>

#if defined(__is_avocados_kernel)
#include <kernel/vga.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__is_avocados_kernel)
const char* print_color(enum vga_color, const char*, const char*);
#endif

const char* success(const char*);
const char* info(const char*);
const char* warn(const char*);
const char* err(const char*);

#ifdef __cplusplus
}
#endif

#endif