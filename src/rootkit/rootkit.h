#ifndef ROOTKIT_H
#define ROOTKIT_H

#include <Uefi.h>
#include <Library/UefiLib.h>

#define ROORKIT_VERSION (0x10)

extern EFI_DRIVER_BINDING_PROTOCOL gRootkitDriverBinding;
extern EFI_COMPONENT_NAME_PROTOCOL gRootkitComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL gRootkitComponentName2;

#endif /* ROOTKIT_H */