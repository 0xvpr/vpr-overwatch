# vpr-overwatch
A command line utility for executing a specified command when a  
file(s) is/are modified.

## Usage
```bash
Error message: Missing arguments..

Usage: ./bin/vpr-overwatch /path/to/file1 /path/to/fileN -c 'command to execute' [ <optional arguments> ]
 or
Usage: ./bin/vpr-overwatch /path/to/file 'command to execute'

optional positional arguments:
  /path/to/file(s), 'command'

required arguments:
  -c            specify a command to be executed
  -f            specify a single file to monitor

optional arguments:
  -i            execute at least once initially, before modification is detected
  -r            recurse through a given directory
  -f            specify frequency in microseconds
  -v            enable minimum verbosity
  -vv           enable increased verbosity
  -vvv          enable maximum verbosity

example:
  ./bin/vpr-overwatch . 'clear && echo testing'
```

## Building
- Linux
  ```bash
  make
  ```

- Windows (using MSVC + CMake)
  ```powershell
  cmake.exe . -B build
  cmake.exe --build build --config Release
  ```
