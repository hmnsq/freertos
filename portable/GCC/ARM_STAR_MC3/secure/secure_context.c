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
#অন্তর্ভাব "secure_context.h"

/* Secure heap includes. */
#অন্তর্ভাব "secure_heap.h"

/* Secure port macros. */
#অন্তর্ভাব "secure_port_macros.h"

/**
 * @brief CONTROL value for privileged tasks.
 *
 * Bit[0] - 0 --> Thread mode is privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#define securecontext_CONTROL_মান_PRIVILEGED      0x02

/**
 * @brief CONTROL value for un-privileged tasks.
 *
 * Bit[0] - 1 --> Thread mode is un-privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#define securecontext_CONTROL_মান_UNPRIVILEGED    0x03

/**
 * @brief Size of stack seal values in bytes.
 */
#define securecontext_স্তূপ_SEAL_আকার               8

/**
 * @brief Stack seal value as recommended by ARM.
 */
#define securecontext_স্তূপ_SEAL_মান              0xFEF5EDA5

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
স্থির uint32_t ulGetSecureContext( শূন্য * pvTaskHandle );

/**
 * @brief Return the secure context to the secure context pool (xSecureContexts).
 *
 * @param[in] ulSecureContextIndex Index of the context in the xSecureContexts array.
 */
স্থির শূন্য vReturnSecureContext( uint32_t ul_Secure_Context_সূচক );

/* These are implemented in assembly. */
বাহ্যিক শূন্য SecureContext_LoadContextAsm( SecureContext_t * pxSecureContext );
বাহ্যিক শূন্য SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext );
/*-----------------------------------------------------------*/

স্থির uint32_t ulGetSecureContext( শূন্য * pvTaskHandle )
{
    /* Start with invalid index. */
    uint32_t i, ul_Secure_Context_সূচক = secureconfigMAX_SECURE_CONTEXTS;

    জন্য( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
    {
        যদি( ( xSecureContexts[ i ].puc_Current_স্তূপ_Pointer == ফাঁকা ) &&
            ( xSecureContexts[ i ].puc_স্তূপ_Limit == ফাঁকা ) &&
            ( xSecureContexts[ i ].puc_স্তূপ_Start == ফাঁকা ) &&
            ( xSecureContexts[ i ].pvTaskHandle == ফাঁকা ) &&
            ( ul_Secure_Context_সূচক == secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_সূচক = i;
        }
        অন্যথা যদি( xSecureContexts[ i ].pvTaskHandle == pvTaskHandle )
        {
            /* A task can only have one secure context. Do not allocate a second
             * context for the same task. */
            ul_Secure_Context_সূচক = secureconfigMAX_SECURE_CONTEXTS;
            বিরতি;
        }
    }

    ফেরত ul_Secure_Context_সূচক;
}
/*-----------------------------------------------------------*/

স্থির শূন্য vReturnSecureContext( uint32_t ul_Secure_Context_সূচক )
{
    xSecureContexts[ ul_Secure_Context_সূচক ].puc_Current_স্তূপ_Pointer = ফাঁকা;
    xSecureContexts[ ul_Secure_Context_সূচক ].puc_স্তূপ_Limit = ফাঁকা;
    xSecureContexts[ ul_Secure_Context_সূচক ].puc_স্তূপ_Start = ফাঁকা;
    xSecureContexts[ ul_Secure_Context_সূচক ].pvTaskHandle = ফাঁকা;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE শূন্য SecureContext_Init( শূন্য )
{
    uint32_t ulIPSR, i;
    স্থির uint32_t ulSecureContextsInitialized = 0;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    যদি( ( ulIPSR != 0 ) && ( ulSecureContextsInitialized == 0 ) )
    {
        /* Ensure to initialize secure contexts only once. */
        ulSecureContextsInitialized = 1;

        /* No stack for thread mode until a task's context is loaded. */
        secureportSET_PSPLIM( securecontext_NO_স্তূপ );
        secureportSET_PSP( securecontext_NO_স্তূপ );

        /* Initialize all secure contexts. */
        জন্য( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
        {
            xSecureContexts[ i ].puc_Current_স্তূপ_Pointer = ফাঁকা;
            xSecureContexts[ i ].puc_স্তূপ_Limit = ফাঁকা;
            xSecureContexts[ i ].puc_স্তূপ_Start = ফাঁকা;
            xSecureContexts[ i ].pvTaskHandle = ফাঁকা;
        }

        #যদি ( configENABLE_MPU == 1 )
        {
            /* Configure thread mode to use PSP and to be unprivileged. */
            secureportSET_CONTROL( securecontext_CONTROL_মান_UNPRIVILEGED );
        }
        #অন্যথা /* configENABLE_MPU */
        {
            /* Configure thread mode to use PSP and to be privileged. */
            secureportSET_CONTROL( securecontext_CONTROL_মান_PRIVILEGED );
        }
        #endif /* configENABLE_MPU */
    }
}
/*-----------------------------------------------------------*/

#যদি ( configENABLE_MPU == 1 )
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_স্তূপ_আকার,
                                                                                       uint32_t ulIsTaskPrivileged,
                                                                                       শূন্য * pvTaskHandle )
#অন্যথা /* configENABLE_MPU */
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_স্তূপ_আকার,
                                                                                       শূন্য * pvTaskHandle )
#endif /* configENABLE_MPU */
{
    uint8_t * puc_স্তূপ_Memory = ফাঁকা;
    uint8_t * puc_স্তূপ_Limit;
    uint32_t ulIPSR, ul_Secure_Context_সূচক;
    SecureContextHandle_t xSecureContextHandle = securecontextINVALID_CONTEXT_ID;

    #যদি ( configENABLE_MPU == 1 )
        uint32_t * pul_Current_স্তূপ_Pointer = ফাঁকা;
    #endif /* configENABLE_MPU */

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_স্তূপ_Limit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode.
     * Also do nothing, if a secure context us already loaded. PSPLIM is set to
     * securecontextNO_STACK when no secure context is loaded. */
    যদি( ( ulIPSR != 0 ) && ( puc_স্তূপ_Limit == securecontext_NO_স্তূপ ) )
    {
        /* Obtain a free secure context. */
        ul_Secure_Context_সূচক = ulGetSecureContext( pvTaskHandle );

        /* Were we able to get a free context? */
        যদি( ul_Secure_Context_সূচক < secureconfigMAX_SECURE_CONTEXTS )
        {
            /* Allocate the stack space if possible. */
            যদি( ( ul_Secure_স্তূপ_আকার < securecontext_স্তূপ_SEAL_আকার ) ||
                ( ul_Secure_স্তূপ_আকার > ( UINT32_MAX - securecontext_স্তূপ_SEAL_আকার ) ) )
            {
                /* Reject stacks that are too small (the CONTROL word would be
                 * written before the allocation, corrupting the secure heap)
                 * and sizes that would overflow when the seal size is added. */
                puc_স্তূপ_Memory = ফাঁকা;
            }
            অন্যথা
            {
                puc_স্তূপ_Memory = pvPortMalloc( ul_Secure_স্তূপ_আকার + securecontext_স্তূপ_SEAL_আকার );
            }

            যদি( puc_স্তূপ_Memory != ফাঁকা )
            {
                /* Since stack grows down, the starting point will be the last
                * location. Note that this location is next to the last
                * allocated byte for stack (excluding the space for seal values)
                * because the hardware decrements the stack pointer before
                * writing i.e. if stack pointer is 0x2, a push operation will
                * decrement the stack pointer to 0x1 and then write at 0x1. */
                xSecureContexts[ ul_Secure_Context_সূচক ].puc_স্তূপ_Start = puc_স্তূপ_Memory + ul_Secure_স্তূপ_আকার;

                /* Seal the created secure process stack. */
                *( uint32_t * ) ( puc_স্তূপ_Memory + ul_Secure_স্তূপ_আকার ) = securecontext_স্তূপ_SEAL_মান;
                *( uint32_t * ) ( puc_স্তূপ_Memory + ul_Secure_স্তূপ_আকার + 4 ) = securecontext_স্তূপ_SEAL_মান;

                /* The stack cannot go beyond this location. This value is
                 * programmed in the PSPLIM register on context switch.*/
                xSecureContexts[ ul_Secure_Context_সূচক ].puc_স্তূপ_Limit = puc_স্তূপ_Memory;

                xSecureContexts[ ul_Secure_Context_সূচক ].pvTaskHandle = pvTaskHandle;

                #যদি ( configENABLE_MPU == 1 )
                {
                    /* Store the correct CONTROL value for the task on the stack.
                     * This value is programmed in the CONTROL register on
                     * context switch. */
                    pul_Current_স্তূপ_Pointer = ( uint32_t * ) xSecureContexts[ ul_Secure_Context_সূচক ].puc_স্তূপ_Start;
                    pul_Current_স্তূপ_Pointer--;

                    যদি( ulIsTaskPrivileged )
                    {
                        *( pul_Current_স্তূপ_Pointer ) = securecontext_CONTROL_মান_PRIVILEGED;
                    }
                    অন্যথা
                    {
                        *( pul_Current_স্তূপ_Pointer ) = securecontext_CONTROL_মান_UNPRIVILEGED;
                    }

                    /* Store the current stack pointer. This value is programmed in
                     * the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_সূচক ].puc_Current_স্তূপ_Pointer = ( uint8_t * ) pul_Current_স্তূপ_Pointer;
                }
                #অন্যথা /* configENABLE_MPU */
                {
                    /* Current SP is set to the starting of the stack. This
                     * value programmed in the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_সূচক ].puc_Current_স্তূপ_Pointer = xSecureContexts[ ul_Secure_Context_সূচক ].puc_স্তূপ_Start;
                }
                #endif /* configENABLE_MPU */

                /* Ensure to never return 0 as a valid context handle. */
                xSecureContextHandle = ul_Secure_Context_সূচক + 1UL;
            }
        }
    }

    ফেরত xSecureContextHandle;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE শূন্য SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                                              শূন্য * pvTaskHandle )
{
    uint32_t ulIPSR, ul_Secure_Context_সূচক;
    uint8_t * puc_স্তূপ_Limit;

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_স্তূপ_Limit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    যদি( ulIPSR != 0 )
    {
        /* Only free if a valid context handle is passed. */
        যদি( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_সূচক = xSecureContextHandle - 1UL;

            /* Ensure that the secure context being deleted is associated with
             * the task and is NOT the currently-loaded context. Freeing a
             * context whose stack is currently loaded in PSPLIM would leave the
             * running task referencing freed secure memory (use-after-free).
             * pvTaskHandle is supplied by the non-secure side and is untrusted,
             * so it is used only as an additional ownership match, not as
             * authority. */
            যদি( ( xSecureContexts[ ul_Secure_Context_সূচক ].pvTaskHandle == pvTaskHandle ) &&
                ( xSecureContexts[ ul_Secure_Context_সূচক ].puc_স্তূপ_Limit != puc_স্তূপ_Limit ) )
            {
                /* Free the stack space. */
                vPortFree( xSecureContexts[ ul_Secure_Context_সূচক ].puc_স্তূপ_Limit );

                /* Return the secure context back to the free secure contexts pool. */
                vReturnSecureContext( ul_Secure_Context_সূচক );
            }
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE শূন্য SecureContext_LoadContext( SecureContextHandle_t xSecureContextHandle,
                                                              শূন্য * pvTaskHandle )
{
    uint8_t * puc_স্তূপ_Limit;
    uint32_t ul_Secure_Context_সূচক;

    যদি( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_সূচক = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_স্তূপ_Limit );

        /* Ensure that no secure context is loaded and the task is loading it's
         * own context. */
        যদি( ( puc_স্তূপ_Limit == securecontext_NO_স্তূপ ) &&
            ( xSecureContexts[ ul_Secure_Context_সূচক ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_LoadContextAsm( &( xSecureContexts[ ul_Secure_Context_সূচক ] ) );
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE শূন্য SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                                              শূন্য * pvTaskHandle )
{
    uint8_t * puc_স্তূপ_Limit;
    uint32_t ul_Secure_Context_সূচক;

    যদি( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_সূচক = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_স্তূপ_Limit );

        /* Ensure that task's context is loaded and the task is saving its own
         * context. */
        যদি( ( xSecureContexts[ ul_Secure_Context_সূচক ].puc_স্তূপ_Limit == puc_স্তূপ_Limit ) &&
            ( xSecureContexts[ ul_Secure_Context_সূচক ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_SaveContextAsm( &( xSecureContexts[ ul_Secure_Context_সূচক ] ) );
        }
    }
}
/*-----------------------------------------------------------*/
