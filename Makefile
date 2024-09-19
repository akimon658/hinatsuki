MOUNT_DIR = /tmp/hinatsuki-mnt

dest/disk.img: deps/edk2/Build/HinatsukiLoaderX64/DEBUG_CLANGPDB/X64/Loader.efi dest/kernel.elf
	qemu-img create -f raw $@ 200M
	mkfs.fat -n 'HINATSUKI' -s 2 -f 2 -R 32 -F 32 $@
	mkdir -p $(MOUNT_DIR)
	mount -o loop $@ $(MOUNT_DIR)
	mkdir -p $(MOUNT_DIR)/EFI/BOOT
	cp $< $(MOUNT_DIR)/EFI/BOOT/BOOTX64.EFI
	cp dest/kernel.elf $(MOUNT_DIR)/kernel.elf
	umount $(MOUNT_DIR)

deps/edk2/BaseTools/Source/C/bin/GenFw:
	make -C deps/edk2/BaseTools/Source/C

deps/edk2/Build/HinatsukiLoaderX64/DEBUG_CLANGPDB/X64/Loader.efi: deps/edk2/BaseTools/Source/C/bin/GenFw HinatsukiLoaderPkg/Main.c HinatsukiLoaderPkg/Loader.inf HinatsukiLoaderPkg/HinatsukiLoaderPkg.dec HinatsukiLoaderPkg/HinatsukiLoaderPkg.dsc
	bash -c "cd deps/edk2 && source edksetup.sh && build"

dest/kernel.elf: kernel/main.o
	ld.lld -L./deps/x86_64-elf/lib --entry KernelMain -z norelro -z separate-loadable-segments --image-base 0x100000 --static -o $@ $<

kernel/main.o: kernel/main.cpp
	clang++ -I./deps/x86_64-elf/include -I./deps/x86_64-elf/include/c++/v1 -nostdlibinc -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -std=c++20 -c $< -o $@
