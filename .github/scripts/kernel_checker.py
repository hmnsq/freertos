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

استورد os
استورد re
من common.سرخی_checker استورد سرخی_Checker

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

KERNEL_تیجا_PARTY_PATTERNS = [
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

KERNEL_سرخی = [
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


صنف Kernel_سرخی_Checker(سرخی_Checker):
    تعریف __init__(
        self,
        سرخی,
        padding=1000,
        ignored_files=کجھ_نئیں,
        ignored_ext=کجھ_نئیں,
        ignored_patterns=کجھ_نئیں,
        py_ext=کجھ_نئیں,
        asm_ext=کجھ_نئیں,
        تیجا_party_patterns=کجھ_نئیں,
        copyright_regex = کجھ_نئیں
    ):
        أعلى().__init__(سرخی, padding, ignored_files, ignored_ext, ignored_patterns,
                         py_ext, asm_ext, تیجا_party_patterns, copyright_regex)

        self.armCollabRegex = re.compile(FREERTOS_ARM_COLLAB_COPYRIGHT_REGEX)

        self.arm_Collab_Files_نمونہ_List = []
        لكل نمونہ في KERNEL_ARM_COLLAB_FILES_PATTERNS:
            self.arm_Collab_Files_نمونہ_List.append(re.compile(نمونہ))

    تعریف isArmCollabFile(self, رستہ):
        لكل نمونہ في self.arm_Collab_Files_نمونہ_List:
            إذا نمونہ.میل(رستہ):
                أرجع سچ
        أرجع خطأ

    تعریف checkArmCollabFile(self, رستہ):
        isValid = خطأ
        file_ext = os.رستہ.splitext(رستہ)[-1]

        نال open(رستہ, encoding="utf-8", errors="ignore") كـ file:
            chunk = file.اقرأ(لمبائی("".join(self.سرخی)) + self.padding)
            سطریں = [("%s\n" % سطر) لكل سطر في chunk.strip().splitlines()][
                : لمبائی(self.سرخی) + 2
            ]
            إذا (لمبائی(سطریں) > 0) و (سطریں[0].لبھو("#!") == 0):
                سطریں.remove(سطریں[0])
            إذا (لمبائی(سطریں) > 0) و (لمبائی(سطریں[-1].strip()) == 0):
                سطریں.remove(سطریں[-1])

        # Split lines in sections.
        سرخیاں = dict()
        سرخیاں["text"] = []
        سرخیاں["copyright"] = []
        سرخیاں["spdx"] = []
        لكل سطر في سطریں:
            إذا self.armCollabRegex.میل(سطر):
                سرخیاں["copyright"].append(سطر)
            وإلاإذا "SPDX-License-Identifier:" في سطر:
                سرخیاں["spdx"].append(سطر)
            وإلا:
                سرخیاں["text"].append(سطر)

        متن_equal = self.is_Valid_سرخی_Section(file_ext, "text", سرخیاں["text"])
        spdx_equal = self.is_Valid_سرخی_Section(file_ext, "spdx", سرخیاں["spdx"])

        إذا متن_equal و spdx_equal:
            # Some files do not have "open-source-office@arm.com" line.
            إذا لمبائی(سرخیاں["copyright"]) == 3 أو لمبائی(سرخیاں["copyright"]) == 2:
                isValid = سچ

        أرجع isValid

    تعریف customCheck(self, رستہ):
        isValid = خطأ
        إذا self.isArmCollabFile(رستہ):
            isValid = self.checkArmCollabFile(رستہ)
        أرجع isValid


تعریف مکھ():
    parser = سرخی_Checker.configArgParser()
    دلیلاں   = parser.parse_دلیلاں()

    # Configure the checks then run
    checker = Kernel_سرخی_Checker(KERNEL_سرخی,
                                  copyright_regex=FREERTOS_COPYRIGHT_REGEX,
                                  ignored_files=KERNEL_IGNORED_FILES,
                                  ignored_ext=KERNEL_IGNORED_EXTENSIONS,
                                  ignored_patterns=KERNEL_IGNORED_PATTERNS,
                                  تیجا_party_patterns=KERNEL_تیجا_PARTY_PATTERNS,
                                  py_ext=KERNEL_PY_EXTENSIONS,
                                  asm_ext=KERNEL_ASM_EXTENSIONS)
    checker.ignoreFile(os.رستہ.ونڈو(__file__)[-1])

    rc = checker.process_دلیلاں(دلیلاں)
    إذا rc:
        checker.showHelp(__file__)

    أرجع rc

إذا __name__ == '__main__':
    exit(مکھ())
