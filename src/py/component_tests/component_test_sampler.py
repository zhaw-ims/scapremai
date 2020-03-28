#!/usr/bin/env python3

"""Test scapremai_sampler."""
import argparse
import pathlib
import os
import subprocess
import tempfile


def main():
    """Execute the test."""
    script_dir = pathlib.Path(os.path.dirname(os.path.realpath(__file__)))
    repo_root = (script_dir / "../../..").resolve()

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        '--release_dir',
        help='path to the directory where released files reside',
        default=str(repo_root / "release"))
    args = parser.parse_args()

    release_dir = pathlib.Path(args.release_dir)
    sampler_pth = release_dir / "bin/scapremai_sampler"

    cases_dir = repo_root / "test_data" / "component_test_sampler"
    cases = sorted(p.name for p in cases_dir.iterdir())
    for case in cases:
        case_dir = cases_dir / case
        print("Executing the test case: {}".format(case_dir))

        sampling_pth = case_dir / "sampling.json"
        if not sampling_pth.exists():
            raise FileNotFoundError("Sampling path not found: {}".format(
                sampling_pth))

        model_pth = case_dir / 'model.so'
        if not model_pth.exists():
            model_pth = case_dir / 'model.dll'

        if not model_pth.exists():
            raise FileNotFoundError(
                "Neither model.so nor model.dll found in: {}".format(case_dir))

        with tempfile.TemporaryDirectory() as tmpdir:
            # yapf: disable
            subprocess.check_call([
                str(sampler_pth),
                '--sampling_path', str(sampling_pth),
                '--model_path', str(model_pth),
                '--outdir', tmpdir
            ])
            # yapf: enable

            print("PASSED!")


if __name__ == "__main__":
    main()
