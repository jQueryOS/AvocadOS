#include <fun.h>

#if defined(__is_avocados_kernel)
#include <kernel/tty.h>
#include <kernel/vga.h>
#endif

void matrix() {
	while(1) {
		#if defined(__is_avocados_kernel)
		setfg(GREEN);
		//length = round rand * 7
		#endif
	}
}