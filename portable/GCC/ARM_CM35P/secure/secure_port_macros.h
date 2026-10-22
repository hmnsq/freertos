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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __SECURE_PORT_MACROS_H__
#ವ್ಯಾಖ್ಯಾನಿಸು __SECURE_PORT_MACROS_H__

/**
 * @brief Byte alignment requirements.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportBYTE_ALIGNMENT         8
#ವ್ಯಾಖ್ಯಾನಿಸು secureport_BYTE_ALIGNMENT_ಮುಖವಾಡ    ( 0x0007 )

/**
 * @brief Macro to declare a function as non-secure callable.
 */
#ಆದರೆ defined( __IAR_SYSTEMS_ICC__ )
    #ವ್ಯಾಖ್ಯಾನಿಸು secureportNON_SECURE_CALLABLE    __cmse_nonsecure_entry __root
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು secureportNON_SECURE_CALLABLE    __attribute__( ( cmse_nonsecure_ನಮೂದು ) ) __attribute__( ( ಬಳಸಿದ ) )
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Set the secure PRIMASK value.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureport_ಗಣ_SECURE_PRIMASK( ul_Primask_ಮೌಲ್ಯ ) \
    __asm ಅಸ್ಥಿರ ( "msr primask, %0" : : "r" ( ul_Primask_ಮೌಲ್ಯ ) : "memory" )

/**
 * @brief Set the non-secure PRIMASK value.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureport_ಗಣ_NON_SECURE_PRIMASK( ul_Primask_ಮೌಲ್ಯ ) \
    __asm ಅಸ್ಥಿರ ( "msr primask_ns, %0" : : "r" ( ul_Primask_ಮೌಲ್ಯ ) : "memory" )

/**
 * @brief Read the PSP value in the given variable.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportREAD_PSP( puc_ಹೊರಹೋಗು_Current_ರಾಶಿ_ಸೂಚಕ ) \
    __asm ಅಸ್ಥಿರ ( "mrs %0, psp"  : "=r" ( puc_ಹೊರಹೋಗು_Current_ರಾಶಿ_ಸೂಚಕ ) )

/**
 * @brief Set the PSP to the given value.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureport_ಗಣ_PSP( puc_Current_ರಾಶಿ_ಸೂಚಕ ) \
    __asm ಅಸ್ಥಿರ ( "msr psp, %0" : : "r" ( puc_Current_ರಾಶಿ_ಸೂಚಕ ) )

/**
 * @brief Read the PSPLIM value in the given variable.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportREAD_PSPLIM( puc_ಹೊರಹೋಗು_ರಾಶಿ_ಎಲ್ಲೆ ) \
    __asm ಅಸ್ಥಿರ ( "mrs %0, psplim"  : "=r" ( puc_ಹೊರಹೋಗು_ರಾಶಿ_ಎಲ್ಲೆ ) )

/**
 * @brief Set the PSPLIM to the given value.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureport_ಗಣ_PSPLIM( puc_ರಾಶಿ_ಎಲ್ಲೆ ) \
    __asm ಅಸ್ಥಿರ ( "msr psplim, %0" : : "r" ( puc_ರಾಶಿ_ಎಲ್ಲೆ ) )

/**
 * @brief Set the NonSecure MSP to the given value.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureport_ಗಣ_MSP_NS( puc_Main_ರಾಶಿ_ಸೂಚಕ ) \
    __asm ಅಸ್ಥಿರ ( "msr msp_ns, %0" : : "r" ( puc_Main_ರಾಶಿ_ಸೂಚಕ ) )

/**
 * @brief Set the CONTROL register to the given value.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureport_ಗಣ_CONTROL( ulControl ) \
    __asm ಅಸ್ಥಿರ ( "msr control, %0" : : "r" ( ulControl ) : "memory" )

/**
 * @brief Read the Interrupt Program Status Register (IPSR) value in the given
 * variable.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportREAD_IPSR( ulIPSR ) \
    __asm ಅಸ್ಥಿರ ( "mrs %0, ipsr"  : "=r" ( ulIPSR ) )

/**
 * @brief PRIMASK value to enable interrupts.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportPRIMASK_ENABLE_INTERRUPTS_VAL     0

/**
 * @brief PRIMASK value to disable interrupts.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportPRIMASK_DISABLE_INTERRUPTS_VAL    1

/**
 * @brief Disable secure interrupts.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportDISABLE_SECURE_INTERRUPTS()        secureport_ಗಣ_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Disable non-secure interrupts.
 *
 * This effectively disables context switches.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportDISABLE_NON_SECURE_INTERRUPTS()    secureport_ಗಣ_NON_SECURE_PRIMASK( secureportPRIMASK_DISABLE_INTERRUPTS_VAL )

/**
 * @brief Enable non-secure interrupts.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportENABLE_NON_SECURE_INTERRUPTS()     secureport_ಗಣ_NON_SECURE_PRIMASK( secureportPRIMASK_ENABLE_INTERRUPTS_VAL )

/**
 * @brief Assert definition.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು secureportASSERT( x )                      \
    ಆದರೆ( ( x ) == 0 )                               \
    {                                              \
        secureportDISABLE_SECURE_INTERRUPTS();     \
        secureportDISABLE_NON_SECURE_INTERRUPTS(); \
        ಗಾಗಿ( ; ; ) {; }                            \
    }

#ಆದರೆ_ಅಂತ್ಯ /* __SECURE_PORT_MACROS_H__ */
