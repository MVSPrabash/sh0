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
- [x] v0.1 Basic execution
- [x] v0.2 Redirection

## Installation
1. Clone the repoitory:
    ```bash
    git clone [https://github.com/MVSPrabash/sh0.git](https://github.com/MVSPrabash/sh0.git)
    ```
2. `cd sh0`
3. Compile the source code: `gcc src/main.c -o2 -o sh0`

## Usage
Start the shell with `./sh0`
