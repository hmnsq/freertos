#!/usr/bin/env python3
ಆನಯನ os
ಆನಯನ argparse

THIS_FILE_PATH = os.path.dirname(os.path.abspath(__file__))
MANIFEST_FILE = os.path.join(THIS_FILE_PATH, '..', '..', 'manifest.yml')

def update_manifest_file(new_version_ಸಂಖ್ಯೆ):
    updated_ಸಾಲುಗಳು = []
    with open(MANIFEST_FILE, 'r') ಇವ f:
        ಪ್ರತಿ ಸಾಲು ಅನ್ತಃ f:
            ಸಾಲು = ಸಾಲು.strip()
            ಯದಿ ಸಾಲು.startswith('version'):
                updated_ಸಾಲುಗಳು.append(f'version: "V{new_version_number}"\n')
            ಅನ್ಯಥಾ:
                updated_ಸಾಲುಗಳು.append(f'{line}\n')

    with open(MANIFEST_FILE, 'w') ಇವ f:
        f.writelines(updated_ಸಾಲುಗಳು)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--version', required=ಸತ್ಯ, help='New version number.')
    args = parser.parse_args()
    ಪ್ರತ್ಯಾಗಮ args

def main():
    args = parse_args()
    update_manifest_file(args.version)

ಯದಿ __name__ == '__main__':
    main()
