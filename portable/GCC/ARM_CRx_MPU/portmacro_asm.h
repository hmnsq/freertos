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

#که_نه_تعریف_شوی PORTMACRO_ASM_H
#تعریف_کړه PORTMACRO_ASM_H

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

#ضمن "FreeRTOSConfig.h"

#که_نه_تعریف_شوی config_ټول_MPU_REGIONS
    #تېروتنه "Set configTOTAL_MPU_REGIONS to the number of MPU regions in FreeRTOSConfig.h"
#وإلاإذا( config_ټول_MPU_REGIONS == 12 )
    #تعریف_کړه پورټ_MPU_ټول_REGIONS ( 12UL )
#وإلاإذا( config_ټول_MPU_REGIONS == 16 )
    #تعریف_کړه پورټ_MPU_ټول_REGIONS ( 16UL )
#وإلا
    #تېروتنه "Set configTOTAL_MPU_REGIONS to the number of MPU regions in FreeRTOSConfig.h"
#د_که_پای /* configTOTAL_MPU_REGIONS */

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
#که_نه_تعریف_شوی configENABLE_FPU
    #تعریف_کړه configENABLE_FPU    1
#د_که_پای /* configENABLE_FPU */

#تعریف_کړه پورټ_ENABLE_FPU configENABLE_FPU

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
#تعریف_کړه USER_ډېرپېښ   0x10U
#تعریف_کړه FIQ_ډېرپېښ    0x11U
#تعریف_کړه IRQ_ډېرپېښ    0x12U
#تعریف_کړه SVC_ډېرپېښ    0x13U
#تعریف_کړه MON_ډېرپېښ    0x16U
#تعریف_کړه ABT_ډېرپېښ    0x17U
#تعریف_کړه HYP_ډېرپېښ    0x1AU
#تعریف_کړه UND_ډېرپېښ    0x1BU
#تعریف_کړه SYS_ډېرپېښ    0x1FU

/**
 * @brief Flag used to mark that a FreeRTOS Task is privileged.
 *
 * @ingroup Port Privilege
 */
#تعریف_کړه پورټ_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

/**
 * @brief SVC numbers for various scheduler operations.
 *
 * @ingroup Scheduler
 *
 * @note These value must not be used in mpu_syscall_numbers.h.
 */
#تعریف_کړه پورټ_SVC_YIELD                 0x0100U
#تعریف_کړه پورټ_SVC_SYSTEM_CALL_EXIT      0x0104U

/**
 * @brief Macros required to manipulate MPU.
 *
 * Further information about MPU can be found in Arm's documentation
 * https://developer.arm.com/documentation/ddi0363/g/System-Control/Register-descriptions/c6--MPU-memory-region-programming-registers
 *
 */

/* MPU sub-region disable settings. This information is encoded in the MPU
 * Region Size and Enable Register. */
#تعریف_کړه پورټ_MPU_SUBREGION_0_DISABLE   ( 0x1UL << 8UL )
#تعریف_کړه پورټ_MPU_SUBREGION_1_DISABLE   ( 0x1UL << 9UL )
#تعریف_کړه پورټ_MPU_SUBREGION_2_DISABLE   ( 0x1UL << 10UL )
#تعریف_کړه پورټ_MPU_SUBREGION_3_DISABLE   ( 0x1UL << 11UL )
#تعریف_کړه پورټ_MPU_SUBREGION_4_DISABLE   ( 0x1UL << 12UL )
#تعریف_کړه پورټ_MPU_SUBREGION_5_DISABLE   ( 0x1UL << 13UL )
#تعریف_کړه پورټ_MPU_SUBREGION_6_DISABLE   ( 0x1UL << 14UL )
#تعریف_کړه پورټ_MPU_SUBREGION_7_DISABLE   ( 0x1UL << 15UL )

/* Default MPU regions. */
#تعریف_کړه پورټ_لومړی_CONFIGURABLE_REGION ( 0 )
#تعریف_کړه پورټ_وروستی_CONFIGURABLE_REGION  ( پورټ_MPU_ټول_REGIONS - 5UL )
#تعریف_کړه پورټ_ډېری_REGION              ( پورټ_MPU_ټول_REGIONS - 4UL )
#تعریف_کړه پورټ_UNPRIVILEGED_FLASH_REGION ( پورټ_MPU_ټول_REGIONS - 3UL )
#تعریف_کړه پورټ_PRIVILEGED_FLASH_REGION   ( پورټ_MPU_ټول_REGIONS - 2UL )
#تعریف_کړه پورټ_PRIVILEGED_RAM_REGION     ( پورټ_MPU_ټول_REGIONS - 1UL )
#تعریف_کړه پورټ_عدد_CONFIGURABLE_REGIONS \
    ( ( پورټ_وروستی_CONFIGURABLE_REGION - پورټ_لومړی_CONFIGURABLE_REGION ) + 1UL )
/* Plus one to make space for the stack region. */
#تعریف_کړه پورټ_ټول_عدد_REGIONS_دننه_TCB        ( پورټ_عدد_CONFIGURABLE_REGIONS + 1UL )

/* MPU region sizes. This information is encoded in the MPU Region Size and
 * Enable Register. */
#تعریف_کړه پورټ_MPU_REGION_اندازه_32_B             ( 0x04UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_64_B             ( 0x05UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_128_B            ( 0x06UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_256_B            ( 0x07UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_512_B            ( 0x08UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_1_KB             ( 0x09UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_2_KB             ( 0x0AUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_4_KB             ( 0x0BUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_8_KB             ( 0x0CUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_16_KB            ( 0x0DUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_32_KB            ( 0x0EUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_64_KB            ( 0x0FUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_128_KB           ( 0x10UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_256_KB           ( 0x11UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_512_KB           ( 0x12UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_1_MB             ( 0x13UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_2_MB             ( 0x14UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_4_MB             ( 0x15UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_8_MB             ( 0x16UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_16_MB            ( 0x17UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_32_MB            ( 0x18UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_64_MB            ( 0x19UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_128_MB           ( 0x1AUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_256_MB           ( 0x1BUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_512_MB           ( 0x1CUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_1_GB             ( 0x1DUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_2_GB             ( 0x1EUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the TEX, S, C and B bits
 * of the MPU Region Access Control Register. */
#تعریف_کړه پورټ_MPU_REGION_STRONGLY_ORDERED_SHAREABLE  ( 0x00UL ) /* TEX=000, S=NA, C=0, B=0. */
#تعریف_کړه پورټ_MPU_REGION_DEVICE_SHAREABLE            ( 0x01UL ) /* TEX=000, S=NA, C=0, B=1. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWTNOWA_NONSHARED   ( 0x02UL ) /* TEX=000, S=0, C=1, B=0. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWTNOWA_SHARED      ( 0x06UL ) /* TEX=000, S=1, C=1, B=0. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWBNOWA_NONSHARED   ( 0x03UL ) /* TEX=000, S=0, C=1, B=1. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWBNOWA_SHARED      ( 0x07UL ) /* TEX=000, S=1, C=1, B=1. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OINC_NONSHARED       ( 0x08UL ) /* TEX=001, S=0, C=0, B=0. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OINC_SHARED          ( 0x0CUL ) /* TEX=001, S=1, C=0, B=0. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWBWA_NONSHARED     ( 0x0BUL ) /* TEX=001, S=0, C=1, B=1. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWBWA_SHARED        ( 0x0FUL ) /* TEX=001, S=1, C=1, B=1. */
#تعریف_کړه پورټ_MPU_REGION_DEVICE_NONSHAREABLE         ( 0x10UL ) /* TEX=010, S=NA, C=0, B=0. */

/* MPU access permissions. This information is encoded in the XN and AP bits of
 * the MPU Region Access Control Register. */
#تعریف_کړه پورټ_MPU_REGION_AP_BITMASK                  ( 0x07UL << 8UL )
#تعریف_کړه پورټ_MPU_REGION_XN_BITMASK                  ( 0x01UL << 12UL )

#تعریف_کړه پورټ_MPU_REGION_PRIV_NA_USER_NA             ( 0x00UL << 8UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_NA_USER_NA_EXEC        ( پورټ_MPU_REGION_PRIV_NA_USER_NA ) /* Priv: X, Unpriv: X. */
#تعریف_کړه پورټ_MPU_REGION_PRIV_NA_USER_NA_NOEXEC      ( پورټ_MPU_REGION_PRIV_NA_USER_NA | \
                                                     پورټ_MPU_REGION_XN_BITMASK ) /* Priv: No Access, Unpriv: No Access. */

#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_USER_NA             ( 0x01UL << 8UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_USER_NA_EXEC        ( پورټ_MPU_REGION_PRIV_RW_USER_NA ) /* Priv: RWX, Unpriv: X. */
#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_USER_NA_NOEXEC      ( پورټ_MPU_REGION_PRIV_RW_USER_NA | \
                                                     پورټ_MPU_REGION_XN_BITMASK ) /* Priv: RW, Unpriv: No access. */

#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_USER_RO             ( 0x02UL << 8UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_USER_RO_EXEC        ( پورټ_MPU_REGION_PRIV_RW_USER_RO ) /* Priv: RWX, Unpriv: RX. */
#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_USER_RO_NOEXEC      ( پورټ_MPU_REGION_PRIV_RW_USER_RO | \
                                                     پورټ_MPU_REGION_XN_BITMASK ) /* Priv: RW, Unpriv: R. */

#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_USER_RW             ( 0x03UL << 8UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_USER_RW_EXEC        ( پورټ_MPU_REGION_PRIV_RW_USER_RW ) /* Priv: RWX, Unpriv: RWX. */
#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_USER_RW_NOEXEC      ( پورټ_MPU_REGION_PRIV_RW_USER_RW | \
                                                     پورټ_MPU_REGION_XN_BITMASK ) /* Priv: RW, Unpriv: RW. */

#تعریف_کړه پورټ_MPU_REGION_PRIV_RO_USER_NA             ( 0x05UL << 8UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RO_USER_NA_EXEC        ( پورټ_MPU_REGION_PRIV_RO_USER_NA ) /* Priv: RX, Unpriv: X. */
#تعریف_کړه پورټ_MPU_REGION_PRIV_RO_USER_NA_NOEXEC      ( پورټ_MPU_REGION_PRIV_RO_USER_NA | \
                                                     پورټ_MPU_REGION_XN_BITMASK ) /* Priv: R, Unpriv: No access. */

#تعریف_کړه پورټ_MPU_REGION_PRIV_RO_USER_RO             ( 0x06UL << 8UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RO_USER_RO_EXEC        ( پورټ_MPU_REGION_PRIV_RO_USER_RO ) /* Priv: RX, Unpriv: RX. */
#تعریف_کړه پورټ_MPU_REGION_PRIV_RO_USER_RO_NOEXEC      ( پورټ_MPU_REGION_PRIV_RO_USER_RO | \
                                                     پورټ_MPU_REGION_XN_BITMASK ) /* Priv: R, Unpriv: R. */

/* MPU region management. */
#تعریف_کړه پورټ_MPU_REGION_EXECUTE_NEVER               ( 0x01UL << 12UL )
#تعریف_کړه پورټ_MPU_REGION_ENABLE                      ( 0x01UL )

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

#إذا( پورټ_ENABLE_FPU == 1 )
    /*
     * +-------------------+-------+----------+--------+----------+----------+----------+------+
     * | ulCriticalNesting | FPSCR |  S0-S31  | R0-R12 | SP (R13) | LR (R14) | PC (R15) | CPSR |
     * +-------------------+-------+----------+--------+----------+----------+----------+------+
     *
     * <------------------><------><---------><--------><---------><--------><----------><----->
     *           1            1        32         13         1         1          1        1
     */
    #تعریف_کړه CONTEXT_اندازه 51U
#وإلا
    /*
     * +-------------------+--------+----------+----------+----------+------+
     * | ulCriticalNesting | R0-R12 | SP (R13) | LR (R14) | PC (R15) | CPSR |
     * +-------------------+--------+----------+----------+----------+------+
     *
     * <------------------><--------><---------><--------><----------><----->
     *           1             13         1         1          1        1
     */
    #تعریف_کړه CONTEXT_اندازه 18U
#د_که_پای /* CONTEXT_SIZE */

/**
 * @brief Offset of xSystemCallStackInfo from the start of a TCB.
 */
#تعریف_کړه پورټ_SYSTEM_CALL_INFO_دننه_واټن             \
    ( ( 1U /* pxTopOfStack. */ +                \
        ( پورټ_ټول_عدد_REGIONS_دننه_TCB * 3U ) + \
        1U /* ulTaskFlags. */                   \
      ) * 4U )

#که_تعریف_شوی __cplusplus
} /* extern C */
#د_که_پای

#د_که_پای /* PORTMACRO_ASM_H */
