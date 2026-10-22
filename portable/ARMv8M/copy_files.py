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

ਆਯਾਤ os
ਆਯਾਤ shutil

_THIS_FILE_DIRECTORY_ = os.ਰਸਤਾ.dirname(os.ਰਸਤਾ.realpath(__file__))
_FREERTOS_PORTABLE_DIRECTORY_ = os.ਰਸਤਾ.dirname(_THIS_FILE_DIRECTORY_)

_COMPILERS_ = ['GCC', 'IAR']
_ARCH_NS_ = ['ARM_CM85', 'ARM_CM85_NTZ', 'ARM_CM55', 'ARM_CM55_NTZ', 'ARM_CM52', 'ARM_CM52_NTZ', 'ARM_CM35P', 'ARM_CM35P_NTZ', 'ARM_CM33', 'ARM_CM33_NTZ', 'ARM_CM23', 'ARM_CM23_NTZ', 'ARM_STAR_MC3', 'ARM_STAR_MC3_NTZ']
_ARCH_S_ = ['ARM_CM85', 'ARM_CM55', 'ARM_CM52', 'ARM_CM35P', 'ARM_CM33', 'ARM_CM23', 'ARM_STAR_MC3']

# Files to be compiled in the Secure Project
_SECURE_COMMON_FILE_PATHS_ = [
    os.ਰਸਤਾ.join('secure', 'context'),
    os.ਰਸਤਾ.join('secure', 'heap'),
    os.ਰਸਤਾ.join('secure', 'init'),
    os.ਰਸਤਾ.join('secure', 'macros')
]

_SECURE_PORTABLE_FILE_PATHS_ = {
    'GCC':{
        'ARM_CM23'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM23')],
        'ARM_CM33'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM35P'    :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM52'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM55'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM85'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_STAR_MC3' :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'GCC', 'ARM_CM33')]
    },
    'IAR':{
        'ARM_CM23'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM23')],
        'ARM_CM33'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM35P'    :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM52'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM55'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM85'     :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_STAR_MC3' :[os.ਰਸਤਾ.join('secure', 'context', 'portable', 'IAR', 'ARM_CM33')]
    }
}

# Files to be compiled in the Non-Secure Project
_NONSECURE_COMMON_FILE_PATHS_ = [
    'non_secure'
]

_NONSECURE_PORTABLE_FILE_PATHS_ = {
    'GCC':{
        'ARM_CM23'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM23')],
        'ARM_CM23_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM23_NTZ')],
        'ARM_CM33'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33')],
        'ARM_CM33_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ')],
        'ARM_CM35P'        : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM35P', 'portmacro.h')],
        'ARM_CM35P_NTZ'    : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM35P', 'portmacro.h')],
        'ARM_CM52'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM52', 'portmacro.h')],
        'ARM_CM52_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM52', 'portmacro.h')],
        'ARM_CM55'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM55', 'portmacro.h')],
        'ARM_CM55_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM55', 'portmacro.h')],
        'ARM_CM85'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM85', 'portmacro.h')],
        'ARM_CM85_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM85', 'portmacro.h')],
        'ARM_STAR_MC3'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_STAR_MC3', 'portmacro.h')],
        'ARM_STAR_MC3_NTZ' : [os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'portasm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.c'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'GCC', 'ARM_STAR_MC3', 'portmacro.h')]
    },
    'IAR':{
        'ARM_CM23'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM23')],
        'ARM_CM23_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM23_NTZ')],
        'ARM_CM33'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33')],
        'ARM_CM33_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ')],
        'ARM_CM35P'        : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM35P', 'portmacro.h')],
        'ARM_CM35P_NTZ'    : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM35P', 'portmacro.h')],
        'ARM_CM52'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM52', 'portmacro.h')],
        'ARM_CM52_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM52', 'portmacro.h')],
        'ARM_CM55'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM55', 'portmacro.h')],
        'ARM_CM55_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM55', 'portmacro.h')],
        'ARM_CM85'         : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM85', 'portmacro.h')],
        'ARM_CM85_NTZ'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM85', 'portmacro.h')],
        'ARM_STAR_MC3'     : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_STAR_MC3', 'portmacro.h')],
        'ARM_STAR_MC3_NTZ' : [os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'portasm.s'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_CM33_NTZ', 'mpu_wrappers_v2_asm.S'),
                              os.ਰਸਤਾ.join('non_secure', 'portable', 'IAR', 'ARM_STAR_MC3', 'portmacro.h')]
    },
}


ਪਰਿਭਾਸ਼ਾ copy_files_ਵਿੱਚ_dir(src_abs_ਰਸਤਾ, dst_abs_ਰਸਤਾ):
    ਜੇ os.ਰਸਤਾ.isfile(src_abs_ਰਸਤਾ):
        ਛਾਪੋ('Src: {}'.format(src_abs_ਰਸਤਾ))
        ਛਾਪੋ('Dst: {}\n'.format(dst_abs_ਰਸਤਾ))
        shutil.copy2(src_abs_ਰਸਤਾ, dst_abs_ਰਸਤਾ)
    ਨਹੀਂਤਾਂ:
        ਲਈ src_file ਵਿੱਚ os.listdir(src_abs_ਰਸਤਾ):
            src_file_abs_ਰਸਤਾ = os.ਰਸਤਾ.join(src_abs_ਰਸਤਾ, src_file)
            ਜੇ os.ਰਸਤਾ.isfile(src_file_abs_ਰਸਤਾ) ਅਤੇ src_file != 'ReadMe.txt':
                ਜੇ ਨਹੀਂ os.ਰਸਤਾ.exists(dst_abs_ਰਸਤਾ):
                    os.makedirs(dst_abs_ਰਸਤਾ)
                ਛਾਪੋ('Src: {}'.format(src_file_abs_ਰਸਤਾ))
                ਛਾਪੋ('Dst: {}\n'.format(dst_abs_ਰਸਤਾ))
                shutil.copy2(src_file_abs_ਰਸਤਾ, dst_abs_ਰਸਤਾ)


ਪਰਿਭਾਸ਼ਾ copy_common_files_for_compiler_and_arch(compiler, arch, src_paths, dst_ਰਸਤਾ):
    ਲਈ src_ਰਸਤਾ ਵਿੱਚ src_paths:

        src_abs_ਰਸਤਾ = os.ਰਸਤਾ.join(_THIS_FILE_DIRECTORY_, src_ਰਸਤਾ)
        dst_abs_ਰਸਤਾ = os.ਰਸਤਾ.join(_FREERTOS_PORTABLE_DIRECTORY_, compiler, arch, dst_ਰਸਤਾ)

        copy_files_ਵਿੱਚ_dir(src_abs_ਰਸਤਾ, dst_abs_ਰਸਤਾ)


ਪਰਿਭਾਸ਼ਾ copy_portable_files_for_compiler_and_arch(compiler, arch, src_paths, dst_ਰਸਤਾ):
    ਲਈ src_ਰਸਤਾ ਵਿੱਚ src_paths[compiler][arch]:

        src_abs_ਰਸਤਾ = os.ਰਸਤਾ.join(_THIS_FILE_DIRECTORY_, src_ਰਸਤਾ)
        dst_abs_ਰਸਤਾ = os.ਰਸਤਾ.join(_FREERTOS_PORTABLE_DIRECTORY_, compiler, arch, dst_ਰਸਤਾ)

        copy_files_ਵਿੱਚ_dir(src_abs_ਰਸਤਾ, dst_abs_ਰਸਤਾ)


ਪਰਿਭਾਸ਼ਾ copy_files():
    # Copy Secure Files
    ਲਈ compiler ਵਿੱਚ _COMPILERS_:
        ਲਈ arch ਵਿੱਚ _ARCH_S_:
            copy_common_files_for_compiler_and_arch(compiler, arch, _SECURE_COMMON_FILE_PATHS_, 'secure')
            copy_portable_files_for_compiler_and_arch(compiler, arch, _SECURE_PORTABLE_FILE_PATHS_, 'secure')

    # Copy Non-Secure Files
    ਲਈ compiler ਵਿੱਚ _COMPILERS_:
        ਲਈ arch ਵਿੱਚ _ARCH_NS_:
            copy_common_files_for_compiler_and_arch(compiler, arch, _NONSECURE_COMMON_FILE_PATHS_, 'non_secure')
            copy_portable_files_for_compiler_and_arch(compiler, arch, _NONSECURE_PORTABLE_FILE_PATHS_, 'non_secure')


ਪਰਿਭਾਸ਼ਾ ਮੁੱਖ():
    copy_files()


ਜੇ __name__ == '__main__':
    ਮੁੱਖ()
