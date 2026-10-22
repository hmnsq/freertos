#!/usr/bin/env python3
import os
import argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_नुमेरो):
    updated_मगा_लिन्या = []
    with open(MANIFEST_FILE, 'r') as f:
        for लिन्या in f:
            लिन्या = लिन्या.strip()
            if लिन्या.startswith('version'):
                updated_मगा_लिन्या.append(f'version: "V{new_version_number}"\n')
            else:
                updated_मगा_लिन्या.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') as f:
        f.writelines(updated_मगा_लिन्या)

def parse_मगा_कातविरान():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=True, help='New version number.')
    मगा_कातविरान = parser.parse_मगा_कातविरान()
    return मगा_कातविरान

def main():
    मगा_कातविरान = parse_मगा_कातविरान()
    update_manifest_file(मगा_कातविरान.version)

if __name__ == '__main__':
    main()
