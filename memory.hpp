#pragma once
#include <Windows.h>

// Utilisation externe (ReadProcessMemory/WriteProcessMemory)
inline HANDLE hProcess = GetCurrentProcess();
inline HMODULE hModule = GetModuleHandle(nullptr);

template <typename T>
T ReadMemory(uintptr_t address) {
    T value{};
    SIZE_T bytesRead;
    if (!ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(T), &bytesRead))
        return T();
    return value;
}

template <typename T>
void WriteMemory(uintptr_t address, const T& value) {
    SIZE_T bytesWritten;
    WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), &bytesWritten);
}