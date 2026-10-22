#!/usr/bin/env python3
استورد os
استورد argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_ژمار):
    updated_هێڵەکان = []
    with open(MANIFEST_FILE, 'r') كـ f:
        لكل هێڵ في f:
            هێڵ = هێڵ.strip()
            إذا هێڵ.startswith('version'):
                updated_هێڵەکان.append(f'version: "V{new_version_number}"\n')
            وإلا:
                updated_هێڵەکان.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') كـ f:
        f.writelines(updated_هێڵەکان)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=صحيح, help='New version number.')
    args = parser.parse_args()
    أرجع args

def main():
    args = parse_args()
    update_manifest_file(args.version)

إذا __name__ == '__main__':
    main()
