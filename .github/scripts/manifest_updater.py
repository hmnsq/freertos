#!/usr/bin/env python3
ଆମଦାନୀ os
ଆମଦାନୀ argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_ସଂଖ୍ୟା):
    updated_ଧାଡ଼ିଗୁଡ଼ିକ = []
    with open(MANIFEST_FILE, 'r') ଇଵ f:
        ପାଇଁ ଧାଡ଼ି ଭିତରେ f:
            ଧାଡ଼ି = ଧାଡ଼ି.strip()
            ଯଦି ଧାଡ଼ି.startswith('version'):
                updated_ଧାଡ଼ିଗୁଡ଼ିକ.append(f'version: "V{new_version_number}"\n')
            ଅନ୍ୟଥା:
                updated_ଧାଡ଼ିଗୁଡ଼ିକ.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') ଇଵ f:
        f.writelines(updated_ଧାଡ଼ିଗୁଡ଼ିକ)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=ସତ୍ୟ, help='New version number.')
    args = parser.parse_args()
    ଫେରନ୍ତୁ args

def ମୁଖ୍ୟ():
    args = parse_args()
    update_manifest_file(args.version)

ଯଦି __name__ == '__main__':
    ମୁଖ୍ୟ()
