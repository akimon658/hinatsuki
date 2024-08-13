MOUNT_DIR = /tmp/hinatsuki-mnt

dest/BOOTX64.EFI: dest/hello.o
	lld-link-18 /subsystem:efi_application /entry:efi_main /out:$@ $<

dest/disk.img: dest/BOOTX64.EFI
	qemu-img create -f raw $@ 200M
	mkfs.fat -n 'HINATSUKI' -s 2 -f 2 -R 32 -F 32 $@
	mkdir -p $(MOUNT_DIR)
	mount -o loop $@ $(MOUNT_DIR)
	mkdir -p $(MOUNT_DIR)/EFI/BOOT
	cp $< $(MOUNT_DIR)/EFI/BOOT/
	umount $(MOUNT_DIR)

dest/hello.o: src/hello.c
	clang++-18 -target x86_64-pc-win32-coff -mno-red-zone -fno-stack-protector -fshort-wchar -Wall -c $< -o $@

.PHONY: run
run:
