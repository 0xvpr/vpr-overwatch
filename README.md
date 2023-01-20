# vpr-overwatch
A command line utility for executing a specified command when a  
file(s) is/are modified.

## Usage
```bash
Error message: Positional arguments or explicit flags required.

Usage: ./bin/vpr-overwatch -f <target_file> -c 'command to execute' [ optional arguments> ]
 or
Usage: /path/to/files 'command to execute'

optional positional arguments:
  path/to/files, command

required arguments:
  -c            specify a command to be executed
  -f            specify a single file to monitor

optional arguments:
  -n            only execute the specified command if a modification is detected
  -r            recurse through a given directory
  -t            time interval in microseconds
  -v            enable minimum verbosity
  -vv           enable increased verbosity
  -vvv          enable maximum verbosity

example:
  ./bin/vpr-overwatch . 'clear && echo testing'
```
