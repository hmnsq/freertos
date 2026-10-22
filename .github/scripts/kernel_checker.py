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

ಆಮದು os
ಆಮದು re
ತಃ common.ಶೀರ್ಷಿಕೆ_checker ಆಮದು ಶೀರ್ಷಿಕೆ_Checker

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

KERNEL_ಮೂರನೇ_PARTY_PATTERNS = [
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

KERNEL_ಶೀರ್ಷಿಕೆ = [
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


ವರ್ಗ Kernel_ಶೀರ್ಷಿಕೆ_Checker(ಶೀರ್ಷಿಕೆ_Checker):
    ವ್ಯಾಖ್ಯಾನ __init__(
        self,
        ಶೀರ್ಷಿಕೆ,
        padding=1000,
        ignored_files=ಏನೂಇಲ್ಲ,
        ignored_ext=ಏನೂಇಲ್ಲ,
        ignored_patterns=ಏನೂಇಲ್ಲ,
        py_ext=ಏನೂಇಲ್ಲ,
        asm_ext=ಏನೂಇಲ್ಲ,
        ಮೂರನೇ_party_patterns=ಏನೂಇಲ್ಲ,
        copyright_regex = ಏನೂಇಲ್ಲ
    ):
        ಪರ().__init__(ಶೀರ್ಷಿಕೆ, padding, ignored_files, ignored_ext, ignored_patterns,
                         py_ext, asm_ext, ಮೂರನೇ_party_patterns, copyright_regex)

        self.armCollabRegex = re.compile(FREERTOS_ARM_COLLAB_COPYRIGHT_REGEX)

        self.arm_Collab_Files_ನಮೂನೆ_List = []
        ಗಾಗಿ ನಮೂನೆ ಒಳಗೆ KERNEL_ARM_COLLAB_FILES_PATTERNS:
            self.arm_Collab_Files_ನಮೂನೆ_List.append(re.compile(ನಮೂನೆ))

    ವ್ಯಾಖ್ಯಾನ isArmCollabFile(self, ಮಾರ್ಗ):
        ಗಾಗಿ ನಮೂನೆ ಒಳಗೆ self.arm_Collab_Files_ನಮೂನೆ_List:
            ಆದರೆ ನಮೂನೆ.ಹೊಂದಿಕೆ(ಮಾರ್ಗ):
                ಹಿಂತಿರುಗಿ ನಿಜ
        ಹಿಂತಿರುಗಿ ಸುಳ್ಳು

    ವ್ಯಾಖ್ಯಾನ checkArmCollabFile(self, ಮಾರ್ಗ):
        isValid = ಸುಳ್ಳು
        file_ext = os.ಮಾರ್ಗ.splitext(ಮಾರ್ಗ)[-1]

        ಜೊತೆ open(ಮಾರ್ಗ, encoding="utf-8", errors="ignore") ಇವ file:
            chunk = file.ಪಠ(ಉದ್ದ("".join(self.ಶೀರ್ಷಿಕೆ)) + self.padding)
            ಸಾಲುಗಳು = [("%s\n" % ಸಾಲು) ಗಾಗಿ ಸಾಲು ಒಳಗೆ chunk.strip().splitlines()][
                : ಉದ್ದ(self.ಶೀರ್ಷಿಕೆ) + 2
            ]
            ಆದರೆ (ಉದ್ದ(ಸಾಲುಗಳು) > 0) ಮತ್ತು (ಸಾಲುಗಳು[0].ಕಂಡುಹಿಡಿ("#!") == 0):
                ಸಾಲುಗಳು.remove(ಸಾಲುಗಳು[0])
            ಆದರೆ (ಉದ್ದ(ಸಾಲುಗಳು) > 0) ಮತ್ತು (ಉದ್ದ(ಸಾಲುಗಳು[-1].strip()) == 0):
                ಸಾಲುಗಳು.remove(ಸಾಲುಗಳು[-1])

        # Split lines in sections.
        ಶೀರ್ಷಿಕೆಗಳು = dict()
        ಶೀರ್ಷಿಕೆಗಳು["text"] = []
        ಶೀರ್ಷಿಕೆಗಳು["copyright"] = []
        ಶೀರ್ಷಿಕೆಗಳು["spdx"] = []
        ಗಾಗಿ ಸಾಲು ಒಳಗೆ ಸಾಲುಗಳು:
            ಆದರೆ self.armCollabRegex.ಹೊಂದಿಕೆ(ಸಾಲು):
                ಶೀರ್ಷಿಕೆಗಳು["copyright"].append(ಸಾಲು)
            ಅಥವಾಆದರೆ "SPDX-License-Identifier:" ಒಳಗೆ ಸಾಲು:
                ಶೀರ್ಷಿಕೆಗಳು["spdx"].append(ಸಾಲು)
            ಇಲ್ಲದಿದ್ದರೆ:
                ಶೀರ್ಷಿಕೆಗಳು["text"].append(ಸಾಲು)

        ಪಠ್ಯ_equal = self.is_Valid_ಶೀರ್ಷಿಕೆ_Section(file_ext, "text", ಶೀರ್ಷಿಕೆಗಳು["text"])
        spdx_equal = self.is_Valid_ಶೀರ್ಷಿಕೆ_Section(file_ext, "spdx", ಶೀರ್ಷಿಕೆಗಳು["spdx"])

        ಆದರೆ ಪಠ್ಯ_equal ಮತ್ತು spdx_equal:
            # Some files do not have "open-source-office@arm.com" line.
            ಆದರೆ ಉದ್ದ(ಶೀರ್ಷಿಕೆಗಳು["copyright"]) == 3 ಅಥವಾ ಉದ್ದ(ಶೀರ್ಷಿಕೆಗಳು["copyright"]) == 2:
                isValid = ನಿಜ

        ಹಿಂತಿರುಗಿ isValid

    ವ್ಯಾಖ್ಯಾನ customCheck(self, ಮಾರ್ಗ):
        isValid = ಸುಳ್ಳು
        ಆದರೆ self.isArmCollabFile(ಮಾರ್ಗ):
            isValid = self.checkArmCollabFile(ಮಾರ್ಗ)
        ಹಿಂತಿರುಗಿ isValid


ವ್ಯಾಖ್ಯಾನ ಮುಖ್ಯ():
    parser = ಶೀರ್ಷಿಕೆ_Checker.configArgParser()
    ವಾದಗಳು   = parser.parse_ವಾದಗಳು()

    # Configure the checks then run
    checker = Kernel_ಶೀರ್ಷಿಕೆ_Checker(KERNEL_ಶೀರ್ಷಿಕೆ,
                                  copyright_regex=FREERTOS_COPYRIGHT_REGEX,
                                  ignored_files=KERNEL_IGNORED_FILES,
                                  ignored_ext=KERNEL_IGNORED_EXTENSIONS,
                                  ignored_patterns=KERNEL_IGNORED_PATTERNS,
                                  ಮೂರನೇ_party_patterns=KERNEL_ಮೂರನೇ_PARTY_PATTERNS,
                                  py_ext=KERNEL_PY_EXTENSIONS,
                                  asm_ext=KERNEL_ASM_EXTENSIONS)
    checker.ignoreFile(os.ಮಾರ್ಗ.ವಿಭಜಿಸು(__file__)[-1])

    rc = checker.process_ವಾದಗಳು(ವಾದಗಳು)
    ಆದರೆ rc:
        checker.showHelp(__file__)

    ಹಿಂತಿರುಗಿ rc

ಆದರೆ __name__ == '__main__':
    exit(ಮುಖ್ಯ())
