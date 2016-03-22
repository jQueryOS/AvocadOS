#!/bin/sh
set -e
. ./headers.sh

DESTDIR="$PWD/sysroot" $MAKE -C $KERNEL_PROJECT install

for PROJECT in $PROJECTS; do
  DESTDIR="$PWD/sysroot" $MAKE -C libs/$PROJECT install
done
