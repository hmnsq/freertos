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

#جيڪڏهن_وصف_نه_ٿيل config_مداخلت_CONTROLLER_بنياد_پتو
    #غلطي "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined. See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_مداخلت_CONTROLLER_CPU_INTERFACE_وٿي
    #غلطي "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_UNIQUE_مداخلت_PRIORITIES
    #غلطي "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_تياري_TICK_مداخلت
    #غلطي "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جيڪڏهن_پورو /* configSETUP_TICK_INTERRUPT */

#جيڪڏهن_وصف_نه_ٿيل config_MAX_API_CALL_مداخلت_ترجيح
    #غلطي "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جيڪڏهن_پورو

#إذا config_MAX_API_CALL_مداخلت_ترجيح == 0
    #غلطي "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#جيڪڏهن_پورو

#إذا config_MAX_API_CALL_مداخلت_ترجيح > config_UNIQUE_مداخلت_PRIORITIES
    #غلطي "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#جيڪڏهن_پورو

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطي "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #جيڪڏهن_پورو
#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#إذا config_MAX_API_CALL_مداخلت_ترجيح <= ( config_UNIQUE_مداخلت_PRIORITIES / 2 )
    #غلطي "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#جيڪڏهن_پورو

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h. */
#جيڪڏهن_وصف_نه_ٿيل config_CLEAR_TICK_مداخلت
    #وصف_ڪريو config_CLEAR_TICK_مداخلت()
#جيڪڏهن_پورو

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#وصف_ڪريو پورٽ_NO_CRITICAL_NESTING          ( ( size_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#وصف_ڪريو پورٽ_UNMASK_قدر                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#وصف_ڪريو پورٽ_NO_FLOATING_نقطو_CONTEXT    ( ( ڍير_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#وصف_ڪريو پورٽ_SP_ELx                       ( ( ڍير_Type_t ) 0x01 )
#وصف_ڪريو پورٽ_SP_EL0                       ( ( ڍير_Type_t ) 0x00 )

#إذا defined( GUEST )
    #وصف_ڪريو پورٽ_EL1                      ( ( ڍير_Type_t ) 0x04 )
    #وصف_ڪريو پورٽ_INITIAL_PSTATE           ( پورٽ_EL1 | پورٽ_SP_EL0 )
#وإلا
    #وصف_ڪريو پورٽ_EL3                      ( ( ڍير_Type_t ) 0x0c )
    /* At the time of writing, the BSP only supports EL3. */
    #وصف_ڪريو پورٽ_INITIAL_PSTATE           ( پورٽ_EL3 | پورٽ_SP_EL0 )
#جيڪڏهن_پورو


/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#وصف_ڪريو پورٽ_ٻٽو_نقطو_بٽ      ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#وصف_ڪريو پورٽ_APSR_گهڻائي_بٽ_نقاب    ( 0x0C )

/* The I bit in the DAIF bits. */
#وصف_ڪريو پورٽ_DAIF_I                 ( 0x80 )

/* Macro to unmask all interrupt priorities. */
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب()                            \
    {                                                         \
        پورٽ_DISABLE_INTERRUPTS();                             \
        پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر = پورٽ_UNMASK_قدر; \
        __asm متطاير ( "DSB SY     \n"                      \
                         "ISB SY     \n" );                   \
        پورٽ_ENABLE_INTERRUPTS();                              \
    }

/* Hardware specifics used when sanity checking the configuration. */
#وصف_ڪريو پورٽ_مداخلت_ترجيح_رجسٽر_وٿي    0x400UL
#وصف_ڪريو پورٽ_MAX_8_ٻٽو_انگ_قدر                       ( ( uint8_t ) 0xff )
#وصف_ڪريو پورٽ_ٻٽو_انگ_0_سيٽ                             ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit registers.*/
#وصف_ڪريو پورٽ_FPU_رجسٽر_لفظ     ( 32 * 2 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورٽ_Restore_Task_Context( فراغ );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
متطاير uint64_t ullCriticalNesting = 9999ULL;

/* Saved as part of the task context.  If ullPortTaskHasFPUContext is non-zero
 * then floating point context must be saved and restored for the task. */
uint64_t ull_پورٽ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint64_t ull_پورٽ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint64_t ull_پورٽ_مداخلت_Nesting = 0;

/* Used in the ASM code. */
__attribute__( ( استعمال_ٿيل ) ) ثابت uint64_t ullICCEOIR = پورٽ_ICCEOIR_پڇاڙي_جو_مداخلت_رجسٽر_پتو;
__attribute__( ( استعمال_ٿيل ) ) ثابت uint64_t ullICCIAR = پورٽ_ICCIAR_مداخلت_ACKNOWLEDGE_رجسٽر_پتو;
__attribute__( ( استعمال_ٿيل ) ) ثابت uint64_t ullICCPMR = پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر_پتو;
__attribute__( ( استعمال_ٿيل ) ) ثابت uint64_t ull_Max_APIPriority_نقاب = ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First all the general purpose registers. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x0101010101010101ULL;        /* R1 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters; /* R0 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x0303030303030303ULL;        /* R3 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x0202020202020202ULL;        /* R2 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x0505050505050505ULL;        /* R5 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x0404040404040404ULL;        /* R4 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x0707070707070707ULL;        /* R7 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x0606060606060606ULL;        /* R6 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x0909090909090909ULL;        /* R9 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x0808080808080808ULL;        /* R8 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1111111111111111ULL;        /* R11 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1010101010101010ULL;        /* R10 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1313131313131313ULL;        /* R13 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1212121212121212ULL;        /* R12 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1515151515151515ULL;        /* R15 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1414141414141414ULL;        /* R14 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1717171717171717ULL;        /* R17 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1616161616161616ULL;        /* R16 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1919191919191919ULL;        /* R19 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x1818181818181818ULL;        /* R18 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2121212121212121ULL;        /* R21 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2020202020202020ULL;        /* R20 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2323232323232323ULL;        /* R23 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2222222222222222ULL;        /* R22 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2525252525252525ULL;        /* R25 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2424242424242424ULL;        /* R24 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2727272727272727ULL;        /* R27 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2626262626262626ULL;        /* R26 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2929292929292929ULL;        /* R29 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2828282828282828ULL;        /* R28 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00;         /* R30 - procedure call link register. */

    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_PSTATE;

    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ; /* Exception return address. */

    #إذا ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = پورٽ_NO_CRITICAL_NESTING;

        /* The task will start without a floating point context.  A task that
         * uses the floating point hardware must call vPortTaskUsesFPU() before
         * executing any floating point instructions. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = پورٽ_NO_FLOATING_نقطو_CONTEXT;
    }
    #وإلاإذا ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_چوٽي_جو_ڍير -= پورٽ_FPU_رجسٽر_لفظ;
        memset( px_چوٽي_جو_ڍير, 0x00, پورٽ_FPU_رجسٽر_لفظ * حجم( ڍير_Type_t ) );

        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = پورٽ_NO_CRITICAL_NESTING;

        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = pdTRUE;
        ull_پورٽ_Task_Has_FPUContext = pdTRUE;
    }
    #وإلا /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #غلطي "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #جيڪڏهن_پورو /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    uint32_t ulAPSR;

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_ترجيح;
        متطاير uint8_t * ثابت puc_پهريون_User_ترجيح_رجسٽر = ( متطاير uint8_t * ثابت ) ( config_مداخلت_CONTROLLER_بنياد_پتو + پورٽ_مداخلت_ترجيح_رجسٽر_وٿي );
        متطاير uint8_t uc_Max_ترجيح_قدر;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ترجيح = *puc_پهريون_User_ترجيح_رجسٽر;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_پهريون_User_ترجيح_رجسٽر = پورٽ_MAX_8_ٻٽو_انگ_قدر;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ترجيح_قدر = *puc_پهريون_User_ترجيح_رجسٽر;

        /* Shift to the least significant bits. */
        طالما( ( uc_Max_ترجيح_قدر & پورٽ_ٻٽو_انگ_0_سيٽ ) != پورٽ_ٻٽو_انگ_0_سيٽ )
        {
            uc_Max_ترجيح_قدر >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */

        configASSERT( uc_Max_ترجيح_قدر >= پورٽ_سڀ_کان_هيٺ_مداخلت_ترجيح );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_پهريون_User_ترجيح_رجسٽر = uc_Original_ترجيح;
    }
    #جيڪڏهن_پورو /* configASSERT_DEFINED */


    /* At the time of writing, the BSP only supports EL3. */
    __asm متطاير ( "MRS %0, CurrentEL" : "=r" ( ulAPSR ) );
    ulAPSR &= پورٽ_APSR_گهڻائي_بٽ_نقاب;

    #إذا defined( GUEST )
    #warning "Building for execution as a guest under XEN. THIS IS NOT A FULLY TESTED PATH."
        configASSERT( ulAPSR == پورٽ_EL1 );

        إذا( ulAPSR == پورٽ_EL1 )
    #وإلا
        configASSERT( ulAPSR == پورٽ_EL3 );

        إذا( ulAPSR == پورٽ_EL3 )
    #جيڪڏهن_پورو
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( پورٽ_ICCBPR_ٻٽو_نقطو_رجسٽر & پورٽ_ٻٽو_نقطو_بٽ ) <= پورٽ_MAX_ٻٽو_نقطو_قدر );

        إذا( ( پورٽ_ICCBPR_ٻٽو_نقطو_رجسٽر & پورٽ_ٻٽو_نقطو_بٽ ) <= پورٽ_MAX_ٻٽو_نقطو_قدر )
        {
            /* Interrupts are turned off in the CPU itself to ensure a tick does
             * not execute while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing. */
            پورٽ_DISABLE_INTERRUPTS();

            /* Start the timer that generates the tick ISR. */
            config_تياري_TICK_مداخلت();

            /* Start the first task executing. */
            v_پورٽ_Restore_Task_Context();
        }
    }

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ullCriticalNesting == 1000ULL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ux_پورٽ_سيٽ_مداخلت_نقاب();

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
        configASSERT( ull_پورٽ_مداخلت_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    إذا( ullCriticalNesting > پورٽ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ullCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ullCriticalNesting == پورٽ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورٽ_CLEAR_مداخلت_نقاب();
        }
    }
}
/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    /* Must be the lowest possible priority. */
    #إذا !defined( QEMU )
    {
        configASSERT( پورٽ_ICCRPR_RUNNING_ترجيح_رجسٽر == ( uint32_t ) ( پورٽ_سڀ_کان_هيٺ_USABLE_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو ) );
    }
    #جيڪڏهن_پورو

    /* Interrupts should not be enabled before this point. */
    #إذا ( configASSERT_DEFINED == 1 )
    {
        uint32_t ul_نقاب_بٽ;

        __asm متطاير ( "mrs %0, daif" : "=r" ( ul_نقاب_بٽ )::"memory" );
        configASSERT( ( ul_نقاب_بٽ & پورٽ_DAIF_I ) != 0 );
    }
    #جيڪڏهن_پورو /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر = ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو );
    __asm متطاير ( "dsb sy     \n"
                     "isb sy     \n" ::: "memory" );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_مداخلت();
    پورٽ_ENABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ull_پورٽ_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    پورٽ_CLEAR_مداخلت_نقاب();
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_FPU_SUPPORT != 2 )

    فراغ v_پورٽ_Task_استعمال_ڪري_FPU( فراغ )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ull_پورٽ_Task_Has_FPUContext = pdTRUE;

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#جيڪڏهن_پورو /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Clear_مداخلت_نقاب( UBaseType_t ux_New_نقاب_قدر )
{
    إذا( ux_New_نقاب_قدر == pdFALSE )
    {
        پورٽ_CLEAR_مداخلت_نقاب();
    }
}
/*-----------------------------------------------------------*/

UBaseType_t ux_پورٽ_سيٽ_مداخلت_نقاب( فراغ )
{
    uint32_t ulReturn;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    پورٽ_DISABLE_INTERRUPTS();

    إذا( پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر == ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    وإلا
    {
        ulReturn = pdFALSE;
        پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر = ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو );
        __asm متطاير ( "dsb sy     \n"
                         "isb sy     \n" ::: "memory" );
    }

    پورٽ_ENABLE_INTERRUPTS();

    أرجع ulReturn;
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورٽ_Validate_مداخلت_ترجيح( فراغ )
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
        configASSERT( پورٽ_ICCRPR_RUNNING_ترجيح_رجسٽر >= ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو ) );

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
        configASSERT( ( پورٽ_ICCBPR_ٻٽو_نقطو_رجسٽر & پورٽ_ٻٽو_نقطو_بٽ ) <= پورٽ_MAX_ٻٽو_نقطو_قدر );
    }

#جيڪڏهن_پورو /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/
