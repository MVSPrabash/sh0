# sh0 - Minimal Linux Shell
Minimal x64 Linux shell written in C to explore Linux process control, file descriptors, and shell internals.

## Features
- External command execution (`fork`, `execvp`, `waitpid`)
- Builtin commands (`cd`, `pwd`, `help`, `exit`)
- I/O redirection (`>`, `<`, `>>`)
- Single command piping (`|`)

#### Features not included
- Scripting
- Full Job Control (`fg`, `bg`, `jobs`, `Ctrl+Z`)
- Wildcard expansion (*, ?)
- Environment variables
- Buildin commands (beyond minimal support)

## Progress
- [X] V0.1  Basic execution
- [X] V0.2  Builtin commands (cd, pwd, etc..)
- [X] V0.3  Redirection
- [X] V0.4  Pipes
- [ ] V0.5  Background jobs (`&`)
- [ ] V0.6  Parsing system rewrite
- [ ] V0.7  Quoting
- [ ] V0.8  Environment variables
- [ ] V0.9  History
- [ ] V1.0  Interactive shell polish

## Project Structure
```text
src/
├── main.c        # Shell loop
├── exec.c        # External command execution + redirection
├── builtins.c    # Builtin commands
├── parser.c      # Command tokenization
```

## Installation
1. Clone the repoitory:
    ```bash
    git clone https://github.com/MVSPrabash/sh0.git
    ```
2. `cd sh0`
3. Compile the source code using the script: `./compile.sh`

## Usage
Start the shell with `./sh0`

## Example Usage

```bash
sh0# ls
sh0# cd ..
sh0# pwd
/home/prabash

sh0# echo hello > file.txt
sh0# cat < file.txt
hello

sh0# echo world >> file.txt
```
## Concepts Explored (so far)
- Process creation (`fork`)
- Program execution (`execvp`)
- Process synchronization (`waitpid`)
- File descriptors and redirection (`dup2`, `open`)
- Shell builtins and process state
