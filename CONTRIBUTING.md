# Contributing

## Setup

1. Install dependencies:

```bash
sudo apt update
sudo apt install -y build-essential libssl-dev
```

2. Build project binaries:

```bash
make all
```

## Validation Before Commit

Run the full test set:

```bash
make test
```

## Commit Guidelines

- Keep changes focused and small
- Write clear commit messages that describe intent
- Avoid committing generated binaries and local `.pes` runtime data

## Pull Request Checklist

- Code builds with `make all`
- Tests pass with `make test`
- Documentation is updated when command behavior changes
