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

#ifndef __SECURE_PORT_MACROS_H__
#define __SECURE_PORT_MACROS_H__

/**
 * @brief Byte alignment requirements.
 */
#define secureportBYTE_ALIGNMENT         8
#define secureportBYTE_ALIGNMENT_MASK    ( 0x0007 )

/**
 * @brief Macro to declare a function as non-secure callable.
 */
#إذا defined( __IAR_SYSTEMS_ICC__ )
    #define secureportNON_SECURE_CALLABLE    __cmse_nonsecure_entry __root
#وإلا
    #define secureportNON_SECURE_CALLABLE    __attribute__( ( cmse_nonsecure_entry ) ) __attribute__( ( used ) )
#endif

/**
 * @brief Set the secure PRIMASK value.
 */
#define secureportSET_SECURE_PRIMASK( ul_Primask_بەها ) \
    __asm متطاير ( "msr primask, %0" : : "r" ( ul_Primask_بەها ) : "memory" )

/**
 * @brief Set the non-secure PRIMASK value.
 */
#define secureportSET_NON_SECURE_PRIMASK( ul_Primask_بەها ) \
    __asm متطاير ( "msr primask_ns, %0" : : "r" ( ul_Primask_بەها ) : "memory" )

/**
 * @brief Read the PSP value in the given variable.
 */
#define secureportREAD_PSP( puc_Out_Current_کەڵەکە_Pointer ) \
    __asm متطاير ( "mrs %0, psp"  : "=r" ( puc_Out_Current_کەڵەکە_Pointer ) )

/**
 * @brief Set the PSP to the given value.
 */
#define secureportSET_PSP( puc_Current_کەڵەکە_Pointer ) \
    __asm متطاير ( "msr psp, %0" : : "r" ( puc_Current_کەڵەکە_Pointer ) )

/**
 * @brief Read the PSPLIM value in the given variable.
 */
#define secureportREAD_PSPLIM( puc_Out_کەڵەکە_Limit ) \
    __asm متطاير ( "mrs %0, psplim"  : "=r" ( puc_Out_کەڵەکە_Limit ) )

/**
 * @brief Set the PSPLIM to the given value.
 */
#define secureportSET_PSPLIM( puc_کەڵەکە_Limit ) \
    __asm متطاير ( "msr psplim, %0" : : "r" ( puc_کەڵەکە_Limit ) )

/**
 * @brief Set the NonSecure MSP to the given value.
 */
#define secureportSET_MSP_NS( puc_Main_کەڵەکە_Pointer ) \
    __asm متطاير ( "msr msp_ns, %0" : : "r" ( puc_Main_کەڵەکە_Pointer ) )

/**
 * @brief Set the CONTROL register to the given value.
 */
#define secureportSET_CONTROL( ulControl ) \
    __asm متطاير ( "msr control, %0" : : "r" ( ulControl ) : "memory" )

/**
 * @brief Read the Interrupt Program Status Register (IPSR) value in the given
 * variable.
 */
#define secureportREAD_IPSR( ulIPSR ) \
    __asm متطاير ( "mrs %0, ipsr"  : "=r" ( ulIPSR ) )

/**
 * @brief PRIMASK value to enable interrupts.
 */
#define secureportPRIMASK_ENABLE_INTERRUPTS_VAL     0

/**
 * @brief PRIMASK value to disable interrupts.
 */
#define secureportPRIMASK_DISABLE_INTERRUPTS_VAL    1

/**
 * @brief Disable secure interrupts.
 */
#define secureportDISABLE_SECURE_INTERRUPTS()        secureportSET_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Disable non-secure interrupts.
 *
 * This effectively disables context switches.
 */
#define secureportDISABLE_NON_SECURE_INTERRUPTS()    secureportSET_NON_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Enable non-secure interrupts.
 */
#define secureportENABLE_NON_SECURE_INTERRUPTS()     secureportSET_NON_SECURE_PRIMASK( secureportPRIMASK_ENABLE_INTERRUPTS_VAL )

/**
 * @brief Assert definition.
 */
#define secureportASSERT( x )                      \
    إذا( ( x ) == 0 )                               \
    {                                              \
        secureportDISABLE_SECURE_INTERRUPTS();     \
        secureportDISABLE_NON_SECURE_INTERRUPTS(); \
        لكل( ; ; ) {; }                            \
    }

#endif /* __SECURE_PORT_MACROS_H__ */
