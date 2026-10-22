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

#यदि_अपरिभाषितम् __SECURE_PORT_MACROS_H__
#परिभाषय __SECURE_PORT_MACROS_H__

/**
 * @brief Byte alignment requirements.
 */
#परिभाषय secureportBYTE_ALIGNMENT         8
#परिभाषय secureport_BYTE_ALIGNMENT_आवरणम्    ( 0x0007 )

/**
 * @brief Macro to declare a function as non-secure callable.
 */
#यदि defined( __IAR_SYSTEMS_ICC__ )
    #परिभाषय secureportNON_SECURE_CALLABLE    __cmse_nonsecure_entry __root
#अन्यथा
    #परिभाषय secureportNON_SECURE_CALLABLE    __attribute__( ( cmse_nonsecure_प्रविष्टिः ) ) __attribute__( ( प्रयुक्तम् ) )
#यदि_अन्तः

/**
 * @brief Set the secure PRIMASK value.
 */
#परिभाषय secureport_समुच्चयः_SECURE_PRIMASK( ul_Primask_मानम् ) \
    __asm चञ्चल ( "msr primask, %0" : : "r" ( ul_Primask_मानम् ) : "memory" )

/**
 * @brief Set the non-secure PRIMASK value.
 */
#परिभाषय secureport_समुच्चयः_NON_SECURE_PRIMASK( ul_Primask_मानम् ) \
    __asm चञ्चल ( "msr primask_ns, %0" : : "r" ( ul_Primask_मानम् ) : "memory" )

/**
 * @brief Read the PSP value in the given variable.
 */
#परिभाषय secureportREAD_PSP( puc_बहिर्गमनम्_Current_राशिः_Pointer ) \
    __asm चञ्चल ( "mrs %0, psp"  : "=r" ( puc_बहिर्गमनम्_Current_राशिः_Pointer ) )

/**
 * @brief Set the PSP to the given value.
 */
#परिभाषय secureport_समुच्चयः_PSP( puc_Current_राशिः_Pointer ) \
    __asm चञ्चल ( "msr psp, %0" : : "r" ( puc_Current_राशिः_Pointer ) )

/**
 * @brief Read the PSPLIM value in the given variable.
 */
#परिभाषय secureportREAD_PSPLIM( puc_बहिर्गमनम्_राशिः_सीमा ) \
    __asm चञ्चल ( "mrs %0, psplim"  : "=r" ( puc_बहिर्गमनम्_राशिः_सीमा ) )

/**
 * @brief Set the PSPLIM to the given value.
 */
#परिभाषय secureport_समुच्चयः_PSPLIM( puc_राशिः_सीमा ) \
    __asm चञ्चल ( "msr psplim, %0" : : "r" ( puc_राशिः_सीमा ) )

/**
 * @brief Set the NonSecure MSP to the given value.
 */
#परिभाषय secureport_समुच्चयः_MSP_NS( puc_Main_राशिः_Pointer ) \
    __asm चञ्चल ( "msr msp_ns, %0" : : "r" ( puc_Main_राशिः_Pointer ) )

/**
 * @brief Set the CONTROL register to the given value.
 */
#परिभाषय secureport_समुच्चयः_CONTROL( ulControl ) \
    __asm चञ्चल ( "msr control, %0" : : "r" ( ulControl ) : "memory" )

/**
 * @brief Read the Interrupt Program Status Register (IPSR) value in the given
 * variable.
 */
#परिभाषय secureportREAD_IPSR( ulIPSR ) \
    __asm चञ्चल ( "mrs %0, ipsr"  : "=r" ( ulIPSR ) )

/**
 * @brief PRIMASK value to enable interrupts.
 */
#परिभाषय secureportPRIMASK_ENABLE_INTERRUPTS_VAL     0

/**
 * @brief PRIMASK value to disable interrupts.
 */
#परिभाषय secureportPRIMASK_DISABLE_INTERRUPTS_VAL    1

/**
 * @brief Disable secure interrupts.
 */
#परिभाषय secureportDISABLE_SECURE_INTERRUPTS()        secureport_समुच्चयः_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Disable non-secure interrupts.
 *
 * This effectively disables context switches.
 */
#परिभाषय secureportDISABLE_NON_SECURE_INTERRUPTS()    secureport_समुच्चयः_NON_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Enable non-secure interrupts.
 */
#परिभाषय secureportENABLE_NON_SECURE_INTERRUPTS()     secureport_समुच्चयः_NON_SECURE_PRIMASK( secureportPRIMASK_ENABLE_INTERRUPTS_VAL )

/**
 * @brief Assert definition.
 */
#परिभाषय secureportASSERT( x )                      \
    यदि( ( x ) == 0 )                               \
    {                                              \
        secureportDISABLE_SECURE_INTERRUPTS();     \
        secureportDISABLE_NON_SECURE_INTERRUPTS(); \
        प्रति( ; ; ) {; }                            \
    }

#यदि_अन्तः /* __SECURE_PORT_MACROS_H__ */
