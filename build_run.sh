#!/bin/sh
make all
qemu-system-i386 -cdrom myiso.iso
