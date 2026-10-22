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

#यदि_अपरिभाषितम् PORTMACRO_ASM_H
#परिभाषय PORTMACRO_ASM_H

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

#अन्तर्भाव "FreeRTOSConfig.h"

#यदि_अपरिभाषितम् config_योग_MPU_REGIONS
    #दोषः "Set configTOTAL_MPU_REGIONS to the number of MPU regions in FreeRTOSConfig.h"
#नोचेद्यदि( config_योग_MPU_REGIONS == 12 )
    #परिभाषय पत्तनम्_MPU_योग_REGIONS ( 12UL )
#नोचेद्यदि( config_योग_MPU_REGIONS == 16 )
    #परिभाषय पत्तनम्_MPU_योग_REGIONS ( 16UL )
#अन्यथा
    #दोषः "Set configTOTAL_MPU_REGIONS to the number of MPU regions in FreeRTOSConfig.h"
#यदि_अन्तः /* configTOTAL_MPU_REGIONS */

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
#यदि_अपरिभाषितम् configENABLE_FPU
    #परिभाषय configENABLE_FPU    1
#यदि_अन्तः /* configENABLE_FPU */

#परिभाषय पत्तनम्_ENABLE_FPU configENABLE_FPU

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
#परिभाषय USER_बहुलकम्   0x10U
#परिभाषय FIQ_बहुलकम्    0x11U
#परिभाषय IRQ_बहुलकम्    0x12U
#परिभाषय SVC_बहुलकम्    0x13U
#परिभाषय MON_बहुलकम्    0x16U
#परिभाषय ABT_बहुलकम्    0x17U
#परिभाषय HYP_बहुलकम्    0x1AU
#परिभाषय UND_बहुलकम्    0x1BU
#परिभाषय SYS_बहुलकम्    0x1FU

/**
 * @brief Flag used to mark that a FreeRTOS Task is privileged.
 *
 * @ingroup Port Privilege
 */
#परिभाषय पत्तनम्_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

/**
 * @brief SVC numbers for various scheduler operations.
 *
 * @ingroup Scheduler
 *
 * @note These value must not be used in mpu_syscall_numbers.h.
 */
#परिभाषय पत्तनम्_SVC_YIELD                 0x0100U
#परिभाषय पत्तनम्_SVC_SYSTEM_CALL_EXIT      0x0104U

/**
 * @brief Macros required to manipulate MPU.
 *
 * Further information about MPU can be found in Arm's documentation
 * https://developer.arm.com/documentation/ddi0363/g/System-Control/Register-descriptions/c6--MPU-memory-region-programming-registers
 *
 */

/* MPU sub-region disable settings. This information is encoded in the MPU
 * Region Size and Enable Register. */
#परिभाषय पत्तनम्_MPU_SUBREGION_0_DISABLE   ( 0x1UL << 8UL )
#परिभाषय पत्तनम्_MPU_SUBREGION_1_DISABLE   ( 0x1UL << 9UL )
#परिभाषय पत्तनम्_MPU_SUBREGION_2_DISABLE   ( 0x1UL << 10UL )
#परिभाषय पत्तनम्_MPU_SUBREGION_3_DISABLE   ( 0x1UL << 11UL )
#परिभाषय पत्तनम्_MPU_SUBREGION_4_DISABLE   ( 0x1UL << 12UL )
#परिभाषय पत्तनम्_MPU_SUBREGION_5_DISABLE   ( 0x1UL << 13UL )
#परिभाषय पत्तनम्_MPU_SUBREGION_6_DISABLE   ( 0x1UL << 14UL )
#परिभाषय पत्तनम्_MPU_SUBREGION_7_DISABLE   ( 0x1UL << 15UL )

/* Default MPU regions. */
#परिभाषय पत्तनम्_FIRST_CONFIGURABLE_REGION ( 0 )
#परिभाषय पत्तनम्_चरमः_CONFIGURABLE_REGION  ( पत्तनम्_MPU_योग_REGIONS - 5UL )
#परिभाषय पत्तनम्_राशिः_REGION              ( पत्तनम्_MPU_योग_REGIONS - 4UL )
#परिभाषय पत्तनम्_UNPRIVILEGED_FLASH_REGION ( पत्तनम्_MPU_योग_REGIONS - 3UL )
#परिभाषय पत्तनम्_PRIVILEGED_FLASH_REGION   ( पत्तनम्_MPU_योग_REGIONS - 2UL )
#परिभाषय पत्तनम्_PRIVILEGED_RAM_REGION     ( पत्तनम्_MPU_योग_REGIONS - 1UL )
#परिभाषय पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS \
    ( ( पत्तनम्_चरमः_CONFIGURABLE_REGION - पत्तनम्_FIRST_CONFIGURABLE_REGION ) + 1UL )
/* Plus one to make space for the stack region. */
#परिभाषय पत्तनम्_योग_अङ्कः_REGIONS_अन्तर्_TCB        ( पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS + 1UL )

/* MPU region sizes. This information is encoded in the MPU Region Size and
 * Enable Register. */
#परिभाषय पत्तनम्_MPU_REGION_आकार_32_B             ( 0x04UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_64_B             ( 0x05UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_128_B            ( 0x06UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_256_B            ( 0x07UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_512_B            ( 0x08UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_1_KB             ( 0x09UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_2_KB             ( 0x0AUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_4_KB             ( 0x0BUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_8_KB             ( 0x0CUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_16_KB            ( 0x0DUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_32_KB            ( 0x0EUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_64_KB            ( 0x0FUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_128_KB           ( 0x10UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_256_KB           ( 0x11UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_512_KB           ( 0x12UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_1_MB             ( 0x13UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_2_MB             ( 0x14UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_4_MB             ( 0x15UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_8_MB             ( 0x16UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_16_MB            ( 0x17UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_32_MB            ( 0x18UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_64_MB            ( 0x19UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_128_MB           ( 0x1AUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_256_MB           ( 0x1BUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_512_MB           ( 0x1CUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_1_GB             ( 0x1DUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_2_GB             ( 0x1EUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the TEX, S, C and B bits
 * of the MPU Region Access Control Register. */
#परिभाषय पत्तनम्_MPU_REGION_STRONGLY_ORDERED_SHAREABLE  ( 0x00UL ) /* TEX=000, S=NA, C=0, B=0. */
#परिभाषय पत्तनम्_MPU_REGION_DEVICE_SHAREABLE            ( 0x01UL ) /* TEX=000, S=NA, C=0, B=1. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWTNOWA_NONSHARED   ( 0x02UL ) /* TEX=000, S=0, C=1, B=0. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWTNOWA_SHARED      ( 0x06UL ) /* TEX=000, S=1, C=1, B=0. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWBNOWA_NONSHARED   ( 0x03UL ) /* TEX=000, S=0, C=1, B=1. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWBNOWA_SHARED      ( 0x07UL ) /* TEX=000, S=1, C=1, B=1. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OINC_NONSHARED       ( 0x08UL ) /* TEX=001, S=0, C=0, B=0. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OINC_SHARED          ( 0x0CUL ) /* TEX=001, S=1, C=0, B=0. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWBWA_NONSHARED     ( 0x0BUL ) /* TEX=001, S=0, C=1, B=1. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWBWA_SHARED        ( 0x0FUL ) /* TEX=001, S=1, C=1, B=1. */
#परिभाषय पत्तनम्_MPU_REGION_DEVICE_NONSHAREABLE         ( 0x10UL ) /* TEX=010, S=NA, C=0, B=0. */

/* MPU access permissions. This information is encoded in the XN and AP bits of
 * the MPU Region Access Control Register. */
#परिभाषय पत्तनम्_MPU_REGION_AP_BITMASK                  ( 0x07UL << 8UL )
#परिभाषय पत्तनम्_MPU_REGION_XN_BITMASK                  ( 0x01UL << 12UL )

#परिभाषय पत्तनम्_MPU_REGION_PRIV_NA_USER_NA             ( 0x00UL << 8UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_NA_USER_NA_EXEC        ( पत्तनम्_MPU_REGION_PRIV_NA_USER_NA ) /* Priv: X, Unpriv: X. */
#परिभाषय पत्तनम्_MPU_REGION_PRIV_NA_USER_NA_NOEXEC      ( पत्तनम्_MPU_REGION_PRIV_NA_USER_NA | \
                                                     पत्तनम्_MPU_REGION_XN_BITMASK ) /* Priv: No Access, Unpriv: No Access. */

#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_USER_NA             ( 0x01UL << 8UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_USER_NA_EXEC        ( पत्तनम्_MPU_REGION_PRIV_RW_USER_NA ) /* Priv: RWX, Unpriv: X. */
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_USER_NA_NOEXEC      ( पत्तनम्_MPU_REGION_PRIV_RW_USER_NA | \
                                                     पत्तनम्_MPU_REGION_XN_BITMASK ) /* Priv: RW, Unpriv: No access. */

#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_USER_RO             ( 0x02UL << 8UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_USER_RO_EXEC        ( पत्तनम्_MPU_REGION_PRIV_RW_USER_RO ) /* Priv: RWX, Unpriv: RX. */
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_USER_RO_NOEXEC      ( पत्तनम्_MPU_REGION_PRIV_RW_USER_RO | \
                                                     पत्तनम्_MPU_REGION_XN_BITMASK ) /* Priv: RW, Unpriv: R. */

#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_USER_RW             ( 0x03UL << 8UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_USER_RW_EXEC        ( पत्तनम्_MPU_REGION_PRIV_RW_USER_RW ) /* Priv: RWX, Unpriv: RWX. */
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_USER_RW_NOEXEC      ( पत्तनम्_MPU_REGION_PRIV_RW_USER_RW | \
                                                     पत्तनम्_MPU_REGION_XN_BITMASK ) /* Priv: RW, Unpriv: RW. */

#परिभाषय पत्तनम्_MPU_REGION_PRIV_RO_USER_NA             ( 0x05UL << 8UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RO_USER_NA_EXEC        ( पत्तनम्_MPU_REGION_PRIV_RO_USER_NA ) /* Priv: RX, Unpriv: X. */
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RO_USER_NA_NOEXEC      ( पत्तनम्_MPU_REGION_PRIV_RO_USER_NA | \
                                                     पत्तनम्_MPU_REGION_XN_BITMASK ) /* Priv: R, Unpriv: No access. */

#परिभाषय पत्तनम्_MPU_REGION_PRIV_RO_USER_RO             ( 0x06UL << 8UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RO_USER_RO_EXEC        ( पत्तनम्_MPU_REGION_PRIV_RO_USER_RO ) /* Priv: RX, Unpriv: RX. */
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RO_USER_RO_NOEXEC      ( पत्तनम्_MPU_REGION_PRIV_RO_USER_RO | \
                                                     पत्तनम्_MPU_REGION_XN_BITMASK ) /* Priv: R, Unpriv: R. */

/* MPU region management. */
#परिभाषय पत्तनम्_MPU_REGION_EXECUTE_NEVER               ( 0x01UL << 12UL )
#परिभाषय पत्तनम्_MPU_REGION_ENABLE                      ( 0x01UL )

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

#यदि( पत्तनम्_ENABLE_FPU == 1 )
    /*
     * +-------------------+-------+----------+--------+----------+----------+----------+------+
     * | ulCriticalNesting | FPSCR |  S0-S31  | R0-R12 | SP (R13) | LR (R14) | PC (R15) | CPSR |
     * +-------------------+-------+----------+--------+----------+----------+----------+------+
     *
     * <------------------><------><---------><--------><---------><--------><----------><----->
     *           1            1        32         13         1         1          1        1
     */
    #परिभाषय CONTEXT_आकार 51U
#अन्यथा
    /*
     * +-------------------+--------+----------+----------+----------+------+
     * | ulCriticalNesting | R0-R12 | SP (R13) | LR (R14) | PC (R15) | CPSR |
     * +-------------------+--------+----------+----------+----------+------+
     *
     * <------------------><--------><---------><--------><----------><----->
     *           1             13         1         1          1        1
     */
    #परिभाषय CONTEXT_आकार 18U
#यदि_अन्तः /* CONTEXT_SIZE */

/**
 * @brief Offset of xSystemCallStackInfo from the start of a TCB.
 */
#परिभाषय पत्तनम्_SYSTEM_CALL_INFO_विस्थापनम्             \
    ( ( 1U /* pxTopOfStack. */ +                \
        ( पत्तनम्_योग_अङ्कः_REGIONS_अन्तर्_TCB * 3U ) + \
        1U /* ulTaskFlags. */                   \
      ) * 4U )

#यदि_परिभाषितम् __cplusplus
} /* extern C */
#यदि_अन्तः

#यदि_अन्तः /* PORTMACRO_ASM_H */
