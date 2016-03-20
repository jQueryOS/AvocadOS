cd $AVOCADOS_DIR
$CROSS_AS kernel/boot.s -o kernel/boot.o
$CROSS_GCC -c kernel/kernel.c -o kernel/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$CROSS_GCC -T kernel/linker.ld -o kernel/avocados.bin -ffreestanding -O2 -nostdlib kernel/boot.o kernel/kernel.o -lgcc
mkdir -p iso/boot/grub
sudo cp kernel/avocados.bin iso/boot/avocados.bin
sudo cp kernel/grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue /usr/lib/grub/i386-pc -o avocados.iso iso
qemu-system-i386 -cdrom avocados.iso