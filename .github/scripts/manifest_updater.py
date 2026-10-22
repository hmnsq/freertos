#!/usr/bin/env python3
આયાત os
આયાત argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_સંખ્યા):
    updated_લીટીઓ = []
    with open(MANIFEST_FILE, 'r') ઇવ f:
        માટે લીટી માં f:
            લીટી = લીટી.strip()
            જો લીટી.startswith('version'):
                updated_લીટીઓ.append(f'version: "V{new_version_number}"\n')
            નહીંતર:
                updated_લીટીઓ.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') ઇવ f:
        f.writelines(updated_લીટીઓ)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=સાચું, help='New version number.')
    args = parser.parse_args()
    પાછા args

def મુખ્ય():
    args = parse_args()
    update_manifest_file(args.version)

જો __name__ == '__main__':
    મુખ્ય()
