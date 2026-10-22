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

#నిర్వచితం_కాకపోతే __SECURE_PORT_MACROS_H__
#నిర్వచించు __SECURE_PORT_MACROS_H__

/**
 * @brief Byte alignment requirements.
 */
#నిర్వచించు secureportBYTE_ALIGNMENT         8
#నిర్వచించు secureport_BYTE_ALIGNMENT_ముసుగు    ( 0x0007 )

/**
 * @brief Macro to declare a function as non-secure callable.
 */
#ఒకవేళ defined( __IAR_SYSTEMS_ICC__ )
    #నిర్వచించు secureportNON_SECURE_CALLABLE    __cmse_nonsecure_entry __root
#లేకపోతే
    #నిర్వచించు secureportNON_SECURE_CALLABLE    __attribute__( ( cmse_nonsecure_నమోదు ) ) __attribute__( ( వాడిన ) )
#అయితే_ముగింపు

/**
 * @brief Set the secure PRIMASK value.
 */
#నిర్వచించు secureport_సమితి_SECURE_PRIMASK( ul_Primask_విలువ ) \
    __asm అస్థిర ( "msr primask, %0" : : "r" ( ul_Primask_విలువ ) : "memory" )

/**
 * @brief Set the non-secure PRIMASK value.
 */
#నిర్వచించు secureport_సమితి_NON_SECURE_PRIMASK( ul_Primask_విలువ ) \
    __asm అస్థిర ( "msr primask_ns, %0" : : "r" ( ul_Primask_విలువ ) : "memory" )

/**
 * @brief Read the PSP value in the given variable.
 */
#నిర్వచించు secureportREAD_PSP( puc_బహిర్గతం_Current_దొంతర_సూచిక ) \
    __asm అస్థిర ( "mrs %0, psp"  : "=r" ( puc_బహిర్గతం_Current_దొంతర_సూచిక ) )

/**
 * @brief Set the PSP to the given value.
 */
#నిర్వచించు secureport_సమితి_PSP( puc_Current_దొంతర_సూచిక ) \
    __asm అస్థిర ( "msr psp, %0" : : "r" ( puc_Current_దొంతర_సూచిక ) )

/**
 * @brief Read the PSPLIM value in the given variable.
 */
#నిర్వచించు secureportREAD_PSPLIM( puc_బహిర్గతం_దొంతర_హద్దు ) \
    __asm అస్థిర ( "mrs %0, psplim"  : "=r" ( puc_బహిర్గతం_దొంతర_హద్దు ) )

/**
 * @brief Set the PSPLIM to the given value.
 */
#నిర్వచించు secureport_సమితి_PSPLIM( puc_దొంతర_హద్దు ) \
    __asm అస్థిర ( "msr psplim, %0" : : "r" ( puc_దొంతర_హద్దు ) )

/**
 * @brief Set the NonSecure MSP to the given value.
 */
#నిర్వచించు secureport_సమితి_MSP_NS( puc_Main_దొంతర_సూచిక ) \
    __asm అస్థిర ( "msr msp_ns, %0" : : "r" ( puc_Main_దొంతర_సూచిక ) )

/**
 * @brief Set the CONTROL register to the given value.
 */
#నిర్వచించు secureport_సమితి_CONTROL( ulControl ) \
    __asm అస్థిర ( "msr control, %0" : : "r" ( ulControl ) : "memory" )

/**
 * @brief Read the Interrupt Program Status Register (IPSR) value in the given
 * variable.
 */
#నిర్వచించు secureportREAD_IPSR( ulIPSR ) \
    __asm అస్థిర ( "mrs %0, ipsr"  : "=r" ( ulIPSR ) )

/**
 * @brief PRIMASK value to enable interrupts.
 */
#నిర్వచించు secureportPRIMASK_ENABLE_INTERRUPTS_VAL     0

/**
 * @brief PRIMASK value to disable interrupts.
 */
#నిర్వచించు secureportPRIMASK_DISABLE_INTERRUPTS_VAL    1

/**
 * @brief Disable secure interrupts.
 */
#నిర్వచించు secureportDISABLE_SECURE_INTERRUPTS()        secureport_సమితి_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Disable non-secure interrupts.
 *
 * This effectively disables context switches.
 */
#నిర్వచించు secureportDISABLE_NON_SECURE_INTERRUPTS()    secureport_సమితి_NON_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Enable non-secure interrupts.
 */
#నిర్వచించు secureportENABLE_NON_SECURE_INTERRUPTS()     secureport_సమితి_NON_SECURE_PRIMASK( secureportPRIMASK_ENABLE_INTERRUPTS_VAL )

/**
 * @brief Assert definition.
 */
#నిర్వచించు secureportASSERT( x )                      \
    ఒకవేళ( ( x ) == 0 )                               \
    {                                              \
        secureportDISABLE_SECURE_INTERRUPTS();     \
        secureportDISABLE_NON_SECURE_INTERRUPTS(); \
        కొరకు( ; ; ) {; }                            \
    }

#అయితే_ముగింపు /* __SECURE_PORT_MACROS_H__ */
