#include "ResourceLoader.h"
#include <stdexcept>

HMODULE ResourceLoader::GetModuleHandle() {
    static HMODULE handle = ::GetModuleHandle(nullptr);
    return handle;
}

std::vector<uint8_t> ResourceLoader::LoadResource(const char* name, const char* type) {
    // 查找资源
    HRSRC resourceHandle = ::FindResource(GetModuleHandle(), name, type);
    if (!resourceHandle) {
        return std::vector<uint8_t>();
    }

    // 加载资源
    HGLOBAL globalHandle = ::LoadResource(GetModuleHandle(), resourceHandle);
    if (!globalHandle) {
        return std::vector<uint8_t>();
    }

    // 获取资源大小和数据指针
    DWORD size = ::SizeofResource(GetModuleHandle(), resourceHandle);
    const void* data = ::LockResource(globalHandle);
    if (!data) {
        return std::vector<uint8_t>();
    }

    // 复制资源数据到 vector
    const uint8_t* byteData = static_cast<const uint8_t*>(data);
    return std::vector<uint8_t>(byteData, byteData + size);
}
