"""
Generate an Advent of Code problem subdirectory.

Usage:
  python new_problem.py 7
  python new_problem.py 7 --root src/problems
  python new_problem.py 7 --force
Requires:
  pip install jinja2
"""
import argparse
from pathlib import Path
from jinja2 import Environment, FileSystemLoader, StrictUndefined


ROOT_DIR = Path(Path.cwd().parent.resolve())
PROBLEM_DIR = Path(ROOT_DIR, "src/problems")
TEST_DIR = Path(ROOT_DIR, "test/tests")
NUM_DAYS = 12


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Generate AoC problem scaffold.")
    p.add_argument("--day", type=int, default = 1, help=f"Day number (1-{NUM_DAYS})")
    p.add_argument("--force", action="store_true", help="Overwrite existing files")
    p.add_argument("--all", action="store_true", help="Generate all days")
    return p.parse_args()


def main() -> None:
    args = parse_args()
    if not args.all and not (1 <= args.day <= NUM_DAYS):
        raise SystemExit(f"Day must be between 1 and {NUM_DAYS}.")

    days = [args.day]
    if args.all:
        days = [x for x in range(1, NUM_DAYS + 1)]

    for day in days:
        day_str = f"{day:02d}"

        # Resolve paths
        day_dir = Path(PROBLEM_DIR, f"day{day_str}")
        header_path = Path(day_dir, f"problem_{day_str}.h")
        source_path = Path(day_dir, f"problem_{day_str}.cpp")
        input_path = Path(day_dir, "input.txt")
        test_path = Path(day_dir, "test.txt")
        test_file_path = Path(TEST_DIR, f"day_{day_str}_tests.cpp")

        # Prepare Jinja
        env = Environment(
            loader=FileSystemLoader(str(Path(ROOT_DIR, "scripts"))),
            undefined=StrictUndefined,
            trim_blocks=True,
            lstrip_blocks=True,
            keep_trailing_newline=True,
        )
        header_template = env.get_template("problem.h.j2")
        source_template = env.get_template("problem.cpp.j2")
        test_template = env.get_template("test.cpp.j2")

        # Create directory
        day_dir.mkdir(parents=True, exist_ok=True)

        # Write files (guarded)
        def write_file(path: Path, content: str):
            if path.exists() and not args.force:
                print(f"[skip] {path} (exists; use --force to overwrite)")
                return
            path.write_text(content, encoding="utf-8")
            print(f"[write] {path}")

        # Render header
        header_code = header_template.render(
            day=day_str,
        )
        write_file(header_path, header_code)

        # Render source
        source_code = source_template.render(
            day=day_str,
        )
        write_file(source_path, source_code)

        # Render test
        test_code = test_template.render(
            day=day_str,
        )
        write_file(test_file_path, test_code)

        # Ensure input.txt exists (don’t overwrite)
        if not input_path.exists():
            input_path.write_text("", encoding="utf-8")
            print(f"[write] {input_path}")
        else:
            print(f"[skip] {input_path} (exists)")

        # Ensure test.txt exists (don’t overwrite)
        if not test_path.exists():
            test_path.write_text("", encoding="utf-8")
            print(f"[write] {test_path}")
        else:
            print(f"[skip] {test_path} (exists)")


if __name__ == "__main__":
    main()
