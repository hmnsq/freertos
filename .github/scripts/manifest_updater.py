#!/usr/bin/env python3
واردکن os
واردکن argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_عدد):
    updated_سطرها = []
    with open(MANIFEST_FILE, 'r') بهعنوان f:
        برای سطر در f:
            سطر = سطر.strip()
            اگر سطر.startswith('version'):
                updated_سطرها.append(f'version: "V{new_version_number}"\n')
            وگرنه:
                updated_سطرها.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') بهعنوان f:
        f.writelines(updated_سطرها)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=درست, help='New version number.')
    args = parser.parse_args()
    بازگشت args

def اصلی():
    args = parse_args()
    update_manifest_file(args.version)

اگر __name__ == '__main__':
    اصلی()
