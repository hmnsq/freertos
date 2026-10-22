#!/usr/bin/env python3
ഇറക്കുമതി os
ഇറക്കുമതി argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_സംഖ്യ):
    updated_വരികൾ = []
    with open(MANIFEST_FILE, 'r') ഇവ f:
        വേണ്ടി വരി ഇൽ f:
            വരി = വരി.strip()
            എങ്കിൽ വരി.startswith('version'):
                updated_വരികൾ.append(f'version: "V{new_version_number}"\n')
            അല്ലെങ്കിൽ:
                updated_വരികൾ.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') ഇവ f:
        f.writelines(updated_വരികൾ)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=സത്യം, help='New version number.')
    args = parser.parse_args()
    തിരികെ args

def പ്രധാന():
    args = parse_args()
    update_manifest_file(args.version)

എങ്കിൽ __name__ == '__main__':
    പ്രധാന()
