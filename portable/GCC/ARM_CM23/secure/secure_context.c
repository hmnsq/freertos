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

/* Secure context includes. */
#شامل "secure_context.h"

/* Secure heap includes. */
#شامل "secure_heap.h"

/* Secure port macros. */
#شامل "secure_port_macros.h"

/**
 * @brief CONTROL value for privileged tasks.
 *
 * Bit[0] - 0 --> Thread mode is privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#define securecontext_CONTROL_مقدار_PRIVILEGED      0x02

/**
 * @brief CONTROL value for un-privileged tasks.
 *
 * Bit[0] - 1 --> Thread mode is un-privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#define securecontext_CONTROL_مقدار_UNPRIVILEGED    0x03

/**
 * @brief Size of stack seal values in bytes.
 */
#define securecontext_پشته_SEAL_SIZE               8

/**
 * @brief Stack seal value as recommended by ARM.
 */
#define securecontext_پشته_SEAL_مقدار              0xFEF5EDA5

/**
 * @brief Maximum number of secure contexts.
 */
#ifndef secureconfigMAX_SECURE_CONTEXTS
    #define secureconfigMAX_SECURE_CONTEXTS    8UL
#endif
/*-----------------------------------------------------------*/

/**
 * @brief Pre-allocated array of secure contexts.
 */
SecureContext_t xSecureContexts[ secureconfigMAX_SECURE_CONTEXTS ];
/*-----------------------------------------------------------*/

/**
 * @brief Get a free secure context for a task from the secure context pool (xSecureContexts).
 *
 * This function ensures that only one secure context is allocated for a task.
 *
 * @param[in] pvTaskHandle The task handle for which the secure context is allocated.
 *
 * @return Index of a free secure context in the xSecureContexts array.
 */
ایستا uint32_t ulGetSecureContext( تهی * pvTaskHandle );

/**
 * @brief Return the secure context to the secure context pool (xSecureContexts).
 *
 * @param[in] ulSecureContextIndex Index of the context in the xSecureContexts array.
 */
ایستا تهی vReturnSecureContext( uint32_t ulSecureContextIndex );

/* These are implemented in assembly. */
بیرونی تهی SecureContext_LoadContextAsm( SecureContext_t * pxSecureContext );
بیرونی تهی SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext );
/*-----------------------------------------------------------*/

ایستا uint32_t ulGetSecureContext( تهی * pvTaskHandle )
{
    /* Start with invalid index. */
    uint32_t i, ulSecureContextIndex = secureconfigMAX_SECURE_CONTEXTS;

    برای( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
    {
        اگر( ( xSecureContexts[ i ].puc_Current_پشته_Pointer == پوچ ) &&
            ( xSecureContexts[ i ].puc_پشته_Limit == پوچ ) &&
            ( xSecureContexts[ i ].puc_پشته_Start == پوچ ) &&
            ( xSecureContexts[ i ].pvTaskHandle == پوچ ) &&
            ( ulSecureContextIndex == secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ulSecureContextIndex = i;
        }
        وگرنه اگر( xSecureContexts[ i ].pvTaskHandle == pvTaskHandle )
        {
            /* A task can only have one secure context. Do not allocate a second
             * context for the same task. */
            ulSecureContextIndex = secureconfigMAX_SECURE_CONTEXTS;
            بشکن;
        }
    }

    بازگشت ulSecureContextIndex;
}
/*-----------------------------------------------------------*/

ایستا تهی vReturnSecureContext( uint32_t ulSecureContextIndex )
{
    xSecureContexts[ ulSecureContextIndex ].puc_Current_پشته_Pointer = پوچ;
    xSecureContexts[ ulSecureContextIndex ].puc_پشته_Limit = پوچ;
    xSecureContexts[ ulSecureContextIndex ].puc_پشته_Start = پوچ;
    xSecureContexts[ ulSecureContextIndex ].pvTaskHandle = پوچ;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE تهی SecureContext_Init( تهی )
{
    uint32_t ulIPSR, i;
    ایستا uint32_t ulSecureContextsInitialized = 0;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    اگر( ( ulIPSR != 0 ) && ( ulSecureContextsInitialized == 0 ) )
    {
        /* Ensure to initialize secure contexts only once. */
        ulSecureContextsInitialized = 1;

        /* No stack for thread mode until a task's context is loaded. */
        secureportSET_PSPLIM( securecontext_NO_پشته );
        secureportSET_PSP( securecontext_NO_پشته );

        /* Initialize all secure contexts. */
        برای( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
        {
            xSecureContexts[ i ].puc_Current_پشته_Pointer = پوچ;
            xSecureContexts[ i ].puc_پشته_Limit = پوچ;
            xSecureContexts[ i ].puc_پشته_Start = پوچ;
            xSecureContexts[ i ].pvTaskHandle = پوچ;
        }

        #اگر ( configENABLE_MPU == 1 )
        {
            /* Configure thread mode to use PSP and to be unprivileged. */
            secureportSET_CONTROL( securecontext_CONTROL_مقدار_UNPRIVILEGED );
        }
        #وگرنه /* configENABLE_MPU */
        {
            /* Configure thread mode to use PSP and to be privileged. */
            secureportSET_CONTROL( securecontext_CONTROL_مقدار_PRIVILEGED );
        }
        #endif /* configENABLE_MPU */
    }
}
/*-----------------------------------------------------------*/

#اگر ( configENABLE_MPU == 1 )
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_پشته_Size,
                                                                                       uint32_t ulIsTaskPrivileged,
                                                                                       تهی * pvTaskHandle )
#وگرنه /* configENABLE_MPU */
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_پشته_Size,
                                                                                       تهی * pvTaskHandle )
#endif /* configENABLE_MPU */
{
    uint8_t * puc_پشته_Memory = پوچ;
    uint8_t * puc_پشته_Limit;
    uint32_t ulIPSR, ulSecureContextIndex;
    SecureContextHandle_t xSecureContextHandle = securecontextINVALID_CONTEXT_ID;

    #اگر ( configENABLE_MPU == 1 )
        uint32_t * pul_Current_پشته_Pointer = پوچ;
    #endif /* configENABLE_MPU */

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_پشته_Limit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode.
     * Also do nothing, if a secure context us already loaded. PSPLIM is set to
     * securecontextNO_STACK when no secure context is loaded. */
    اگر( ( ulIPSR != 0 ) && ( puc_پشته_Limit == securecontext_NO_پشته ) )
    {
        /* Obtain a free secure context. */
        ulSecureContextIndex = ulGetSecureContext( pvTaskHandle );

        /* Were we able to get a free context? */
        اگر( ulSecureContextIndex < secureconfigMAX_SECURE_CONTEXTS )
        {
            /* Allocate the stack space if possible. */
            اگر( ( ul_Secure_پشته_Size < securecontext_پشته_SEAL_SIZE ) ||
                ( ul_Secure_پشته_Size > ( UINT32_MAX - securecontext_پشته_SEAL_SIZE ) ) )
            {
                /* Reject stacks that are too small (the CONTROL word would be
                 * written before the allocation, corrupting the secure heap)
                 * and sizes that would overflow when the seal size is added. */
                puc_پشته_Memory = پوچ;
            }
            وگرنه
            {
                puc_پشته_Memory = pvPortMalloc( ul_Secure_پشته_Size + securecontext_پشته_SEAL_SIZE );
            }

            اگر( puc_پشته_Memory != پوچ )
            {
                /* Since stack grows down, the starting point will be the last
                * location. Note that this location is next to the last
                * allocated byte for stack (excluding the space for seal values)
                * because the hardware decrements the stack pointer before
                * writing i.e. if stack pointer is 0x2, a push operation will
                * decrement the stack pointer to 0x1 and then write at 0x1. */
                xSecureContexts[ ulSecureContextIndex ].puc_پشته_Start = puc_پشته_Memory + ul_Secure_پشته_Size;

                /* Seal the created secure process stack. */
                *( uint32_t * ) ( puc_پشته_Memory + ul_Secure_پشته_Size ) = securecontext_پشته_SEAL_مقدار;
                *( uint32_t * ) ( puc_پشته_Memory + ul_Secure_پشته_Size + 4 ) = securecontext_پشته_SEAL_مقدار;

                /* The stack cannot go beyond this location. This value is
                 * programmed in the PSPLIM register on context switch.*/
                xSecureContexts[ ulSecureContextIndex ].puc_پشته_Limit = puc_پشته_Memory;

                xSecureContexts[ ulSecureContextIndex ].pvTaskHandle = pvTaskHandle;

                #اگر ( configENABLE_MPU == 1 )
                {
                    /* Store the correct CONTROL value for the task on the stack.
                     * This value is programmed in the CONTROL register on
                     * context switch. */
                    pul_Current_پشته_Pointer = ( uint32_t * ) xSecureContexts[ ulSecureContextIndex ].puc_پشته_Start;
                    pul_Current_پشته_Pointer--;

                    اگر( ulIsTaskPrivileged )
                    {
                        *( pul_Current_پشته_Pointer ) = securecontext_CONTROL_مقدار_PRIVILEGED;
                    }
                    وگرنه
                    {
                        *( pul_Current_پشته_Pointer ) = securecontext_CONTROL_مقدار_UNPRIVILEGED;
                    }

                    /* Store the current stack pointer. This value is programmed in
                     * the PSP register on context switch. */
                    xSecureContexts[ ulSecureContextIndex ].puc_Current_پشته_Pointer = ( uint8_t * ) pul_Current_پشته_Pointer;
                }
                #وگرنه /* configENABLE_MPU */
                {
                    /* Current SP is set to the starting of the stack. This
                     * value programmed in the PSP register on context switch. */
                    xSecureContexts[ ulSecureContextIndex ].puc_Current_پشته_Pointer = xSecureContexts[ ulSecureContextIndex ].puc_پشته_Start;
                }
                #endif /* configENABLE_MPU */

                /* Ensure to never return 0 as a valid context handle. */
                xSecureContextHandle = ulSecureContextIndex + 1UL;
            }
        }
    }

    بازگشت xSecureContextHandle;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE تهی SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                                              تهی * pvTaskHandle )
{
    uint32_t ulIPSR, ulSecureContextIndex;
    uint8_t * puc_پشته_Limit;

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_پشته_Limit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    اگر( ulIPSR != 0 )
    {
        /* Only free if a valid context handle is passed. */
        اگر( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ulSecureContextIndex = xSecureContextHandle - 1UL;

            /* Ensure that the secure context being deleted is associated with
             * the task and is NOT the currently-loaded context. Freeing a
             * context whose stack is currently loaded in PSPLIM would leave the
             * running task referencing freed secure memory (use-after-free).
             * pvTaskHandle is supplied by the non-secure side and is untrusted,
             * so it is used only as an additional ownership match, not as
             * authority. */
            اگر( ( xSecureContexts[ ulSecureContextIndex ].pvTaskHandle == pvTaskHandle ) &&
                ( xSecureContexts[ ulSecureContextIndex ].puc_پشته_Limit != puc_پشته_Limit ) )
            {
                /* Free the stack space. */
                vPortFree( xSecureContexts[ ulSecureContextIndex ].puc_پشته_Limit );

                /* Return the secure context back to the free secure contexts pool. */
                vReturnSecureContext( ulSecureContextIndex );
            }
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE تهی SecureContext_LoadContext( SecureContextHandle_t xSecureContextHandle,
                                                              تهی * pvTaskHandle )
{
    uint8_t * puc_پشته_Limit;
    uint32_t ulSecureContextIndex;

    اگر( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ulSecureContextIndex = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_پشته_Limit );

        /* Ensure that no secure context is loaded and the task is loading it's
         * own context. */
        اگر( ( puc_پشته_Limit == securecontext_NO_پشته ) &&
            ( xSecureContexts[ ulSecureContextIndex ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_LoadContextAsm( &( xSecureContexts[ ulSecureContextIndex ] ) );
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE تهی SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                                              تهی * pvTaskHandle )
{
    uint8_t * puc_پشته_Limit;
    uint32_t ulSecureContextIndex;

    اگر( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ulSecureContextIndex = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_پشته_Limit );

        /* Ensure that task's context is loaded and the task is saving its own
         * context. */
        اگر( ( xSecureContexts[ ulSecureContextIndex ].puc_پشته_Limit == puc_پشته_Limit ) &&
            ( xSecureContexts[ ulSecureContextIndex ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_SaveContextAsm( &( xSecureContexts[ ulSecureContextIndex ] ) );
        }
    }
}
/*-----------------------------------------------------------*/
