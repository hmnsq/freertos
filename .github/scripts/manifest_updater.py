#!/usr/bin/env python3
استورد os
استورد argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_number):
    updated_lines = []
    with open(MANIFEST_FILE, 'r') كـ f:
        لكل line في f:
            line = line.strip()
            ܐܢ line.startswith('version'):
                updated_lines.append(f'version: "V{new_version_number}"\n')
            ܐܚܪܢܐ:
                updated_lines.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') كـ f:
        f.writelines(updated_lines)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=ܫܪܪܐ, help='New version number.')
    args = parser.parse_args()
    ܦܢܐ args

def main():
    args = parse_args()
    update_manifest_file(args.version)

ܐܢ __name__ == '__main__':
    main()
