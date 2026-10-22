#!/usr/bin/env python3
আনযন os
আনযন argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_সংখ্যা):
    updated_সাৰিগুলি = []
    with open(MANIFEST_FILE, 'r') ইৱ f:
        বাবে সাৰি অন্তঃ f:
            সাৰি = সাৰি.strip()
            যদি সাৰি.startswith('version'):
                updated_সাৰিগুলি.append(f'version: "V{new_version_number}"\n')
            অন্যথা:
                updated_সাৰিগুলি.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') ইৱ f:
        f.writelines(updated_সাৰিগুলি)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=সঁচা, help='New version number.')
    args = parser.parse_args()
    ঘূৰাই args

def main():
    args = parse_args()
    update_manifest_file(args.version)

যদি __name__ == '__main__':
    main()
