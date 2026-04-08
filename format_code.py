#!/usr/bin/env python3
"""使用 clang-format 按仓库根目录 .clang-format 格式化指定 C/C++ 源码。"""

import os
import shutil
import subprocess
import sys
from pathlib import Path

# 需要格式化的目录和文件
FORMAT_DIRS = (
    "sharesrc/libsecurity",
    "TTClient")
EXTRA_FILES = (
    "sharesrc/global_define.h",
    "sharesrc/version_info.h")

# 需要格式化的文件后缀
SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx", ".inl"}

# os.walk 时跳过的子目录名（避免第三方或生成目录被误扫）
SKIP_DIR_NAMES = {".git", ".vs", "bin", "obj", "out", "build", "ipch", "node_modules"}

def collect_source_files(root: Path) -> list[str]:
    files: list[str] = []

    for relative_dir in FORMAT_DIRS:
        base_dir = root / relative_dir
        if not base_dir.is_dir():
            continue

        for current_root, dirnames, filenames in os.walk(base_dir):
            dirnames[:] = [d for d in dirnames if d not in SKIP_DIR_NAMES]

            for filename in filenames:
                file_path = Path(current_root) / filename
                if file_path.suffix.lower() in SOURCE_SUFFIXES:
                    files.append(str(file_path))

    for rel in EXTRA_FILES:
        p = root / rel
        if p.is_file():
            files.append(str(p))

    files.sort()
    return files


def main() -> int:
    root = Path(__file__).resolve().parent
    clang_format = os.environ.get("CLANG_FORMAT", "clang-format")

    cf_path = Path(clang_format)
    if not cf_path.is_file() and shutil.which(clang_format) is None:
        print(
            f"error: '{clang_format}' not found. Install LLVM clang-format or set CLANG_FORMAT.",
            file=sys.stderr,
        )
        return 1

    files = collect_source_files(root)
    if not files:
        print("no source files matched")
        return 0

    subprocess.run([clang_format, "-i", "--style=file", *files], check=True)
    print(f"formatted {len(files)} file(s) (.clang-format)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
