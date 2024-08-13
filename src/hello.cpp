#include "../deps/UEFI-CPP-headers/UEFI/UEFI.h"

EFI_STATUS efi_main(EFI_HANDLE, EFI_SYSTEM_TABLE *SystemTable) {
  SystemTable->ConOut->OutputString(SystemTable->ConOut, u"Hello, world!\n");
  while (true)
    ;
  return EFI_SUCCESS;
}
