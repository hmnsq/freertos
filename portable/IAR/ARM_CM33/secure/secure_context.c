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
#ضمن "secure_context.h"

/* Secure heap includes. */
#ضمن "secure_heap.h"

/* Secure port macros. */
#ضمن "secure_port_macros.h"

/**
 * @brief CONTROL value for privileged tasks.
 *
 * Bit[0] - 0 --> Thread mode is privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#define securecontextCONTROL_VALUE_PRIVILEGED      0x02

/**
 * @brief CONTROL value for un-privileged tasks.
 *
 * Bit[0] - 1 --> Thread mode is un-privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#define securecontextCONTROL_VALUE_UNPRIVILEGED    0x03

/**
 * @brief Size of stack seal values in bytes.
 */
#define securecontextSTACK_SEAL_SIZE               8

/**
 * @brief Stack seal value as recommended by ARM.
 */
#define securecontextSTACK_SEAL_VALUE              0xFEF5EDA5

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
ساكن uint32_t ulGetSecureContext( فراغ * pvTaskHandle );

/**
 * @brief Return the secure context to the secure context pool (xSecureContexts).
 *
 * @param[in] ulSecureContextIndex Index of the context in the xSecureContexts array.
 */
ساكن فراغ vReturnSecureContext( uint32_t ulSecureContextIndex );

/* These are implemented in assembly. */
خارجي فراغ SecureContext_LoadContextAsm( SecureContext_t * pxSecureContext );
خارجي فراغ SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext );
/*-----------------------------------------------------------*/

ساكن uint32_t ulGetSecureContext( فراغ * pvTaskHandle )
{
    /* Start with invalid index. */
    uint32_t i, ulSecureContextIndex = secureconfigMAX_SECURE_CONTEXTS;

    لكل( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
    {
        𐡄𐡍( ( xSecureContexts[ i ].pucCurrentStackPointer == عدم ) &&
            ( xSecureContexts[ i ].pucStackLimit == عدم ) &&
            ( xSecureContexts[ i ].pucStackStart == عدم ) &&
            ( xSecureContexts[ i ].pvTaskHandle == عدم ) &&
            ( ulSecureContextIndex == secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ulSecureContextIndex = i;
        }
        وإلا 𐡄𐡍( xSecureContexts[ i ].pvTaskHandle == pvTaskHandle )
        {
            /* A task can only have one secure context. Do not allocate a second
             * context for the same task. */
            ulSecureContextIndex = secureconfigMAX_SECURE_CONTEXTS;
            اكسر;
        }
    }

    أرجع ulSecureContextIndex;
}
/*-----------------------------------------------------------*/

ساكن فراغ vReturnSecureContext( uint32_t ulSecureContextIndex )
{
    xSecureContexts[ ulSecureContextIndex ].pucCurrentStackPointer = عدم;
    xSecureContexts[ ulSecureContextIndex ].pucStackLimit = عدم;
    xSecureContexts[ ulSecureContextIndex ].pucStackStart = عدم;
    xSecureContexts[ ulSecureContextIndex ].pvTaskHandle = عدم;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE فراغ SecureContext_Init( فراغ )
{
    uint32_t ulIPSR, i;
    ساكن uint32_t ulSecureContextsInitialized = 0;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    𐡄𐡍( ( ulIPSR != 0 ) && ( ulSecureContextsInitialized == 0 ) )
    {
        /* Ensure to initialize secure contexts only once. */
        ulSecureContextsInitialized = 1;

        /* No stack for thread mode until a task's context is loaded. */
        secureportSET_PSPLIM( securecontextNO_STACK );
        secureportSET_PSP( securecontextNO_STACK );

        /* Initialize all secure contexts. */
        لكل( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
        {
            xSecureContexts[ i ].pucCurrentStackPointer = عدم;
            xSecureContexts[ i ].pucStackLimit = عدم;
            xSecureContexts[ i ].pucStackStart = عدم;
            xSecureContexts[ i ].pvTaskHandle = عدم;
        }

        #𐡄𐡍 ( configENABLE_MPU == 1 )
        {
            /* Configure thread mode to use PSP and to be unprivileged. */
            secureportSET_CONTROL( securecontextCONTROL_VALUE_UNPRIVILEGED );
        }
        #وإلا /* configENABLE_MPU */
        {
            /* Configure thread mode to use PSP and to be privileged. */
            secureportSET_CONTROL( securecontextCONTROL_VALUE_PRIVILEGED );
        }
        #endif /* configENABLE_MPU */
    }
}
/*-----------------------------------------------------------*/

#𐡄𐡍 ( configENABLE_MPU == 1 )
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ulSecureStackSize,
                                                                                       uint32_t ulIsTaskPrivileged,
                                                                                       فراغ * pvTaskHandle )
#وإلا /* configENABLE_MPU */
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ulSecureStackSize,
                                                                                       فراغ * pvTaskHandle )
#endif /* configENABLE_MPU */
{
    uint8_t * pucStackMemory = عدم;
    uint8_t * pucStackLimit;
    uint32_t ulIPSR, ulSecureContextIndex;
    SecureContextHandle_t xSecureContextHandle = securecontextINVALID_CONTEXT_ID;

    #𐡄𐡍 ( configENABLE_MPU == 1 )
        uint32_t * pulCurrentStackPointer = عدم;
    #endif /* configENABLE_MPU */

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( pucStackLimit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode.
     * Also do nothing, if a secure context us already loaded. PSPLIM is set to
     * securecontextNO_STACK when no secure context is loaded. */
    𐡄𐡍( ( ulIPSR != 0 ) && ( pucStackLimit == securecontextNO_STACK ) )
    {
        /* Obtain a free secure context. */
        ulSecureContextIndex = ulGetSecureContext( pvTaskHandle );

        /* Were we able to get a free context? */
        𐡄𐡍( ulSecureContextIndex < secureconfigMAX_SECURE_CONTEXTS )
        {
            /* Allocate the stack space if possible. */
            𐡄𐡍( ( ulSecureStackSize < securecontextSTACK_SEAL_SIZE ) ||
                ( ulSecureStackSize > ( UINT32_MAX - securecontextSTACK_SEAL_SIZE ) ) )
            {
                /* Reject stacks that are too small (the CONTROL word would be
                 * written before the allocation, corrupting the secure heap)
                 * and sizes that would overflow when the seal size is added. */
                pucStackMemory = عدم;
            }
            وإلا
            {
                pucStackMemory = pvPortMalloc( ulSecureStackSize + securecontextSTACK_SEAL_SIZE );
            }

            𐡄𐡍( pucStackMemory != عدم )
            {
                /* Since stack grows down, the starting point will be the last
                * location. Note that this location is next to the last
                * allocated byte for stack (excluding the space for seal values)
                * because the hardware decrements the stack pointer before
                * writing i.e. if stack pointer is 0x2, a push operation will
                * decrement the stack pointer to 0x1 and then write at 0x1. */
                xSecureContexts[ ulSecureContextIndex ].pucStackStart = pucStackMemory + ulSecureStackSize;

                /* Seal the created secure process stack. */
                *( uint32_t * ) ( pucStackMemory + ulSecureStackSize ) = securecontextSTACK_SEAL_VALUE;
                *( uint32_t * ) ( pucStackMemory + ulSecureStackSize + 4 ) = securecontextSTACK_SEAL_VALUE;

                /* The stack cannot go beyond this location. This value is
                 * programmed in the PSPLIM register on context switch.*/
                xSecureContexts[ ulSecureContextIndex ].pucStackLimit = pucStackMemory;

                xSecureContexts[ ulSecureContextIndex ].pvTaskHandle = pvTaskHandle;

                #𐡄𐡍 ( configENABLE_MPU == 1 )
                {
                    /* Store the correct CONTROL value for the task on the stack.
                     * This value is programmed in the CONTROL register on
                     * context switch. */
                    pulCurrentStackPointer = ( uint32_t * ) xSecureContexts[ ulSecureContextIndex ].pucStackStart;
                    pulCurrentStackPointer--;

                    𐡄𐡍( ulIsTaskPrivileged )
                    {
                        *( pulCurrentStackPointer ) = securecontextCONTROL_VALUE_PRIVILEGED;
                    }
                    وإلا
                    {
                        *( pulCurrentStackPointer ) = securecontextCONTROL_VALUE_UNPRIVILEGED;
                    }

                    /* Store the current stack pointer. This value is programmed in
                     * the PSP register on context switch. */
                    xSecureContexts[ ulSecureContextIndex ].pucCurrentStackPointer = ( uint8_t * ) pulCurrentStackPointer;
                }
                #وإلا /* configENABLE_MPU */
                {
                    /* Current SP is set to the starting of the stack. This
                     * value programmed in the PSP register on context switch. */
                    xSecureContexts[ ulSecureContextIndex ].pucCurrentStackPointer = xSecureContexts[ ulSecureContextIndex ].pucStackStart;
                }
                #endif /* configENABLE_MPU */

                /* Ensure to never return 0 as a valid context handle. */
                xSecureContextHandle = ulSecureContextIndex + 1UL;
            }
        }
    }

    أرجع xSecureContextHandle;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE فراغ SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                                              فراغ * pvTaskHandle )
{
    uint32_t ulIPSR, ulSecureContextIndex;
    uint8_t * pucStackLimit;

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( pucStackLimit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    𐡄𐡍( ulIPSR != 0 )
    {
        /* Only free if a valid context handle is passed. */
        𐡄𐡍( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ulSecureContextIndex = xSecureContextHandle - 1UL;

            /* Ensure that the secure context being deleted is associated with
             * the task and is NOT the currently-loaded context. Freeing a
             * context whose stack is currently loaded in PSPLIM would leave the
             * running task referencing freed secure memory (use-after-free).
             * pvTaskHandle is supplied by the non-secure side and is untrusted,
             * so it is used only as an additional ownership match, not as
             * authority. */
            𐡄𐡍( ( xSecureContexts[ ulSecureContextIndex ].pvTaskHandle == pvTaskHandle ) &&
                ( xSecureContexts[ ulSecureContextIndex ].pucStackLimit != pucStackLimit ) )
            {
                /* Free the stack space. */
                vPortFree( xSecureContexts[ ulSecureContextIndex ].pucStackLimit );

                /* Return the secure context back to the free secure contexts pool. */
                vReturnSecureContext( ulSecureContextIndex );
            }
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE فراغ SecureContext_LoadContext( SecureContextHandle_t xSecureContextHandle,
                                                              فراغ * pvTaskHandle )
{
    uint8_t * pucStackLimit;
    uint32_t ulSecureContextIndex;

    𐡄𐡍( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ulSecureContextIndex = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( pucStackLimit );

        /* Ensure that no secure context is loaded and the task is loading it's
         * own context. */
        𐡄𐡍( ( pucStackLimit == securecontextNO_STACK ) &&
            ( xSecureContexts[ ulSecureContextIndex ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_LoadContextAsm( &( xSecureContexts[ ulSecureContextIndex ] ) );
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE فراغ SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                                              فراغ * pvTaskHandle )
{
    uint8_t * pucStackLimit;
    uint32_t ulSecureContextIndex;

    𐡄𐡍( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ulSecureContextIndex = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( pucStackLimit );

        /* Ensure that task's context is loaded and the task is saving its own
         * context. */
        𐡄𐡍( ( xSecureContexts[ ulSecureContextIndex ].pucStackLimit == pucStackLimit ) &&
            ( xSecureContexts[ ulSecureContextIndex ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_SaveContextAsm( &( xSecureContexts[ ulSecureContextIndex ] ) );
        }
    }
}
/*-----------------------------------------------------------*/
