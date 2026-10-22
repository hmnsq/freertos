#!/usr/bin/env python3
దిగుమతి os
దిగుమతి argparse

THIS_FILE_మార్గం = os.మార్గం.dirname(os.మార్గం.abspath(__file__))
MANIFEST_FILE = os.మార్గం.join(THIS_FILE_మార్గం, '..', '..', 'manifest.yml')

నిర్వచనం update_manifest_file(new_సంస్కరణ_సంఖ్య):
    updated_పంక్తులు = []
    తోడుగా open(MANIFEST_FILE, 'r') ఇవ f:
        కొరకు పంక్తి లో f:
            పంక్తి = పంక్తి.strip()
            ఒకవేళ పంక్తి.startswith('version'):
                updated_పంక్తులు.append(f'version: "V{new_version_number}"\n')
            లేకపోతే:
                updated_పంక్తులు.append(f'{line}\n')

    తోడుగా open(MANIFEST_FILE, 'w') ఇవ f:
        f.writelines(updated_పంక్తులు)

నిర్వచనం parse_వాదనలు():
    parser = argparse.వాదం_Parser()
    parser.కూడు_వాదం('-v', '--version', required=నిజం, help='New version number.')
    వాదనలు = parser.parse_వాదనలు()
    తిరిగి వాదనలు

నిర్వచనం ప్రధాన():
    వాదనలు = parse_వాదనలు()
    update_manifest_file(వాదనలు.సంస్కరణ)

ఒకవేళ __name__ == '__main__':
    ప్రధాన()
