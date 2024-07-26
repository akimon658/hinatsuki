ifeq ($(shell uname),Darwin)
	MOUNT_DIR = /tmp/hinatsuki-mnt
	mkdir -p $(MOUNT_DIR)
	MOUNT = hdiutil attach -mountpoint
	UNMOUNT = hdiutil detach
endif

disk.img: boot/BOOTX64.EFI
	qemu-img create -f raw $@ 200M
	mkfs.fat -n 'HINATSUKI' -s 2 -f 2 -R 32 -F 32 $@
	$(MOUNT) $(MOUNT_DIR) $@
	mkdir -p $(MOUNT_DIR)/EFI/BOOT
	cp $< $(MOUNT_DIR)/EFI/BOOT/BOOTX64.EFI
	$(UNMOUNT) $(MOUNT_DIR)
