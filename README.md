# sh0 - Minimal Linux Shell
Minimal x64 Linux shell written in C to explore Linux process control, file descriptors, and shell internals.

## Features
- External command execution (`fork`, `execvp`, `waitpid`)
- Builtin commands (`cd`, `pwd`, `help`, `exit`)
- I/O redirection (`>`, `<`, `>>`)
- Single-pipe command pipelines (`|`)

#### Features not included
- Scripting
- Full Job Control (`fg`, `bg`, `jobs`, `Ctrl+Z`)
- Wildcard expansion (*, ?)
- Environment variables
- Builtin commands (beyond minimal support)

## Known Limitations
- Mixed piping and redirection are not yet supported
- Multiple pipes (`a | b | c`) are not yet supported

## Progress
- [X] V0.1  Basic execution
- [X] V0.2  Builtin commands (cd, pwd, etc..)
- [X] V0.3  Redirection
- [X] V0.4  Single-pipe support
- [ ] V0.5  Background jobs (`&`)
- [ ] V0.6  Parsing system rewrite
- [ ] V0.7  Quoting
- [ ] V0.8  Environment variables
- [ ] V0.9  History
- [ ] V1.0  Interactive shell polish

## Project Structure
```text
src/
├── main.c         # Shell loop
├── exec.c         # Command dispatch + external execution
├── builtins.c     # Builtin commands
├── parser.c       # Command tokenization
├── pipeline.c     # Pipe handling (`|`)
├── exec.h
├── builtins.h
├── parser.h
└── pipeline.h
```

## Installation
1. Clone the repository:
    ```bash
    git clone https://github.com/MVSPrabash/sh0.git
    ```
2. `cd sh0`
3. Compile the source code using the script: `./compile.sh`

## Usage
Start the shell with `./sh0`

## Example Usage

```bash
sh0# pwd
/home/prabash

sh0# echo hello > file.txt
sh0# echo world >> file.txt
sh0# cat < file.txt
hello world

sh0# cat test.txt | grep test
test
test1
```
## Concepts Explored (so far)
- Process creation (`fork`)
- Program execution (`execvp`)
- Process synchronization (`waitpid`)
- File descriptors and redirection (`dup2`, `open`)
- Shell builtins and process state
- Inter-process communication (`pipe`)
