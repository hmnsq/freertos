#!/usr/bin/env python3
استورد os
استورد argparse

THIS_FILE_مسیر = os.مسیر.dirname(os.مسیر.abspath(__file__))
MANIFEST_FILE = os.مسیر.join(THIS_FILE_مسیر, '..', '..', 'manifest.yml')

تعریف update_manifest_file(new_نسخه_عدد):
    updated_سطرها = []
    با open(MANIFEST_FILE, 'r') كـ f:
        لكل سطر في f:
            سطر = سطر.strip()
            إذا سطر.startswith('version'):
                updated_سطرها.append(f'version: "V{new_version_number}"\n')
            وإلا:
                updated_سطرها.append(f'{line}\n')

    با open(MANIFEST_FILE, 'w') كـ f:
        f.writelines(updated_سطرها)

تعریف parse_آرگومانها():
    parser = argparse.آرگومان_Parser()
    parser.جمع_کن_آرگومان('-v', '--version', required=درست, help='New version number.')
    آرگومانها = parser.parse_آرگومانها()
    أرجع آرگومانها

تعریف اصلی():
    آرگومانها = parse_آرگومانها()
    update_manifest_file(آرگومانها.نسخه)

إذا __name__ == '__main__':
    اصلی()
