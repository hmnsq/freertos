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
من common.سرلیک_checker استورد سرلیک_Checker

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

KERNEL_دریم_PARTY_PATTERNS = [
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

KERNEL_سرلیک = [
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


صنف Kernel_سرلیک_Checker(سرلیک_Checker):
    تعریف __init__(
        self,
        سرلیک,
        padding=1000,
        ignored_files=هیڅ,
        ignored_ext=هیڅ,
        ignored_patterns=هیڅ,
        py_ext=هیڅ,
        asm_ext=هیڅ,
        دریم_party_patterns=هیڅ,
        copyright_regex = هیڅ
    ):
        أعلى().__init__(سرلیک, padding, ignored_files, ignored_ext, ignored_patterns,
                         py_ext, asm_ext, دریم_party_patterns, copyright_regex)

        self.armCollabRegex = re.compile(FREERTOS_ARM_COLLAB_COPYRIGHT_REGEX)

        self.arm_Collab_Files_نمونه_List = []
        لكل نمونه في KERNEL_ARM_COLLAB_FILES_PATTERNS:
            self.arm_Collab_Files_نمونه_List.append(re.compile(نمونه))

    تعریف isArmCollabFile(self, لار):
        لكل نمونه في self.arm_Collab_Files_نمونه_List:
            إذا نمونه.سمون(لار):
                أرجع ریښتیا
        أرجع خطأ

    تعریف checkArmCollabFile(self, لار):
        isValid = خطأ
        file_ext = os.لار.splitext(لار)[-1]

        سره open(لار, encoding="utf-8", errors="ignore") كـ file:
            chunk = file.اقرأ(اوږدوالی("".join(self.سرلیک)) + self.padding)
            کرښې = [("%s\n" % کرښه) لكل کرښه في chunk.strip().splitlines()][
                : اوږدوالی(self.سرلیک) + 2
            ]
            إذا (اوږدوالی(کرښې) > 0) و (کرښې[0].پیدا_کړه("#!") == 0):
                کرښې.remove(کرښې[0])
            إذا (اوږدوالی(کرښې) > 0) و (اوږدوالی(کرښې[-1].strip()) == 0):
                کرښې.remove(کرښې[-1])

        # Split lines in sections.
        سرلیکونه = dict()
        سرلیکونه["text"] = []
        سرلیکونه["copyright"] = []
        سرلیکونه["spdx"] = []
        لكل کرښه في کرښې:
            إذا self.armCollabRegex.سمون(کرښه):
                سرلیکونه["copyright"].append(کرښه)
            وإلاإذا "SPDX-License-Identifier:" في کرښه:
                سرلیکونه["spdx"].append(کرښه)
            وإلا:
                سرلیکونه["text"].append(کرښه)

        متن_equal = self.is_Valid_سرلیک_Section(file_ext, "text", سرلیکونه["text"])
        spdx_equal = self.is_Valid_سرلیک_Section(file_ext, "spdx", سرلیکونه["spdx"])

        إذا متن_equal و spdx_equal:
            # Some files do not have "open-source-office@arm.com" line.
            إذا اوږدوالی(سرلیکونه["copyright"]) == 3 أو اوږدوالی(سرلیکونه["copyright"]) == 2:
                isValid = ریښتیا

        أرجع isValid

    تعریف customCheck(self, لار):
        isValid = خطأ
        إذا self.isArmCollabFile(لار):
            isValid = self.checkArmCollabFile(لار)
        أرجع isValid


تعریف اصلي():
    parser = سرلیک_Checker.configArgParser()
    دلیلونه   = parser.parse_دلیلونه()

    # Configure the checks then run
    checker = Kernel_سرلیک_Checker(KERNEL_سرلیک,
                                  copyright_regex=FREERTOS_COPYRIGHT_REGEX,
                                  ignored_files=KERNEL_IGNORED_FILES,
                                  ignored_ext=KERNEL_IGNORED_EXTENSIONS,
                                  ignored_patterns=KERNEL_IGNORED_PATTERNS,
                                  دریم_party_patterns=KERNEL_دریم_PARTY_PATTERNS,
                                  py_ext=KERNEL_PY_EXTENSIONS,
                                  asm_ext=KERNEL_ASM_EXTENSIONS)
    checker.ignoreFile(os.لار.وېشل(__file__)[-1])

    rc = checker.process_دلیلونه(دلیلونه)
    إذا rc:
        checker.showHelp(__file__)

    أرجع rc

إذا __name__ == '__main__':
    exit(اصلي())
