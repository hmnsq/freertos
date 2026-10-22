/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

#اگر_تعریف_نشده __SECURE_PORT_MACROS_H__
#تعریف_کن __SECURE_PORT_MACROS_H__

/**
 * @brief Byte alignment requirements.
 */
#تعریف_کن secureportBYTE_ALIGNMENT         8
#تعریف_کن secureport_BYTE_ALIGNMENT_ماسک    ( 0x0007 )

/**
 * @brief Macro to declare a function as non-secure callable.
 */
#إذا defined( __IAR_SYSTEMS_ICC__ )
    #تعریف_کن secureportNON_SECURE_CALLABLE    __cmse_nonsecure_entry __root
#وإلا
    #تعریف_کن secureportNON_SECURE_CALLABLE    __attribute__( ( cmse_nonsecure_مدخل ) ) __attribute__( ( استفاده_شده ) )
#پایان_اگر

/**
 * @brief Set the secure PRIMASK value.
 */
#تعریف_کن secureport_مجموعه_SECURE_PRIMASK( ul_Primask_مقدار ) \
    __asm متطاير ( "msr primask, %0" : : "r" ( ul_Primask_مقدار ) : "memory" )

/**
 * @brief Set the non-secure PRIMASK value.
 */
#تعریف_کن secureport_مجموعه_NON_SECURE_PRIMASK( ul_Primask_مقدار ) \
    __asm متطاير ( "msr primask_ns, %0" : : "r" ( ul_Primask_مقدار ) : "memory" )

/**
 * @brief Read the PSP value in the given variable.
 */
#تعریف_کن secureportREAD_PSP( puc_بیرون_Current_پشته_اشاره_گر ) \
    __asm متطاير ( "mrs %0, psp"  : "=r" ( puc_بیرون_Current_پشته_اشاره_گر ) )

/**
 * @brief Set the PSP to the given value.
 */
#تعریف_کن secureport_مجموعه_PSP( puc_Current_پشته_اشاره_گر ) \
    __asm متطاير ( "msr psp, %0" : : "r" ( puc_Current_پشته_اشاره_گر ) )

/**
 * @brief Read the PSPLIM value in the given variable.
 */
#تعریف_کن secureportREAD_PSPLIM( puc_بیرون_پشته_حد ) \
    __asm متطاير ( "mrs %0, psplim"  : "=r" ( puc_بیرون_پشته_حد ) )

/**
 * @brief Set the PSPLIM to the given value.
 */
#تعریف_کن secureport_مجموعه_PSPLIM( puc_پشته_حد ) \
    __asm متطاير ( "msr psplim, %0" : : "r" ( puc_پشته_حد ) )

/**
 * @brief Set the NonSecure MSP to the given value.
 */
#تعریف_کن secureport_مجموعه_MSP_NS( puc_Main_پشته_اشاره_گر ) \
    __asm متطاير ( "msr msp_ns, %0" : : "r" ( puc_Main_پشته_اشاره_گر ) )

/**
 * @brief Set the CONTROL register to the given value.
 */
#تعریف_کن secureport_مجموعه_CONTROL( ulControl ) \
    __asm متطاير ( "msr control, %0" : : "r" ( ulControl ) : "memory" )

/**
 * @brief Read the Interrupt Program Status Register (IPSR) value in the given
 * variable.
 */
#تعریف_کن secureportREAD_IPSR( ulIPSR ) \
    __asm متطاير ( "mrs %0, ipsr"  : "=r" ( ulIPSR ) )

/**
 * @brief PRIMASK value to enable interrupts.
 */
#تعریف_کن secureportPRIMASK_ENABLE_INTERRUPTS_VAL     0

/**
 * @brief PRIMASK value to disable interrupts.
 */
#تعریف_کن secureportPRIMASK_DISABLE_INTERRUPTS_VAL    1

/**
 * @brief Disable secure interrupts.
 */
#تعریف_کن secureportDISABLE_SECURE_INTERRUPTS()        secureport_مجموعه_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Disable non-secure interrupts.
 *
 * This effectively disables context switches.
 */
#تعریف_کن secureportDISABLE_NON_SECURE_INTERRUPTS()    secureport_مجموعه_NON_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Enable non-secure interrupts.
 */
#تعریف_کن secureportENABLE_NON_SECURE_INTERRUPTS()     secureport_مجموعه_NON_SECURE_PRIMASK( secureportPRIMASK_ENABLE_INTERRUPTS_VAL )

/**
 * @brief Assert definition.
 */
#تعریف_کن secureportASSERT( x )                      \
    إذا( ( x ) == 0 )                               \
    {                                              \
        secureportDISABLE_SECURE_INTERRUPTS();     \
        secureportDISABLE_NON_SECURE_INTERRUPTS(); \
        لكل( ; ; ) {; }                            \
    }

#پایان_اگر /* __SECURE_PORT_MACROS_H__ */
