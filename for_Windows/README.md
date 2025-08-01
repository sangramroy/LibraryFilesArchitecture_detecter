# Library Architecture Detector

## ✅ What it does
This program:
- Reads `.so` (shared object) files from a given folder.
- Detects the architecture (ARM, x86, etc.) of each `.so` file.
- Ignores non-library or invalid files.

## ✅ Supported Architectures
- armeabi-v7a
- arm64-v8a
- x86
- x86-64
- mips

## ✅ Requirements
- MSYS2 with `ucrt64` toolchain (GCC installed)

## ✅ Build

Open MSYS2 `ucrt64` terminal and run:

```bash
make
