# Build Your Own Git (C++)

A lightweight Git implementation built entirely from scratch in **C++17**, recreating Git's core object storage model without using the Git source code or libraries.

The project implements Git's low-level plumbing commands by directly constructing and parsing **Blob**, **Tree**, and **Commit** objects, while leveraging **SHA-1 hashing**, **Zlib compression**, and **filesystem traversal** to emulate Git's internal object database.

---

## Features

- Implemented `git init` to initialize a Git repository by creating the complete `.git` directory structure.
- Built `git hash-object -w` to generate SHA-1 object IDs, compress file contents using Zlib, and store Blob objects in Git's object database.
- Implemented `git cat-file -p` to locate, decompress, parse, and display stored Blob objects.
- Developed `git write-tree` using recursive filesystem traversal to generate Tree objects representing directory hierarchies.
- Implemented `git ls-tree --name-only` to parse Tree objects and list tracked files and directories.
- Built `git commit-tree` to generate Commit objects containing tree references, parent commits, author metadata, timestamps, and commit messages.
- Recreated Git's internal object storage format, including object headers, binary serialization, SHA-1 hashing, and compressed storage under `.git/objects`.

---

## Technologies

- **Language:** C++17
- **Libraries:** STL, `<filesystem>`, OpenSSL (SHA-1), Zlib
- **Concepts:** Git Internals, Object Storage, Binary File Parsing, Recursive Directory Traversal, Compression, Cryptographic Hashing

---

## Project Structure

```text
build-your-own-git/
├── Makefile
├── include/
│   ├── git_objects.hpp
│   ├── git_commands.hpp
│   └── utils.hpp
└── src/
    ├── main.cpp
    ├── git_objects.cpp
    ├── git_commands.cpp
    └── utils.cpp
```

---

## Git Commands Implemented

| Command | Description |
|---------|-------------|
| `init` | Initialize a new Git repository |
| `hash-object -w <file>` | Create and store Blob objects |
| `cat-file -p <hash>` | Read and display Blob contents |
| `write-tree` | Create Tree objects from the working directory |
| `ls-tree --name-only <hash>` | Display entries stored in a Tree object |
| `commit-tree <tree_sha> -m <message>` | Create Commit objects referencing Tree and parent commits |

---

## Learning Outcomes

This project provided a hands-on understanding of Git's internal architecture, including:

- Git object model (Blob, Tree, Commit)
- SHA-1 based content-addressable storage
- Binary serialization and parsing
- Zlib compression/decompression
- Recursive filesystem traversal
- Git object database layout (`.git/objects`)
- Commit graph construction using parent references
