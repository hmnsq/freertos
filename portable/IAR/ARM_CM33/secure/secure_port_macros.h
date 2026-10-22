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

#که_نه_تعریف_شوی __SECURE_PORT_MACROS_H__
#تعریف_کړه __SECURE_PORT_MACROS_H__

/**
 * @brief Byte alignment requirements.
 */
#تعریف_کړه secureportBYTE_ALIGNMENT         8
#تعریف_کړه secureport_BYTE_ALIGNMENT_ماسک    ( 0x0007 )

/**
 * @brief Macro to declare a function as non-secure callable.
 */
#إذا defined( __IAR_SYSTEMS_ICC__ )
    #تعریف_کړه secureportNON_SECURE_CALLABLE    __cmse_nonsecure_entry __root
#وإلا
    #تعریف_کړه secureportNON_SECURE_CALLABLE    __attribute__( ( cmse_nonsecure_ثبت ) ) __attribute__( ( کارول_شوی ) )
#د_که_پای

/**
 * @brief Set the secure PRIMASK value.
 */
#تعریف_کړه secureport_سېټ_SECURE_PRIMASK( ul_Primask_ارزښت ) \
    __asm متطاير ( "msr primask, %0" : : "r" ( ul_Primask_ارزښت ) : "memory" )

/**
 * @brief Set the non-secure PRIMASK value.
 */
#تعریف_کړه secureport_سېټ_NON_SECURE_PRIMASK( ul_Primask_ارزښت ) \
    __asm متطاير ( "msr primask_ns, %0" : : "r" ( ul_Primask_ارزښت ) : "memory" )

/**
 * @brief Read the PSP value in the given variable.
 */
#تعریف_کړه secureportREAD_PSP( puc_بهر_Current_ډېری_اشاره_ګر ) \
    __asm متطاير ( "mrs %0, psp"  : "=r" ( puc_بهر_Current_ډېری_اشاره_ګر ) )

/**
 * @brief Set the PSP to the given value.
 */
#تعریف_کړه secureport_سېټ_PSP( puc_Current_ډېری_اشاره_ګر ) \
    __asm متطاير ( "msr psp, %0" : : "r" ( puc_Current_ډېری_اشاره_ګر ) )

/**
 * @brief Read the PSPLIM value in the given variable.
 */
#تعریف_کړه secureportREAD_PSPLIM( puc_بهر_ډېری_حد ) \
    __asm متطاير ( "mrs %0, psplim"  : "=r" ( puc_بهر_ډېری_حد ) )

/**
 * @brief Set the PSPLIM to the given value.
 */
#تعریف_کړه secureport_سېټ_PSPLIM( puc_ډېری_حد ) \
    __asm متطاير ( "msr psplim, %0" : : "r" ( puc_ډېری_حد ) )

/**
 * @brief Set the NonSecure MSP to the given value.
 */
#تعریف_کړه secureport_سېټ_MSP_NS( puc_Main_ډېری_اشاره_ګر ) \
    __asm متطاير ( "msr msp_ns, %0" : : "r" ( puc_Main_ډېری_اشاره_ګر ) )

/**
 * @brief Set the CONTROL register to the given value.
 */
#تعریف_کړه secureport_سېټ_CONTROL( ulControl ) \
    __asm متطاير ( "msr control, %0" : : "r" ( ulControl ) : "memory" )

/**
 * @brief Read the Interrupt Program Status Register (IPSR) value in the given
 * variable.
 */
#تعریف_کړه secureportREAD_IPSR( ulIPSR ) \
    __asm متطاير ( "mrs %0, ipsr"  : "=r" ( ulIPSR ) )

/**
 * @brief PRIMASK value to enable interrupts.
 */
#تعریف_کړه secureportPRIMASK_ENABLE_INTERRUPTS_VAL     0

/**
 * @brief PRIMASK value to disable interrupts.
 */
#تعریف_کړه secureportPRIMASK_DISABLE_INTERRUPTS_VAL    1

/**
 * @brief Disable secure interrupts.
 */
#تعریف_کړه secureportDISABLE_SECURE_INTERRUPTS()        secureport_سېټ_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Disable non-secure interrupts.
 *
 * This effectively disables context switches.
 */
#تعریف_کړه secureportDISABLE_NON_SECURE_INTERRUPTS()    secureport_سېټ_NON_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Enable non-secure interrupts.
 */
#تعریف_کړه secureportENABLE_NON_SECURE_INTERRUPTS()     secureport_سېټ_NON_SECURE_PRIMASK( secureportPRIMASK_ENABLE_INTERRUPTS_VAL )

/**
 * @brief Assert definition.
 */
#تعریف_کړه secureportASSERT( x )                      \
    إذا( ( x ) == 0 )                               \
    {                                              \
        secureportDISABLE_SECURE_INTERRUPTS();     \
        secureportDISABLE_NON_SECURE_INTERRUPTS(); \
        لكل( ; ; ) {; }                            \
    }

#د_که_پای /* __SECURE_PORT_MACROS_H__ */
