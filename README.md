# sh0 - Minimal Linux Shell
Minimal x64 Linux shell written in C with basic features, designed to explore process control, file descriptors and Inter-Process Communication concepts.

## Features
- Command line execution
- IO redirection
- Piping
- Command history

#### Features not included
- Scripting
- Job Control
- Wildcard expansion (*, ?)
- Environment Control (env variables)
- Buildin command (beyond minimal support)

## Progress
- [X] V0.1  Basic execution
- [X] V0.2  Builtin commands (cd, pwd, etc..)
- [ ] V0.3  Redirection
- [ ] V0.4  Pipes
- [ ] V0.5  Background jobs
- [ ] V0.6  Lexer/parser rewrite
- [ ] V0.7  Quoting
- [ ] V0.8  Environment variables
- [ ] V0.9  History
- [ ] V1.0  Interactive shell polish

## Installation
1. Clone the repoitory:
    ```bash
    git clone https://github.com/MVSPrabash/sh0.git
    ```
2. `cd sh0`
3. Compile the source code using the script: `./compile.sh`

## Usage
Start the shell with `./sh0`
