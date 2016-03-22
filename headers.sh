#!/bin/sh
set -e
. ./config.sh

mkdir -p sysroot

DESTDIR="$PWD/sysroot" $MAKE -C $KERNEL_HEADER_PROJECT install-headers

for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  DESTDIR="$PWD/sysroot" $MAKE -C libs/$PROJECT install-headers
done
