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
#تعریف_کړه securecontext_CONTROL_ارزښت_PRIVILEGED      0x02

/**
 * @brief CONTROL value for un-privileged tasks.
 *
 * Bit[0] - 1 --> Thread mode is un-privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#تعریف_کړه securecontext_CONTROL_ارزښت_UNPRIVILEGED    0x03

/**
 * @brief Size of stack seal values in bytes.
 */
#تعریف_کړه securecontext_ډېری_SEAL_اندازه               8

/**
 * @brief Stack seal value as recommended by ARM.
 */
#تعریف_کړه securecontext_ډېری_SEAL_ارزښت              0xFEF5EDA5

/**
 * @brief Maximum number of secure contexts.
 */
#که_نه_تعریف_شوی secureconfigMAX_SECURE_CONTEXTS
    #تعریف_کړه secureconfigMAX_SECURE_CONTEXTS    8UL
#د_که_پای
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
ساكن فراغ vReturnSecureContext( uint32_t ul_Secure_Context_شاخص );

/* These are implemented in assembly. */
خارجي فراغ Secure_Context_بارول_Context_Asm( SecureContext_t * pxSecureContext );
خارجي فراغ SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext );
/*-----------------------------------------------------------*/

ساكن uint32_t ulGetSecureContext( فراغ * pvTaskHandle )
{
    /* Start with invalid index. */
    uint32_t i, ul_Secure_Context_شاخص = secureconfigMAX_SECURE_CONTEXTS;

    لكل( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
    {
        إذا( ( xSecureContexts[ i ].puc_Current_ډېری_اشاره_ګر == عدم ) &&
            ( xSecureContexts[ i ].puc_ډېری_حد == عدم ) &&
            ( xSecureContexts[ i ].puc_ډېری_پیل == عدم ) &&
            ( xSecureContexts[ i ].pvTaskHandle == عدم ) &&
            ( ul_Secure_Context_شاخص == secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_شاخص = i;
        }
        وإلا إذا( xSecureContexts[ i ].pvTaskHandle == pvTaskHandle )
        {
            /* A task can only have one secure context. Do not allocate a second
             * context for the same task. */
            ul_Secure_Context_شاخص = secureconfigMAX_SECURE_CONTEXTS;
            اكسر;
        }
    }

    أرجع ul_Secure_Context_شاخص;
}
/*-----------------------------------------------------------*/

ساكن فراغ vReturnSecureContext( uint32_t ul_Secure_Context_شاخص )
{
    xSecureContexts[ ul_Secure_Context_شاخص ].puc_Current_ډېری_اشاره_ګر = عدم;
    xSecureContexts[ ul_Secure_Context_شاخص ].puc_ډېری_حد = عدم;
    xSecureContexts[ ul_Secure_Context_شاخص ].puc_ډېری_پیل = عدم;
    xSecureContexts[ ul_Secure_Context_شاخص ].pvTaskHandle = عدم;
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
    إذا( ( ulIPSR != 0 ) && ( ulSecureContextsInitialized == 0 ) )
    {
        /* Ensure to initialize secure contexts only once. */
        ulSecureContextsInitialized = 1;

        /* No stack for thread mode until a task's context is loaded. */
        secureport_سېټ_PSPLIM( securecontext_NO_ډېری );
        secureport_سېټ_PSP( securecontext_NO_ډېری );

        /* Initialize all secure contexts. */
        لكل( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
        {
            xSecureContexts[ i ].puc_Current_ډېری_اشاره_ګر = عدم;
            xSecureContexts[ i ].puc_ډېری_حد = عدم;
            xSecureContexts[ i ].puc_ډېری_پیل = عدم;
            xSecureContexts[ i ].pvTaskHandle = عدم;
        }

        #إذا ( configENABLE_MPU == 1 )
        {
            /* Configure thread mode to use PSP and to be unprivileged. */
            secureport_سېټ_CONTROL( securecontext_CONTROL_ارزښت_UNPRIVILEGED );
        }
        #وإلا /* configENABLE_MPU */
        {
            /* Configure thread mode to use PSP and to be privileged. */
            secureport_سېټ_CONTROL( securecontext_CONTROL_ارزښت_PRIVILEGED );
        }
        #د_که_پای /* configENABLE_MPU */
    }
}
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ډېری_اندازه,
                                                                                       uint32_t ulIsTaskPrivileged,
                                                                                       فراغ * pvTaskHandle )
#وإلا /* configENABLE_MPU */
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ډېری_اندازه,
                                                                                       فراغ * pvTaskHandle )
#د_که_پای /* configENABLE_MPU */
{
    uint8_t * puc_ډېری_حافظه = عدم;
    uint8_t * puc_ډېری_حد;
    uint32_t ulIPSR, ul_Secure_Context_شاخص;
    SecureContextHandle_t xSecureContextHandle = securecontextINVALID_CONTEXT_ID;

    #إذا ( configENABLE_MPU == 1 )
        uint32_t * pul_Current_ډېری_اشاره_ګر = عدم;
    #د_که_پای /* configENABLE_MPU */

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ډېری_حد );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode.
     * Also do nothing, if a secure context us already loaded. PSPLIM is set to
     * securecontextNO_STACK when no secure context is loaded. */
    إذا( ( ulIPSR != 0 ) && ( puc_ډېری_حد == securecontext_NO_ډېری ) )
    {
        /* Obtain a free secure context. */
        ul_Secure_Context_شاخص = ulGetSecureContext( pvTaskHandle );

        /* Were we able to get a free context? */
        إذا( ul_Secure_Context_شاخص < secureconfigMAX_SECURE_CONTEXTS )
        {
            /* Allocate the stack space if possible. */
            إذا( ( ul_Secure_ډېری_اندازه < securecontext_ډېری_SEAL_اندازه ) ||
                ( ul_Secure_ډېری_اندازه > ( UINT32_MAX - securecontext_ډېری_SEAL_اندازه ) ) )
            {
                /* Reject stacks that are too small (the CONTROL word would be
                 * written before the allocation, corrupting the secure heap)
                 * and sizes that would overflow when the seal size is added. */
                puc_ډېری_حافظه = عدم;
            }
            وإلا
            {
                puc_ډېری_حافظه = pv_پورټ_Malloc( ul_Secure_ډېری_اندازه + securecontext_ډېری_SEAL_اندازه );
            }

            إذا( puc_ډېری_حافظه != عدم )
            {
                /* Since stack grows down, the starting point will be the last
                * location. Note that this location is next to the last
                * allocated byte for stack (excluding the space for seal values)
                * because the hardware decrements the stack pointer before
                * writing i.e. if stack pointer is 0x2, a push operation will
                * decrement the stack pointer to 0x1 and then write at 0x1. */
                xSecureContexts[ ul_Secure_Context_شاخص ].puc_ډېری_پیل = puc_ډېری_حافظه + ul_Secure_ډېری_اندازه;

                /* Seal the created secure process stack. */
                *( uint32_t * ) ( puc_ډېری_حافظه + ul_Secure_ډېری_اندازه ) = securecontext_ډېری_SEAL_ارزښت;
                *( uint32_t * ) ( puc_ډېری_حافظه + ul_Secure_ډېری_اندازه + 4 ) = securecontext_ډېری_SEAL_ارزښت;

                /* The stack cannot go beyond this location. This value is
                 * programmed in the PSPLIM register on context switch.*/
                xSecureContexts[ ul_Secure_Context_شاخص ].puc_ډېری_حد = puc_ډېری_حافظه;

                xSecureContexts[ ul_Secure_Context_شاخص ].pvTaskHandle = pvTaskHandle;

                #إذا ( configENABLE_MPU == 1 )
                {
                    /* Store the correct CONTROL value for the task on the stack.
                     * This value is programmed in the CONTROL register on
                     * context switch. */
                    pul_Current_ډېری_اشاره_ګر = ( uint32_t * ) xSecureContexts[ ul_Secure_Context_شاخص ].puc_ډېری_پیل;
                    pul_Current_ډېری_اشاره_ګر--;

                    إذا( ulIsTaskPrivileged )
                    {
                        *( pul_Current_ډېری_اشاره_ګر ) = securecontext_CONTROL_ارزښت_PRIVILEGED;
                    }
                    وإلا
                    {
                        *( pul_Current_ډېری_اشاره_ګر ) = securecontext_CONTROL_ارزښت_UNPRIVILEGED;
                    }

                    /* Store the current stack pointer. This value is programmed in
                     * the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_شاخص ].puc_Current_ډېری_اشاره_ګر = ( uint8_t * ) pul_Current_ډېری_اشاره_ګر;
                }
                #وإلا /* configENABLE_MPU */
                {
                    /* Current SP is set to the starting of the stack. This
                     * value programmed in the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_شاخص ].puc_Current_ډېری_اشاره_ګر = xSecureContexts[ ul_Secure_Context_شاخص ].puc_ډېری_پیل;
                }
                #د_که_پای /* configENABLE_MPU */

                /* Ensure to never return 0 as a valid context handle. */
                xSecureContextHandle = ul_Secure_Context_شاخص + 1UL;
            }
        }
    }

    أرجع xSecureContextHandle;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE فراغ SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                                              فراغ * pvTaskHandle )
{
    uint32_t ulIPSR, ul_Secure_Context_شاخص;
    uint8_t * puc_ډېری_حد;

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ډېری_حد );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    إذا( ulIPSR != 0 )
    {
        /* Only free if a valid context handle is passed. */
        إذا( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_شاخص = xSecureContextHandle - 1UL;

            /* Ensure that the secure context being deleted is associated with
             * the task and is NOT the currently-loaded context. Freeing a
             * context whose stack is currently loaded in PSPLIM would leave the
             * running task referencing freed secure memory (use-after-free).
             * pvTaskHandle is supplied by the non-secure side and is untrusted,
             * so it is used only as an additional ownership match, not as
             * authority. */
            إذا( ( xSecureContexts[ ul_Secure_Context_شاخص ].pvTaskHandle == pvTaskHandle ) &&
                ( xSecureContexts[ ul_Secure_Context_شاخص ].puc_ډېری_حد != puc_ډېری_حد ) )
            {
                /* Free the stack space. */
                v_پورټ_Free( xSecureContexts[ ul_Secure_Context_شاخص ].puc_ډېری_حد );

                /* Return the secure context back to the free secure contexts pool. */
                vReturnSecureContext( ul_Secure_Context_شاخص );
            }
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE فراغ Secure_Context_بارول_Context( SecureContextHandle_t xSecureContextHandle,
                                                              فراغ * pvTaskHandle )
{
    uint8_t * puc_ډېری_حد;
    uint32_t ul_Secure_Context_شاخص;

    إذا( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_شاخص = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ډېری_حد );

        /* Ensure that no secure context is loaded and the task is loading it's
         * own context. */
        إذا( ( puc_ډېری_حد == securecontext_NO_ډېری ) &&
            ( xSecureContexts[ ul_Secure_Context_شاخص ].pvTaskHandle == pvTaskHandle ) )
        {
            Secure_Context_بارول_Context_Asm( &( xSecureContexts[ ul_Secure_Context_شاخص ] ) );
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE فراغ SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                                              فراغ * pvTaskHandle )
{
    uint8_t * puc_ډېری_حد;
    uint32_t ul_Secure_Context_شاخص;

    إذا( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_شاخص = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ډېری_حد );

        /* Ensure that task's context is loaded and the task is saving its own
         * context. */
        إذا( ( xSecureContexts[ ul_Secure_Context_شاخص ].puc_ډېری_حد == puc_ډېری_حد ) &&
            ( xSecureContexts[ ul_Secure_Context_شاخص ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_SaveContextAsm( &( xSecureContexts[ ul_Secure_Context_شاخص ] ) );
        }
    }
}
/*-----------------------------------------------------------*/
