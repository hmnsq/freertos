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

आनयन os
आनयन re
तः common.शीर्षकम्_checker आनयन शीर्षकम्_Checker

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

KERNEL_THIRD_PARTY_PATTERNS = [
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

KERNEL_शीर्षकम् = [
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


वर्ग Kernel_शीर्षकम्_Checker(शीर्षकम्_Checker):
    परिभाषा __init__(
        self,
        शीर्षकम्,
        padding=1000,
        ignored_files=किमपि_न,
        ignored_ext=किमपि_न,
        ignored_patterns=किमपि_न,
        py_ext=किमपि_न,
        asm_ext=किमपि_न,
        third_party_patterns=किमपि_न,
        copyright_regex = किमपि_न
    ):
        पर().__init__(शीर्षकम्, padding, ignored_files, ignored_ext, ignored_patterns,
                         py_ext, asm_ext, third_party_patterns, copyright_regex)

        self.armCollabRegex = re.compile(FREERTOS_ARM_COLLAB_COPYRIGHT_REGEX)

        self.arm_Collab_Files_आदर्शः_List = []
        प्रति आदर्शः अन्तः KERNEL_ARM_COLLAB_FILES_PATTERNS:
            self.arm_Collab_Files_आदर्शः_List.append(re.compile(आदर्शः))

    परिभाषा isArmCollabFile(self, मार्गः):
        प्रति आदर्शः अन्तः self.arm_Collab_Files_आदर्शः_List:
            यदि आदर्शः.मेलनम्(मार्गः):
                प्रत्यागम सत्य
        प्रत्यागम असत्य

    परिभाषा checkArmCollabFile(self, मार्गः):
        isValid = असत्य
        file_ext = os.मार्गः.splitext(मार्गः)[-1]

        सह open(मार्गः, encoding="utf-8", errors="ignore") इव file:
            chunk = file.पठ(दीर्घता("".join(self.शीर्षकम्)) + self.padding)
            पङ्क्तयः = [("%s\n" % पङ्क्तिः) प्रति पङ्क्तिः अन्तः chunk.strip().splitlines()][
                : दीर्घता(self.शीर्षकम्) + 2
            ]
            यदि (दीर्घता(पङ्क्तयः) > 0) च (पङ्क्तयः[0].find("#!") == 0):
                पङ्क्तयः.remove(पङ्क्तयः[0])
            यदि (दीर्घता(पङ्क्तयः) > 0) च (दीर्घता(पङ्क्तयः[-1].strip()) == 0):
                पङ्क्तयः.remove(पङ्क्तयः[-1])

        # Split lines in sections.
        शीर्षकाणि = dict()
        शीर्षकाणि["text"] = []
        शीर्षकाणि["copyright"] = []
        शीर्षकाणि["spdx"] = []
        प्रति पङ्क्तिः अन्तः पङ्क्तयः:
            यदि self.armCollabRegex.मेलनम्(पङ्क्तिः):
                शीर्षकाणि["copyright"].append(पङ्क्तिः)
            नोचेद्यदि "SPDX-License-Identifier:" अन्तः पङ्क्तिः:
                शीर्षकाणि["spdx"].append(पङ्क्तिः)
            अन्यथा:
                शीर्षकाणि["text"].append(पङ्क्तिः)

        text_equal = self.is_Valid_शीर्षकम्_Section(file_ext, "text", शीर्षकाणि["text"])
        spdx_equal = self.is_Valid_शीर्षकम्_Section(file_ext, "spdx", शीर्षकाणि["spdx"])

        यदि text_equal च spdx_equal:
            # Some files do not have "open-source-office@arm.com" line.
            यदि दीर्घता(शीर्षकाणि["copyright"]) == 3 वा दीर्घता(शीर्षकाणि["copyright"]) == 2:
                isValid = सत्य

        प्रत्यागम isValid

    परिभाषा customCheck(self, मार्गः):
        isValid = असत्य
        यदि self.isArmCollabFile(मार्गः):
            isValid = self.checkArmCollabFile(मार्गः)
        प्रत्यागम isValid


परिभाषा मुख्यम्():
    parser = शीर्षकम्_Checker.configArgParser()
    तर्काः   = parser.parse_तर्काः()

    # Configure the checks then run
    checker = Kernel_शीर्षकम्_Checker(KERNEL_शीर्षकम्,
                                  copyright_regex=FREERTOS_COPYRIGHT_REGEX,
                                  ignored_files=KERNEL_IGNORED_FILES,
                                  ignored_ext=KERNEL_IGNORED_EXTENSIONS,
                                  ignored_patterns=KERNEL_IGNORED_PATTERNS,
                                  third_party_patterns=KERNEL_THIRD_PARTY_PATTERNS,
                                  py_ext=KERNEL_PY_EXTENSIONS,
                                  asm_ext=KERNEL_ASM_EXTENSIONS)
    checker.ignoreFile(os.मार्गः.विभज(__file__)[-1])

    rc = checker.process_तर्काः(तर्काः)
    यदि rc:
        checker.showHelp(__file__)

    प्रत्यागम rc

यदि __name__ == '__main__':
    exit(मुख्यम्())
