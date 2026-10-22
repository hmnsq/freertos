#!/usr/bin/env python3
ಆಮದು os
ಆಮದು argparse

THIS_FILE_ಮಾರ್ಗ = os.ಮಾರ್ಗ.dirname(os.ಮಾರ್ಗ.abspath(__file__))
MANIFEST_FILE = os.ಮಾರ್ಗ.join(THIS_FILE_ಮಾರ್ಗ, '..', '..', 'manifest.yml')

ವ್ಯಾಖ್ಯಾನ update_manifest_file(new_ಆವೃತ್ತಿ_ಸಂಖ್ಯೆ):
    updated_ಸಾಲುಗಳು = []
    ಜೊತೆ open(MANIFEST_FILE, 'r') ಇವ f:
        ಗಾಗಿ ಸಾಲು ಒಳಗೆ f:
            ಸಾಲು = ಸಾಲು.strip()
            ಆದರೆ ಸಾಲು.startswith('version'):
                updated_ಸಾಲುಗಳು.append(f'version: "V{new_version_number}"\n')
            ಇಲ್ಲದಿದ್ದರೆ:
                updated_ಸಾಲುಗಳು.append(f'{line}\n')

    ಜೊತೆ open(MANIFEST_FILE, 'w') ಇವ f:
        f.writelines(updated_ಸಾಲುಗಳು)

ವ್ಯಾಖ್ಯಾನ parse_ವಾದಗಳು():
    parser = argparse.ವಾದ_Parser()
    parser.ಕೂಡಿಸು_ವಾದ('-v', '--version', required=ನಿಜ, help='New version number.')
    ವಾದಗಳು = parser.parse_ವಾದಗಳು()
    ಹಿಂತಿರುಗಿ ವಾದಗಳು

ವ್ಯಾಖ್ಯಾನ ಮುಖ್ಯ():
    ವಾದಗಳು = parse_ವಾದಗಳು()
    update_manifest_file(ವಾದಗಳು.ಆವೃತ್ತಿ)

ಆದರೆ __name__ == '__main__':
    ಮುಖ್ಯ()
