#!/usr/bin/env python3
ਆਯਾਤ os
ਆਯਾਤ argparse

THIS_FILE_ਰਸਤਾ = os.ਰਸਤਾ.dirname(os.ਰਸਤਾ.abspath(__file__))
MANIFEST_FILE = os.ਰਸਤਾ.join(THIS_FILE_ਰਸਤਾ, '..', '..', 'manifest.yml')

ਪਰਿਭਾਸ਼ਾ update_manifest_file(new_ਸੰਸਕਰਣ_ਸੰਖਿਆ):
    updated_ਸਤਰਾਂ = []
    ਨਾਲ open(MANIFEST_FILE, 'r') ਇਵ f:
        ਲਈ ਸਤਰ ਵਿੱਚ f:
            ਸਤਰ = ਸਤਰ.strip()
            ਜੇ ਸਤਰ.startswith('version'):
                updated_ਸਤਰਾਂ.append(f'version: "V{new_version_number}"\n')
            ਨਹੀਂਤਾਂ:
                updated_ਸਤਰਾਂ.append(f'{line}\n')

    ਨਾਲ open(MANIFEST_FILE, 'w') ਇਵ f:
        f.writelines(updated_ਸਤਰਾਂ)

ਪਰਿਭਾਸ਼ਾ parse_ਦਲੀਲਾਂ():
    parser = argparse.ਦਲੀਲ_Parser()
    parser.ਜੋੜੋ_ਦਲੀਲ('-v', '--version', required=ਸੱਚ, help='New version number.')
    ਦਲੀਲਾਂ = parser.parse_ਦਲੀਲਾਂ()
    ਵਾਪਸ ਦਲੀਲਾਂ

ਪਰਿਭਾਸ਼ਾ ਮੁੱਖ():
    ਦਲੀਲਾਂ = parse_ਦਲੀਲਾਂ()
    update_manifest_file(ਦਲੀਲਾਂ.ਸੰਸਕਰਣ)

ਜੇ __name__ == '__main__':
    ਮੁੱਖ()
