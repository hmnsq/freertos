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
#समावेश "secure_context.h"

/* Secure heap includes. */
#समावेश "secure_heap.h"

/* Secure port macros. */
#समावेश "secure_port_macros.h"

/**
 * @brief CONTROL value for privileged tasks.
 *
 * Bit[0] - 0 --> Thread mode is privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#घोषणा securecontext_CONTROL_मूल्य_PRIVILEGED      0x02

/**
 * @brief CONTROL value for un-privileged tasks.
 *
 * Bit[0] - 1 --> Thread mode is un-privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#घोषणा securecontext_CONTROL_मूल्य_UNPRIVILEGED    0x03

/**
 * @brief Size of stack seal values in bytes.
 */
#घोषणा securecontext_ढेर_SEAL_आकार               8

/**
 * @brief Stack seal value as recommended by ARM.
 */
#घोषणा securecontext_ढेर_SEAL_मूल्य              0xFEF5EDA5

/**
 * @brief Maximum number of secure contexts.
 */
#अगर_अघोषित secureconfigMAX_SECURE_CONTEXTS
    #घोषणा secureconfigMAX_SECURE_CONTEXTS    8UL
#पूर्ण_अगर
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
अटल uint32_t ulGetSecureContext( व्योम * pvTaskHandle );

/**
 * @brief Return the secure context to the secure context pool (xSecureContexts).
 *
 * @param[in] ulSecureContextIndex Index of the context in the xSecureContexts array.
 */
अटल व्योम vReturnSecureContext( uint32_t ul_Secure_Context_सूचकांक );

/* These are implemented in assembly. */
बाह्य व्योम SecureContext_LoadContextAsm( SecureContext_t * pxSecureContext );
बाह्य व्योम SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext );
/*-----------------------------------------------------------*/

अटल uint32_t ulGetSecureContext( व्योम * pvTaskHandle )
{
    /* Start with invalid index. */
    uint32_t i, ul_Secure_Context_सूचकांक = secureconfigMAX_SECURE_CONTEXTS;

    क्रम( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
    {
        अगर( ( xSecureContexts[ i ].puc_Current_ढेर_Pointer == शून्य ) &&
            ( xSecureContexts[ i ].puc_ढेर_Limit == शून्य ) &&
            ( xSecureContexts[ i ].puc_ढेर_Start == शून्य ) &&
            ( xSecureContexts[ i ].pvTaskHandle == शून्य ) &&
            ( ul_Secure_Context_सूचकांक == secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_सूचकांक = i;
        }
        अन्यथा अगर( xSecureContexts[ i ].pvTaskHandle == pvTaskHandle )
        {
            /* A task can only have one secure context. Do not allocate a second
             * context for the same task. */
            ul_Secure_Context_सूचकांक = secureconfigMAX_SECURE_CONTEXTS;
            अवरोध;
        }
    }

    वापस ul_Secure_Context_सूचकांक;
}
/*-----------------------------------------------------------*/

अटल व्योम vReturnSecureContext( uint32_t ul_Secure_Context_सूचकांक )
{
    xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_Current_ढेर_Pointer = शून्य;
    xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_ढेर_Limit = शून्य;
    xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_ढेर_Start = शून्य;
    xSecureContexts[ ul_Secure_Context_सूचकांक ].pvTaskHandle = शून्य;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE व्योम SecureContext_Init( व्योम )
{
    uint32_t ulIPSR, i;
    अटल uint32_t ulSecureContextsInitialized = 0;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    अगर( ( ulIPSR != 0 ) && ( ulSecureContextsInitialized == 0 ) )
    {
        /* Ensure to initialize secure contexts only once. */
        ulSecureContextsInitialized = 1;

        /* No stack for thread mode until a task's context is loaded. */
        secureportSET_PSPLIM( securecontext_NO_ढेर );
        secureportSET_PSP( securecontext_NO_ढेर );

        /* Initialize all secure contexts. */
        क्रम( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
        {
            xSecureContexts[ i ].puc_Current_ढेर_Pointer = शून्य;
            xSecureContexts[ i ].puc_ढेर_Limit = शून्य;
            xSecureContexts[ i ].puc_ढेर_Start = शून्य;
            xSecureContexts[ i ].pvTaskHandle = शून्य;
        }

        #अगर ( configENABLE_MPU == 1 )
        {
            /* Configure thread mode to use PSP and to be unprivileged. */
            secureportSET_CONTROL( securecontext_CONTROL_मूल्य_UNPRIVILEGED );
        }
        #अन्यथा /* configENABLE_MPU */
        {
            /* Configure thread mode to use PSP and to be privileged. */
            secureportSET_CONTROL( securecontext_CONTROL_मूल्य_PRIVILEGED );
        }
        #पूर्ण_अगर /* configENABLE_MPU */
    }
}
/*-----------------------------------------------------------*/

#अगर ( configENABLE_MPU == 1 )
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ढेर_आकार,
                                                                                       uint32_t ulIsTaskPrivileged,
                                                                                       व्योम * pvTaskHandle )
#अन्यथा /* configENABLE_MPU */
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ढेर_आकार,
                                                                                       व्योम * pvTaskHandle )
#पूर्ण_अगर /* configENABLE_MPU */
{
    uint8_t * puc_ढेर_Memory = शून्य;
    uint8_t * puc_ढेर_Limit;
    uint32_t ulIPSR, ul_Secure_Context_सूचकांक;
    SecureContextHandle_t xSecureContextHandle = securecontextINVALID_CONTEXT_ID;

    #अगर ( configENABLE_MPU == 1 )
        uint32_t * pul_Current_ढेर_Pointer = शून्य;
    #पूर्ण_अगर /* configENABLE_MPU */

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ढेर_Limit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode.
     * Also do nothing, if a secure context us already loaded. PSPLIM is set to
     * securecontextNO_STACK when no secure context is loaded. */
    अगर( ( ulIPSR != 0 ) && ( puc_ढेर_Limit == securecontext_NO_ढेर ) )
    {
        /* Obtain a free secure context. */
        ul_Secure_Context_सूचकांक = ulGetSecureContext( pvTaskHandle );

        /* Were we able to get a free context? */
        अगर( ul_Secure_Context_सूचकांक < secureconfigMAX_SECURE_CONTEXTS )
        {
            /* Allocate the stack space if possible. */
            अगर( ( ul_Secure_ढेर_आकार < securecontext_ढेर_SEAL_आकार ) ||
                ( ul_Secure_ढेर_आकार > ( UINT32_MAX - securecontext_ढेर_SEAL_आकार ) ) )
            {
                /* Reject stacks that are too small (the CONTROL word would be
                 * written before the allocation, corrupting the secure heap)
                 * and sizes that would overflow when the seal size is added. */
                puc_ढेर_Memory = शून्य;
            }
            अन्यथा
            {
                puc_ढेर_Memory = pvPortMalloc( ul_Secure_ढेर_आकार + securecontext_ढेर_SEAL_आकार );
            }

            अगर( puc_ढेर_Memory != शून्य )
            {
                /* Since stack grows down, the starting point will be the last
                * location. Note that this location is next to the last
                * allocated byte for stack (excluding the space for seal values)
                * because the hardware decrements the stack pointer before
                * writing i.e. if stack pointer is 0x2, a push operation will
                * decrement the stack pointer to 0x1 and then write at 0x1. */
                xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_ढेर_Start = puc_ढेर_Memory + ul_Secure_ढेर_आकार;

                /* Seal the created secure process stack. */
                *( uint32_t * ) ( puc_ढेर_Memory + ul_Secure_ढेर_आकार ) = securecontext_ढेर_SEAL_मूल्य;
                *( uint32_t * ) ( puc_ढेर_Memory + ul_Secure_ढेर_आकार + 4 ) = securecontext_ढेर_SEAL_मूल्य;

                /* The stack cannot go beyond this location. This value is
                 * programmed in the PSPLIM register on context switch.*/
                xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_ढेर_Limit = puc_ढेर_Memory;

                xSecureContexts[ ul_Secure_Context_सूचकांक ].pvTaskHandle = pvTaskHandle;

                #अगर ( configENABLE_MPU == 1 )
                {
                    /* Store the correct CONTROL value for the task on the stack.
                     * This value is programmed in the CONTROL register on
                     * context switch. */
                    pul_Current_ढेर_Pointer = ( uint32_t * ) xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_ढेर_Start;
                    pul_Current_ढेर_Pointer--;

                    अगर( ulIsTaskPrivileged )
                    {
                        *( pul_Current_ढेर_Pointer ) = securecontext_CONTROL_मूल्य_PRIVILEGED;
                    }
                    अन्यथा
                    {
                        *( pul_Current_ढेर_Pointer ) = securecontext_CONTROL_मूल्य_UNPRIVILEGED;
                    }

                    /* Store the current stack pointer. This value is programmed in
                     * the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_Current_ढेर_Pointer = ( uint8_t * ) pul_Current_ढेर_Pointer;
                }
                #अन्यथा /* configENABLE_MPU */
                {
                    /* Current SP is set to the starting of the stack. This
                     * value programmed in the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_Current_ढेर_Pointer = xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_ढेर_Start;
                }
                #पूर्ण_अगर /* configENABLE_MPU */

                /* Ensure to never return 0 as a valid context handle. */
                xSecureContextHandle = ul_Secure_Context_सूचकांक + 1UL;
            }
        }
    }

    वापस xSecureContextHandle;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE व्योम SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                                              व्योम * pvTaskHandle )
{
    uint32_t ulIPSR, ul_Secure_Context_सूचकांक;
    uint8_t * puc_ढेर_Limit;

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ढेर_Limit );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    अगर( ulIPSR != 0 )
    {
        /* Only free if a valid context handle is passed. */
        अगर( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_सूचकांक = xSecureContextHandle - 1UL;

            /* Ensure that the secure context being deleted is associated with
             * the task and is NOT the currently-loaded context. Freeing a
             * context whose stack is currently loaded in PSPLIM would leave the
             * running task referencing freed secure memory (use-after-free).
             * pvTaskHandle is supplied by the non-secure side and is untrusted,
             * so it is used only as an additional ownership match, not as
             * authority. */
            अगर( ( xSecureContexts[ ul_Secure_Context_सूचकांक ].pvTaskHandle == pvTaskHandle ) &&
                ( xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_ढेर_Limit != puc_ढेर_Limit ) )
            {
                /* Free the stack space. */
                vPortFree( xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_ढेर_Limit );

                /* Return the secure context back to the free secure contexts pool. */
                vReturnSecureContext( ul_Secure_Context_सूचकांक );
            }
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE व्योम SecureContext_LoadContext( SecureContextHandle_t xSecureContextHandle,
                                                              व्योम * pvTaskHandle )
{
    uint8_t * puc_ढेर_Limit;
    uint32_t ul_Secure_Context_सूचकांक;

    अगर( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_सूचकांक = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ढेर_Limit );

        /* Ensure that no secure context is loaded and the task is loading it's
         * own context. */
        अगर( ( puc_ढेर_Limit == securecontext_NO_ढेर ) &&
            ( xSecureContexts[ ul_Secure_Context_सूचकांक ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_LoadContextAsm( &( xSecureContexts[ ul_Secure_Context_सूचकांक ] ) );
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE व्योम SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                                              व्योम * pvTaskHandle )
{
    uint8_t * puc_ढेर_Limit;
    uint32_t ul_Secure_Context_सूचकांक;

    अगर( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_सूचकांक = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ढेर_Limit );

        /* Ensure that task's context is loaded and the task is saving its own
         * context. */
        अगर( ( xSecureContexts[ ul_Secure_Context_सूचकांक ].puc_ढेर_Limit == puc_ढेर_Limit ) &&
            ( xSecureContexts[ ul_Secure_Context_सूचकांक ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_SaveContextAsm( &( xSecureContexts[ ul_Secure_Context_सूचकांक ] ) );
        }
    }
}
/*-----------------------------------------------------------*/
