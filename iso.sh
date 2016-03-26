#!/bin/sh
set -e
. ./build.sh

mkdir -p iso/boot/grub

cp sysroot/boot/avocados.kernel iso/boot/avocados.kernel
cat > iso/boot/grub/grub.cfg << EOF
menuentry "avocados" {
	multiboot /boot/avocados.kernel
}
EOF
grub-mkrescue -o avocados.iso iso
