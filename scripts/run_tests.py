#!/usr/bin/env python3
"""
Test runner for Code Library.
Compiles and executes test suites in tests/ and standalone verification binaries.
Enforces differential tests, boundary assertions, and randomized invariants.
"""

import os
import sys
import subprocess
import time
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
TESTS_DIR = REPO_ROOT / "tests"
BIN_DIR = TESTS_DIR / "bin"

def run_all_tests():
    BIN_DIR.mkdir(parents=True, exist_ok=True)
    test_files = sorted(list(TESTS_DIR.glob("test_*.cpp")))
    if not test_files:
        print("No test files found in tests/")
        return 0

    print(f"Running {len(test_files)} test suite(s)...")
    passed = 0
    failed = 0
    failures = []

    for idx, tf in enumerate(test_files, 1):
        rel = tf.relative_to(REPO_ROOT).as_posix()
        exe_name = tf.stem + (".exe" if os.name == "nt" else "")
        exe_path = BIN_DIR / exe_name

        # Compile test binary
        build_cmd = [
            "g++", "-std=gnu++17", "-O2", "-Wall", "-Wextra",
            f"-I{REPO_ROOT}",
            str(tf),
            "-o", str(exe_path)
        ]
        build_res = subprocess.run(build_cmd, capture_output=True, text=True)
        if build_res.returncode != 0:
            failed += 1
            print(f"[{idx}/{len(test_files)}] BUILD FAILED: {rel}")
            failures.append((rel, "Compilation Error", build_res.stderr))
            continue

        # Execute test binary
        t0 = time.time()
        run_res = subprocess.run([str(exe_path)], capture_output=True, text=True, timeout=60)
        dt = time.time() - t0

        if run_res.returncode == 0:
            passed += 1
            print(f"[{idx}/{len(test_files)}] PASSED ({dt:.2f}s): {rel}")
            if run_res.stdout.strip():
                for line in run_res.stdout.strip().splitlines()[-3:]:
                    print(f"    {line}")
        else:
            failed += 1
            print(f"[{idx}/{len(test_files)}] FAILED (exit code {run_res.returncode}): {rel}")
            failures.append((rel, f"Execution Failure (Code {run_res.returncode})", run_res.stderr or run_res.stdout))

    print("\n--- Test Suite Summary ---")
    print(f"Total Suites: {len(test_files)}")
    print(f"Passed:       {passed}")
    print(f"Failed:       {failed}")

    if failures:
        print("\nFailures:")
        for rel, reason, detail in failures:
            print(f"\n{rel} - {reason}:\n{detail}")
        sys.exit(1)
    else:
        print("\nAll test suites passed successfully.")
        return 0

if __name__ == "__main__":
    sys.exit(run_all_tests())
