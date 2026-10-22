#!/usr/bin/env python3
import os
import argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_number):
    updated_lines = []
    with open(MANIFEST_FILE, 'r') as f:
        为 line in f:
            line = line.strip()
            如果 line.startswith('version'):
                updated_lines.append(f'version: "V{new_version_number}"\n')
            否则:
                updated_lines.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') as f:
        f.writelines(updated_lines)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=True, help='New version number.')
    args = parser.parse_args()
    返回 args

def 主要():
    args = parse_args()
    update_manifest_file(args.version)

如果 __name__ == '__main__':
    主要()
