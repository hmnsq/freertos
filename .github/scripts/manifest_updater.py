#!/usr/bin/env python3
استورد os
استورد argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_لمب):
    updated_ليوك = []
    with open(MANIFEST_FILE, 'r') كـ f:
        لكل لي في f:
            لي = لي.strip()
            إذا لي.startswith('version'):
                updated_ليوك.append(f'version: "V{new_version_number}"\n')
            وإلا:
                updated_ليوك.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') كـ f:
        f.writelines(updated_ليوك)

def parse_حجوجي():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=صحيح, help='New version number.')
    حجوجي = parser.parse_حجوجي()
    أرجع حجوجي

def main():
    حجوجي = parse_حجوجي()
    update_manifest_file(حجوجي.version)

إذا __name__ == '__main__':
    main()
