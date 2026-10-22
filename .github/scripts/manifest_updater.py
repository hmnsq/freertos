#!/usr/bin/env python3
आनयन os
आनयन argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_सङ्ख्या):
    updated_पङ्क्तिहरू = []
    with open(MANIFEST_FILE, 'r') इव f:
        लागि पङ्क्ति अन्तः f:
            पङ्क्ति = पङ्क्ति.strip()
            यदि पङ्क्ति.startswith('version'):
                updated_पङ्क्तिहरू.append(f'version: "V{new_version_number}"\n')
            अन्यथा:
                updated_पङ्क्तिहरू.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') इव f:
        f.writelines(updated_पङ्क्तिहरू)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=सत्य, help='New version number.')
    args = parser.parse_args()
    फर्काऊ args

def main():
    args = parse_args()
    update_manifest_file(args.version)

यदि __name__ == '__main__':
    main()
