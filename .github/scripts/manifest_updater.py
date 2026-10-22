#!/usr/bin/env python3
استورد os
استورد argparse

THIS_FILE_رستو = os.رستو.dirname(os.رستو.abspath(__file__))
MANIFEST_FILE = os.رستو.join(THIS_FILE_رستو, '..', '..', 'manifest.yml')

وصف update_manifest_file(new_نسخو_عدد):
    updated_سٽون = []
    سان open(MANIFEST_FILE, 'r') كـ f:
        لكل سٽ في f:
            سٽ = سٽ.strip()
            إذا سٽ.startswith('version'):
                updated_سٽون.append(f'version: "V{new_version_number}"\n')
            وإلا:
                updated_سٽون.append(f'{line}\n')

    سان open(MANIFEST_FILE, 'w') كـ f:
        f.writelines(updated_سٽون)

وصف parse_دليلون():
    parser = argparse.دليل_Parser()
    parser.جوڙيو_دليل('-v', '--version', required=سچ, help='New version number.')
    دليلون = parser.parse_دليلون()
    أرجع دليلون

وصف مکيه():
    دليلون = parse_دليلون()
    update_manifest_file(دليلون.نسخو)

إذا __name__ == '__main__':
    مکيه()
