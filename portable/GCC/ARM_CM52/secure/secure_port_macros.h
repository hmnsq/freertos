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

#अगर_अघोषित __SECURE_PORT_MACROS_H__
#घोषणा __SECURE_PORT_MACROS_H__

/**
 * @brief Byte alignment requirements.
 */
#घोषणा secureportBYTE_ALIGNMENT         8
#घोषणा secureportBYTE_ALIGNMENT_MASK    ( 0x0007 )

/**
 * @brief Macro to declare a function as non-secure callable.
 */
#अगर defined( __IAR_SYSTEMS_ICC__ )
    #घोषणा secureportNON_SECURE_CALLABLE    __cmse_nonsecure_entry __root
#अन्यथा
    #घोषणा secureportNON_SECURE_CALLABLE    __attribute__( ( cmse_nonsecure_entry ) ) __attribute__( ( used ) )
#पूर्ण_अगर

/**
 * @brief Set the secure PRIMASK value.
 */
#घोषणा secureportSET_SECURE_PRIMASK( ul_Primask_मूल्य ) \
    __asm अस्थिर ( "msr primask, %0" : : "r" ( ul_Primask_मूल्य ) : "memory" )

/**
 * @brief Set the non-secure PRIMASK value.
 */
#घोषणा secureportSET_NON_SECURE_PRIMASK( ul_Primask_मूल्य ) \
    __asm अस्थिर ( "msr primask_ns, %0" : : "r" ( ul_Primask_मूल्य ) : "memory" )

/**
 * @brief Read the PSP value in the given variable.
 */
#घोषणा secureportREAD_PSP( puc_Out_Current_ढेर_Pointer ) \
    __asm अस्थिर ( "mrs %0, psp"  : "=r" ( puc_Out_Current_ढेर_Pointer ) )

/**
 * @brief Set the PSP to the given value.
 */
#घोषणा secureportSET_PSP( puc_Current_ढेर_Pointer ) \
    __asm अस्थिर ( "msr psp, %0" : : "r" ( puc_Current_ढेर_Pointer ) )

/**
 * @brief Read the PSPLIM value in the given variable.
 */
#घोषणा secureportREAD_PSPLIM( puc_Out_ढेर_Limit ) \
    __asm अस्थिर ( "mrs %0, psplim"  : "=r" ( puc_Out_ढेर_Limit ) )

/**
 * @brief Set the PSPLIM to the given value.
 */
#घोषणा secureportSET_PSPLIM( puc_ढेर_Limit ) \
    __asm अस्थिर ( "msr psplim, %0" : : "r" ( puc_ढेर_Limit ) )

/**
 * @brief Set the NonSecure MSP to the given value.
 */
#घोषणा secureportSET_MSP_NS( puc_Main_ढेर_Pointer ) \
    __asm अस्थिर ( "msr msp_ns, %0" : : "r" ( puc_Main_ढेर_Pointer ) )

/**
 * @brief Set the CONTROL register to the given value.
 */
#घोषणा secureportSET_CONTROL( ulControl ) \
    __asm अस्थिर ( "msr control, %0" : : "r" ( ulControl ) : "memory" )

/**
 * @brief Read the Interrupt Program Status Register (IPSR) value in the given
 * variable.
 */
#घोषणा secureportREAD_IPSR( ulIPSR ) \
    __asm अस्थिर ( "mrs %0, ipsr"  : "=r" ( ulIPSR ) )

/**
 * @brief PRIMASK value to enable interrupts.
 */
#घोषणा secureportPRIMASK_ENABLE_INTERRUPTS_VAL     0

/**
 * @brief PRIMASK value to disable interrupts.
 */
#घोषणा secureportPRIMASK_DISABLE_INTERRUPTS_VAL    1

/**
 * @brief Disable secure interrupts.
 */
#घोषणा secureportDISABLE_SECURE_INTERRUPTS()        secureportSET_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Disable non-secure interrupts.
 *
 * This effectively disables context switches.
 */
#घोषणा secureportDISABLE_NON_SECURE_INTERRUPTS()    secureportSET_NON_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Enable non-secure interrupts.
 */
#घोषणा secureportENABLE_NON_SECURE_INTERRUPTS()     secureportSET_NON_SECURE_PRIMASK( secureportPRIMASK_ENABLE_INTERRUPTS_VAL )

/**
 * @brief Assert definition.
 */
#घोषणा secureportASSERT( x )                      \
    अगर( ( x ) == 0 )                               \
    {                                              \
        secureportDISABLE_SECURE_INTERRUPTS();     \
        secureportDISABLE_NON_SECURE_INTERRUPTS(); \
        क्रम( ; ; ) {; }                            \
    }

#पूर्ण_अगर /* __SECURE_PORT_MACROS_H__ */
