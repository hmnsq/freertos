#!/usr/bin/env python3
आयात os
आयात argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.मेल(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_संख्या):
    updated_पंक्तियाँ = []
    with open(MANIFEST_FILE, 'r') as f:
        क्रम पंक्ति in f:
            पंक्ति = पंक्ति.strip()
            अगर पंक्ति.startswith('version'):
                updated_पंक्तियाँ.append(f'version: "V{new_version_number}"\n')
            अन्यथा:
                updated_पंक्तियाँ.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') as f:
        f.writelines(updated_पंक्तियाँ)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=True, help='New version number.')
    तर्क = parser.parse_args()
    वापस तर्क

def मुख्य():
    तर्क = parse_args()
    update_manifest_file(तर्क.version)

अगर __name__ == '__main__':
    मुख्य()
