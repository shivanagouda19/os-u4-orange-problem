# PES-VCS (Mini Version Control System)

A small Git-like version control system written in C. This project stores content-addressed objects, tracks staged files in an index, creates commits, and prints commit history.

## Features

- `pes init`: initialize a `.pes` repository
- `pes add <file>...`: stage one or more files
- `pes status`: show staged, modified, deleted, and untracked files
- `pes commit -m "message"`: create a commit from staged files
- `pes log`: walk and print commit history

## Command Reference

- `./pes init`: create `.pes` metadata directories and HEAD reference
- `./pes add <path>...`: hash file content as blob objects and stage entries in index
- `./pes status`: compare working tree with index and print staged/unstaged/untracked files
- `./pes commit -m "message"`: build tree from index, create commit object, and move branch head
- `./pes log`: print commit history by following parent links

## Repository Layout

- `pes.c`: CLI command dispatch
- `object.c`: object read/write in `.pes/objects`
- `tree.c`: tree creation and serialization
- `index.c`: staging index load/save/add/status helpers
- `commit.c`: commit creation and history traversal
- `test_objects.c`: object-store unit tests
- `test_tree.c`: tree unit tests
- `test_sequence.sh`: end-to-end integration flow
- `Makefile`: build and test targets

## Requirements

- Linux
- `gcc`
- OpenSSL crypto library (`libcrypto`)

On Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential libssl-dev
```

## Author Configuration

The commit author string is read from the `PES_AUTHOR` environment variable.
If it is not set, the program uses a built-in default value.

```bash
export PES_AUTHOR="Your Name <your-email-or-id>"
```

## Build

```bash
make          # build pes
make all      # build pes + test binaries
```

## Run Tests

```bash
make test-unit         # runs test_objects and test_tree
make test-integration  # runs full sequence script
make test              # runs all tests
```

## Quick Start

```bash
./pes init

echo "hello" > hello.txt
./pes add hello.txt
./pes status
./pes commit -m "Initial commit"
./pes log
```

## Clean Build Artifacts

```bash
make clean
```

This removes generated binaries, object files, and `.pes` test repository data.
