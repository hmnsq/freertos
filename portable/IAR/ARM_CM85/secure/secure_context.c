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
#ਅਨ੍ਤਰ੍ਭਾਵ "secure_context.h"

/* Secure heap includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "secure_heap.h"

/* Secure port macros. */
#ਅਨ੍ਤਰ੍ਭਾਵ "secure_port_macros.h"

/**
 * @brief CONTROL value for privileged tasks.
 *
 * Bit[0] - 0 --> Thread mode is privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ securecontext_CONTROL_ਮੁੱਲ_PRIVILEGED      0x02

/**
 * @brief CONTROL value for un-privileged tasks.
 *
 * Bit[0] - 1 --> Thread mode is un-privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ securecontext_CONTROL_ਮੁੱਲ_UNPRIVILEGED    0x03

/**
 * @brief Size of stack seal values in bytes.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ securecontext_ਢੇਰ_SEAL_ਮਾਪ               8

/**
 * @brief Stack seal value as recommended by ARM.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ securecontext_ਢੇਰ_SEAL_ਮੁੱਲ              0xFEF5EDA5

/**
 * @brief Maximum number of secure contexts.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ secureconfigMAX_SECURE_CONTEXTS
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureconfigMAX_SECURE_CONTEXTS    8UL
#ਜੇ_ਅੰਤ
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
ਸਥਿਰ uint32_t ulGetSecureContext( ਖਾਲੀ * pvTaskHandle );

/**
 * @brief Return the secure context to the secure context pool (xSecureContexts).
 *
 * @param[in] ulSecureContextIndex Index of the context in the xSecureContexts array.
 */
ਸਥਿਰ ਖਾਲੀ vReturnSecureContext( uint32_t ul_Secure_Context_ਸੂਚਕਾਂਕ );

/* These are implemented in assembly. */
ਬਾਹਰੀ ਖਾਲੀ Secure_Context_ਲੱਦੋ_Context_Asm( SecureContext_t * pxSecureContext );
ਬਾਹਰੀ ਖਾਲੀ SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext );
/*-----------------------------------------------------------*/

ਸਥਿਰ uint32_t ulGetSecureContext( ਖਾਲੀ * pvTaskHandle )
{
    /* Start with invalid index. */
    uint32_t i, ul_Secure_Context_ਸੂਚਕਾਂਕ = secureconfigMAX_SECURE_CONTEXTS;

    ਲਈ( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
    {
        ਜੇ( ( xSecureContexts[ i ].puc_Current_ਢੇਰ_ਸੂਚਕ == ਨਿਰਾ ) &&
            ( xSecureContexts[ i ].puc_ਢੇਰ_ਹੱਦਬੰਦੀ == ਨਿਰਾ ) &&
            ( xSecureContexts[ i ].puc_ਢੇਰ_ਸ਼ੁਰੂ == ਨਿਰਾ ) &&
            ( xSecureContexts[ i ].pvTaskHandle == ਨਿਰਾ ) &&
            ( ul_Secure_Context_ਸੂਚਕਾਂਕ == secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_ਸੂਚਕਾਂਕ = i;
        }
        ਨਹੀਂਤਾਂ ਜੇ( xSecureContexts[ i ].pvTaskHandle == pvTaskHandle )
        {
            /* A task can only have one secure context. Do not allocate a second
             * context for the same task. */
            ul_Secure_Context_ਸੂਚਕਾਂਕ = secureconfigMAX_SECURE_CONTEXTS;
            ਰੋਕੋ;
        }
    }

    ਵਾਪਸ ul_Secure_Context_ਸੂਚਕਾਂਕ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ vReturnSecureContext( uint32_t ul_Secure_Context_ਸੂਚਕਾਂਕ )
{
    xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_Current_ਢੇਰ_ਸੂਚਕ = ਨਿਰਾ;
    xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_ਢੇਰ_ਹੱਦਬੰਦੀ = ਨਿਰਾ;
    xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_ਢੇਰ_ਸ਼ੁਰੂ = ਨਿਰਾ;
    xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].pvTaskHandle = ਨਿਰਾ;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ਖਾਲੀ SecureContext_Init( ਖਾਲੀ )
{
    uint32_t ulIPSR, i;
    ਸਥਿਰ uint32_t ulSecureContextsInitialized = 0;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    ਜੇ( ( ulIPSR != 0 ) && ( ulSecureContextsInitialized == 0 ) )
    {
        /* Ensure to initialize secure contexts only once. */
        ulSecureContextsInitialized = 1;

        /* No stack for thread mode until a task's context is loaded. */
        secureport_ਸੈੱਟ_PSPLIM( securecontext_NO_ਢੇਰ );
        secureport_ਸੈੱਟ_PSP( securecontext_NO_ਢੇਰ );

        /* Initialize all secure contexts. */
        ਲਈ( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
        {
            xSecureContexts[ i ].puc_Current_ਢੇਰ_ਸੂਚਕ = ਨਿਰਾ;
            xSecureContexts[ i ].puc_ਢੇਰ_ਹੱਦਬੰਦੀ = ਨਿਰਾ;
            xSecureContexts[ i ].puc_ਢੇਰ_ਸ਼ੁਰੂ = ਨਿਰਾ;
            xSecureContexts[ i ].pvTaskHandle = ਨਿਰਾ;
        }

        #ਜੇ ( configENABLE_MPU == 1 )
        {
            /* Configure thread mode to use PSP and to be unprivileged. */
            secureport_ਸੈੱਟ_CONTROL( securecontext_CONTROL_ਮੁੱਲ_UNPRIVILEGED );
        }
        #ਨਹੀਂਤਾਂ /* configENABLE_MPU */
        {
            /* Configure thread mode to use PSP and to be privileged. */
            secureport_ਸੈੱਟ_CONTROL( securecontext_CONTROL_ਮੁੱਲ_PRIVILEGED );
        }
        #ਜੇ_ਅੰਤ /* configENABLE_MPU */
    }
}
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ਢੇਰ_ਮਾਪ,
                                                                                       uint32_t ulIsTaskPrivileged,
                                                                                       ਖਾਲੀ * pvTaskHandle )
#ਨਹੀਂਤਾਂ /* configENABLE_MPU */
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ਢੇਰ_ਮਾਪ,
                                                                                       ਖਾਲੀ * pvTaskHandle )
#ਜੇ_ਅੰਤ /* configENABLE_MPU */
{
    uint8_t * puc_ਢੇਰ_ਸਮ੍ਰਿਤੀ = ਨਿਰਾ;
    uint8_t * puc_ਢੇਰ_ਹੱਦਬੰਦੀ;
    uint32_t ulIPSR, ul_Secure_Context_ਸੂਚਕਾਂਕ;
    SecureContextHandle_t xSecureContextHandle = securecontextINVALID_CONTEXT_ID;

    #ਜੇ ( configENABLE_MPU == 1 )
        uint32_t * pul_Current_ਢੇਰ_ਸੂਚਕ = ਨਿਰਾ;
    #ਜੇ_ਅੰਤ /* configENABLE_MPU */

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ਢੇਰ_ਹੱਦਬੰਦੀ );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode.
     * Also do nothing, if a secure context us already loaded. PSPLIM is set to
     * securecontextNO_STACK when no secure context is loaded. */
    ਜੇ( ( ulIPSR != 0 ) && ( puc_ਢੇਰ_ਹੱਦਬੰਦੀ == securecontext_NO_ਢੇਰ ) )
    {
        /* Obtain a free secure context. */
        ul_Secure_Context_ਸੂਚਕਾਂਕ = ulGetSecureContext( pvTaskHandle );

        /* Were we able to get a free context? */
        ਜੇ( ul_Secure_Context_ਸੂਚਕਾਂਕ < secureconfigMAX_SECURE_CONTEXTS )
        {
            /* Allocate the stack space if possible. */
            ਜੇ( ( ul_Secure_ਢੇਰ_ਮਾਪ < securecontext_ਢੇਰ_SEAL_ਮਾਪ ) ||
                ( ul_Secure_ਢੇਰ_ਮਾਪ > ( UINT32_MAX - securecontext_ਢੇਰ_SEAL_ਮਾਪ ) ) )
            {
                /* Reject stacks that are too small (the CONTROL word would be
                 * written before the allocation, corrupting the secure heap)
                 * and sizes that would overflow when the seal size is added. */
                puc_ਢੇਰ_ਸਮ੍ਰਿਤੀ = ਨਿਰਾ;
            }
            ਨਹੀਂਤਾਂ
            {
                puc_ਢੇਰ_ਸਮ੍ਰਿਤੀ = pv_ਪੋਰਟ_Malloc( ul_Secure_ਢੇਰ_ਮਾਪ + securecontext_ਢੇਰ_SEAL_ਮਾਪ );
            }

            ਜੇ( puc_ਢੇਰ_ਸਮ੍ਰਿਤੀ != ਨਿਰਾ )
            {
                /* Since stack grows down, the starting point will be the last
                * location. Note that this location is next to the last
                * allocated byte for stack (excluding the space for seal values)
                * because the hardware decrements the stack pointer before
                * writing i.e. if stack pointer is 0x2, a push operation will
                * decrement the stack pointer to 0x1 and then write at 0x1. */
                xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_ਢੇਰ_ਸ਼ੁਰੂ = puc_ਢੇਰ_ਸਮ੍ਰਿਤੀ + ul_Secure_ਢੇਰ_ਮਾਪ;

                /* Seal the created secure process stack. */
                *( uint32_t * ) ( puc_ਢੇਰ_ਸਮ੍ਰਿਤੀ + ul_Secure_ਢੇਰ_ਮਾਪ ) = securecontext_ਢੇਰ_SEAL_ਮੁੱਲ;
                *( uint32_t * ) ( puc_ਢੇਰ_ਸਮ੍ਰਿਤੀ + ul_Secure_ਢੇਰ_ਮਾਪ + 4 ) = securecontext_ਢੇਰ_SEAL_ਮੁੱਲ;

                /* The stack cannot go beyond this location. This value is
                 * programmed in the PSPLIM register on context switch.*/
                xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_ਢੇਰ_ਹੱਦਬੰਦੀ = puc_ਢੇਰ_ਸਮ੍ਰਿਤੀ;

                xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].pvTaskHandle = pvTaskHandle;

                #ਜੇ ( configENABLE_MPU == 1 )
                {
                    /* Store the correct CONTROL value for the task on the stack.
                     * This value is programmed in the CONTROL register on
                     * context switch. */
                    pul_Current_ਢੇਰ_ਸੂਚਕ = ( uint32_t * ) xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_ਢੇਰ_ਸ਼ੁਰੂ;
                    pul_Current_ਢੇਰ_ਸੂਚਕ--;

                    ਜੇ( ulIsTaskPrivileged )
                    {
                        *( pul_Current_ਢੇਰ_ਸੂਚਕ ) = securecontext_CONTROL_ਮੁੱਲ_PRIVILEGED;
                    }
                    ਨਹੀਂਤਾਂ
                    {
                        *( pul_Current_ਢੇਰ_ਸੂਚਕ ) = securecontext_CONTROL_ਮੁੱਲ_UNPRIVILEGED;
                    }

                    /* Store the current stack pointer. This value is programmed in
                     * the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_Current_ਢੇਰ_ਸੂਚਕ = ( uint8_t * ) pul_Current_ਢੇਰ_ਸੂਚਕ;
                }
                #ਨਹੀਂਤਾਂ /* configENABLE_MPU */
                {
                    /* Current SP is set to the starting of the stack. This
                     * value programmed in the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_Current_ਢੇਰ_ਸੂਚਕ = xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_ਢੇਰ_ਸ਼ੁਰੂ;
                }
                #ਜੇ_ਅੰਤ /* configENABLE_MPU */

                /* Ensure to never return 0 as a valid context handle. */
                xSecureContextHandle = ul_Secure_Context_ਸੂਚਕਾਂਕ + 1UL;
            }
        }
    }

    ਵਾਪਸ xSecureContextHandle;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ਖਾਲੀ SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                                              ਖਾਲੀ * pvTaskHandle )
{
    uint32_t ulIPSR, ul_Secure_Context_ਸੂਚਕਾਂਕ;
    uint8_t * puc_ਢੇਰ_ਹੱਦਬੰਦੀ;

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ਢੇਰ_ਹੱਦਬੰਦੀ );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    ਜੇ( ulIPSR != 0 )
    {
        /* Only free if a valid context handle is passed. */
        ਜੇ( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_ਸੂਚਕਾਂਕ = xSecureContextHandle - 1UL;

            /* Ensure that the secure context being deleted is associated with
             * the task and is NOT the currently-loaded context. Freeing a
             * context whose stack is currently loaded in PSPLIM would leave the
             * running task referencing freed secure memory (use-after-free).
             * pvTaskHandle is supplied by the non-secure side and is untrusted,
             * so it is used only as an additional ownership match, not as
             * authority. */
            ਜੇ( ( xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].pvTaskHandle == pvTaskHandle ) &&
                ( xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_ਢੇਰ_ਹੱਦਬੰਦੀ != puc_ਢੇਰ_ਹੱਦਬੰਦੀ ) )
            {
                /* Free the stack space. */
                v_ਪੋਰਟ_Free( xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_ਢੇਰ_ਹੱਦਬੰਦੀ );

                /* Return the secure context back to the free secure contexts pool. */
                vReturnSecureContext( ul_Secure_Context_ਸੂਚਕਾਂਕ );
            }
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ਖਾਲੀ Secure_Context_ਲੱਦੋ_Context( SecureContextHandle_t xSecureContextHandle,
                                                              ਖਾਲੀ * pvTaskHandle )
{
    uint8_t * puc_ਢੇਰ_ਹੱਦਬੰਦੀ;
    uint32_t ul_Secure_Context_ਸੂਚਕਾਂਕ;

    ਜੇ( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_ਸੂਚਕਾਂਕ = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ਢੇਰ_ਹੱਦਬੰਦੀ );

        /* Ensure that no secure context is loaded and the task is loading it's
         * own context. */
        ਜੇ( ( puc_ਢੇਰ_ਹੱਦਬੰਦੀ == securecontext_NO_ਢੇਰ ) &&
            ( xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].pvTaskHandle == pvTaskHandle ) )
        {
            Secure_Context_ਲੱਦੋ_Context_Asm( &( xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ] ) );
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ਖਾਲੀ SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                                              ਖਾਲੀ * pvTaskHandle )
{
    uint8_t * puc_ਢੇਰ_ਹੱਦਬੰਦੀ;
    uint32_t ul_Secure_Context_ਸੂਚਕਾਂਕ;

    ਜੇ( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_ਸੂਚਕਾਂਕ = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ਢੇਰ_ਹੱਦਬੰਦੀ );

        /* Ensure that task's context is loaded and the task is saving its own
         * context. */
        ਜੇ( ( xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].puc_ਢੇਰ_ਹੱਦਬੰਦੀ == puc_ਢੇਰ_ਹੱਦਬੰਦੀ ) &&
            ( xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_SaveContextAsm( &( xSecureContexts[ ul_Secure_Context_ਸੂਚਕਾਂਕ ] ) );
        }
    }
}
/*-----------------------------------------------------------*/
