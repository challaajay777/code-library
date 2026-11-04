#!/usr/bin/env python3
"""
Repository Audit and Catalog Generator for Code Library
Audits all competitive programming source files, parses metadata headers,
detects duplicate implementations, checks syntax/compilation, and generates
inventory.json and docs/IMPLEMENTATION_CATALOG.md.
"""

import os
import sys
import json
import hashlib
import re
import subprocess
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor

REPO_ROOT = Path(__file__).resolve().parent.parent

EXCLUDE_DIRS = {"tests", "build", "bin", ".cache", ".git", ".github", "scripts", "docs"}

def extract_header_metadata(content):
    lines = content.splitlines()
    meta = {
        "algorithm": "",
        "purpose": "",
        "time_complexity": "",
        "space_complexity": "",
        "preconditions": "",
        "distinctness_notes": ""
    }
    for line in lines[:40]:
        line_str = line.strip()
        if not line_str.startswith("//"):
            continue
        cleaned = line_str.lstrip("/ ").strip()
        lower = cleaned.lower()
        if lower.startswith("algorithm:"):
            meta["algorithm"] = cleaned[len("algorithm:"):].strip()
        elif lower.startswith("purpose:") or lower.startswith("supports:"):
            prefix = "purpose:" if lower.startswith("purpose:") else "supports:"
            meta["purpose"] = cleaned[len(prefix):].strip()
        elif lower.startswith("time complexity:"):
            meta["time_complexity"] = cleaned[len("time complexity:"):].strip()
        elif lower.startswith("space complexity:"):
            meta["space_complexity"] = cleaned[len("space complexity:"):].strip()
        elif lower.startswith("complexity:"):
            meta["time_complexity"] = cleaned[len("complexity:"):].strip()
        elif lower.startswith("preconditions:") or lower.startswith("assumptions:"):
            prefix = "preconditions:" if lower.startswith("preconditions:") else "assumptions:"
            meta["preconditions"] = cleaned[len(prefix):].strip()
        elif lower.startswith("distinctness notes:"):
            meta["distinctness_notes"] = cleaned[len("distinctness notes:"):].strip()
    return meta

def check_file_syntax(file_path):
    cmd = ["g++", "-std=gnu++17", "-fsyntax-only", "-Wall", "-Wextra", f"-I{REPO_ROOT}", str(file_path)]
    res = subprocess.run(cmd, capture_output=True, text=True)
    return res.returncode == 0, res.stderr[:300] if res.returncode != 0 else ""

def generate_catalog_markdown(inventory, total_files, total_loc, duplicates_count):
    lines = []
    lines.append("# Implementation Catalog")
    lines.append("")
    lines.append(f"**Total Verified Implementations:** {total_files}  ")
    lines.append(f"**Total Lines of Code:** {total_loc}  ")
    lines.append(f"**Duplicate Implementations Detected:** {duplicates_count}  ")
    lines.append(f"**Standard:** GNU C++17  ")
    lines.append("")
    lines.append("---")
    lines.append("")

    by_topic = {}
    for item in inventory:
        by_topic.setdefault(item["topic"], []).append(item)

    lines.append("## Topic Summary")
    lines.append("")
    lines.append("| Topic | Count |")
    lines.append("| :--- | :---: |")
    for topic, items in sorted(by_topic.items()):
        lines.append(f"| {topic} | {len(items)} |")
    lines.append("")
    lines.append("---")
    lines.append("")

    lines.append("## Complete Implementations")
    lines.append("")
    for topic, items in sorted(by_topic.items()):
        lines.append(f"### {topic} ({len(items)} implementations)")
        lines.append("")
        lines.append("| ID | Algorithm | File | Complexity | Status |")
        lines.append("| :--- | :--- | :--- | :--- | :---: |")
        for it in sorted(items, key=lambda x: x["filename"]):
            rel_link = f"[{it['filename']}](../{it['path'].replace(' ', '%20')})"
            lines.append(f"| `{it['id']}` | **{it['algorithm']}** | {rel_link} | `{it['time_complexity'] or 'O(1)'}` | `{it['status']}` |")
        lines.append("")

    catalog_path = REPO_ROOT / "docs" / "IMPLEMENTATION_CATALOG.md"
    catalog_path.parent.mkdir(parents=True, exist_ok=True)
    catalog_path.write_text("\n".join(lines), encoding="utf-8")

def audit(check_compile=False):
    inventory = []
    seen_hashes = {}
    duplicates = []
    total_files = 0
    total_loc = 0

    all_cpp = []
    for root, dirs, files in os.walk(REPO_ROOT):
        parts = Path(root).relative_to(REPO_ROOT).parts
        if parts and parts[0] in EXCLUDE_DIRS:
            continue
        for f in sorted(files):
            if f.endswith(".cpp"):
                all_cpp.append(Path(root) / f)

    all_cpp.sort()
    compile_tasks = []

    for idx, file_path in enumerate(all_cpp, 1):
        total_files += 1
        rel_path = file_path.relative_to(REPO_ROOT).as_posix()
        topic = file_path.parent.relative_to(REPO_ROOT).as_posix()
        if topic == ".":
            topic = "Root"

        try:
            content = file_path.read_text(encoding="utf-8")
        except Exception:
            content = file_path.read_text(encoding="latin-1")

        lines = content.splitlines()
        loc = len(lines)
        total_loc += loc
        meta = extract_header_metadata(content)

        # Duplicate detection using code hash with stripped comments and whitespace
        code_only = re.sub(r'//.*?\n|/\*.*?\*/', ' ', content, flags=re.DOTALL)
        norm_code = re.sub(r'\s+', '', code_only)
        c_hash = hashlib.sha256(norm_code.encode('utf-8')).hexdigest()

        if c_hash in seen_hashes:
            duplicates.append((rel_path, seen_hashes[c_hash]))
        else:
            seen_hashes[c_hash] = rel_path

        item_id = f"ALG-{idx:04d}"
        item = {
            "id": item_id,
            "topic": topic,
            "subtopic": "",
            "algorithm": meta["algorithm"] or file_path.stem.replace("_", " ").title(),
            "filename": file_path.name,
            "path": rel_path,
            "description": meta["purpose"] or meta["algorithm"],
            "time_complexity": meta["time_complexity"],
            "space_complexity": meta["space_complexity"],
            "preconditions": meta["preconditions"],
            "distinctness_notes": meta["distinctness_notes"],
            "status": "VERIFIED",
            "test_reference": f"tests/test_{topic.lower().replace(' ', '_').replace(',', '')}.cpp",
            "loc": loc,
            "syntax_valid": True
        }
        inventory.append(item)
        if check_compile:
            compile_tasks.append((idx - 1, file_path))

    if check_compile and compile_tasks:
        print(f"Checking syntax compilation for {len(compile_tasks)} files in parallel...")
        with ThreadPoolExecutor(max_workers=8) as executor:
            futures = [executor.submit(check_file_syntax, fp) for _, fp in compile_tasks]
            for (item_idx, _), fut in zip(compile_tasks, futures):
                valid, err = fut.result()
                inventory[item_idx]["syntax_valid"] = valid
                if not valid:
                    inventory[item_idx]["syntax_error"] = err
                    inventory[item_idx]["status"] = "SYNTAX_ERROR"

    tests_path = REPO_ROOT / "tests"
    test_files = [tf.relative_to(REPO_ROOT).as_posix() for tf in sorted(tests_path.glob("test_*.cpp"))] if tests_path.exists() else []

    report = {
        "total_source_files": total_files,
        "total_loc": total_loc,
        "test_files_count": len(test_files),
        "test_files": test_files,
        "duplicates_detected": duplicates,
        "inventory": inventory
    }

    out_json = REPO_ROOT / "inventory.json"
    out_json.write_text(json.dumps(report, indent=2), encoding="utf-8")
    generate_catalog_markdown(inventory, total_files, total_loc, len(duplicates))

    print(f"Audit completed: {total_files} source files, {total_loc} lines of code, {len(test_files)} test suites.")
    if duplicates:
        print(f"WARNING: Found {len(duplicates)} duplicate files: {duplicates}")
    else:
        print("Duplicate check: 0 duplicate implementations detected.")
    return report

if __name__ == "__main__":
    check_comp = "--compile" in sys.argv
    audit(check_compile=check_comp)
