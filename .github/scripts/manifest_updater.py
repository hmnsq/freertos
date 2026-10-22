#!/usr/bin/env python3
आनयन os
आनयन argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_सङ्ख्या):
    updated_पङ्क्तयः = []
    with open(MANIFEST_FILE, 'r') इव f:
        अत्थाय पङ्क्तिः अन्तः f:
            पङ्क्तिः = पङ्क्तिः.strip()
            सचे पङ्क्तिः.startswith('version'):
                updated_पङ्क्तयः.append(f'version: "V{new_version_number}"\n')
            अञ्ञथा:
                updated_पङ्क्तयः.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') इव f:
        f.writelines(updated_पङ्क्तयः)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=सच्च, help='New version number.')
    args = parser.parse_args()
    पटिनिवत्त args

def main():
    args = parse_args()
    update_manifest_file(args.version)

सचे __name__ == '__main__':
    main()
