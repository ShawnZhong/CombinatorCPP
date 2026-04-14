#!/usr/bin/env python3

import re
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
README_PATH = ROOT / "README.md"
GITHUB_BLOB_BASE = "https://github.com/ShawnZhong/combinatory_logic.cpp/blob"
ANCHOR_NAME_RE = r"[A-Z][A-Z0-9_]*"
README_BLOCK_RE = re.compile(
    rf"(?P<begin><!--\s*ANCHOR-BEGIN:\s*(?P<anchor>{ANCHOR_NAME_RE})\s*-->\n?)"
    rf"(?P<body>.*?)"
    rf"(?P<end><!--\s*ANCHOR-END:\s*(?P=anchor)\s*-->)",
    re.S,
)
SOURCE_ANCHOR_RE = re.compile(
    rf"ANCHOR-(?P<kind>BEGIN|END):\s*(?P<anchor>{ANCHOR_NAME_RE})\s*$"
)


def collect_source_ranges(filename: str) -> dict[str, tuple[int, int]]:
    lines = (ROOT / filename).read_text().splitlines()
    anchors = {}
    open_anchor = None

    for line_number, line in enumerate(lines, start=1):
        match = SOURCE_ANCHOR_RE.search(line)
        if not match:
            continue

        anchor = match.group("anchor")
        if match.group("kind") == "BEGIN":
            if open_anchor is not None:
                raise ValueError(
                    f"{filename}: nested anchor begin for {anchor} inside {open_anchor[0]}"
                )
            if anchor in anchors:
                raise ValueError(f"{filename}: duplicate anchor begin for {anchor}")
            open_anchor = (anchor, line_number)
            continue

        if open_anchor is None:
            raise ValueError(f"{filename}: anchor end for {anchor} without a begin")
        if anchor != open_anchor[0]:
            raise ValueError(
                f"{filename}: anchor end for {anchor} does not match begin for {open_anchor[0]}"
            )
        anchors[anchor] = (open_anchor[1], line_number)
        open_anchor = None

    if open_anchor is not None:
        raise ValueError(f"{filename}: anchor begin for {open_anchor[0]} is missing an end")

    return anchors


def current_head_hash() -> str:
    return subprocess.check_output(
        ["git", "rev-parse", "HEAD"],
        cwd=ROOT,
        text=True,
    ).strip()


def render_links(filename: str, line_range: tuple[int, int], commit_hash: str) -> str:
    start, end = line_range
    return (
        f"[`L{start}-L{end}`]"
        f"({GITHUB_BLOB_BASE}/{commit_hash}/{filename}#L{start}-L{end})"
    )


def render_table(
    lambda_range: tuple[int, int], template_range: tuple[int, int], commit_hash: str
) -> str:
    return "\n".join(
        [
            "| `lambda.cpp` | `template.cpp` |",
            "| --- | --- |",
            (
                f"| {render_links('lambda.cpp', lambda_range, commit_hash)} | "
                f"{render_links('template.cpp', template_range, commit_hash)} |"
            ),
            "",
        ]
    )


def update_readme(readme_text: str) -> str:
    lambda_ranges = collect_source_ranges("lambda.cpp")
    template_ranges = collect_source_ranges("template.cpp")
    commit_hash = current_head_hash()
    seen = set()
    matches = 0

    def replace(match: re.Match[str]) -> str:
        nonlocal matches
        matches += 1
        anchor = match.group("anchor")

        if anchor in seen:
            raise ValueError(f"README.md: duplicate anchor block for {anchor}")
        seen.add(anchor)

        if anchor not in lambda_ranges:
            raise ValueError(f"lambda.cpp: missing anchor {anchor}")
        if anchor not in template_ranges:
            raise ValueError(f"template.cpp: missing anchor {anchor}")

        return (
            match.group("begin")
            + render_table(
                lambda_ranges[anchor],
                template_ranges[anchor],
                commit_hash,
            )
            + match.group("end")
        )

    updated = README_BLOCK_RE.sub(replace, readme_text)
    if matches == 0:
        raise ValueError("README.md does not contain any ANCHOR blocks")
    return updated


def main() -> None:
    README_PATH.write_text(update_readme(README_PATH.read_text()))


if __name__ == "__main__":
    main()
