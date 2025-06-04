#pragma once
#include <Windows.h>
#include <vector>
#include <string>

class ResourceLoader {
public:
    static std::vector<uint8_t> LoadResource(const char* name, const char* type = "RCDATA");
private:
    static HMODULE GetModuleHandle();
};
