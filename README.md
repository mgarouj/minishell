<div align="center">

# 🐚 minishell

**A small Bash-like shell written in C: parsing, pipes, redirections, heredocs, expansion, signals and builtins.**

![Language](https://img.shields.io/badge/language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Readline](https://img.shields.io/badge/lib-GNU%20readline-4EAA25?style=for-the-badge&logo=gnubash&logoColor=white)
![School](https://img.shields.io/badge/school-1337%20%7C%2042-000000?style=for-the-badge&logo=42&logoColor=white)
![Team](https://img.shields.io/badge/team-2%20people-blueviolet?style=for-the-badge)

</div>

---

## 📖 About

**minishell** is one of the biggest projects of the 42 common core: build your own shell, modeled on **Bash**. It reads a command line, checks its syntax, splits it into tokens, expands variables, handles quotes and redirections, then runs the commands, either as builtins or as child processes connected by pipes.

The project is a deep dive into **process management, file descriptors, signals, parsing and memory management** in C.

## ✨ Features

### 🧾 Parsing
- Interactive prompt with **command history** (GNU readline)
- **Tokenizer** for words, pipes `|` and redirections `<` `>` `>>` `<<`
- **Single quotes** `'...'`: no interpretation at all
- **Double quotes** `"..."`: everything literal except `$`
- **Variable expansion**: `$VAR`, `$?` (last exit status), with word splitting for unquoted values
- **Syntax errors** reported like Bash (exit status `2`):
  ```
  minishell: syntax error near unexpected token `|'
  minishell: syntax error near unexpected token 'newline'
  minishell: syntax error missing quote
  ```

### 🔀 Redirections & pipes
| Operator | Meaning |
|:---:|---|
| `<` | Redirect input from a file |
| `>` | Redirect output to a file (truncate) |
| `>>` | Redirect output to a file (append) |
| `<<` | **Heredoc**: read input until a delimiter line |
| `\|` | Pipe the output of one command into the next |

- Any number of pipes: `cat file | grep a | sort | uniq -c | wc -l`
- Heredocs run in a **child process**. They expand `$VAR` unless the delimiter is quoted (`<< "EOF"`), stop cleanly on `Ctrl-C`, and show a warning on `Ctrl-D`.

### 🛠️ Builtins
| Command | Behavior |
|---|---|
| `echo` | With the `-n` option |
| `cd` | Relative or absolute path; no argument → `$HOME`; updates `PWD` / `OLDPWD` |
| `pwd` | Print the current directory |
| `export` | Set variables, or list them in sorted order with no arguments |
| `unset` | Remove variables |
| `env` | Print the environment |
| `exit` | With an optional numeric status (handles non-numeric and too-many-argument errors) |

### ⚡ Execution
- Searches each directory in `PATH`, and also accepts absolute and relative paths
- A builtin run alone executes **in the parent** (so `cd` and `export` change the shell itself); inside a pipeline it runs in a child
- Bash-like exit codes: `127` command not found, `126` permission denied, `130` after `Ctrl-C`
- Sets up `SHLVL`, a default `PATH` and `_` when the environment is empty (`env -i ./minishell`)

### 📡 Signals
| Key | Prompt | During a running command |
|:---:|---|---|
| `Ctrl-C` | New, clean prompt (`$?` = 130) | Interrupts the command |
| `Ctrl-D` | Exits the shell | — |
| `Ctrl-\` | Ignored | Default behavior |

### 🧹 Memory
- A custom **garbage collector** tracks every allocation, so everything is freed in one call
- A **file-descriptor collector** makes sure no fd leaks between commands

## 🏗️ Architecture

```
 readline ─► syntax check ─► tokenize ─► expand & remove quotes ─► build commands ─► execute
               parsing/        parsing/        parsing/                parsing/          exc/
```

```
minishell/
├── minishell.c        # main loop: prompt → parse → execute
├── minishell.h        # structs, enums, prototypes
├── parsing/           # syntax errors, tokenizer, expansion, quotes, heredoc, redirections, signals
├── exc/               # PATH lookup, single command, pipelines, fd redirection, wait / exit codes
├── built/             # echo, cd, pwd, export, unset, env, exit
├── env_list/          # environment linked list (export / update values)
├── utils/             # garbage collector, fd collector, string helpers
└── libft_fonction/    # libft helpers
```

## 🚀 Build & run

> Requires the **GNU readline** library. On macOS: `brew install readline`

```bash
git clone https://github.com/mgarouj/minishell.git
cd minishell
make
./minishell
```

### Try it

```bash
mohammed ali $ echo "Hello $USER" | tr a-z A-Z
mohammed ali $ ls -la > out.txt
mohammed ali $ cat < out.txt | wc -l
mohammed ali $ cat << EOF
> home is $HOME
> EOF
mohammed ali $ export NAME=42
mohammed ali $ echo $NAME
mohammed ali $ ls nothing_here
mohammed ali $ echo $?
mohammed ali $ exit 42
```

> ℹ️ Like the subject requires, `&&`, `||`, `;` and wildcards are **not** handled.

## 👥 Authors

This project was built as a team of two at **1337 (42 Network)**:

- **Mohammed Ali Garouj** — [@mgarouj](https://github.com/mgarouj)
- **Fatima-Ezzahra Belkasse**

---

<div align="center">Made with ☕ at 1337 / 42 Network</div>
