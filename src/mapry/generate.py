#!/usr/bin/env python3
"""Generate the code for all the Mapry schemas."""

import os
import pathlib
import subprocess

import mapry.parse


def generate_cpp(repo_root: pathlib.Path, schema: mapry.Schema,
                 schema_path: pathlib.Path) -> None:
    """Generate the C++ code for the given Mapry schema."""
    namespace_parts = schema.cpp.namespace.split("::")
    outdir = repo_root / 'src' / 'cpp' / os.path.join(*namespace_parts)

    subprocess.check_call([
        'mapry-to', 'cpp', '--schema', str(schema_path), '--outdir', outdir
    ])


def main() -> None:
    script_dir = pathlib.Path(os.path.dirname(os.path.realpath(__file__)))
    repo_root = script_dir.parent.parent

    schema_pths = sorted(script_dir.glob("*.json"))

    for schema_pth in schema_pths:
        print("Generating the for the schema: {}".format(schema_pth))
        schema = mapry.parse.schema_from_json_file(schema_pth)
        generate_cpp(repo_root=repo_root, schema=schema, schema_path=schema_pth)


if __name__ == "__main__":
    main()
