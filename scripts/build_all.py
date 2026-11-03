#!/usr/bin/env python3
"""
Build verification tool for Code Library.
Compiles every C++ source and test file to guarantee clean standard compliance under GNU C++17.
"""

import os
import sys
import subprocess
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

def build_all():
    print("Starting full compilation check...")
    cpp_files = []
    for p in REPO_ROOT.rglob("*.cpp"):
        if "build" in p.parts or ".cache" in p.parts or "bin" in p.parts:
            continue
        cpp_files.append(p)

    print(f"Discovered {len(cpp_files)} C++ source files.")
    passed = 0
    failed = 0
    errors = []

    for idx, f in enumerate(cpp_files, 1):
        rel = f.relative_to(REPO_ROOT).as_posix()
        cmd = ["g++", "-std=gnu++17", "-O2", "-Wall", "-Wextra", "-fsyntax-only", str(f)]
        res = subprocess.run(cmd, capture_output=True, text=True)
        if res.returncode == 0:
            passed += 1
            print(f"[{idx}/{len(cpp_files)}] OK: {rel}")
        else:
            failed += 1
            print(f"[{idx}/{len(cpp_files)}] FAILED: {rel}")
            errors.append((rel, res.stderr))

    print("\n--- Compilation Summary ---")
    print(f"Total checked: {len(cpp_files)}")
    print(f"Passed: {passed}")
    print(f"Failed: {failed}")

    if errors:
        print("\nErrors encountered:")
        for r, err in errors:
            print(f"\nFile: {r}\nError:\n{err}")
        sys.exit(1)
    else:
        print("\nAll files successfully compiled under GNU C++17.")

if __name__ == "__main__":
    build_all()
