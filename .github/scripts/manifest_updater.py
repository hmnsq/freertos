#!/usr/bin/env python3
import os
import argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_number):
    updated_lines = []
    with open(MANIFEST_FILE, 'r') as f:
        ສຳລັບ line anta_h f:
            line = line.strip()
            ຖ້າ line.startswith('version'):
                updated_lines.append(f'version: "V{new_version_number}"\n')
            ບໍ່ດັ່ງນັ້ນ:
                updated_lines.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') as f:
        f.writelines(updated_lines)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=True, help='New version number.')
    args = parser.parse_args()
    ສົ່ງຄືນ args

def main():
    args = parse_args()
    update_manifest_file(args.version)

ຖ້າ __name__ == '__main__':
    main()
