.set ALIGN,    1<<0 # align loaded modules on page boundaries
.set MEMINFO,  1<<1 # memory map
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

# Multiboot Standard
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Provide a 16KiB stack
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384
stack_top:

# entry point, no return as bootloader is gone
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
	call kernel_early
	call _init
	call kernel_main
	cli
.Lhang:
	hlt
	jmp .Lhang

# set size of _start to current location (.) minus start
# useful when debugging/for call tracing
.size _start, . - _start
