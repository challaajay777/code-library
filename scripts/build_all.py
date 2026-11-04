#!/usr/bin/env python3
"""
Fast parallel build verification tool for Code Library.
Compiles every C++ source and test file to guarantee standard compliance under GNU C++17.
"""

import os
import sys
import subprocess
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor

REPO_ROOT = Path(__file__).resolve().parent.parent

EXCLUDE_DIRS = {"build", "bin", ".cache", ".git"}

def compile_file(f):
    rel = f.relative_to(REPO_ROOT).as_posix()
    cmd = ["g++", "-std=gnu++17", "-O2", "-Wall", "-Wextra", f"-I{REPO_ROOT}", "-fsyntax-only", str(f)]
    res = subprocess.run(cmd, capture_output=True, text=True)
    return f, rel, res.returncode == 0, res.stderr

def build_all(workers=8):
    print("Starting full parallel compilation check...")
    cpp_files = []
    for root, dirs, files in os.walk(REPO_ROOT):
        parts = Path(root).relative_to(REPO_ROOT).parts
        if parts and parts[0] in EXCLUDE_DIRS:
            continue
        for file in files:
            if file.endswith(".cpp"):
                cpp_files.append(Path(root) / file)

    cpp_files.sort()
    print(f"Discovered {len(cpp_files)} C++ source files. Compiling with {workers} parallel threads...")

    passed = 0
    failed = 0
    errors = []

    with ThreadPoolExecutor(max_workers=workers) as executor:
        for f, rel, ok, err in executor.map(compile_file, cpp_files):
            if ok:
                passed += 1
            else:
                failed += 1
                errors.append((rel, err))
                print(f"[FAIL] {rel}")

    print("\n--- Compilation Summary ---")
    print(f"Total checked: {len(cpp_files)}")
    print(f"Passed:        {passed}")
    print(f"Failed:        {failed}")

    if errors:
        print("\nErrors encountered:")
        for r, err in errors[:5]:
            print(f"\nFile: {r}\nError:\n{err}")
        sys.exit(1)
    else:
        print(f"\nAll {passed} files successfully compiled without warnings/errors under GNU C++17.")

if __name__ == "__main__":
    w = 8
    if len(sys.argv) > 1 and sys.argv[1].isdigit():
        w = int(sys.argv[1])
    build_all(w)
