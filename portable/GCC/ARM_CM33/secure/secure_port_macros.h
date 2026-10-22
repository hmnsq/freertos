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

#اگر_غیر_تعریف_شدہ __SECURE_PORT_MACROS_H__
#تعریف_کرو __SECURE_PORT_MACROS_H__

/**
 * @brief Byte alignment requirements.
 */
#تعریف_کرو secureportBYTE_ALIGNMENT         8
#تعریف_کرو secureport_BYTE_ALIGNMENT_نقاب    ( 0x0007 )

/**
 * @brief Macro to declare a function as non-secure callable.
 */
#اگر defined( __IAR_SYSTEMS_ICC__ )
    #تعریف_کرو secureportNON_SECURE_CALLABLE    __cmse_nonsecure_entry __root
#ورنہ
    #تعریف_کرو secureportNON_SECURE_CALLABLE    __attribute__( ( cmse_nonsecure_اندراج ) ) __attribute__( ( مستعمل ) )
#اگر_ختم

/**
 * @brief Set the secure PRIMASK value.
 */
#تعریف_کرو secureport_سیٹ_SECURE_PRIMASK( ul_Primask_قدر ) \
    __asm متلون ( "msr primask, %0" : : "r" ( ul_Primask_قدر ) : "memory" )

/**
 * @brief Set the non-secure PRIMASK value.
 */
#تعریف_کرو secureport_سیٹ_NON_SECURE_PRIMASK( ul_Primask_قدر ) \
    __asm متلون ( "msr primask_ns, %0" : : "r" ( ul_Primask_قدر ) : "memory" )

/**
 * @brief Read the PSP value in the given variable.
 */
#تعریف_کرو secureportREAD_PSP( puc_برآمد_Current_ڈھیر_اشارہ_گر ) \
    __asm متلون ( "mrs %0, psp"  : "=r" ( puc_برآمد_Current_ڈھیر_اشارہ_گر ) )

/**
 * @brief Set the PSP to the given value.
 */
#تعریف_کرو secureport_سیٹ_PSP( puc_Current_ڈھیر_اشارہ_گر ) \
    __asm متلون ( "msr psp, %0" : : "r" ( puc_Current_ڈھیر_اشارہ_گر ) )

/**
 * @brief Read the PSPLIM value in the given variable.
 */
#تعریف_کرو secureportREAD_PSPLIM( puc_برآمد_ڈھیر_حد_بندی ) \
    __asm متلون ( "mrs %0, psplim"  : "=r" ( puc_برآمد_ڈھیر_حد_بندی ) )

/**
 * @brief Set the PSPLIM to the given value.
 */
#تعریف_کرو secureport_سیٹ_PSPLIM( puc_ڈھیر_حد_بندی ) \
    __asm متلون ( "msr psplim, %0" : : "r" ( puc_ڈھیر_حد_بندی ) )

/**
 * @brief Set the NonSecure MSP to the given value.
 */
#تعریف_کرو secureport_سیٹ_MSP_NS( puc_Main_ڈھیر_اشارہ_گر ) \
    __asm متلون ( "msr msp_ns, %0" : : "r" ( puc_Main_ڈھیر_اشارہ_گر ) )

/**
 * @brief Set the CONTROL register to the given value.
 */
#تعریف_کرو secureport_سیٹ_CONTROL( ulControl ) \
    __asm متلون ( "msr control, %0" : : "r" ( ulControl ) : "memory" )

/**
 * @brief Read the Interrupt Program Status Register (IPSR) value in the given
 * variable.
 */
#تعریف_کرو secureportREAD_IPSR( ulIPSR ) \
    __asm متلون ( "mrs %0, ipsr"  : "=r" ( ulIPSR ) )

/**
 * @brief PRIMASK value to enable interrupts.
 */
#تعریف_کرو secureportPRIMASK_ENABLE_INTERRUPTS_VAL     0

/**
 * @brief PRIMASK value to disable interrupts.
 */
#تعریف_کرو secureportPRIMASK_DISABLE_INTERRUPTS_VAL    1

/**
 * @brief Disable secure interrupts.
 */
#تعریف_کرو secureportDISABLE_SECURE_INTERRUPTS()        secureport_سیٹ_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Disable non-secure interrupts.
 *
 * This effectively disables context switches.
 */
#تعریف_کرو secureportDISABLE_NON_SECURE_INTERRUPTS()    secureport_سیٹ_NON_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Enable non-secure interrupts.
 */
#تعریف_کرو secureportENABLE_NON_SECURE_INTERRUPTS()     secureport_سیٹ_NON_SECURE_PRIMASK( secureportPRIMASK_ENABLE_INTERRUPTS_VAL )

/**
 * @brief Assert definition.
 */
#تعریف_کرو secureportASSERT( x )                      \
    اگر( ( x ) == 0 )                               \
    {                                              \
        secureportDISABLE_SECURE_INTERRUPTS();     \
        secureportDISABLE_NON_SECURE_INTERRUPTS(); \
        برائے( ; ; ) {; }                            \
    }

#اگر_ختم /* __SECURE_PORT_MACROS_H__ */
