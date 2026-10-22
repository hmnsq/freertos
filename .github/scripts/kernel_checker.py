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
من common.سرآیند_checker استورد سرآیند_Checker

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

KERNEL_سوم_PARTY_PATTERNS = [
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

KERNEL_سرآیند = [
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


صنف Kernel_سرآیند_Checker(سرآیند_Checker):
    تعریف __init__(
        self,
        سرآیند,
        padding=1000,
        ignored_files=هیچ,
        ignored_ext=هیچ,
        ignored_patterns=هیچ,
        py_ext=هیچ,
        asm_ext=هیچ,
        سوم_party_patterns=هیچ,
        copyright_regex = هیچ
    ):
        أعلى().__init__(سرآیند, padding, ignored_files, ignored_ext, ignored_patterns,
                         py_ext, asm_ext, سوم_party_patterns, copyright_regex)

        self.armCollabRegex = re.compile(FREERTOS_ARM_COLLAB_COPYRIGHT_REGEX)

        self.arm_Collab_Files_الگو_List = []
        لكل الگو في KERNEL_ARM_COLLAB_FILES_PATTERNS:
            self.arm_Collab_Files_الگو_List.append(re.compile(الگو))

    تعریف isArmCollabFile(self, مسیر):
        لكل الگو في self.arm_Collab_Files_الگو_List:
            إذا الگو.تطابق(مسیر):
                أرجع درست
        أرجع خطأ

    تعریف checkArmCollabFile(self, مسیر):
        isValid = خطأ
        file_ext = os.مسیر.splitext(مسیر)[-1]

        با open(مسیر, encoding="utf-8", errors="ignore") كـ file:
            chunk = file.اقرأ(طول("".join(self.سرآیند)) + self.padding)
            سطرها = [("%s\n" % سطر) لكل سطر في chunk.strip().splitlines()][
                : طول(self.سرآیند) + 2
            ]
            إذا (طول(سطرها) > 0) و (سطرها[0].پیدا_کن("#!") == 0):
                سطرها.remove(سطرها[0])
            إذا (طول(سطرها) > 0) و (طول(سطرها[-1].strip()) == 0):
                سطرها.remove(سطرها[-1])

        # Split lines in sections.
        سرآیندها = dict()
        سرآیندها["text"] = []
        سرآیندها["copyright"] = []
        سرآیندها["spdx"] = []
        لكل سطر في سطرها:
            إذا self.armCollabRegex.تطابق(سطر):
                سرآیندها["copyright"].append(سطر)
            وإلاإذا "SPDX-License-Identifier:" في سطر:
                سرآیندها["spdx"].append(سطر)
            وإلا:
                سرآیندها["text"].append(سطر)

        متن_equal = self.is_Valid_سرآیند_Section(file_ext, "text", سرآیندها["text"])
        spdx_equal = self.is_Valid_سرآیند_Section(file_ext, "spdx", سرآیندها["spdx"])

        إذا متن_equal و spdx_equal:
            # Some files do not have "open-source-office@arm.com" line.
            إذا طول(سرآیندها["copyright"]) == 3 أو طول(سرآیندها["copyright"]) == 2:
                isValid = درست

        أرجع isValid

    تعریف customCheck(self, مسیر):
        isValid = خطأ
        إذا self.isArmCollabFile(مسیر):
            isValid = self.checkArmCollabFile(مسیر)
        أرجع isValid


تعریف اصلی():
    parser = سرآیند_Checker.configArgParser()
    آرگومانها   = parser.parse_آرگومانها()

    # Configure the checks then run
    checker = Kernel_سرآیند_Checker(KERNEL_سرآیند,
                                  copyright_regex=FREERTOS_COPYRIGHT_REGEX,
                                  ignored_files=KERNEL_IGNORED_FILES,
                                  ignored_ext=KERNEL_IGNORED_EXTENSIONS,
                                  ignored_patterns=KERNEL_IGNORED_PATTERNS,
                                  سوم_party_patterns=KERNEL_سوم_PARTY_PATTERNS,
                                  py_ext=KERNEL_PY_EXTENSIONS,
                                  asm_ext=KERNEL_ASM_EXTENSIONS)
    checker.ignoreFile(os.مسیر.تقسیم(__file__)[-1])

    rc = checker.process_آرگومانها(آرگومانها)
    إذا rc:
        checker.showHelp(__file__)

    أرجع rc

إذا __name__ == '__main__':
    exit(اصلی())
