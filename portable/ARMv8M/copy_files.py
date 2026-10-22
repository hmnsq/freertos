#/*
# * FreeRTOS Kernel <DEVELOPMENT BRANCH>
# * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
ಆಮದು shutil

_THIS_FILE_DIRECTORY_ = os.ಮಾರ್ಗ.dirname(os.ಮಾರ್ಗ.realpath(__file__))
_FREERTOS_PORTABLE_DIRECTORY_ = os.ಮಾರ್ಗ.dirname(_THIS_FILE_DIRECTORY_)

_COMPILERS_ = ['GCC', 'IAR']
_ARCH_NS_ = ['ARM_CM85', 'ARM_CM85_NTZ', 'ARM_CM55', 'ARM_CM55_NTZ', 'ARM_CM52', 'ARM_CM52_NTZ', 'ARM_CM35P', 'ARM_CM35P_NTZ', 'ARM_CM33', 'ARM_CM33_NTZ', 'ARM_CM23', 'ARM_CM23_NTZ', 'ARM_STAR_MC3', 'ARM_STAR_MC3_NTZ']
_ARCH_S_ = ['ARM_CM85', 'ARM_CM55', 'ARM_CM52', 'ARM_CM35P', 'ARM_CM33', 'ARM_CM23', 'ARM_STAR_MC3']

# Files to be compiled in the Secure Project
_SECURE_COMMON_FILE_PATHS_ = [
    os.ಮಾರ್ಗ.join('secure', 'context'),
    os.ಮಾರ್ಗ.join('secure', 'heap'),
    os.ಮಾರ್ಗ.join('secure', 'init'),
    os.ಮಾರ್ಗ.join('secure', 'macros')
]

_SECURE_PORTABLE_FILE_PATHS_ = {
    'GCC':{
        'ARM_CM23'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM23')],
        'ARM_CM33'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM35P'    :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM52'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM55'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM85'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_STAR_MC3' :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')]
    },
    'IAR':{
        'ARM_CM23'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM23')],
        'ARM_CM33'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM35P'    :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM52'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM55'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM85'     :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_STAR_MC3' :[os.ಮಾರ್ಗ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')]
    }
}

# Files to be compiled in the Non-Secure Project
_NONSECURE_COMMON_FILE_PATHS_ = [
    'non_secure'
]

_NONSECURE_PORTABLE_FILE_PATHS_ = {
    'GCC':{
        'ARM_CM23'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM23')],
        'ARM_CM23_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM23_NTZ')],
        'ARM_CM33'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM33_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ')],
        'ARM_CM35P'        : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM35P', 'portmacro.h')],
        'ARM_CM35P_NTZ'    : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM35P', 'portmacro.h')],
        'ARM_CM52'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM52', 'portmacro.h')],
        'ARM_CM52_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM52', 'portmacro.h')],
        'ARM_CM55'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM55', 'portmacro.h')],
        'ARM_CM55_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM55', 'portmacro.h')],
        'ARM_CM85'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM85', 'portmacro.h')],
        'ARM_CM85_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM85', 'portmacro.h')],
        'ARM_STAR_MC3'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_STAR_MC3', 'portmacro.h')],
        'ARM_STAR_MC3_NTZ' : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'GCC', 'ARM_STAR_MC3', 'portmacro.h')]
    },
    'IAR':{
        'ARM_CM23'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM23')],
        'ARM_CM23_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM23_NTZ')],
        'ARM_CM33'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM33_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ')],
        'ARM_CM35P'        : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM35P', 'portmacro.h')],
        'ARM_CM35P_NTZ'    : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM35P', 'portmacro.h')],
        'ARM_CM52'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM52', 'portmacro.h')],
        'ARM_CM52_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM52', 'portmacro.h')],
        'ARM_CM55'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM55', 'portmacro.h')],
        'ARM_CM55_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM55', 'portmacro.h')],
        'ARM_CM85'         : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM85', 'portmacro.h')],
        'ARM_CM85_NTZ'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM85', 'portmacro.h')],
        'ARM_STAR_MC3'     : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_STAR_MC3', 'portmacro.h')],
        'ARM_STAR_MC3_NTZ' : [os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ಮಾರ್ಗ.join('non_secure', 'portable', 'IAR', 'ARM_STAR_MC3', 'portmacro.h')]
    },
}


ವ್ಯಾಖ್ಯಾನ copy_files_ಒಳ_dir(src_abs_ಮಾರ್ಗ, dst_abs_ಮಾರ್ಗ):
    ಆದರೆ os.ಮಾರ್ಗ.isfile(src_abs_ಮಾರ್ಗ):
        ಮುದ್ರಿಸು('Src: {}'.format(src_abs_ಮಾರ್ಗ))
        ಮುದ್ರಿಸು('Dst: {}\n'.format(dst_abs_ಮಾರ್ಗ))
        shutil.copy2(src_abs_ಮಾರ್ಗ, dst_abs_ಮಾರ್ಗ)
    ಇಲ್ಲದಿದ್ದರೆ:
        ಗಾಗಿ src_file ಒಳಗೆ os.listdir(src_abs_ಮಾರ್ಗ):
            src_file_abs_ಮಾರ್ಗ = os.ಮಾರ್ಗ.join(src_abs_ಮಾರ್ಗ, src_file)
            ಆದರೆ os.ಮಾರ್ಗ.isfile(src_file_abs_ಮಾರ್ಗ) ಮತ್ತು src_file != 'ReadMe.txt':
                ಆದರೆ ಅಲ್ಲ os.ಮಾರ್ಗ.exists(dst_abs_ಮಾರ್ಗ):
                    os.makedirs(dst_abs_ಮಾರ್ಗ)
                ಮುದ್ರಿಸು('Src: {}'.format(src_file_abs_ಮಾರ್ಗ))
                ಮುದ್ರಿಸು('Dst: {}\n'.format(dst_abs_ಮಾರ್ಗ))
                shutil.copy2(src_file_abs_ಮಾರ್ಗ, dst_abs_ಮಾರ್ಗ)


ವ್ಯಾಖ್ಯಾನ copy_common_files_for_compiler_and_arch(compiler, arch, src_paths, dst_ಮಾರ್ಗ):
    ಗಾಗಿ src_ಮಾರ್ಗ ಒಳಗೆ src_paths:

        src_abs_ಮಾರ್ಗ = os.ಮಾರ್ಗ.join(_THIS_FILE_DIRECTORY_, src_ಮಾರ್ಗ)
        dst_abs_ಮಾರ್ಗ = os.ಮಾರ್ಗ.join(_FREERTOS_PORTABLE_DIRECTORY_, compiler, arch, dst_ಮಾರ್ಗ)

        copy_files_ಒಳ_dir(src_abs_ಮಾರ್ಗ, dst_abs_ಮಾರ್ಗ)


ವ್ಯಾಖ್ಯಾನ copy_portable_files_for_compiler_and_arch(compiler, arch, src_paths, dst_ಮಾರ್ಗ):
    ಗಾಗಿ src_ಮಾರ್ಗ ಒಳಗೆ src_paths[compiler][arch]:

        src_abs_ಮಾರ್ಗ = os.ಮಾರ್ಗ.join(_THIS_FILE_DIRECTORY_, src_ಮಾರ್ಗ)
        dst_abs_ಮಾರ್ಗ = os.ಮಾರ್ಗ.join(_FREERTOS_PORTABLE_DIRECTORY_, compiler, arch, dst_ಮಾರ್ಗ)

        copy_files_ಒಳ_dir(src_abs_ಮಾರ್ಗ, dst_abs_ಮಾರ್ಗ)


ವ್ಯಾಖ್ಯಾನ copy_files():
    # Copy Secure Files
    ಗಾಗಿ compiler ಒಳಗೆ _COMPILERS_:
        ಗಾಗಿ arch ಒಳಗೆ _ARCH_S_:
            copy_common_files_for_compiler_and_arch(compiler, arch, _SECURE_COMMON_FILE_PATHS_, 'secure')
            copy_portable_files_for_compiler_and_arch(compiler, arch, _SECURE_PORTABLE_FILE_PATHS_, 'secure')

    # Copy Non-Secure Files
    ಗಾಗಿ compiler ಒಳಗೆ _COMPILERS_:
        ಗಾಗಿ arch ಒಳಗೆ _ARCH_NS_:
            copy_common_files_for_compiler_and_arch(compiler, arch, _NONSECURE_COMMON_FILE_PATHS_, 'non_secure')
            copy_portable_files_for_compiler_and_arch(compiler, arch, _NONSECURE_PORTABLE_FILE_PATHS_, 'non_secure')


ವ್ಯಾಖ್ಯಾನ ಮುಖ್ಯ():
    copy_files()


ಆದರೆ __name__ == '__main__':
    ಮುಖ್ಯ()
