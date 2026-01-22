# C-Tail: Tail Implementation

![Build Status](https://github.com/MarekHusenica/proc_scan/actions/workflows/tests.yml/badge.svg)
![Language](https://img.shields.io/badge/language-C11-blue.svg)
![Testing](https://img.shields.io/badge/tests-PyTest-green.svg)

A Unix-style `proc_scan` utility written in **C11**

## Motivation
I was bored and wanted to make something quick :D
This project is mainly for learning ctypes and library testing in python
The tests are very simple, and don't really test much
The doubly linked list implementation can be improved

## Tech Stack
* **Core:** C11, GCC
* **Testing:** Python 3, PyTest, Subprocess API, Valgrind
* **Automation:** GNU Make, GitHub Actions
* **Environment:** Linux / WSL

## Project Structure
```text
├── src/                 # C source files
├── tests/               # Python integration tests
├── Makefile             # Build and test automation
└── .github/workflows/   # CI/CD pipeline configuration
```