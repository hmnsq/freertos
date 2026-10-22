#!/usr/bin/env python3
আমদানি os
আমদানি argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_সংখ্যা):
    updated_সারিগুলি = []
    with open(MANIFEST_FILE, 'r') ইব f:
        জন্য সারি মধ্যে f:
            সারি = সারি.strip()
            যদি সারি.startswith('version'):
                updated_সারিগুলি.append(f'version: "V{new_version_number}"\n')
            অন্যথা:
                updated_সারিগুলি.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') ইব f:
        f.writelines(updated_সারিগুলি)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=সত্য, help='New version number.')
    args = parser.parse_args()
    ফেরত args

def প্রধান():
    args = parse_args()
    update_manifest_file(args.version)

যদি __name__ == '__main__':
    প্রধান()
