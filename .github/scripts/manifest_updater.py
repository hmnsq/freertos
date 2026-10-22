#!/usr/bin/env python3
आनयन os
आनयन argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_संख्या):
    updated_पंक्तियाँ = []
    with open(MANIFEST_FILE, 'r') इव f:
        प्रति पंक्ति अन्तः f:
            पंक्ति = पंक्ति.strip()
            यदि पंक्ति.startswith('version'):
                updated_पंक्तियाँ.append(f'version: "V{new_version_number}"\n')
            अन्यथा:
                updated_पंक्तियाँ.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') इव f:
        f.writelines(updated_पंक्तियाँ)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=सत्य, help='New version number.')
    args = parser.parse_args()
    प्रत्यागम args

def main():
    args = parse_args()
    update_manifest_file(args.version)

यदि __name__ == '__main__':
    main()
