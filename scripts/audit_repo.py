#!/usr/bin/env python3
"""
Repository Audit and Inventory Tool for Code Library
Audits all competitive programming source files, parses metadata headers,
detects duplicate implementations, checks syntax/compilation, and generates inventory.json.
"""

import os
import sys
import json
import hashlib
import re
import subprocess
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

CATEGORY_DIRS = [
    "Basics, Arrays, and Implementation",
    "Data Structures",
    "Graph Theory",
    "Trees and Tree Algorithms",
    "Dynamic Programming",
    "Strings and Text Algorithms",
    "Number Theory",
    "Combinatorics and Probability",
    "Geometry",
    "Algebra, Matrices, and Polynomials",
    "Game Theory and Search",
    "Optimization and Advanced Techniques",
    "Interactive, Output-Sensitive, and Contest Techniques",
    "Computational Complexity and Theory",
    "Specialized Data Structures and Advanced Range Queries",
    "Advanced Number Theory and Arithmetic Functions",
    "Advanced Strings and Automata",
    "Advanced Geometry and Spatial Algorithms",
    "Advanced Flow, Matching, and Optimization",
    "More Specialized Contest Algorithms",
    "Templates"
]

def extract_header_metadata(content):
    lines = content.splitlines()
    meta = {
        "algorithm": "",
        "supports": "",
        "indexing": "",
        "complexity": "",
        "preconditions": ""
    }
    for line in lines[:30]:
        line_str = line.strip()
        if not line_str.startswith("//"):
            continue
        cleaned = line_str.lstrip("/ ").strip()
        if cleaned.lower().startswith("algorithm:"):
            meta["algorithm"] = cleaned[len("algorithm:"):].strip()
        elif cleaned.lower().startswith("supports:"):
            meta["supports"] = cleaned[len("supports:"):].strip()
        elif cleaned.lower().startswith("indexing:"):
            meta["indexing"] = cleaned[len("indexing:"):].strip()
        elif cleaned.lower().startswith("complexity:"):
            meta["complexity"] = cleaned[len("complexity:"):].strip()
        elif cleaned.lower().startswith("preconditions:"):
            meta["preconditions"] = cleaned[len("preconditions:"):].strip()
    return meta

def tokenize_code(content):
    # Remove comments and whitespace to compare semantic code structure
    no_comments = re.sub(r'//.*?\n|/\*.*?\*/', ' ', content, flags=re.DOTALL)
    tokens = re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b|[^\w\s]', no_comments)
    return tokens

def audit(check_compile=False):
    inventory = []
    seen_hashes = {}
    duplicates = []
    total_files = 0
    total_loc = 0

    for cat in CATEGORY_DIRS:
        cat_path = REPO_ROOT / cat
        if not cat_path.exists():
            continue
        for file_path in sorted(cat_path.glob("*.cpp")):
            total_files += 1
            rel_path = file_path.relative_to(REPO_ROOT).as_posix()
            try:
                content = file_path.read_text(encoding="utf-8")
            except Exception as e:
                content = file_path.read_text(encoding="latin-1")
            
            lines = content.splitlines()
            loc = len(lines)
            total_loc += loc
            size = file_path.stat().st_size
            meta = extract_header_metadata(content)
            has_main = bool(re.search(r'\bint\s+main\s*\(', content))

            # Hash for exact duplicate detection
            norm_content = re.sub(r'\s+', '', content)
            c_hash = hashlib.sha256(norm_content.encode('utf-8')).hexdigest()
            if c_hash in seen_hashes:
                duplicates.append((rel_path, seen_hashes[c_hash]))
            else:
                seen_hashes[c_hash] = rel_path

            item = {
                "path": rel_path,
                "category": cat,
                "filename": file_path.name,
                "algorithm": meta["algorithm"] or file_path.stem.replace("_", " ").title(),
                "supports": meta["supports"],
                "indexing": meta["indexing"],
                "complexity": meta["complexity"],
                "preconditions": meta["preconditions"],
                "loc": loc,
                "bytes": size,
                "has_main": has_main,
                "status": "implemented"
            }

            if check_compile:
                res = subprocess.run(
                    ["g++", "-std=gnu++17", "-fsyntax-only", "-Wall", "-Wextra", str(file_path)],
                    capture_output=True,
                    text=True
                )
                item["syntax_valid"] = (res.returncode == 0)
                if res.returncode != 0:
                    item["syntax_error"] = res.stderr[:300]
            
            inventory.append(item)

    # Check tests directory
    tests_path = REPO_ROOT / "tests"
    test_files = []
    if tests_path.exists():
        for tf in sorted(tests_path.glob("*.cpp")):
            test_files.append(tf.relative_to(REPO_ROOT).as_posix())

    report = {
        "total_source_files": total_files,
        "total_loc": total_loc,
        "test_files_count": len(test_files),
        "test_files": test_files,
        "duplicates_detected": duplicates,
        "inventory": inventory
    }

    out_json = REPO_ROOT / "inventory.json"
    with open(out_json, "w", encoding="utf-8") as f:
        json.dump(report, f, indent=2)

    print(f"Audit completed: {total_files} source files, {total_loc} lines of code, {len(test_files)} test suites.")
    if duplicates:
        print(f"WARNING: Found {len(duplicates)} duplicate files: {duplicates}")
    else:
        print("Duplicate check: 0 duplicate implementations detected.")
    return report

if __name__ == "__main__":
    check_comp = "--compile" in sys.argv
    audit(check_compile=check_comp)
