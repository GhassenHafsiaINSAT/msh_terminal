# Mini Shell

A simple shell implementation from scratch to understand **system calls, signal handling, process synchronization, exit status, and text parsing**.

## Features

### Special Variables

- `$?` → Exit status of the last command
- `$$` → PID of the mini shell
- `$SHELL` → Path of the mini shell executable

### Signal Handling

- **Ctrl+C (SIGINT)** → Graceful termination of processes
- **Ctrl+Z (SIGTSTP)** → Suspending processes

### Built-in Commands (using system calls)

- `exit` → Exit the shell
- `cd` → Change directory
- `pwd` → Print current directory
- *(More can be added as needed)*

### Background Process Support

- Run commands in the background using `&`
- Display details of background processes

### Pipe Functionality

- Enable communication between multiple processes using `|`

