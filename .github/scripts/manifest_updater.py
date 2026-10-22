#!/usr/bin/env python3
استورد os
استورد argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_رقم):
    updated_أسطر = []
    with open(MANIFEST_FILE, 'r') كـ f:
        لكل سطر في f:
            سطر = سطر.strip()
            إذا سطر.startswith('version'):
                updated_أسطر.append(f'version: "V{new_version_number}"\n')
            وإلا:
                updated_أسطر.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') كـ f:
        f.writelines(updated_أسطر)

def parse_وسائط():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=صحيح, help='New version number.')
    وسائط = parser.parse_وسائط()
    أرجع وسائط

def main():
    وسائط = parse_وسائط()
    update_manifest_file(وسائط.version)

إذا __name__ == '__main__':
    main()
