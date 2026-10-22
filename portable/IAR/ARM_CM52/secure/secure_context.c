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
#అన్తర్భావ "secure_context.h"

/* Secure heap includes. */
#అన్తర్భావ "secure_heap.h"

/* Secure port macros. */
#అన్తర్భావ "secure_port_macros.h"

/**
 * @brief CONTROL value for privileged tasks.
 *
 * Bit[0] - 0 --> Thread mode is privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#నిర్వచించు securecontext_CONTROL_విలువ_PRIVILEGED      0x02

/**
 * @brief CONTROL value for un-privileged tasks.
 *
 * Bit[0] - 1 --> Thread mode is un-privileged.
 * Bit[1] - 1 --> Thread mode uses PSP.
 */
#నిర్వచించు securecontext_CONTROL_విలువ_UNPRIVILEGED    0x03

/**
 * @brief Size of stack seal values in bytes.
 */
#నిర్వచించు securecontext_దొంతర_SEAL_కొలత               8

/**
 * @brief Stack seal value as recommended by ARM.
 */
#నిర్వచించు securecontext_దొంతర_SEAL_విలువ              0xFEF5EDA5

/**
 * @brief Maximum number of secure contexts.
 */
#నిర్వచితం_కాకపోతే secureconfigMAX_SECURE_CONTEXTS
    #నిర్వచించు secureconfigMAX_SECURE_CONTEXTS    8UL
#అయితే_ముగింపు
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
స్థిర uint32_t ulGetSecureContext( శూన్య * pvTaskHandle );

/**
 * @brief Return the secure context to the secure context pool (xSecureContexts).
 *
 * @param[in] ulSecureContextIndex Index of the context in the xSecureContexts array.
 */
స్థిర శూన్య vReturnSecureContext( uint32_t ul_Secure_Context_సూచీ );

/* These are implemented in assembly. */
బాహ్య శూన్య Secure_Context_ఎక్కించు_Context_Asm( SecureContext_t * pxSecureContext );
బాహ్య శూన్య SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext );
/*-----------------------------------------------------------*/

స్థిర uint32_t ulGetSecureContext( శూన్య * pvTaskHandle )
{
    /* Start with invalid index. */
    uint32_t i, ul_Secure_Context_సూచీ = secureconfigMAX_SECURE_CONTEXTS;

    కొరకు( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
    {
        ఒకవేళ( ( xSecureContexts[ i ].puc_Current_దొంతర_సూచిక == ఖాళీ ) &&
            ( xSecureContexts[ i ].puc_దొంతర_హద్దు == ఖాళీ ) &&
            ( xSecureContexts[ i ].puc_దొంతర_ప్రారంభం == ఖాళీ ) &&
            ( xSecureContexts[ i ].pvTaskHandle == ఖాళీ ) &&
            ( ul_Secure_Context_సూచీ == secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_సూచీ = i;
        }
        లేకపోతే ఒకవేళ( xSecureContexts[ i ].pvTaskHandle == pvTaskHandle )
        {
            /* A task can only have one secure context. Do not allocate a second
             * context for the same task. */
            ul_Secure_Context_సూచీ = secureconfigMAX_SECURE_CONTEXTS;
            ఆపు;
        }
    }

    తిరిగి ul_Secure_Context_సూచీ;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య vReturnSecureContext( uint32_t ul_Secure_Context_సూచీ )
{
    xSecureContexts[ ul_Secure_Context_సూచీ ].puc_Current_దొంతర_సూచిక = ఖాళీ;
    xSecureContexts[ ul_Secure_Context_సూచీ ].puc_దొంతర_హద్దు = ఖాళీ;
    xSecureContexts[ ul_Secure_Context_సూచీ ].puc_దొంతర_ప్రారంభం = ఖాళీ;
    xSecureContexts[ ul_Secure_Context_సూచీ ].pvTaskHandle = ఖాళీ;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE శూన్య SecureContext_Init( శూన్య )
{
    uint32_t ulIPSR, i;
    స్థిర uint32_t ulSecureContextsInitialized = 0;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    ఒకవేళ( ( ulIPSR != 0 ) && ( ulSecureContextsInitialized == 0 ) )
    {
        /* Ensure to initialize secure contexts only once. */
        ulSecureContextsInitialized = 1;

        /* No stack for thread mode until a task's context is loaded. */
        secureport_సమితి_PSPLIM( securecontext_NO_దొంతర );
        secureport_సమితి_PSP( securecontext_NO_దొంతర );

        /* Initialize all secure contexts. */
        కొరకు( i = 0; i < secureconfigMAX_SECURE_CONTEXTS; i++ )
        {
            xSecureContexts[ i ].puc_Current_దొంతర_సూచిక = ఖాళీ;
            xSecureContexts[ i ].puc_దొంతర_హద్దు = ఖాళీ;
            xSecureContexts[ i ].puc_దొంతర_ప్రారంభం = ఖాళీ;
            xSecureContexts[ i ].pvTaskHandle = ఖాళీ;
        }

        #ఒకవేళ ( configENABLE_MPU == 1 )
        {
            /* Configure thread mode to use PSP and to be unprivileged. */
            secureport_సమితి_CONTROL( securecontext_CONTROL_విలువ_UNPRIVILEGED );
        }
        #లేకపోతే /* configENABLE_MPU */
        {
            /* Configure thread mode to use PSP and to be privileged. */
            secureport_సమితి_CONTROL( securecontext_CONTROL_విలువ_PRIVILEGED );
        }
        #అయితే_ముగింపు /* configENABLE_MPU */
    }
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_దొంతర_కొలత,
                                                                                       uint32_t ulIsTaskPrivileged,
                                                                                       శూన్య * pvTaskHandle )
#లేకపోతే /* configENABLE_MPU */
    secureportNON_SECURE_CALLABLE SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_దొంతర_కొలత,
                                                                                       శూన్య * pvTaskHandle )
#అయితే_ముగింపు /* configENABLE_MPU */
{
    uint8_t * puc_దొంతర_జ్ఞాపకం = ఖాళీ;
    uint8_t * puc_దొంతర_హద్దు;
    uint32_t ulIPSR, ul_Secure_Context_సూచీ;
    SecureContextHandle_t xSecureContextHandle = securecontextINVALID_CONTEXT_ID;

    #ఒకవేళ ( configENABLE_MPU == 1 )
        uint32_t * pul_Current_దొంతర_సూచిక = ఖాళీ;
    #అయితే_ముగింపు /* configENABLE_MPU */

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_దొంతర_హద్దు );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode.
     * Also do nothing, if a secure context us already loaded. PSPLIM is set to
     * securecontextNO_STACK when no secure context is loaded. */
    ఒకవేళ( ( ulIPSR != 0 ) && ( puc_దొంతర_హద్దు == securecontext_NO_దొంతర ) )
    {
        /* Obtain a free secure context. */
        ul_Secure_Context_సూచీ = ulGetSecureContext( pvTaskHandle );

        /* Were we able to get a free context? */
        ఒకవేళ( ul_Secure_Context_సూచీ < secureconfigMAX_SECURE_CONTEXTS )
        {
            /* Allocate the stack space if possible. */
            ఒకవేళ( ( ul_Secure_దొంతర_కొలత < securecontext_దొంతర_SEAL_కొలత ) ||
                ( ul_Secure_దొంతర_కొలత > ( UINT32_MAX - securecontext_దొంతర_SEAL_కొలత ) ) )
            {
                /* Reject stacks that are too small (the CONTROL word would be
                 * written before the allocation, corrupting the secure heap)
                 * and sizes that would overflow when the seal size is added. */
                puc_దొంతర_జ్ఞాపకం = ఖాళీ;
            }
            లేకపోతే
            {
                puc_దొంతర_జ్ఞాపకం = pv_పోర్టు_Malloc( ul_Secure_దొంతర_కొలత + securecontext_దొంతర_SEAL_కొలత );
            }

            ఒకవేళ( puc_దొంతర_జ్ఞాపకం != ఖాళీ )
            {
                /* Since stack grows down, the starting point will be the last
                * location. Note that this location is next to the last
                * allocated byte for stack (excluding the space for seal values)
                * because the hardware decrements the stack pointer before
                * writing i.e. if stack pointer is 0x2, a push operation will
                * decrement the stack pointer to 0x1 and then write at 0x1. */
                xSecureContexts[ ul_Secure_Context_సూచీ ].puc_దొంతర_ప్రారంభం = puc_దొంతర_జ్ఞాపకం + ul_Secure_దొంతర_కొలత;

                /* Seal the created secure process stack. */
                *( uint32_t * ) ( puc_దొంతర_జ్ఞాపకం + ul_Secure_దొంతర_కొలత ) = securecontext_దొంతర_SEAL_విలువ;
                *( uint32_t * ) ( puc_దొంతర_జ్ఞాపకం + ul_Secure_దొంతర_కొలత + 4 ) = securecontext_దొంతర_SEAL_విలువ;

                /* The stack cannot go beyond this location. This value is
                 * programmed in the PSPLIM register on context switch.*/
                xSecureContexts[ ul_Secure_Context_సూచీ ].puc_దొంతర_హద్దు = puc_దొంతర_జ్ఞాపకం;

                xSecureContexts[ ul_Secure_Context_సూచీ ].pvTaskHandle = pvTaskHandle;

                #ఒకవేళ ( configENABLE_MPU == 1 )
                {
                    /* Store the correct CONTROL value for the task on the stack.
                     * This value is programmed in the CONTROL register on
                     * context switch. */
                    pul_Current_దొంతర_సూచిక = ( uint32_t * ) xSecureContexts[ ul_Secure_Context_సూచీ ].puc_దొంతర_ప్రారంభం;
                    pul_Current_దొంతర_సూచిక--;

                    ఒకవేళ( ulIsTaskPrivileged )
                    {
                        *( pul_Current_దొంతర_సూచిక ) = securecontext_CONTROL_విలువ_PRIVILEGED;
                    }
                    లేకపోతే
                    {
                        *( pul_Current_దొంతర_సూచిక ) = securecontext_CONTROL_విలువ_UNPRIVILEGED;
                    }

                    /* Store the current stack pointer. This value is programmed in
                     * the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_సూచీ ].puc_Current_దొంతర_సూచిక = ( uint8_t * ) pul_Current_దొంతర_సూచిక;
                }
                #లేకపోతే /* configENABLE_MPU */
                {
                    /* Current SP is set to the starting of the stack. This
                     * value programmed in the PSP register on context switch. */
                    xSecureContexts[ ul_Secure_Context_సూచీ ].puc_Current_దొంతర_సూచిక = xSecureContexts[ ul_Secure_Context_సూచీ ].puc_దొంతర_ప్రారంభం;
                }
                #అయితే_ముగింపు /* configENABLE_MPU */

                /* Ensure to never return 0 as a valid context handle. */
                xSecureContextHandle = ul_Secure_Context_సూచీ + 1UL;
            }
        }
    }

    తిరిగి xSecureContextHandle;
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE శూన్య SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                                              శూన్య * pvTaskHandle )
{
    uint32_t ulIPSR, ul_Secure_Context_సూచీ;
    uint8_t * puc_దొంతర_హద్దు;

    /* Read the Interrupt Program Status Register (IPSR) and Process Stack Limit
     * Register (PSPLIM) value. */
    secureportREAD_IPSR( ulIPSR );
    secureportREAD_PSPLIM( puc_దొంతర_హద్దు );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    ఒకవేళ( ulIPSR != 0 )
    {
        /* Only free if a valid context handle is passed. */
        ఒకవేళ( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
        {
            ul_Secure_Context_సూచీ = xSecureContextHandle - 1UL;

            /* Ensure that the secure context being deleted is associated with
             * the task and is NOT the currently-loaded context. Freeing a
             * context whose stack is currently loaded in PSPLIM would leave the
             * running task referencing freed secure memory (use-after-free).
             * pvTaskHandle is supplied by the non-secure side and is untrusted,
             * so it is used only as an additional ownership match, not as
             * authority. */
            ఒకవేళ( ( xSecureContexts[ ul_Secure_Context_సూచీ ].pvTaskHandle == pvTaskHandle ) &&
                ( xSecureContexts[ ul_Secure_Context_సూచీ ].puc_దొంతర_హద్దు != puc_దొంతర_హద్దు ) )
            {
                /* Free the stack space. */
                v_పోర్టు_Free( xSecureContexts[ ul_Secure_Context_సూచీ ].puc_దొంతర_హద్దు );

                /* Return the secure context back to the free secure contexts pool. */
                vReturnSecureContext( ul_Secure_Context_సూచీ );
            }
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE శూన్య Secure_Context_ఎక్కించు_Context( SecureContextHandle_t xSecureContextHandle,
                                                              శూన్య * pvTaskHandle )
{
    uint8_t * puc_దొంతర_హద్దు;
    uint32_t ul_Secure_Context_సూచీ;

    ఒకవేళ( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_సూచీ = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_దొంతర_హద్దు );

        /* Ensure that no secure context is loaded and the task is loading it's
         * own context. */
        ఒకవేళ( ( puc_దొంతర_హద్దు == securecontext_NO_దొంతర ) &&
            ( xSecureContexts[ ul_Secure_Context_సూచీ ].pvTaskHandle == pvTaskHandle ) )
        {
            Secure_Context_ఎక్కించు_Context_Asm( &( xSecureContexts[ ul_Secure_Context_సూచీ ] ) );
        }
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE శూన్య SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                                              శూన్య * pvTaskHandle )
{
    uint8_t * puc_దొంతర_హద్దు;
    uint32_t ul_Secure_Context_సూచీ;

    ఒకవేళ( ( xSecureContextHandle > 0UL ) && ( xSecureContextHandle <= secureconfigMAX_SECURE_CONTEXTS ) )
    {
        ul_Secure_Context_సూచీ = xSecureContextHandle - 1UL;

        secureportREAD_PSPLIM( puc_దొంతర_హద్దు );

        /* Ensure that task's context is loaded and the task is saving its own
         * context. */
        ఒకవేళ( ( xSecureContexts[ ul_Secure_Context_సూచీ ].puc_దొంతర_హద్దు == puc_దొంతర_హద్దు ) &&
            ( xSecureContexts[ ul_Secure_Context_సూచీ ].pvTaskHandle == pvTaskHandle ) )
        {
            SecureContext_SaveContextAsm( &( xSecureContexts[ ul_Secure_Context_సూచీ ] ) );
        }
    }
}
/*-----------------------------------------------------------*/
