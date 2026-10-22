#!/usr/bin/env python3
استورد os
استورد argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_سان):
    updated_قۇرلار = []
    with open(MANIFEST_FILE, 'r') كـ f:
        لكل قۇر في f:
            قۇر = قۇر.strip()
            إذا قۇر.startswith('version'):
                updated_قۇرلار.append(f'version: "V{new_version_number}"\n')
            وإلا:
                updated_قۇرلار.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') كـ f:
        f.writelines(updated_قۇرلار)

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
