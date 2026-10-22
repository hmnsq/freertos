#!/usr/bin/env python3
இறக்குமதி os
இறக்குமதி argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_எண்):
    updated_வரிகள் = []
    with open(MANIFEST_FILE, 'r') இவ f:
        க்கு வரி உள் f:
            வரி = வரி.strip()
            எனில் வரி.startswith('version'):
                updated_வரிகள்.append(f'version: "V{new_version_number}"\n')
            இல்லையெனில்:
                updated_வரிகள்.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') இவ f:
        f.writelines(updated_வரிகள்)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=உண்மை, help='New version number.')
    args = parser.parse_args()
    திரும்பு args

def முதன்மை():
    args = parse_args()
    update_manifest_file(args.version)

எனில் __name__ == '__main__':
    முதன்மை()
