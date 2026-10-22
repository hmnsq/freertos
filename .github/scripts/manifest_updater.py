#!/usr/bin/env python3
درآمد os
درآمد argparse

THIS_FILE_راستہ = os.راستہ.dirname(os.راستہ.abspath(__file__))
MANIFEST_FILE = os.راستہ.join(THIS_FILE_راستہ, '..', '..', 'manifest.yml')

تعریف update_manifest_file(new_نسخہ_نمبر):
    updated_سطریں = []
    ساتھ open(MANIFEST_FILE, 'r') بطور f:
        برائے سطر میں f:
            سطر = سطر.strip()
            اگر سطر.startswith('version'):
                updated_سطریں.append(f'version: "V{new_version_number}"\n')
            ورنہ:
                updated_سطریں.append(f'{line}\n')

    ساتھ open(MANIFEST_FILE, 'w') بطور f:
        f.writelines(updated_سطریں)

تعریف parse_دلائل():
    parser = argparse.دلیل_Parser()
    parser.جوڑو_دلیل('-v', '--version', required=سچ, help='New version number.')
    دلائل = parser.parse_دلائل()
    واپس دلائل

تعریف مین():
    دلائل = parse_دلائل()
    update_manifest_file(دلائل.نسخہ)

اگر __name__ == '__main__':
    مین()
