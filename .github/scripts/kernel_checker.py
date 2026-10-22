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

ਆਯਾਤ os
ਆਯਾਤ re
ਤਃ common.ਸਿਰਲੇਖ_checker ਆਯਾਤ ਸਿਰਲੇਖ_Checker

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

KERNEL_ਤੀਜਾ_PARTY_PATTERNS = [
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

KERNEL_ਸਿਰਲੇਖ = [
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


ਵਰਗ Kernel_ਸਿਰਲੇਖ_Checker(ਸਿਰਲੇਖ_Checker):
    ਪਰਿਭਾਸ਼ਾ __init__(
        self,
        ਸਿਰਲੇਖ,
        padding=1000,
        ignored_files=ਕੁਝ_ਨਹੀਂ,
        ignored_ext=ਕੁਝ_ਨਹੀਂ,
        ignored_patterns=ਕੁਝ_ਨਹੀਂ,
        py_ext=ਕੁਝ_ਨਹੀਂ,
        asm_ext=ਕੁਝ_ਨਹੀਂ,
        ਤੀਜਾ_party_patterns=ਕੁਝ_ਨਹੀਂ,
        copyright_regex = ਕੁਝ_ਨਹੀਂ
    ):
        ਪਰਮ().__init__(ਸਿਰਲੇਖ, padding, ignored_files, ignored_ext, ignored_patterns,
                         py_ext, asm_ext, ਤੀਜਾ_party_patterns, copyright_regex)

        self.armCollabRegex = re.compile(FREERTOS_ARM_COLLAB_COPYRIGHT_REGEX)

        self.arm_Collab_Files_ਨਮੂਨਾ_List = []
        ਲਈ ਨਮੂਨਾ ਵਿੱਚ KERNEL_ARM_COLLAB_FILES_PATTERNS:
            self.arm_Collab_Files_ਨਮੂਨਾ_List.append(re.compile(ਨਮੂਨਾ))

    ਪਰਿਭਾਸ਼ਾ isArmCollabFile(self, ਰਸਤਾ):
        ਲਈ ਨਮੂਨਾ ਵਿੱਚ self.arm_Collab_Files_ਨਮੂਨਾ_List:
            ਜੇ ਨਮੂਨਾ.ਮੇਲ(ਰਸਤਾ):
                ਵਾਪਸ ਸੱਚ
        ਵਾਪਸ ਝੂਠ

    ਪਰਿਭਾਸ਼ਾ checkArmCollabFile(self, ਰਸਤਾ):
        isValid = ਝੂਠ
        file_ext = os.ਰਸਤਾ.splitext(ਰਸਤਾ)[-1]

        ਨਾਲ open(ਰਸਤਾ, encoding="utf-8", errors="ignore") ਇਵ file:
            chunk = file.ਪਠ(ਲੰਬਾਈ("".join(self.ਸਿਰਲੇਖ)) + self.padding)
            ਸਤਰਾਂ = [("%s\n" % ਸਤਰ) ਲਈ ਸਤਰ ਵਿੱਚ chunk.strip().splitlines()][
                : ਲੰਬਾਈ(self.ਸਿਰਲੇਖ) + 2
            ]
            ਜੇ (ਲੰਬਾਈ(ਸਤਰਾਂ) > 0) ਅਤੇ (ਸਤਰਾਂ[0].ਲੱਭੋ("#!") == 0):
                ਸਤਰਾਂ.remove(ਸਤਰਾਂ[0])
            ਜੇ (ਲੰਬਾਈ(ਸਤਰਾਂ) > 0) ਅਤੇ (ਲੰਬਾਈ(ਸਤਰਾਂ[-1].strip()) == 0):
                ਸਤਰਾਂ.remove(ਸਤਰਾਂ[-1])

        # Split lines in sections.
        ਸਿਰਲੇਖਾਂ = dict()
        ਸਿਰਲੇਖਾਂ["text"] = []
        ਸਿਰਲੇਖਾਂ["copyright"] = []
        ਸਿਰਲੇਖਾਂ["spdx"] = []
        ਲਈ ਸਤਰ ਵਿੱਚ ਸਤਰਾਂ:
            ਜੇ self.armCollabRegex.ਮੇਲ(ਸਤਰ):
                ਸਿਰਲੇਖਾਂ["copyright"].append(ਸਤਰ)
            ਜਾਂਜੇ "SPDX-License-Identifier:" ਵਿੱਚ ਸਤਰ:
                ਸਿਰਲੇਖਾਂ["spdx"].append(ਸਤਰ)
            ਨਹੀਂਤਾਂ:
                ਸਿਰਲੇਖਾਂ["text"].append(ਸਤਰ)

        ਪਾਠ_equal = self.is_Valid_ਸਿਰਲੇਖ_Section(file_ext, "text", ਸਿਰਲੇਖਾਂ["text"])
        spdx_equal = self.is_Valid_ਸਿਰਲੇਖ_Section(file_ext, "spdx", ਸਿਰਲੇਖਾਂ["spdx"])

        ਜੇ ਪਾਠ_equal ਅਤੇ spdx_equal:
            # Some files do not have "open-source-office@arm.com" line.
            ਜੇ ਲੰਬਾਈ(ਸਿਰਲੇਖਾਂ["copyright"]) == 3 ਜਾਂ ਲੰਬਾਈ(ਸਿਰਲੇਖਾਂ["copyright"]) == 2:
                isValid = ਸੱਚ

        ਵਾਪਸ isValid

    ਪਰਿਭਾਸ਼ਾ customCheck(self, ਰਸਤਾ):
        isValid = ਝੂਠ
        ਜੇ self.isArmCollabFile(ਰਸਤਾ):
            isValid = self.checkArmCollabFile(ਰਸਤਾ)
        ਵਾਪਸ isValid


ਪਰਿਭਾਸ਼ਾ ਮੁੱਖ():
    parser = ਸਿਰਲੇਖ_Checker.configArgParser()
    ਦਲੀਲਾਂ   = parser.parse_ਦਲੀਲਾਂ()

    # Configure the checks then run
    checker = Kernel_ਸਿਰਲੇਖ_Checker(KERNEL_ਸਿਰਲੇਖ,
                                  copyright_regex=FREERTOS_COPYRIGHT_REGEX,
                                  ignored_files=KERNEL_IGNORED_FILES,
                                  ignored_ext=KERNEL_IGNORED_EXTENSIONS,
                                  ignored_patterns=KERNEL_IGNORED_PATTERNS,
                                  ਤੀਜਾ_party_patterns=KERNEL_ਤੀਜਾ_PARTY_PATTERNS,
                                  py_ext=KERNEL_PY_EXTENSIONS,
                                  asm_ext=KERNEL_ASM_EXTENSIONS)
    checker.ignoreFile(os.ਰਸਤਾ.ਵੰਡੋ(__file__)[-1])

    rc = checker.process_ਦਲੀਲਾਂ(ਦਲੀਲਾਂ)
    ਜੇ rc:
        checker.showHelp(__file__)

    ਵਾਪਸ rc

ਜੇ __name__ == '__main__':
    exit(ਮੁੱਖ())
