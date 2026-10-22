#!/usr/bin/env python3
استورد os
استورد argparse

THIS_FILE_رستہ = os.رستہ.dirname(os.رستہ.abspath(__file__))
MANIFEST_FILE = os.رستہ.join(THIS_FILE_رستہ, '..', '..', 'manifest.yml')

تعریف update_manifest_file(new_نسخہ_نمبر):
    updated_سطریں = []
    نال open(MANIFEST_FILE, 'r') كـ f:
        لكل سطر في f:
            سطر = سطر.strip()
            إذا سطر.startswith('version'):
                updated_سطریں.append(f'version: "V{new_version_number}"\n')
            وإلا:
                updated_سطریں.append(f'{line}\n')

    نال open(MANIFEST_FILE, 'w') كـ f:
        f.writelines(updated_سطریں)

تعریف parse_دلیلاں():
    parser = argparse.دلیل_Parser()
    parser.جوڑو_دلیل('-v', '--version', required=سچ, help='New version number.')
    دلیلاں = parser.parse_دلیلاں()
    أرجع دلیلاں

تعریف مکھ():
    دلیلاں = parse_دلیلاں()
    update_manifest_file(دلیلاں.نسخہ)

إذا __name__ == '__main__':
    مکھ()
