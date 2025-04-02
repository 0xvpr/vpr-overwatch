<h1 align="center">vpr-omega-zero</h1>
<p align="center">
  <img src="https://img.shields.io/badge/Windows-supported-44CC11"/>
  <img src="https://img.shields.io/badge/Mac-supported-44CC11"/>
  <img src="https://img.shields.io/badge/Linux-supported-44CC11"/>
  <a href="https://mit-license.org/"><img src="https://img.shields.io/badge/License-MIT-44CC11"/></a>
  <img src="https://img.shields.io/github/actions/workflow/status/0xvpr/vpr-overwatch/build.yml?label=Build"/>
  <img src="https://img.shields.io/github/actions/workflow/status/0xvpr/vpr-overwatch/tests.yml?label=Tests"/>
</p>

### vpr-overwatch
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
