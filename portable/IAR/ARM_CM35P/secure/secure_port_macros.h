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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __SECURE_PORT_MACROS_H__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __SECURE_PORT_MACROS_H__

/**
 * @brief Byte alignment requirements.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportBYTE_ALIGNMENT         8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureport_BYTE_ALIGNMENT_ਨਕਾਬ    ( 0x0007 )

/**
 * @brief Macro to declare a function as non-secure callable.
 */
#ਜੇ defined( __IAR_SYSTEMS_ICC__ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportNON_SECURE_CALLABLE    __cmse_nonsecure_entry __root
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportNON_SECURE_CALLABLE    __attribute__( ( cmse_nonsecure_ਇੰਦਰਾਜ ) ) __attribute__( ( ਵਰਤਿਆ ) )
#ਜੇ_ਅੰਤ

/**
 * @brief Set the secure PRIMASK value.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureport_ਸੈੱਟ_SECURE_PRIMASK( ul_Primask_ਮੁੱਲ ) \
    __asm ਅਸਥਿਰ ( "msr primask, %0" : : "r" ( ul_Primask_ਮੁੱਲ ) : "memory" )

/**
 * @brief Set the non-secure PRIMASK value.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureport_ਸੈੱਟ_NON_SECURE_PRIMASK( ul_Primask_ਮੁੱਲ ) \
    __asm ਅਸਥਿਰ ( "msr primask_ns, %0" : : "r" ( ul_Primask_ਮੁੱਲ ) : "memory" )

/**
 * @brief Read the PSP value in the given variable.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportREAD_PSP( puc_ਬਾਹਰਲਾ_Current_ਢੇਰ_ਸੂਚਕ ) \
    __asm ਅਸਥਿਰ ( "mrs %0, psp"  : "=r" ( puc_ਬਾਹਰਲਾ_Current_ਢੇਰ_ਸੂਚਕ ) )

/**
 * @brief Set the PSP to the given value.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureport_ਸੈੱਟ_PSP( puc_Current_ਢੇਰ_ਸੂਚਕ ) \
    __asm ਅਸਥਿਰ ( "msr psp, %0" : : "r" ( puc_Current_ਢੇਰ_ਸੂਚਕ ) )

/**
 * @brief Read the PSPLIM value in the given variable.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportREAD_PSPLIM( puc_ਬਾਹਰਲਾ_ਢੇਰ_ਹੱਦਬੰਦੀ ) \
    __asm ਅਸਥਿਰ ( "mrs %0, psplim"  : "=r" ( puc_ਬਾਹਰਲਾ_ਢੇਰ_ਹੱਦਬੰਦੀ ) )

/**
 * @brief Set the PSPLIM to the given value.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureport_ਸੈੱਟ_PSPLIM( puc_ਢੇਰ_ਹੱਦਬੰਦੀ ) \
    __asm ਅਸਥਿਰ ( "msr psplim, %0" : : "r" ( puc_ਢੇਰ_ਹੱਦਬੰਦੀ ) )

/**
 * @brief Set the NonSecure MSP to the given value.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureport_ਸੈੱਟ_MSP_NS( puc_Main_ਢੇਰ_ਸੂਚਕ ) \
    __asm ਅਸਥਿਰ ( "msr msp_ns, %0" : : "r" ( puc_Main_ਢੇਰ_ਸੂਚਕ ) )

/**
 * @brief Set the CONTROL register to the given value.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureport_ਸੈੱਟ_CONTROL( ulControl ) \
    __asm ਅਸਥਿਰ ( "msr control, %0" : : "r" ( ulControl ) : "memory" )

/**
 * @brief Read the Interrupt Program Status Register (IPSR) value in the given
 * variable.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportREAD_IPSR( ulIPSR ) \
    __asm ਅਸਥਿਰ ( "mrs %0, ipsr"  : "=r" ( ulIPSR ) )

/**
 * @brief PRIMASK value to enable interrupts.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportPRIMASK_ENABLE_INTERRUPTS_VAL     0

/**
 * @brief PRIMASK value to disable interrupts.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportPRIMASK_DISABLE_INTERRUPTS_VAL    1

/**
 * @brief Disable secure interrupts.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportDISABLE_SECURE_INTERRUPTS()        secureport_ਸੈੱਟ_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Disable non-secure interrupts.
 *
 * This effectively disables context switches.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportDISABLE_NON_SECURE_INTERRUPTS()    secureport_ਸੈੱਟ_NON_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Enable non-secure interrupts.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportENABLE_NON_SECURE_INTERRUPTS()     secureport_ਸੈੱਟ_NON_SECURE_PRIMASK( secureportPRIMASK_ENABLE_INTERRUPTS_VAL )

/**
 * @brief Assert definition.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureportASSERT( x )                      \
    ਜੇ( ( x ) == 0 )                               \
    {                                              \
        secureportDISABLE_SECURE_INTERRUPTS();     \
        secureportDISABLE_NON_SECURE_INTERRUPTS(); \
        ਲਈ( ; ; ) {; }                            \
    }

#ਜੇ_ਅੰਤ /* __SECURE_PORT_MACROS_H__ */
