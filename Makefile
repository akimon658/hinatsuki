MOUNT_DIR = /tmp/hinatsuki-mnt

dest/disk.img: deps/edk2/Build/HinatsukiLoaderX64/DEBUG_CLANGPDB/X64/Loader.efi
	qemu-img create -f raw $@ 200M
	mkfs.fat -n 'HINATSUKI' -s 2 -f 2 -R 32 -F 32 $@
	mkdir -p $(MOUNT_DIR)
	mount -o loop $@ $(MOUNT_DIR)
	mkdir -p $(MOUNT_DIR)/EFI/BOOT
	cp $< $(MOUNT_DIR)/EFI/BOOT/BOOTX64.EFI
	umount $(MOUNT_DIR)

deps/edk2/Build/HinatsukiLoaderX64/DEBUG_CLANGPDB/X64/Loader.efi: HinatsukiLoaderPkg/Main.c HinatsukiLoaderPkg/Loader.inf HinatsukiLoaderPkg/HinatsukiLoaderPkg.dec HinatsukiLoaderPkg/HinatsukiLoaderPkg.dsc
	make -C deps/edk2/BaseTools/Source/C
	bash -c "cd deps/edk2 && source edksetup.sh && build"
