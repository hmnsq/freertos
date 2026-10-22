/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2024 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_ASM_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_ASM_H

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "FreeRTOSConfig.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಒಟ್ಟು_MPU_REGIONS
    #ದೋಷ "Set configTOTAL_MPU_REGIONS to the number of MPU regions in FreeRTOSConfig.h"
#ಅಥವಾಆದರೆ( config_ಒಟ್ಟು_MPU_REGIONS == 12 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_ಒಟ್ಟು_REGIONS ( 12UL )
#ಅಥವಾಆದರೆ( config_ಒಟ್ಟು_MPU_REGIONS == 16 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_ಒಟ್ಟು_REGIONS ( 16UL )
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ "Set configTOTAL_MPU_REGIONS to the number of MPU regions in FreeRTOSConfig.h"
#ಆದರೆ_ಅಂತ್ಯ /* configTOTAL_MPU_REGIONS */

/*
 * The application write can disable Floating Point Unit (FPU) support by
 * setting configENABLE_FPU to 0. Floating point context stored in TCB
 * comprises of 32 floating point registers (D0-D31) and FPSCR register.
 * Disabling FPU, therefore, reduces the per-task RAM usage by
 * ( 32 + 1 ) * 4 = 132 bytes per task.
 *
 * BE CAREFUL DISABLING THIS: Certain standard library APIs try to optimize
 * themselves by using the floating point registers. If the FPU support is
 * disabled, the use of such APIs may result in memory corruption.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_FPU
    #ವ್ಯಾಖ್ಯಾನಿಸು configENABLE_FPU    1
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_FPU */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_FPU configENABLE_FPU

/* On the ArmV7-R Architecture the Operating mode of the Processor is set
 * using the Current Program Status Register (CPSR) Mode bits, [4:0]. The only
 * unprivileged mode is User Mode.
 *
 * Additional information about the Processor Modes can be found here:
 * https://developer.arm.com/documentation/ddi0406/cb/System-Level-Architecture/The-System-Level-Programmers--Model/ARM-processor-modes-and-ARM-core-registers/ARM-processor-modes?lang=en
 *
 */

/**
 * @brief CPSR bits for various processor modes.
 *
 * @ingroup Port Privilege
 */
#ವ್ಯಾಖ್ಯಾನಿಸು USER_ಬಹುಲಕ   0x10U
#ವ್ಯಾಖ್ಯಾನಿಸು FIQ_ಬಹುಲಕ    0x11U
#ವ್ಯಾಖ್ಯಾನಿಸು IRQ_ಬಹುಲಕ    0x12U
#ವ್ಯಾಖ್ಯಾನಿಸು SVC_ಬಹುಲಕ    0x13U
#ವ್ಯಾಖ್ಯಾನಿಸು MON_ಬಹುಲಕ    0x16U
#ವ್ಯಾಖ್ಯಾನಿಸು ABT_ಬಹುಲಕ    0x17U
#ವ್ಯಾಖ್ಯಾನಿಸು HYP_ಬಹುಲಕ    0x1AU
#ವ್ಯಾಖ್ಯಾನಿಸು UND_ಬಹುಲಕ    0x1BU
#ವ್ಯಾಖ್ಯಾನಿಸು SYS_ಬಹುಲಕ    0x1FU

/**
 * @brief Flag used to mark that a FreeRTOS Task is privileged.
 *
 * @ingroup Port Privilege
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

/**
 * @brief SVC numbers for various scheduler operations.
 *
 * @ingroup Scheduler
 *
 * @note These value must not be used in mpu_syscall_numbers.h.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_YIELD                 0x0100U
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_SYSTEM_CALL_EXIT      0x0104U

/**
 * @brief Macros required to manipulate MPU.
 *
 * Further information about MPU can be found in Arm's documentation
 * https://developer.arm.com/documentation/ddi0363/g/System-Control/Register-descriptions/c6--MPU-memory-region-programming-registers
 *
 */

/* MPU sub-region disable settings. This information is encoded in the MPU
 * Region Size and Enable Register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_SUBREGION_0_DISABLE   ( 0x1UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_SUBREGION_1_DISABLE   ( 0x1UL << 9UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_SUBREGION_2_DISABLE   ( 0x1UL << 10UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_SUBREGION_3_DISABLE   ( 0x1UL << 11UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_SUBREGION_4_DISABLE   ( 0x1UL << 12UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_SUBREGION_5_DISABLE   ( 0x1UL << 13UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_SUBREGION_6_DISABLE   ( 0x1UL << 14UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_SUBREGION_7_DISABLE   ( 0x1UL << 15UL )

/* Default MPU regions. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_CONFIGURABLE_REGION ( 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆಯ_CONFIGURABLE_REGION  ( ಪೋರ್ಟ್_MPU_ಒಟ್ಟು_REGIONS - 5UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_REGION              ( ಪೋರ್ಟ್_MPU_ಒಟ್ಟು_REGIONS - 4UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION ( ಪೋರ್ಟ್_MPU_ಒಟ್ಟು_REGIONS - 3UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION   ( ಪೋರ್ಟ್_MPU_ಒಟ್ಟು_REGIONS - 2UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION     ( ಪೋರ್ಟ್_MPU_ಒಟ್ಟು_REGIONS - 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS \
    ( ( ಪೋರ್ಟ್_ಕೊನೆಯ_CONFIGURABLE_REGION - ಪೋರ್ಟ್_ಮೊದಲ_CONFIGURABLE_REGION ) + 1UL )
/* Plus one to make space for the stack region. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS_ಒಳ_TCB        ( ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS + 1UL )

/* MPU region sizes. This information is encoded in the MPU Region Size and
 * Enable Register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_32_B             ( 0x04UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_64_B             ( 0x05UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_128_B            ( 0x06UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_256_B            ( 0x07UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_512_B            ( 0x08UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_1_KB             ( 0x09UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_2_KB             ( 0x0AUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_4_KB             ( 0x0BUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_8_KB             ( 0x0CUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_16_KB            ( 0x0DUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_32_KB            ( 0x0EUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_64_KB            ( 0x0FUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_128_KB           ( 0x10UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_256_KB           ( 0x11UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_512_KB           ( 0x12UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_1_MB             ( 0x13UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_2_MB             ( 0x14UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_4_MB             ( 0x15UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_8_MB             ( 0x16UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_16_MB            ( 0x17UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_32_MB            ( 0x18UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_64_MB            ( 0x19UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_128_MB           ( 0x1AUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_256_MB           ( 0x1BUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_512_MB           ( 0x1CUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_1_GB             ( 0x1DUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_2_GB             ( 0x1EUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the TEX, S, C and B bits
 * of the MPU Region Access Control Register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_STRONGLY_ORDERED_SHAREABLE  ( 0x00UL ) /* TEX=000, S=NA, C=0, B=0. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_DEVICE_SHAREABLE            ( 0x01UL ) /* TEX=000, S=NA, C=0, B=1. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWTNOWA_NONSHARED   ( 0x02UL ) /* TEX=000, S=0, C=1, B=0. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWTNOWA_SHARED      ( 0x06UL ) /* TEX=000, S=1, C=1, B=0. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWBNOWA_NONSHARED   ( 0x03UL ) /* TEX=000, S=0, C=1, B=1. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWBNOWA_SHARED      ( 0x07UL ) /* TEX=000, S=1, C=1, B=1. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OINC_NONSHARED       ( 0x08UL ) /* TEX=001, S=0, C=0, B=0. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OINC_SHARED          ( 0x0CUL ) /* TEX=001, S=1, C=0, B=0. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWBWA_NONSHARED     ( 0x0BUL ) /* TEX=001, S=0, C=1, B=1. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWBWA_SHARED        ( 0x0FUL ) /* TEX=001, S=1, C=1, B=1. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_DEVICE_NONSHAREABLE         ( 0x10UL ) /* TEX=010, S=NA, C=0, B=0. */

/* MPU access permissions. This information is encoded in the XN and AP bits of
 * the MPU Region Access Control Register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_AP_BITMASK                  ( 0x07UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_XN_BITMASK                  ( 0x01UL << 12UL )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_NA_USER_NA             ( 0x00UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_NA_USER_NA_EXEC        ( ಪೋರ್ಟ್_MPU_REGION_PRIV_NA_USER_NA ) /* Priv: X, Unpriv: X. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_NA_USER_NA_NOEXEC      ( ಪೋರ್ಟ್_MPU_REGION_PRIV_NA_USER_NA | \
                                                     ಪೋರ್ಟ್_MPU_REGION_XN_BITMASK ) /* Priv: No Access, Unpriv: No Access. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_NA             ( 0x01UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_NA_EXEC        ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_NA ) /* Priv: RWX, Unpriv: X. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_NA_NOEXEC      ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_NA | \
                                                     ಪೋರ್ಟ್_MPU_REGION_XN_BITMASK ) /* Priv: RW, Unpriv: No access. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RO             ( 0x02UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RO_EXEC        ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RO ) /* Priv: RWX, Unpriv: RX. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RO_NOEXEC      ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RO | \
                                                     ಪೋರ್ಟ್_MPU_REGION_XN_BITMASK ) /* Priv: RW, Unpriv: R. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RW             ( 0x03UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RW_EXEC        ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RW ) /* Priv: RWX, Unpriv: RWX. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RW_NOEXEC      ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RW | \
                                                     ಪೋರ್ಟ್_MPU_REGION_XN_BITMASK ) /* Priv: RW, Unpriv: RW. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_NA             ( 0x05UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_NA_EXEC        ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_NA ) /* Priv: RX, Unpriv: X. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_NA_NOEXEC      ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_NA | \
                                                     ಪೋರ್ಟ್_MPU_REGION_XN_BITMASK ) /* Priv: R, Unpriv: No access. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_RO             ( 0x06UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_RO_EXEC        ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_RO ) /* Priv: RX, Unpriv: RX. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_RO_NOEXEC      ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_RO | \
                                                     ಪೋರ್ಟ್_MPU_REGION_XN_BITMASK ) /* Priv: R, Unpriv: R. */

/* MPU region management. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER               ( 0x01UL << 12UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ENABLE                      ( 0x01UL )

/**
 * @brief The size (in words) of a task context.
 *
 * An array of this size is allocated in TCB where a task's context is saved
 * when it is switched out.
 *
 * Information about Floating Point Unit (FPU):
 * https://developer.arm.com/documentation/den0042/a/Floating-Point
 *
 * Additional information related to the Cortex R4-F's FPU Implementation:
 * https://developer.arm.com/documentation/ddi0363/e/fpu-programmer-s-model
 *
 * Additional information related to the Cortex R5-F's FPU Implementation:
 * https://developer.arm.com/documentation/ddi0460/d/FPU-Programmers-Model
 *
 * Additional information related to the ArmV7-R CPSR:
 * https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Application-Level-Programmers--Model/The-Application-Program-Status-Register--APSR-?lang=en
 *
 * Additional information related to the GPRs:
 * https://developer.arm.com/documentation/ddi0406/cb/System-Level-Architecture/The-System-Level-Programmers--Model/ARM-processor-modes-and-ARM-core-registers/ARM-core-registers?lang=en
 *
 */

#ಆದರೆ( ಪೋರ್ಟ್_ENABLE_FPU == 1 )
    /*
     * +-------------------+-------+----------+--------+----------+----------+----------+------+
     * | ulCriticalNesting | FPSCR |  S0-S31  | R0-R12 | SP (R13) | LR (R14) | PC (R15) | CPSR |
     * +-------------------+-------+----------+--------+----------+----------+----------+------+
     *
     * <------------------><------><---------><--------><---------><--------><----------><----->
     *           1            1        32         13         1         1          1        1
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು CONTEXT_ಗಾತ್ರ 51U
#ಇಲ್ಲದಿದ್ದರೆ
    /*
     * +-------------------+--------+----------+----------+----------+------+
     * | ulCriticalNesting | R0-R12 | SP (R13) | LR (R14) | PC (R15) | CPSR |
     * +-------------------+--------+----------+----------+----------+------+
     *
     * <------------------><--------><---------><--------><----------><----->
     *           1             13         1         1          1        1
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು CONTEXT_ಗಾತ್ರ 18U
#ಆದರೆ_ಅಂತ್ಯ /* CONTEXT_SIZE */

/**
 * @brief Offset of xSystemCallStackInfo from the start of a TCB.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SYSTEM_CALL_INFO_ಸ್ಥಾನಾಂತರ             \
    ( ( 1U /* pxTopOfStack. */ +                \
        ( ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS_ಒಳ_TCB * 3U ) + \
        1U /* ulTaskFlags. */                   \
      ) * 4U )

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
} /* extern C */
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_ASM_H */
