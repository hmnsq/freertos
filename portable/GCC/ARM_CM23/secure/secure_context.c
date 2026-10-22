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
#ಅನ್ತರ್ಭಾವ "secure_context.h"

/* Secure heap includes. */
#ಅನ್ತರ್ಭಾವ "secure_heap.h"

/* Secure port macros. */
#ಅನ್ತರ್ಭಾವ "secure_port_macros.h"

/**
 * @brief CONTROL value for privileged tasks.
 *
 * Bit[0] - 0 --> Thread mode is privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#define securecontext_CONTROL_ಮೌಲ್ಯ_PRIVILEGED      0x02

/**
 * @brief CONTROL value for un-privileged tasks.
 *
 * Bit[0] - 1 --> Thread mode is un-privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#define securecontext_CONTROL_ಮೌಲ್ಯ_UNPRIVILEGED    0x03

/**
 * @brief Size of stack seal values in bytes.
 */
#define securecontext_ರಾಶಿ_SEAL_SIZE               8

/**
 * @brief Stack seal value as recommended by ARM.
 */
#define securecontext_ರಾಶಿ_SEAL_ಮೌಲ್ಯ              0xFEF5EDA5

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
ಸ್ಥಿರ uint32_t ulGetSecureContext( ಶೂನ್ಯ * pvTaskHandle );

/**
 * @brief Return the secure context to the secure context pool (xSecureContexts).
 *
 * @param[in] ulSecureContextIndex Index of the context in the xSecureContexts array.
 */
ಸ್ಥಿರ ಶೂನ್ಯ vReturnSecureContext( uint32_t ulSecureContextIndex );

/* These are implemented in assembly. */
ಬಾಹ್ಯ ಶೂನ್ಯ SecureContext_LoadContextAsm( SecureContext_t * pxSecureContext );
ಬಾಹ್ಯ ಶೂನ್ಯ SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext );
/*-----------------------------------------------------------*/

ಸ್ಥಿರ uint32_t ulGetSecureContext( ಶೂನ್ಯ * pvTaskHandle )
{
    /* Start with invalid index. */
    uint32_t i, ulSecureContextIndex = secureconfigMAX_SECURE_CONTEXTS;

    ಪ್ರತಿ( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
    {
        ಯದಿ( ( xSecureContexts[ i ].puc_Current_ರಾಶಿ_Pointer == ರಿಕ್ತ ) &&
            ( xSecureContexts[ i ].puc_ರಾಶಿ_Limit == ರಿಕ್ತ ) &&
            ( xSecureContexts[ i ].puc_ರಾಶಿ_Start == ರಿಕ್ತ ) &&
            ( xSecureContexts[ i ].pvTaskHandle == ರಿಕ್ತ ) &&
            ( ulSecureContextIndex == secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ulSecureContextIndex = i;
        }
        ಅನ್ಯಥಾ ಯದಿ( xSecureContexts[ i ].pvTaskHandle == pvTaskHandle )
        {
            /* A task can only have one secure context. Do not allocate a second
             * context for the same task. */
            ulSecureContextIndex = secureconfigMAX_SECURE_CONTEXTS;
            ಭಙ್ಗ;
        }
    }

    ಪ್ರತ್ಯಾಗಮ ulSecureContextIndex;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ vReturnSecureContext( uint32_t ulSecureContextIndex )
{
    xSecureContexts[ ulSecureContextIndex ].puc_Current_ರಾಶಿ_Pointer = ರಿಕ್ತ;
    xSecureContexts[ ulSecureContextIndex ].puc_ರಾಶಿ_Limit = ರಿಕ್ತ;
    xSecureContexts[ ulSecureContextIndex ].puc_ರಾಶಿ_Start = ರಿಕ್ತ;
    xSecureContexts[ ulSecureContextIndex ].pvTaskHandle = ರಿಕ್ತ;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ಶೂನ್ಯ SecureContext_Init( ಶೂನ್ಯ )
{
    uint32_t ulIPSR, i;
    ಸ್ಥಿರ uint32_t ulSecureContextsInitialized = 0;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    ಯದಿ( ( ulIPSR != 0 ) && ( ulSecureContextsInitialized == 0 ) )
    {
        /* Ensure to initialize secure contexts only once. */
        ulSecureContextsInitialized = 1;

        /* No stack for thread mode until a task's context is loaded. */
        secureportSET_PSPLIM( securecontext_NO_ರಾಶಿ );
        secureportSET_PSP( securecontext_NO_ರಾಶಿ );

        /* Initialize all secure contexts. */
        ಪ್ರತಿ( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
        {
            xSecureContexts[ i ].puc_Current_ರಾಶಿ_Pointer = ರಿಕ್ತ;
            xSecureContexts[ i ].puc_ರಾಶಿ_Limit = ರಿಕ್ತ;
            xSecureContexts[ i ].puc_ರಾಶಿ_Start = ರಿಕ್ತ;
            xSecureContexts[ i ].pvTaskHandle = ರಿಕ್ತ;
        }

        #ಯದಿ ( configENABLE_MPU == 1 )
        {
            /* Configure thread mode to use PSP and to be unprivileged. */
            secureportSET_CONTROL( securecontext_CONTROL_ಮೌಲ್ಯ_UNPRIVILEGED );
        }
        #ಅನ್ಯಥಾ /* configENABLE_MPU */
        {
            /* Configure thread mode to use PSP and to be privileged. */
            secureportSET_CONTROL( securecontext_CONTROL_ಮೌಲ್ಯ_PRIVILEGED );
        }
        #endif /* configENABLE_MPU */
    }
}
/*-----------------------------------------------------------*/

#ಯದಿ ( configENABLE_MPU == 1 )
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ರಾಶಿ_Size,
                                                                                       uint32_t ulIsTaskPrivileged,
                                                                                       ಶೂನ್ಯ * pvTaskHandle )
#ಅನ್ಯಥಾ /* configENABLE_MPU */
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ರಾಶಿ_Size,
                                                                                       ಶೂನ್ಯ * pvTaskHandle )
#endif /* configENABLE_MPU */
{
    uint8_t * puc_ರಾಶಿ_Memory = ರಿಕ್ತ;
    uint8_t * puc_ರಾಶಿ_Limit;
    uint32_t ulIPSR, ulSecureContextIndex;
    SecureContextHandle_t xSecureContextHandle = securecontextINVALID_CONTEXT_ID;

    #ಯದಿ ( configENABLE_MPU == 1 )
        uint32_t * pul_Current_ರಾಶಿ_Pointer = ರಿಕ್ತ;
    #endif /* configENABLE_MPU */

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ರಾಶಿ_Limit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode.
     * Also do nothing, if a secure context us already loaded. PSPLIM is set to
     * securecontextNO_STACK when no secure context is loaded. */
    ಯದಿ( ( ulIPSR != 0 ) && ( puc_ರಾಶಿ_Limit == securecontext_NO_ರಾಶಿ ) )
    {
        /* Obtain a free secure context. */
        ulSecureContextIndex = ulGetSecureContext( pvTaskHandle );

        /* Were we able to get a free context? */
        ಯದಿ( ulSecureContextIndex < secureconfigMAX_SECURE_CONTEXTS )
        {
            /* Allocate the stack space if possible. */
            ಯದಿ( ( ul_Secure_ರಾಶಿ_Size < securecontext_ರಾಶಿ_SEAL_SIZE ) ||
                ( ul_Secure_ರಾಶಿ_Size > ( UINT32_MAX - securecontext_ರಾಶಿ_SEAL_SIZE ) ) )
            {
                /* Reject stacks that are too small (the CONTROL word would be
                 * written before the allocation, corrupting the secure heap)
                 * and sizes that would overflow when the seal size is added. */
                puc_ರಾಶಿ_Memory = ರಿಕ್ತ;
            }
            ಅನ್ಯಥಾ
            {
                puc_ರಾಶಿ_Memory = pvPortMalloc( ul_Secure_ರಾಶಿ_Size + securecontext_ರಾಶಿ_SEAL_SIZE );
            }

            ಯದಿ( puc_ರಾಶಿ_Memory != ರಿಕ್ತ )
            {
                /* Since stack grows down, the starting point will be the last
                * location. Note that this location is next to the last
                * allocated byte for stack (excluding the space for seal values)
                * because the hardware decrements the stack pointer before
                * writing i.e. if stack pointer is 0x2, a push operation will
                * decrement the stack pointer to 0x1 and then write at 0x1. */
                xSecureContexts[ ulSecureContextIndex ].puc_ರಾಶಿ_Start = puc_ರಾಶಿ_Memory + ul_Secure_ರಾಶಿ_Size;

                /* Seal the created secure process stack. */
                *( uint32_t * ) ( puc_ರಾಶಿ_Memory + ul_Secure_ರಾಶಿ_Size ) = securecontext_ರಾಶಿ_SEAL_ಮೌಲ್ಯ;
                *( uint32_t * ) ( puc_ರಾಶಿ_Memory + ul_Secure_ರಾಶಿ_Size + 4 ) = securecontext_ರಾಶಿ_SEAL_ಮೌಲ್ಯ;

                /* The stack cannot go beyond this location. This value is
                 * programmed in the PSPLIM register on context switch.*/
                xSecureContexts[ ulSecureContextIndex ].puc_ರಾಶಿ_Limit = puc_ರಾಶಿ_Memory;

                xSecureContexts[ ulSecureContextIndex ].pvTaskHandle = pvTaskHandle;

                #ಯದಿ ( configENABLE_MPU == 1 )
                {
                    /* Store the correct CONTROL value for the task on the stack.
                     * This value is programmed in the CONTROL register on
                     * context switch. */
                    pul_Current_ರಾಶಿ_Pointer = ( uint32_t * ) xSecureContexts[ ulSecureContextIndex ].puc_ರಾಶಿ_Start;
                    pul_Current_ರಾಶಿ_Pointer--;

                    ಯದಿ( ulIsTaskPrivileged )
                    {
                        *( pul_Current_ರಾಶಿ_Pointer ) = securecontext_CONTROL_ಮೌಲ್ಯ_PRIVILEGED;
                    }
                    ಅನ್ಯಥಾ
                    {
                        *( pul_Current_ರಾಶಿ_Pointer ) = securecontext_CONTROL_ಮೌಲ್ಯ_UNPRIVILEGED;
                    }

                    /* Store the current stack pointer. This value is programmed in
                     * the PSP register on context switch. */
                    xSecureContexts[ ulSecureContextIndex ].puc_Current_ರಾಶಿ_Pointer = ( uint8_t * ) pul_Current_ರಾಶಿ_Pointer;
                }
                #ಅನ್ಯಥಾ /* configENABLE_MPU */
                {
                    /* Current SP is set to the starting of the stack. This
                     * value programmed in the PSP register on context switch. */
                    xSecureContexts[ ulSecureContextIndex ].puc_Current_ರಾಶಿ_Pointer = xSecureContexts[ ulSecureContextIndex ].puc_ರಾಶಿ_Start;
                }
                #endif /* configENABLE_MPU */

                /* Ensure to never return 0 as a valid context handle. */
                xSecureContextHandle = ulSecureContextIndex + 1UL;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ xSecureContextHandle;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ಶೂನ್ಯ SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                                              ಶೂನ್ಯ * pvTaskHandle )
{
    uint32_t ulIPSR, ulSecureContextIndex;
    uint8_t * puc_ರಾಶಿ_Limit;

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ರಾಶಿ_Limit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    ಯದಿ( ulIPSR != 0 )
    {
        /* Only free if a valid context handle is passed. */
        ಯದಿ( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ulSecureContextIndex = xSecureContextHandle - 1UL;

            /* Ensure that the secure context being deleted is associated with
             * the task and is NOT the currently-loaded context. Freeing a
             * context whose stack is currently loaded in PSPLIM would leave the
             * running task referencing freed secure memory (use-after-free).
             * pvTaskHandle is supplied by the non-secure side and is untrusted,
             * so it is used only as an additional ownership match, not as
             * authority. */
            ಯದಿ( ( xSecureContexts[ ulSecureContextIndex ].pvTaskHandle == pvTaskHandle ) &&
                ( xSecureContexts[ ulSecureContextIndex ].puc_ರಾಶಿ_Limit != puc_ರಾಶಿ_Limit ) )
            {
                /* Free the stack space. */
                vPortFree( xSecureContexts[ ulSecureContextIndex ].puc_ರಾಶಿ_Limit );

                /* Return the secure context back to the free secure contexts pool. */
                vReturnSecureContext( ulSecureContextIndex );
            }
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ಶೂನ್ಯ SecureContext_LoadContext( SecureContextHandle_t xSecureContextHandle,
                                                              ಶೂನ್ಯ * pvTaskHandle )
{
    uint8_t * puc_ರಾಶಿ_Limit;
    uint32_t ulSecureContextIndex;

    ಯದಿ( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ulSecureContextIndex = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ರಾಶಿ_Limit );

        /* Ensure that no secure context is loaded and the task is loading it's
         * own context. */
        ಯದಿ( ( puc_ರಾಶಿ_Limit == securecontext_NO_ರಾಶಿ ) &&
            ( xSecureContexts[ ulSecureContextIndex ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_LoadContextAsm( &( xSecureContexts[ ulSecureContextIndex ] ) );
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ಶೂನ್ಯ SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                                              ಶೂನ್ಯ * pvTaskHandle )
{
    uint8_t * puc_ರಾಶಿ_Limit;
    uint32_t ulSecureContextIndex;

    ಯದಿ( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ulSecureContextIndex = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ರಾಶಿ_Limit );

        /* Ensure that task's context is loaded and the task is saving its own
         * context. */
        ಯದಿ( ( xSecureContexts[ ulSecureContextIndex ].puc_ರಾಶಿ_Limit == puc_ರಾಶಿ_Limit ) &&
            ( xSecureContexts[ ulSecureContextIndex ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_SaveContextAsm( &( xSecureContexts[ ulSecureContextIndex ] ) );
        }
    }
}
/*-----------------------------------------------------------*/
