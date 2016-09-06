#!/usr/bin/env python

from collections import defaultdict
import os
import argparse


def split(ff_path, dirname=""):
    """split the force field parameters in one ff into individual files
    Keyword Arguments:
    ff_path  -- file path
    dirname  -- output directory, the same directory as the input file by default
    """
    contents = defaultdict(list)
    common_lines = []
    if dirname == "":
        dirname = os.path.dirname(ff_path)
    with open(ff_path, 'r') as ifs:
        for line in ifs:
            if not line.startswith('MCS'):
                common_lines.append(line)
            else:
                complex_id = line.split()[1]
                contents[complex_id].append(line)

    for key in contents:
        contents[key] = common_lines + contents[key]
        ofn = os.path.join(dirname, key + 'ff')
        with open(ofn, 'w') as ofs:
            ofs.writelines(contents[key])


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description="split large ff file into individual files")
    parser.add_argument(
        "-d",
        "--directory",
        default="",
        type=str,
        help="output directory, directory of the ff file by default")
    parser.add_argument("-f", "--ff", type=str, help="ligand ff file")

    args = parser.parse_args()

    work_dir = args.directory
    lig_ff = args.ff
    split(lig_ff, dirname=work_dir)
