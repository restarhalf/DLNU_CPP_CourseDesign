#include "ResourceLoader.h"

HMODULE ResourceLoader::GetModuleHandle() {
    static HMODULE handle = ::GetModuleHandle(NULL);
    return handle;
}

std::vector<uint8_t> ResourceLoader::LoadResource(const char* name, const char* type) {
    HRSRC resourceHandle = FindResource(GetModuleHandle(), name, type);
    if (!resourceHandle) {
        return std::vector<uint8_t>();
    }

    HGLOBAL globalHandle = LoadResource(GetModuleHandle(), resourceHandle);
    if (!globalHandle) {
        return std::vector<uint8_t>();
    }

    DWORD size = SizeofResource(GetModuleHandle(), resourceHandle);
    void* data = LockResource(globalHandle);
    if (!data) {
        return std::vector<uint8_t>();
    }

    std::vector<uint8_t> buffer(static_cast<uint8_t*>(data),
                               static_cast<uint8_t*>(data) + size);
    return buffer;
}
