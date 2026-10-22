#!/usr/bin/env python3
#/*
# * FreeRTOS Kernel <DEVELOPMENT BRANCH>
# * Copyright (C) 2024 Amazon.com, Inc. or its affiliates. All Rights Reserved.
# * Copyright 2026 Arm Limited and/or its affiliates <open-source-office@arm.com>
# *
# * SPDX-License-Identifier: MIT
# *
# * Permission is hereby granted, free of charge, to any person obtaining a copy of
# * this software and associated documentation files (the "Software"), to deal in
# * the Software without restriction, including without limitation the rights to
# * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# * the Software, and to permit persons to whom the Software is furnished to do so,
# * subject to the following conditions:
# *
# * The above copyright notice and this permission notice shall be included in all
# * copies or substantial portions of the Software.
# *
# * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# *
# * https://www.FreeRTOS.org
# * https://github.com/FreeRTOS
# *
# */

దిగుమతి os
దిగుమతి re
తః common.శీర్షిక_checker దిగుమతి శీర్షిక_Checker

#--------------------------------------------------------------------------------------------------
#                                            CONFIG
#--------------------------------------------------------------------------------------------------
KERNEL_IGNORED_FILES = [
    'FreeRTOS-openocd.c',
    'Makefile',
    '.DS_Store',
    'cspell.config.yaml',
    '.clang-format'
]

KERNEL_IGNORED_EXTENSIONS = [
    '.yml',
    '.css',
    '.idx',
    '.md',
    '.url',
    '.sty',
    '.0-rc2',
    '.s82',
    '.js',
    '.out',
    '.pack',
    '.2',
    '.1-kernel-only',
    '.0-kernel-only',
    '.0-rc1',
    '.readme',
    '.tex',
    '.png',
    '.bat',
    '.sh',
    '.txt',
    '.cmake',
    '.config'
]

KERNEL_ASM_EXTENSIONS = [
    '.s',
    '.S',
    '.src',
    '.inc',
    '.s26',
    '.s43',
    '.s79',
    '.s85',
    '.s87',
    '.s90',
    '.asm',
    '.h'
]

KERNEL_PY_EXTENSIONS = [
    '.py'
]

KERNEL_IGNORED_PATTERNS = [
    r'.*\.git.*',
    r'.*portable/IAR/AtmelSAM7S64/.*AT91SAM7.*',
    r'.*portable/GCC/ARM7_AT91SAM7S/.*',
    r'.*portable/MPLAB/PIC18F/stdio.h',
    r'.*portable/ThirdParty/xClang/XCOREAI/*',
    r'.*IAR/ARM_C*',
    r'.*IAR/78K0R/*',
    r'.*CCS/MSP430X/*',
    r'.*portable/template/*',
    r'.*template_configuration/*'
]

KERNEL_మూడవ_PARTY_PATTERNS = [
    r'.*portable/ThirdParty/GCC/Posix/port*',
    r'.*portable/ThirdParty/*',
    r'.*portable/IAR/AVR32_UC3/.*',
    r'.*portable/GCC/AVR32_UC3/.*',
]

KERNEL_ARM_COLLAB_FILES_PATTERNS = [
    r'.*portable/ARMv8M/*',
    r'.*portable/.*/ARM_CM23*',
    r'.*portable/.*/ARM_CM33*',
    r'.*portable/.*/ARM_CM35*',
    r'.*portable/.*/ARM_CM52*',
    r'.*portable/.*/ARM_CM55*',
    r'.*portable/.*/ARM_CM85*',
    r'.*portable/.*/ARM_CM0*',
    r'.*portable/.*/ARM_CM3_MPU*',
    r'.*portable/.*/ARM_CM4_MPU*',
    r'.*portable/.*/ARM_CM4F_MPU*',
    r'.*portable/.*/ARM_CR82*',
    r'.*portable/.*/ARM_STAR_MC3*',
    r'.*include/task\.h$',
    r'.*tasks\.c$',
]

KERNEL_శీర్షిక = [
    '/*\n',
    ' * FreeRTOS Kernel <DEVELOPMENT BRANCH>\n',
    ' * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.\n',
    ' *\n',
    ' * SPDX-License-Identifier: MIT\n',
    ' *\n',
    ' * Permission is hereby granted, free of charge, to any person obtaining a copy of\n',
    ' * this software and associated documentation files (the "Software"), to deal in\n',
    ' * the Software without restriction, including without limitation the rights to\n',
    ' * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of\n',
    ' * the Software, and to permit persons to whom the Software is furnished to do so,\n',
    ' * subject to the following conditions:\n',
    ' *\n',
    ' * The above copyright notice and this permission notice shall be included in all\n',
    ' * copies or substantial portions of the Software.\n',
    ' *\n',
    ' * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n',
    ' * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS\n',
    ' * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR\n',
    ' * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER\n',
    ' * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN\n',
    ' * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n',
    ' *\n',
    ' * https://www.FreeRTOS.org\n',
    ' * https://github.com/FreeRTOS\n',
    ' *\n',
    ' */\n',
]


FREERTOS_COPYRIGHT_REGEX = r"^(;|#)?( *(\/\*|\*|#|\/\/))? Copyright \(C\) 20\d\d Amazon.com, Inc. or its affiliates. All Rights Reserved\.( \*\/)?$"
ARM_COLLAB_YEAR_REGEX = r"20\d\d(?:-20\d\d|, 20\d\d)?"

FREERTOS_ARM_COLLAB_COPYRIGHT_REGEX = r"(^(;|#)?( *(\/\*|\*|#|\/\/))? Copyright \(C\) 20\d\d Amazon.com, Inc. or its affiliates. All Rights Reserved\.( \*\/)?$)|" + \
                                      rf"(^(;|#)?( *(\/\*|\*|#|\/\/))? Copyright { ARM_COLLAB_YEAR_REGEX } Arm Limited and/or its affiliates( +<open-source-office@arm\.com>)?( \*\/)?$)|" + \
                                      r"(^(;|#)?( *(\/\*|\*|#|\/\/))? Copyright \(c\) 20\d\d(-20\d\d)? Arm Technology \(China\) Co., Ltd.All Rights Reserved\.( \*\/)?$)|" + \
                                      r"(^(;|#)?( *(\/\*|\*|#|\/\/))? <open-source-office@arm\.com>( \*\/)?$)"


తరగతి Kernel_శీర్షిక_Checker(శీర్షిక_Checker):
    నిర్వచనం __init__(
        self,
        శీర్షిక,
        padding=1000,
        ignored_files=ఏమీలేదు,
        ignored_ext=ఏమీలేదు,
        ignored_patterns=ఏమీలేదు,
        py_ext=ఏమీలేదు,
        asm_ext=ఏమీలేదు,
        మూడవ_party_patterns=ఏమీలేదు,
        copyright_regex = ఏమీలేదు
    ):
        పర().__init__(శీర్షిక, padding, ignored_files, ignored_ext, ignored_patterns,
                         py_ext, asm_ext, మూడవ_party_patterns, copyright_regex)

        self.armCollabRegex = re.compile(FREERTOS_ARM_COLLAB_COPYRIGHT_REGEX)

        self.arm_Collab_Files_నమూనా_List = []
        కొరకు నమూనా లో KERNEL_ARM_COLLAB_FILES_PATTERNS:
            self.arm_Collab_Files_నమూనా_List.append(re.compile(నమూనా))

    నిర్వచనం isArmCollabFile(self, మార్గం):
        కొరకు నమూనా లో self.arm_Collab_Files_నమూనా_List:
            ఒకవేళ నమూనా.సరిపోలిక(మార్గం):
                తిరిగి నిజం
        తిరిగి అబద్ధం

    నిర్వచనం checkArmCollabFile(self, మార్గం):
        isValid = అబద్ధం
        file_ext = os.మార్గం.splitext(మార్గం)[-1]

        తోడుగా open(మార్గం, encoding="utf-8", errors="ignore") ఇవ file:
            chunk = file.పఠ(పొడవు("".join(self.శీర్షిక)) + self.padding)
            పంక్తులు = [("%s\n" % పంక్తి) కొరకు పంక్తి లో chunk.strip().splitlines()][
                : పొడవు(self.శీర్షిక) + 2
            ]
            ఒకవేళ (పొడవు(పంక్తులు) > 0) మరియు (పంక్తులు[0].కనుగొను("#!") == 0):
                పంక్తులు.remove(పంక్తులు[0])
            ఒకవేళ (పొడవు(పంక్తులు) > 0) మరియు (పొడవు(పంక్తులు[-1].strip()) == 0):
                పంక్తులు.remove(పంక్తులు[-1])

        # Split lines in sections.
        శీర్షికలు = dict()
        శీర్షికలు["text"] = []
        శీర్షికలు["copyright"] = []
        శీర్షికలు["spdx"] = []
        కొరకు పంక్తి లో పంక్తులు:
            ఒకవేళ self.armCollabRegex.సరిపోలిక(పంక్తి):
                శీర్షికలు["copyright"].append(పంక్తి)
            లేదావేళ "SPDX-License-Identifier:" లో పంక్తి:
                శీర్షికలు["spdx"].append(పంక్తి)
            లేకపోతే:
                శీర్షికలు["text"].append(పంక్తి)

        పాఠ్యం_equal = self.is_Valid_శీర్షిక_Section(file_ext, "text", శీర్షికలు["text"])
        spdx_equal = self.is_Valid_శీర్షిక_Section(file_ext, "spdx", శీర్షికలు["spdx"])

        ఒకవేళ పాఠ్యం_equal మరియు spdx_equal:
            # Some files do not have "open-source-office@arm.com" line.
            ఒకవేళ పొడవు(శీర్షికలు["copyright"]) == 3 లేదా పొడవు(శీర్షికలు["copyright"]) == 2:
                isValid = నిజం

        తిరిగి isValid

    నిర్వచనం customCheck(self, మార్గం):
        isValid = అబద్ధం
        ఒకవేళ self.isArmCollabFile(మార్గం):
            isValid = self.checkArmCollabFile(మార్గం)
        తిరిగి isValid


నిర్వచనం ప్రధాన():
    parser = శీర్షిక_Checker.configArgParser()
    వాదనలు   = parser.parse_వాదనలు()

    # Configure the checks then run
    checker = Kernel_శీర్షిక_Checker(KERNEL_శీర్షిక,
                                  copyright_regex=FREERTOS_COPYRIGHT_REGEX,
                                  ignored_files=KERNEL_IGNORED_FILES,
                                  ignored_ext=KERNEL_IGNORED_EXTENSIONS,
                                  ignored_patterns=KERNEL_IGNORED_PATTERNS,
                                  మూడవ_party_patterns=KERNEL_మూడవ_PARTY_PATTERNS,
                                  py_ext=KERNEL_PY_EXTENSIONS,
                                  asm_ext=KERNEL_ASM_EXTENSIONS)
    checker.ignoreFile(os.మార్గం.విభజించు(__file__)[-1])

    rc = checker.process_వాదనలు(వాదనలు)
    ఒకవేళ rc:
        checker.showHelp(__file__)

    తిరిగి rc

ఒకవేళ __name__ == '__main__':
    exit(ప్రధాన())
