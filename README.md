# File Integrity Verifier

A lightweight C++ project focused on learning modern C++ practices. The File Integrity Verifier scans a given directory, extracts metadata, and verifies whether changes have occurred since the last recorded state.

## Modes
* Write: scans directory and records metadata
* Read: load existing integrity record
* Verify (WIP): compares the existing integrity record with the current directory and files.
