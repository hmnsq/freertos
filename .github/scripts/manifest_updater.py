#!/usr/bin/env python3
आनयन os
आनयन argparse

THIS_FILE_मार्गः = os.मार्गः.dirname(os.मार्गः.abspath(__file__))
MANIFEST_FILE = os.मार्गः.join(THIS_FILE_मार्गः, '..', '..', 'manifest.yml')

परिभाषा update_manifest_file(new_संस्करणम्_सङ्ख्या):
    updated_पङ्क्तयः = []
    सह open(MANIFEST_FILE, 'r') इव f:
        प्रति पङ्क्तिः अन्तः f:
            पङ्क्तिः = पङ्क्तिः.strip()
            यदि पङ्क्तिः.startswith('version'):
                updated_पङ्क्तयः.append(f'version: "V{new_version_number}"\n')
            अन्यथा:
                updated_पङ्क्तयः.append(f'{line}\n')

    सह open(MANIFEST_FILE, 'w') इव f:
        f.writelines(updated_पङ्क्तयः)

परिभाषा parse_तर्काः():
    parser = argparse.तर्कः_Parser()
    parser.सङ्कलय_तर्कः('-v', '--version', required=सत्य, help='New version number.')
    तर्काः = parser.parse_तर्काः()
    प्रत्यागम तर्काः

परिभाषा मुख्यम्():
    तर्काः = parse_तर्काः()
    update_manifest_file(तर्काः.संस्करणम्)

यदि __name__ == '__main__':
    मुख्यम्()
