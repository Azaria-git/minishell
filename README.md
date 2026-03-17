# Minishell

Minishell is a project developed as part of the 42 school curriculum. It is a simplified implementation of a Unix shell, allowing you to execute commands, manage redirections, pipes, environment variables, and other essential shell features.

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Authors](#authors)

## Description
Minishell aims to reproduce the basic behavior of a Unix shell. It allows users to execute commands, manipulate the environment, manage history and signals, and use features such as pipes and redirections.

## Features
- Execute commands with arguments
- Redirection management (`>`, `<`, `>>`, `<<`)
- Pipe management (`|`)
- Environment variables (`export`, `unset`, `$VAR`)
- Built-in commands (`cd`, `echo`, `pwd`, `env`, `exit`, `export`, `unset`)
- Command history management
- Signal handling (Ctrl+C, Ctrl+\, etc.)
- Error handling and explicit messages

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/Azaria-git/minishell.git
   cd minishell
   ```
2. Build the project:
   ```sh
   make
   ```

## Usage
Start the shell with:
```sh
./minishell
```
You can then enter commands as in a classic shell.

## Project Structure
- `minishell.c` / `minishell.h`: Entry point and main definitions
- `builtins/`: Implementation of built-in commands
- `common/`: Common utility functions
- `executor/`: Command and process execution management
- `history/`: Command history management
- `Libft/`: Utility function library
- `parsing/`: User command parsing and processing
- `signals/`: Signal handling

## Authors
- Azaria Ravelomanana (<aravelom@student.42antananarivo.mg>)

---
Project developed as part of 42 school.