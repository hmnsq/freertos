#!/usr/bin/env python3
आयात os
आयात argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_संख्या):
    updated_ओळी = []
    with open(MANIFEST_FILE, 'r') इव f:
        साठी ओळ मध्ये f:
            ओळ = ओळ.strip()
            जर ओळ.startswith('version'):
                updated_ओळी.append(f'version: "V{new_version_number}"\n')
            अन्यथा:
                updated_ओळी.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') इव f:
        f.writelines(updated_ओळी)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=सत्य, help='New version number.')
    args = parser.parse_args()
    परत args

def main():
    args = parse_args()
    update_manifest_file(args.version)

जर __name__ == '__main__':
    main()
