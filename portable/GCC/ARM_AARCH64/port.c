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

/* Standard includes. */
#ضمن <stdlib.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#که_نه_تعریف_شوی config_مداخله_CONTROLLER_بنسټ_پته
    #تېروتنه "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined. See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای

#که_نه_تعریف_شوی config_مداخله_CONTROLLER_CPU_INTERFACE_دننه_واټن
    #تېروتنه "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای

#که_نه_تعریف_شوی config_UNIQUE_مداخله_PRIORITIES
    #تېروتنه "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای

#که_نه_تعریف_شوی config_تیاری_TICK_مداخله
    #تېروتنه "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای /* configSETUP_TICK_INTERRUPT */

#که_نه_تعریف_شوی config_MAX_API_CALL_مداخله_لومړیتوب
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای

#إذا config_MAX_API_CALL_مداخله_لومړیتوب == 0
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#د_که_پای

#إذا config_MAX_API_CALL_مداخله_لومړیتوب > config_UNIQUE_مداخله_PRIORITIES
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#د_که_پای

#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #تېروتنه "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #د_که_پای
#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#إذا config_MAX_API_CALL_مداخله_لومړیتوب <= ( config_UNIQUE_مداخله_PRIORITIES / 2 )
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#د_که_پای

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h. */
#که_نه_تعریف_شوی config_CLEAR_TICK_مداخله
    #تعریف_کړه config_CLEAR_TICK_مداخله()
#د_که_پای

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کړه پورټ_NO_CRITICAL_NESTING          ( ( size_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#تعریف_کړه پورټ_UNMASK_ارزښت                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کړه پورټ_NO_FLOATING_ټکی_CONTEXT    ( ( ډېری_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#تعریف_کړه پورټ_SP_ELx                       ( ( ډېری_Type_t ) 0x01 )
#تعریف_کړه پورټ_SP_EL0                       ( ( ډېری_Type_t ) 0x00 )

#إذا defined( GUEST )
    #تعریف_کړه پورټ_EL1                      ( ( ډېری_Type_t ) 0x04 )
    #تعریف_کړه پورټ_INITIAL_PSTATE           ( پورټ_EL1 | پورټ_SP_EL0 )
#وإلا
    #تعریف_کړه پورټ_EL3                      ( ( ډېری_Type_t ) 0x0c )
    /* At the time of writing, the BSP only supports EL3. */
    #تعریف_کړه پورټ_INITIAL_PSTATE           ( پورټ_EL3 | پورټ_SP_EL0 )
#د_که_پای


/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#تعریف_کړه پورټ_دوګونی_ټکی_بټونه      ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#تعریف_کړه پورټ_APSR_ډېرپېښ_بټونه_ماسک    ( 0x0C )

/* The I bit in the DAIF bits. */
#تعریف_کړه پورټ_DAIF_I                 ( 0x80 )

/* Macro to unmask all interrupt priorities. */
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک()                            \
    {                                                         \
        پورټ_DISABLE_INTERRUPTS();                             \
        پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی = پورټ_UNMASK_ارزښت; \
        __asm متطاير ( "DSB SY     \n"                      \
                         "ISB SY     \n" );                   \
        پورټ_ENABLE_INTERRUPTS();                              \
    }

/* Hardware specifics used when sanity checking the configuration. */
#تعریف_کړه پورټ_مداخله_لومړیتوب_ثبتوونکی_دننه_واټن    0x400UL
#تعریف_کړه پورټ_MAX_8_بټ_ارزښت                       ( ( uint8_t ) 0xff )
#تعریف_کړه پورټ_بټ_0_سېټ                             ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit registers.*/
#تعریف_کړه پورټ_FPU_ثبتوونکی_ټکي     ( 32 * 2 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورټ_Restore_Task_Context( فراغ );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
متطاير uint64_t ullCriticalNesting = 9999ULL;

/* Saved as part of the task context.  If ullPortTaskHasFPUContext is non-zero
 * then floating point context must be saved and restored for the task. */
uint64_t ull_پورټ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint64_t ull_پورټ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint64_t ull_پورټ_مداخله_Nesting = 0;

/* Used in the ASM code. */
__attribute__( ( کارول_شوی ) ) ثابت uint64_t ullICCEOIR = پورټ_ICCEOIR_پای_ټکی_د_مداخله_ثبتوونکی_پته;
__attribute__( ( کارول_شوی ) ) ثابت uint64_t ullICCIAR = پورټ_ICCIAR_مداخله_ACKNOWLEDGE_ثبتوونکی_پته;
__attribute__( ( کارول_شوی ) ) ثابت uint64_t ullICCPMR = پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی_پته;
__attribute__( ( کارول_شوی ) ) ثابت uint64_t ull_Max_APIPriority_ماسک = ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First all the general purpose registers. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x0101010101010101ULL;        /* R1 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R0 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x0303030303030303ULL;        /* R3 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x0202020202020202ULL;        /* R2 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x0505050505050505ULL;        /* R5 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x0404040404040404ULL;        /* R4 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x0707070707070707ULL;        /* R7 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x0606060606060606ULL;        /* R6 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x0909090909090909ULL;        /* R9 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x0808080808080808ULL;        /* R8 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1111111111111111ULL;        /* R11 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1010101010101010ULL;        /* R10 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1313131313131313ULL;        /* R13 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1212121212121212ULL;        /* R12 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1515151515151515ULL;        /* R15 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1414141414141414ULL;        /* R14 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1717171717171717ULL;        /* R17 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1616161616161616ULL;        /* R16 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1919191919191919ULL;        /* R19 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x1818181818181818ULL;        /* R18 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2121212121212121ULL;        /* R21 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2020202020202020ULL;        /* R20 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2323232323232323ULL;        /* R23 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2222222222222222ULL;        /* R22 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2525252525252525ULL;        /* R25 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2424242424242424ULL;        /* R24 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2727272727272727ULL;        /* R27 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2626262626262626ULL;        /* R26 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2929292929292929ULL;        /* R29 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2828282828282828ULL;        /* R28 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00;         /* R30 - procedure call link register. */

    px_سر_د_ډېری--;
    *px_سر_د_ډېری = پورټ_INITIAL_PSTATE;

    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ; /* Exception return address. */

    #إذا ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = پورټ_NO_CRITICAL_NESTING;

        /* The task will start without a floating point context.  A task that
         * uses the floating point hardware must call vPortTaskUsesFPU() before
         * executing any floating point instructions. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = پورټ_NO_FLOATING_ټکی_CONTEXT;
    }
    #وإلاإذا ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_سر_د_ډېری -= پورټ_FPU_ثبتوونکی_ټکي;
        memset( px_سر_د_ډېری, 0x00, پورټ_FPU_ثبتوونکی_ټکي * حجم( ډېری_Type_t ) );

        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = پورټ_NO_CRITICAL_NESTING;

        px_سر_د_ډېری--;
        *px_سر_د_ډېری = pdTRUE;
        ull_پورټ_Task_Has_FPUContext = pdTRUE;
    }
    #وإلا /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #تېروتنه "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #د_که_پای /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    uint32_t ulAPSR;

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_لومړیتوب;
        متطاير uint8_t * ثابت puc_لومړی_User_لومړیتوب_ثبتوونکی = ( متطاير uint8_t * ثابت ) ( config_مداخله_CONTROLLER_بنسټ_پته + پورټ_مداخله_لومړیتوب_ثبتوونکی_دننه_واټن );
        متطاير uint8_t uc_Max_لومړیتوب_ارزښت;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_لومړیتوب = *puc_لومړی_User_لومړیتوب_ثبتوونکی;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_لومړی_User_لومړیتوب_ثبتوونکی = پورټ_MAX_8_بټ_ارزښت;

        /* Read the value back to see how many bits stuck. */
        uc_Max_لومړیتوب_ارزښت = *puc_لومړی_User_لومړیتوب_ثبتوونکی;

        /* Shift to the least significant bits. */
        طالما( ( uc_Max_لومړیتوب_ارزښت & پورټ_بټ_0_سېټ ) != پورټ_بټ_0_سېټ )
        {
            uc_Max_لومړیتوب_ارزښت >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */

        configASSERT( uc_Max_لومړیتوب_ارزښت >= پورټ_ټیټ_ترین_مداخله_لومړیتوب );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_لومړی_User_لومړیتوب_ثبتوونکی = uc_Original_لومړیتوب;
    }
    #د_که_پای /* configASSERT_DEFINED */


    /* At the time of writing, the BSP only supports EL3. */
    __asm متطاير ( "MRS %0, CurrentEL" : "=r" ( ulAPSR ) );
    ulAPSR &= پورټ_APSR_ډېرپېښ_بټونه_ماسک;

    #إذا defined( GUEST )
    #warning "Building for execution as a guest under XEN. THIS IS NOT A FULLY TESTED PATH."
        configASSERT( ulAPSR == پورټ_EL1 );

        إذا( ulAPSR == پورټ_EL1 )
    #وإلا
        configASSERT( ulAPSR == پورټ_EL3 );

        إذا( ulAPSR == پورټ_EL3 )
    #د_که_پای
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( پورټ_ICCBPR_دوګونی_ټکی_ثبتوونکی & پورټ_دوګونی_ټکی_بټونه ) <= پورټ_MAX_دوګونی_ټکی_ارزښت );

        إذا( ( پورټ_ICCBPR_دوګونی_ټکی_ثبتوونکی & پورټ_دوګونی_ټکی_بټونه ) <= پورټ_MAX_دوګونی_ټکی_ارزښت )
        {
            /* Interrupts are turned off in the CPU itself to ensure a tick does
             * not execute while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing. */
            پورټ_DISABLE_INTERRUPTS();

            /* Start the timer that generates the tick ISR. */
            config_تیاری_TICK_مداخله();

            /* Start the first task executing. */
            v_پورټ_Restore_Task_Context();
        }
    }

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ullCriticalNesting == 1000ULL );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ux_پورټ_سېټ_مداخله_ماسک();

    /* Now interrupts are disabled ullCriticalNesting can be accessed
     * directly.  Increment ullCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ullCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    إذا( ullCriticalNesting == 1ULL )
    {
        configASSERT( ull_پورټ_مداخله_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    إذا( ullCriticalNesting > پورټ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ullCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ullCriticalNesting == پورټ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورټ_CLEAR_مداخله_ماسک();
        }
    }
}
/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    /* Must be the lowest possible priority. */
    #إذا !defined( QEMU )
    {
        configASSERT( پورټ_ICCRPR_RUNNING_لومړیتوب_ثبتوونکی == ( uint32_t ) ( پورټ_ټیټ_ترین_USABLE_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) );
    }
    #د_که_پای

    /* Interrupts should not be enabled before this point. */
    #إذا ( configASSERT_DEFINED == 1 )
    {
        uint32_t ul_ماسک_بټونه;

        __asm متطاير ( "mrs %0, daif" : "=r" ( ul_ماسک_بټونه )::"memory" );
        configASSERT( ( ul_ماسک_بټونه & پورټ_DAIF_I ) != 0 );
    }
    #د_که_پای /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی = ( uint32_t ) ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه );
    __asm متطاير ( "dsb sy     \n"
                     "isb sy     \n" ::: "memory" );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_مداخله();
    پورټ_ENABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ull_پورټ_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    پورټ_CLEAR_مداخله_ماسک();
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_FPU_SUPPORT != 2 )

    فراغ v_پورټ_Task_کاروي_FPU( فراغ )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ull_پورټ_Task_Has_FPUContext = pdTRUE;

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#د_که_پای /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

فراغ v_پورټ_Clear_مداخله_ماسک( UBaseType_t ux_New_ماسک_ارزښت )
{
    إذا( ux_New_ماسک_ارزښت == pdFALSE )
    {
        پورټ_CLEAR_مداخله_ماسک();
    }
}
/*-----------------------------------------------------------*/

UBaseType_t ux_پورټ_سېټ_مداخله_ماسک( فراغ )
{
    uint32_t ulReturn;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    پورټ_DISABLE_INTERRUPTS();

    إذا( پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی == ( uint32_t ) ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    وإلا
    {
        ulReturn = pdFALSE;
        پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی = ( uint32_t ) ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه );
        __asm متطاير ( "dsb sy     \n"
                         "isb sy     \n" ::: "memory" );
    }

    پورټ_ENABLE_INTERRUPTS();

    أرجع ulReturn;
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورټ_Validate_مداخله_لومړیتوب( فراغ )
    {
        /* The following assertion will fail if a service routine (ISR) for
         * an interrupt that has been assigned a priority above
         * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
         * function.  ISR safe FreeRTOS API functions must *only* be called
         * from interrupts that have been assigned a priority at or below
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * Numerically low interrupt priority numbers represent logically high
         * interrupt priorities, therefore the priority of the interrupt must
         * be set to a value equal to or numerically *higher* than
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * FreeRTOS maintains separate thread and ISR API functions to ensure
         * interrupt entry is as fast and simple as possible. */
        configASSERT( پورټ_ICCRPR_RUNNING_لومړیتوب_ثبتوونکی >= ( uint32_t ) ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) );

        /* Priority grouping:  The interrupt controller (GIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * The priority grouping is configured by the GIC's binary point register
         * (ICCBPR).  Writing 0 to ICCBPR will ensure it is set to its lowest
         * possible value (which may be above 0). */
        configASSERT( ( پورټ_ICCBPR_دوګونی_ټکی_ثبتوونکی & پورټ_دوګونی_ټکی_بټونه ) <= پورټ_MAX_دوګونی_ټکی_ارزښت );
    }

#د_که_پای /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/
