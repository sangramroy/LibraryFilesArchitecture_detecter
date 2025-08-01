# 🧩 Library Architecture Detector (C++ ELF Parser)

This project is a lightweight C++ utility that scans a directory of `.so` (shared object) files and detects the CPU architecture each was compiled for. It gracefully skips invalid or corrupted files and clearly displays the architecture of valid libraries.

---

## 📁 Project Structure

```
LibraryArchDetector/
├── lib_files/                     # Folder containing .so library files to analyze
├── lib_arch_detector.cpp         # Main C++ source file
├── arch_detector                 # Compiled executable (after running make)
├── Makefile                      # Makefile to build the program
└── README.md                     # Project documentation
```

---

## ✅ Supported Architectures

The tool supports detecting the following ELF architectures:

* **armeabi-v7a** — ARM 32-bit
* **arm64-v8a** — ARM 64-bit (AArch64)
* **x86** — Intel 80386 (32-bit)
* **x86-64** — AMD x86-64 (64-bit)
* **mips** — MIPS processors

---

## ⚙️ Build Instructions (for Linux / WSL)

> **Requirements:**
>
> * Ubuntu (or any Linux distribution) via WSL or native
> * GCC compiler with C++17 or higher

### 🛠 Steps

```bash
# Open your WSL terminal
cd ~/path/to/LibraryArchDetector
make
```

This will compile `lib_arch_detector.cpp` and produce an executable named `arch_detector`.

---

## 🚀 How to Run

Pass the folder path containing `.so` files as an argument:

```bash
./arch_detector lib_files/
```

### 🖥 Example Output

```
Total number of libraries: 6

File                               ArchType
====                               ========
libanw.14.so                       armeabi-v7a
libudev.so                         armeabi-v7a
libanw.18.so                       x86
libiomx.13.so                      mips
libARMClientService_arm64-v8a.so  arm64-v8a
libjniloader.so                    x86-64
```
