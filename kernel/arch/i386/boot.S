.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # Multiboot flags
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

# entry point, doesn't make sense to return as bootloader is gone
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

# set size of the _start symbol to the current location (.) minus its start
# useful when debugging and for call tracing
.size _start, . - _start
