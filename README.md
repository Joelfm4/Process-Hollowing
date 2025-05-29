```
        _____                               _    _       _ _               _             
       |  __ \                             | |  | |     | | |             (_)            
       | |__) | __ ___   ___ ___  ___ ___  | |__| | ___ | | | _____      ___ _ __   __ _ 
       |  ___/ '__/ _ \ / __/ _ \/ __/ __| |  __  |/ _ \| | |/ _ \ \ /\ / / | '_ \ / _` |
       | |   | | | (_) | (_|  __/\__ \__ \ | |  | | (_) | | | (_) \ V  V /| | | | | (_| |
       |_|   |_|  \___/ \___\___||___/___/ |_|  |_|\___/|_|_|\___/ \_/\_/ |_|_| |_|\__, |
                                                                                    __/ |
                                                                                   |___/ 
```

## Project Overview
This project is a simple and rudimentary implementation of process hollowing written in C++.

## How it works (Overview)
- `CreateProcessA`: Creates a new process in a suspended state.
- `VirtualAllocEx`: Allocates memory within the target process to hold the shellcode.
- `WriteProcessMemory`: Writes the shellcode into the allocated memory space.
- `GetThreadContext`: Retrieves the context (registers, etc.) of the main thread of the target process.
- `SetThreadContext`: Modifies the thread context to redirect execution to the shellcode.
- `ResumeThread`: Resumes the suspended thread, effectively executing the injected shellcode.
