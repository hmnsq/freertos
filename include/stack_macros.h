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

#ifndef ರಾಶಿ_MACROS_H
#define ರಾಶಿ_MACROS_H

/*
 * Call the stack overflow hook function if the stack of the task being swapped
 * out is currently overflowed, or looks like it might have overflowed in the
 * past.
 *
 * Setting configCHECK_FOR_STACK_OVERFLOW to 1 will cause the macro to check
 * the current stack state only - comparing the current top of stack value to
 * the stack limit.  Setting configCHECK_FOR_STACK_OVERFLOW to greater than 1
 * will also cause the last few stack bytes to be checked to ensure the value
 * to which the bytes were set when the task was created have not been
 * overwritten.  Note this second test does not guarantee that an overflowed
 * stack will always be recognised.
 */

/*-----------------------------------------------------------*/

/*
 * portSTACK_LIMIT_PADDING is a number of extra words to consider to be in
 * use on the stack.
 */
#ifndef port_ರಾಶಿ_LIMIT_PADDING
    #define port_ರಾಶಿ_LIMIT_PADDING    0
#endif

/* Stack overflow check is not straight forward to implement for MPU ports
 * because of the following reasons:
 * 1. The context is stored in TCB and as a result, pxTopOfStack member points
 *    to the context location in TCB.
 * 2. System calls are executed on a separate privileged only stack.
 *
 * It is still okay because an MPU region is used to protect task stack which
 * means task stack overflow will trigger an MPU fault for unprivileged tasks.
 * Additionally, architectures with hardware stack overflow checking support
 * (such as Armv8-M) will trigger a fault when a task's stack overflows.
 */
#ಯದಿ ( ( config_CHECK_FOR_ರಾಶಿ_OVERFLOW == 1 ) && ( port_ರಾಶಿ_GROWTH < 0 ) && ( portUSING_MPU_WRAPPERS != 1 ) )

/* Only the current stack state is to be checked. */
    #define task_CHECK_FOR_ರಾಶಿ_OVERFLOW()                                                      \
    ಕುರು                                                                                          \
    {                                                                                           \
        /* Is the currently saved stack pointer within the stack limit? */                      \
        ಯದಿ( pxCurrentTCB->px_ತುದಿ_Of_ರಾಶಿ <= pxCurrentTCB->px_ರಾಶಿ + port_ರಾಶಿ_LIMIT_PADDING )     \
        {                                                                                       \
            ವರ್ಣ * pcOverflowTaskName = pxCurrentTCB->pcTaskName;                               \
            v_Application_ರಾಶಿ_Overflow_Hook( ( TaskHandle_t ) pxCurrentTCB, pcOverflowTaskName ); \
        }                                                                                       \
    } ಯಾವತ್( 0 )

#endif /* configCHECK_FOR_STACK_OVERFLOW == 1 */
/*-----------------------------------------------------------*/

#ಯದಿ ( ( config_CHECK_FOR_ರಾಶಿ_OVERFLOW == 1 ) && ( port_ರಾಶಿ_GROWTH > 0 ) && ( portUSING_MPU_WRAPPERS != 1 ) )

/* Only the current stack state is to be checked. */
    #define task_CHECK_FOR_ರಾಶಿ_OVERFLOW()                                                       \
    ಕುರು                                                                                           \
    {                                                                                            \
        /* Is the currently saved stack pointer within the stack limit? */                       \
        ಯದಿ( pxCurrentTCB->px_ತುದಿ_Of_ರಾಶಿ >= pxCurrentTCB->px_End_Of_ರಾಶಿ - port_ರಾಶಿ_LIMIT_PADDING ) \
        {                                                                                        \
            ವರ್ಣ * pcOverflowTaskName = pxCurrentTCB->pcTaskName;                                \
            v_Application_ರಾಶಿ_Overflow_Hook( ( TaskHandle_t ) pxCurrentTCB, pcOverflowTaskName );  \
        }                                                                                        \
    } ಯಾವತ್( 0 )

#endif /* configCHECK_FOR_STACK_OVERFLOW == 1 */
/*-----------------------------------------------------------*/

#ಯದಿ ( ( config_CHECK_FOR_ರಾಶಿ_OVERFLOW > 1 ) && ( port_ರಾಶಿ_GROWTH < 0 ) && ( portUSING_MPU_WRAPPERS != 1 ) )

    #define task_CHECK_FOR_ರಾಶಿ_OVERFLOW()                                                       \
    ಕುರು                                                                                           \
    {                                                                                            \
        ಧ್ರುವ uint32_t * ಧ್ರುವ pul_ರಾಶಿ = ( uint32_t * ) pxCurrentTCB->px_ರಾಶಿ;                  \
        ಧ್ರುವ uint32_t ul_Check_ಮೌಲ್ಯ = ( uint32_t ) 0xa5a5a5a5U;                                  \
                                                                                                 \
        ಯದಿ( ( pxCurrentTCB->px_ತುದಿ_Of_ರಾಶಿ <= pxCurrentTCB->px_ರಾಶಿ + port_ರಾಶಿ_LIMIT_PADDING ) || \
            ( pul_ರಾಶಿ[ 0 ] != ul_Check_ಮೌಲ್ಯ ) ||                                                 \
            ( pul_ರಾಶಿ[ 1 ] != ul_Check_ಮೌಲ್ಯ ) ||                                                 \
            ( pul_ರಾಶಿ[ 2 ] != ul_Check_ಮೌಲ್ಯ ) ||                                                 \
            ( pul_ರಾಶಿ[ 3 ] != ul_Check_ಮೌಲ್ಯ ) )                                                  \
        {                                                                                        \
            ವರ್ಣ * pcOverflowTaskName = pxCurrentTCB->pcTaskName;                                \
            v_Application_ರಾಶಿ_Overflow_Hook( ( TaskHandle_t ) pxCurrentTCB, pcOverflowTaskName );  \
        }                                                                                        \
    } ಯಾವತ್( 0 )

#endif /* #if( configCHECK_FOR_STACK_OVERFLOW > 1 ) */
/*-----------------------------------------------------------*/

#ಯದಿ ( ( config_CHECK_FOR_ರಾಶಿ_OVERFLOW > 1 ) && ( port_ರಾಶಿ_GROWTH > 0 ) && ( portUSING_MPU_WRAPPERS != 1 ) )

    #define task_CHECK_FOR_ರಾಶಿ_OVERFLOW()                                                                                                \
    ಕುರು                                                                                                                                    \
    {                                                                                                                                     \
        int8_t * pc_End_Of_ರಾಶಿ = ( int8_t * ) pxCurrentTCB->px_End_Of_ರಾಶಿ;                                                                  \
        ಸ್ಥಿರ ಧ್ರುವ uint8_t uc_Expected_ರಾಶಿ_Bytes[] = { tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE,   \
                                                        tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE,   \
                                                        tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE,   \
                                                        tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE,   \
                                                        tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE, tsk_ರಾಶಿ_FILL_BYTE }; \
                                                                                                                                          \
        pc_End_Of_ರಾಶಿ -= ಪರಿಮಾಣ( uc_Expected_ರಾಶಿ_Bytes );                                                                                   \
                                                                                                                                          \
        ಯದಿ( ( pxCurrentTCB->px_ತುದಿ_Of_ರಾಶಿ >= pxCurrentTCB->px_End_Of_ರಾಶಿ - port_ರಾಶಿ_LIMIT_PADDING ) ||                                     \
            ( memcmp( ( ಶೂನ್ಯ * ) pc_End_Of_ರಾಶಿ, ( ಶೂನ್ಯ * ) uc_Expected_ರಾಶಿ_Bytes, ಪರಿಮಾಣ( uc_Expected_ರಾಶಿ_Bytes ) ) != 0 ) )                 \
        {                                                                                                                                 \
            ವರ್ಣ * pcOverflowTaskName = pxCurrentTCB->pcTaskName;                                                                         \
            v_Application_ರಾಶಿ_Overflow_Hook( ( TaskHandle_t ) pxCurrentTCB, pcOverflowTaskName );                                           \
        }                                                                                                                                 \
    } ಯಾವತ್( 0 )

#endif /* #if( configCHECK_FOR_STACK_OVERFLOW > 1 ) */
/*-----------------------------------------------------------*/

/* Remove stack overflow macro if not being used. */
#ifndef task_CHECK_FOR_ರಾಶಿ_OVERFLOW
    #define task_CHECK_FOR_ರಾಶಿ_OVERFLOW()
#endif



#endif /* STACK_MACROS_H */
