#!/bin/sh

qemu-system-aarch64 -M virt -cpu cortex-a72 -device ramfb \
 -drive file=fat:rw:vfs,if=none,id=drv -bios ./ovmf.fd \
 -device virtio-blk-device,drive=drv -m 1G -device qemu-xhci \
 -device usb-kbd -s -D guest_errors
