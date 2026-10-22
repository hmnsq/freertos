#!/usr/bin/env python3
استورد os
استورد argparse

THIS_FILE_لار = os.لار.dirname(os.لار.abspath(__file__))
MANIFEST_FILE = os.لار.join(THIS_FILE_لار, '..', '..', 'manifest.yml')

تعریف update_manifest_file(new_نسخه_شمېره):
    updated_کرښې = []
    سره open(MANIFEST_FILE, 'r') كـ f:
        لكل کرښه في f:
            کرښه = کرښه.strip()
            إذا کرښه.startswith('version'):
                updated_کرښې.append(f'version: "V{new_version_number}"\n')
            وإلا:
                updated_کرښې.append(f'{line}\n')

    سره open(MANIFEST_FILE, 'w') كـ f:
        f.writelines(updated_کرښې)

تعریف parse_دلیلونه():
    parser = argparse.دلیل_Parser()
    parser.جمع_کړه_دلیل('-v', '--version', required=ریښتیا, help='New version number.')
    دلیلونه = parser.parse_دلیلونه()
    أرجع دلیلونه

تعریف اصلي():
    دلیلونه = parse_دلیلونه()
    update_manifest_file(دلیلونه.نسخه)

إذا __name__ == '__main__':
    اصلي()
