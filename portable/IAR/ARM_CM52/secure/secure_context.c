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
#تعریف_کرو securecontext_CONTROL_قدر_PRIVILEGED      0x02

/**
 * @brief CONTROL value for un-privileged tasks.
 *
 * Bit[0] - 1 --> Thread mode is un-privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#تعریف_کرو securecontext_CONTROL_قدر_UNPRIVILEGED    0x03

/**
 * @brief Size of stack seal values in bytes.
 */
#تعریف_کرو securecontext_ڈھیر_SEAL_سائز               8

/**
 * @brief Stack seal value as recommended by ARM.
 */
#تعریف_کرو securecontext_ڈھیر_SEAL_قدر              0xFEF5EDA5

/**
 * @brief Maximum number of secure contexts.
 */
#اگر_غیر_تعریف_شدہ secureconfigMAX_SECURE_CONTEXTS
    #تعریف_کرو secureconfigMAX_SECURE_CONTEXTS    8UL
#اگر_ختم
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
ساکن uint32_t ulGetSecureContext( خالی * pvTaskHandle );

/**
 * @brief Return the secure context to the secure context pool (xSecureContexts).
 *
 * @param[in] ulSecureContextIndex Index of the context in the xSecureContexts array.
 */
ساکن خالی vReturnSecureContext( uint32_t ul_Secure_Context_اشاریہ );

/* These are implemented in assembly. */
خارجی خالی Secure_Context_بھرو_Context_Asm( SecureContext_t * pxSecureContext );
خارجی خالی SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext );
/*-----------------------------------------------------------*/

ساکن uint32_t ulGetSecureContext( خالی * pvTaskHandle )
{
    /* Start with invalid index. */
    uint32_t i, ul_Secure_Context_اشاریہ = secureconfigMAX_SECURE_CONTEXTS;

    برائے( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
    {
        اگر( ( xSecureContexts[ i ].puc_Current_ڈھیر_اشارہ_گر == تہی ) &&
            ( xSecureContexts[ i ].puc_ڈھیر_حد_بندی == تہی ) &&
            ( xSecureContexts[ i ].puc_ڈھیر_آغاز == تہی ) &&
            ( xSecureContexts[ i ].pvTaskHandle == تہی ) &&
            ( ul_Secure_Context_اشاریہ == secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_اشاریہ = i;
        }
        ورنہ اگر( xSecureContexts[ i ].pvTaskHandle == pvTaskHandle )
        {
            /* A task can only have one secure context. Do not allocate a second
             * context for the same task. */
            ul_Secure_Context_اشاریہ = secureconfigMAX_SECURE_CONTEXTS;
            توڑو;
        }
    }

    واپس ul_Secure_Context_اشاریہ;
}
/*-----------------------------------------------------------*/

ساکن خالی vReturnSecureContext( uint32_t ul_Secure_Context_اشاریہ )
{
    xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_Current_ڈھیر_اشارہ_گر = تہی;
    xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_ڈھیر_حد_بندی = تہی;
    xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_ڈھیر_آغاز = تہی;
    xSecureContexts[ ul_Secure_Context_اشاریہ ].pvTaskHandle = تہی;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE خالی SecureContext_Init( خالی )
{
    uint32_t ulIPSR, i;
    ساکن uint32_t ulSecureContextsInitialized = 0;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    اگر( ( ulIPSR != 0 ) && ( ulSecureContextsInitialized == 0 ) )
    {
        /* Ensure to initialize secure contexts only once. */
        ulSecureContextsInitialized = 1;

        /* No stack for thread mode until a task's context is loaded. */
        secureport_سیٹ_PSPLIM( securecontext_NO_ڈھیر );
        secureport_سیٹ_PSP( securecontext_NO_ڈھیر );

        /* Initialize all secure contexts. */
        برائے( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
        {
            xSecureContexts[ i ].puc_Current_ڈھیر_اشارہ_گر = تہی;
            xSecureContexts[ i ].puc_ڈھیر_حد_بندی = تہی;
            xSecureContexts[ i ].puc_ڈھیر_آغاز = تہی;
            xSecureContexts[ i ].pvTaskHandle = تہی;
        }

        #اگر ( configENABLE_MPU == 1 )
        {
            /* Configure thread mode to use PSP and to be unprivileged. */
            secureport_سیٹ_CONTROL( securecontext_CONTROL_قدر_UNPRIVILEGED );
        }
        #ورنہ /* configENABLE_MPU */
        {
            /* Configure thread mode to use PSP and to be privileged. */
            secureport_سیٹ_CONTROL( securecontext_CONTROL_قدر_PRIVILEGED );
        }
        #اگر_ختم /* configENABLE_MPU */
    }
}
/*-----------------------------------------------------------*/

#اگر ( configENABLE_MPU == 1 )
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ڈھیر_سائز,
                                                                                       uint32_t ulIsTaskPrivileged,
                                                                                       خالی * pvTaskHandle )
#ورنہ /* configENABLE_MPU */
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ڈھیر_سائز,
                                                                                       خالی * pvTaskHandle )
#اگر_ختم /* configENABLE_MPU */
{
    uint8_t * puc_ڈھیر_حافظہ = تہی;
    uint8_t * puc_ڈھیر_حد_بندی;
    uint32_t ulIPSR, ul_Secure_Context_اشاریہ;
    SecureContextHandle_t xSecureContextHandle = securecontextINVALID_CONTEXT_ID;

    #اگر ( configENABLE_MPU == 1 )
        uint32_t * pul_Current_ڈھیر_اشارہ_گر = تہی;
    #اگر_ختم /* configENABLE_MPU */

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ڈھیر_حد_بندی );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode.
     * Also do nothing, if a secure context us already loaded. PSPLIM is set to
     * securecontextNO_STACK when no secure context is loaded. */
    اگر( ( ulIPSR != 0 ) && ( puc_ڈھیر_حد_بندی == securecontext_NO_ڈھیر ) )
    {
        /* Obtain a free secure context. */
        ul_Secure_Context_اشاریہ = ulGetSecureContext( pvTaskHandle );

        /* Were we able to get a free context? */
        اگر( ul_Secure_Context_اشاریہ < secureconfigMAX_SECURE_CONTEXTS )
        {
            /* Allocate the stack space if possible. */
            اگر( ( ul_Secure_ڈھیر_سائز < securecontext_ڈھیر_SEAL_سائز ) ||
                ( ul_Secure_ڈھیر_سائز > ( UINT32_MAX - securecontext_ڈھیر_SEAL_سائز ) ) )
            {
                /* Reject stacks that are too small (the CONTROL word would be
                 * written before the allocation, corrupting the secure heap)
                 * and sizes that would overflow when the seal size is added. */
                puc_ڈھیر_حافظہ = تہی;
            }
            ورنہ
            {
                puc_ڈھیر_حافظہ = pv_پورٹ_Malloc( ul_Secure_ڈھیر_سائز + securecontext_ڈھیر_SEAL_سائز );
            }

            اگر( puc_ڈھیر_حافظہ != تہی )
            {
                /* Since stack grows down, the starting point will be the last
                * location. Note that this location is next to the last
                * allocated byte for stack (excluding the space for seal values)
                * because the hardware decrements the stack pointer before
                * writing i.e. if stack pointer is 0x2, a push operation will
                * decrement the stack pointer to 0x1 and then write at 0x1. */
                xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_ڈھیر_آغاز = puc_ڈھیر_حافظہ + ul_Secure_ڈھیر_سائز;

                /* Seal the created secure process stack. */
                *( uint32_t * ) ( puc_ڈھیر_حافظہ + ul_Secure_ڈھیر_سائز ) = securecontext_ڈھیر_SEAL_قدر;
                *( uint32_t * ) ( puc_ڈھیر_حافظہ + ul_Secure_ڈھیر_سائز + 4 ) = securecontext_ڈھیر_SEAL_قدر;

                /* The stack cannot go beyond this location. This value is
                 * programmed in the PSPLIM register on context switch.*/
                xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_ڈھیر_حد_بندی = puc_ڈھیر_حافظہ;

                xSecureContexts[ ul_Secure_Context_اشاریہ ].pvTaskHandle = pvTaskHandle;

                #اگر ( configENABLE_MPU == 1 )
                {
                    /* Store the correct CONTROL value for the task on the stack.
                     * This value is programmed in the CONTROL register on
                     * context switch. */
                    pul_Current_ڈھیر_اشارہ_گر = ( uint32_t * ) xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_ڈھیر_آغاز;
                    pul_Current_ڈھیر_اشارہ_گر--;

                    اگر( ulIsTaskPrivileged )
                    {
                        *( pul_Current_ڈھیر_اشارہ_گر ) = securecontext_CONTROL_قدر_PRIVILEGED;
                    }
                    ورنہ
                    {
                        *( pul_Current_ڈھیر_اشارہ_گر ) = securecontext_CONTROL_قدر_UNPRIVILEGED;
                    }

                    /* Store the current stack pointer. This value is programmed in
                     * the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_Current_ڈھیر_اشارہ_گر = ( uint8_t * ) pul_Current_ڈھیر_اشارہ_گر;
                }
                #ورنہ /* configENABLE_MPU */
                {
                    /* Current SP is set to the starting of the stack. This
                     * value programmed in the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_Current_ڈھیر_اشارہ_گر = xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_ڈھیر_آغاز;
                }
                #اگر_ختم /* configENABLE_MPU */

                /* Ensure to never return 0 as a valid context handle. */
                xSecureContextHandle = ul_Secure_Context_اشاریہ + 1UL;
            }
        }
    }

    واپس xSecureContextHandle;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE خالی SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                                              خالی * pvTaskHandle )
{
    uint32_t ulIPSR, ul_Secure_Context_اشاریہ;
    uint8_t * puc_ڈھیر_حد_بندی;

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_ڈھیر_حد_بندی );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    اگر( ulIPSR != 0 )
    {
        /* Only free if a valid context handle is passed. */
        اگر( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_اشاریہ = xSecureContextHandle - 1UL;

            /* Ensure that the secure context being deleted is associated with
             * the task and is NOT the currently-loaded context. Freeing a
             * context whose stack is currently loaded in PSPLIM would leave the
             * running task referencing freed secure memory (use-after-free).
             * pvTaskHandle is supplied by the non-secure side and is untrusted,
             * so it is used only as an additional ownership match, not as
             * authority. */
            اگر( ( xSecureContexts[ ul_Secure_Context_اشاریہ ].pvTaskHandle == pvTaskHandle ) &&
                ( xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_ڈھیر_حد_بندی != puc_ڈھیر_حد_بندی ) )
            {
                /* Free the stack space. */
                v_پورٹ_Free( xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_ڈھیر_حد_بندی );

                /* Return the secure context back to the free secure contexts pool. */
                vReturnSecureContext( ul_Secure_Context_اشاریہ );
            }
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE خالی Secure_Context_بھرو_Context( SecureContextHandle_t xSecureContextHandle,
                                                              خالی * pvTaskHandle )
{
    uint8_t * puc_ڈھیر_حد_بندی;
    uint32_t ul_Secure_Context_اشاریہ;

    اگر( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_اشاریہ = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ڈھیر_حد_بندی );

        /* Ensure that no secure context is loaded and the task is loading it's
         * own context. */
        اگر( ( puc_ڈھیر_حد_بندی == securecontext_NO_ڈھیر ) &&
            ( xSecureContexts[ ul_Secure_Context_اشاریہ ].pvTaskHandle == pvTaskHandle ) )
        {
            Secure_Context_بھرو_Context_Asm( &( xSecureContexts[ ul_Secure_Context_اشاریہ ] ) );
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE خالی SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                                              خالی * pvTaskHandle )
{
    uint8_t * puc_ڈھیر_حد_بندی;
    uint32_t ul_Secure_Context_اشاریہ;

    اگر( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_اشاریہ = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_ڈھیر_حد_بندی );

        /* Ensure that task's context is loaded and the task is saving its own
         * context. */
        اگر( ( xSecureContexts[ ul_Secure_Context_اشاریہ ].puc_ڈھیر_حد_بندی == puc_ڈھیر_حد_بندی ) &&
            ( xSecureContexts[ ul_Secure_Context_اشاریہ ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_SaveContextAsm( &( xSecureContexts[ ul_Secure_Context_اشاریہ ] ) );
        }
    }
}
/*-----------------------------------------------------------*/
