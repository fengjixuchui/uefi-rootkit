#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/FvLib.h>
#include <Library/DebugAgentLib.h>
#include <Library/DebugLib.h>

EFI_STATUS EFIAPI
RootkitEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{

    DEBUG((DEBUG_INFO, "Hello world\n"));

    return EFI_SUCCESS;
}
