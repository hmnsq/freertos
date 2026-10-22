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

#جے_بنا_تعریف config_رکاوٹ_CONTROLLER_ادھار_پتہ
    #غلطی "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined. See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جے_انت

#جے_بنا_تعریف config_رکاوٹ_CONTROLLER_CPU_INTERFACE_وتھ
    #غلطی "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جے_انت

#جے_بنا_تعریف config_UNIQUE_رکاوٹ_PRIORITIES
    #غلطی "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جے_انت

#جے_بنا_تعریف config_تیاری_TICK_رکاوٹ
    #غلطی "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جے_انت /* configSETUP_TICK_INTERRUPT */

#جے_بنا_تعریف config_MAX_API_CALL_رکاوٹ_ترجیح
    #غلطی "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#جے_انت

#إذا config_MAX_API_CALL_رکاوٹ_ترجیح == 0
    #غلطی "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#جے_انت

#إذا config_MAX_API_CALL_رکاوٹ_ترجیح > config_UNIQUE_رکاوٹ_PRIORITIES
    #غلطی "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#جے_انت

#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطی "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #جے_انت
#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#إذا config_MAX_API_CALL_رکاوٹ_ترجیح <= ( config_UNIQUE_رکاوٹ_PRIORITIES / 2 )
    #غلطی "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#جے_انت

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h. */
#جے_بنا_تعریف config_CLEAR_TICK_رکاوٹ
    #تعریف_کرو config_CLEAR_TICK_رکاوٹ()
#جے_انت

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING          ( ( size_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#تعریف_کرو پورٹ_UNMASK_قدر                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کرو پورٹ_NO_FLOATING_نقطہ_CONTEXT    ( ( ڈھیر_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#تعریف_کرو پورٹ_SP_ELx                       ( ( ڈھیر_Type_t ) 0x01 )
#تعریف_کرو پورٹ_SP_EL0                       ( ( ڈھیر_Type_t ) 0x00 )

#إذا defined( GUEST )
    #تعریف_کرو پورٹ_EL1                      ( ( ڈھیر_Type_t ) 0x04 )
    #تعریف_کرو پورٹ_INITIAL_PSTATE           ( پورٹ_EL1 | پورٹ_SP_EL0 )
#وإلا
    #تعریف_کرو پورٹ_EL3                      ( ( ڈھیر_Type_t ) 0x0c )
    /* At the time of writing, the BSP only supports EL3. */
    #تعریف_کرو پورٹ_INITIAL_PSTATE           ( پورٹ_EL3 | پورٹ_SP_EL0 )
#جے_انت


/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#تعریف_کرو پورٹ_ثنائی_نقطہ_بٹ      ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#تعریف_کرو پورٹ_APSR_منوال_بٹ_نقاب    ( 0x0C )

/* The I bit in the DAIF bits. */
#تعریف_کرو پورٹ_DAIF_I                 ( 0x80 )

/* Macro to unmask all interrupt priorities. */
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب()                            \
    {                                                         \
        پورٹ_DISABLE_INTERRUPTS();                             \
        پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر = پورٹ_UNMASK_قدر; \
        __asm متطاير ( "DSB SY     \n"                      \
                         "ISB SY     \n" );                   \
        پورٹ_ENABLE_INTERRUPTS();                              \
    }

/* Hardware specifics used when sanity checking the configuration. */
#تعریف_کرو پورٹ_رکاوٹ_ترجیح_رجسٹر_وتھ    0x400UL
#تعریف_کرو پورٹ_MAX_8_ثنائی_ہندسہ_قدر                       ( ( uint8_t ) 0xff )
#تعریف_کرو پورٹ_ثنائی_ہندسہ_0_سیٹ                             ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit registers.*/
#تعریف_کرو پورٹ_FPU_رجسٹر_الفاظ     ( 32 * 2 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورٹ_Restore_Task_Context( فراغ );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
متطاير uint64_t ullCriticalNesting = 9999ULL;

/* Saved as part of the task context.  If ullPortTaskHasFPUContext is non-zero
 * then floating point context must be saved and restored for the task. */
uint64_t ull_پورٹ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint64_t ull_پورٹ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint64_t ull_پورٹ_رکاوٹ_Nesting = 0;

/* Used in the ASM code. */
__attribute__( ( ورتیا ) ) ثابت uint64_t ullICCEOIR = پورٹ_ICCEOIR_سرا_دا_رکاوٹ_رجسٹر_پتہ;
__attribute__( ( ورتیا ) ) ثابت uint64_t ullICCIAR = پورٹ_ICCIAR_رکاوٹ_ACKNOWLEDGE_رجسٹر_پتہ;
__attribute__( ( ورتیا ) ) ثابت uint64_t ullICCPMR = پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر_پتہ;
__attribute__( ( ورتیا ) ) ثابت uint64_t ull_Max_APIPriority_نقاب = ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First all the general purpose registers. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x0101010101010101ULL;        /* R1 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x0303030303030303ULL;        /* R3 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x0202020202020202ULL;        /* R2 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x0505050505050505ULL;        /* R5 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x0404040404040404ULL;        /* R4 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x0707070707070707ULL;        /* R7 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x0606060606060606ULL;        /* R6 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x0909090909090909ULL;        /* R9 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x0808080808080808ULL;        /* R8 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1111111111111111ULL;        /* R11 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1010101010101010ULL;        /* R10 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1313131313131313ULL;        /* R13 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1212121212121212ULL;        /* R12 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1515151515151515ULL;        /* R15 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1414141414141414ULL;        /* R14 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1717171717171717ULL;        /* R17 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1616161616161616ULL;        /* R16 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1919191919191919ULL;        /* R19 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x1818181818181818ULL;        /* R18 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2121212121212121ULL;        /* R21 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2020202020202020ULL;        /* R20 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2323232323232323ULL;        /* R23 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2222222222222222ULL;        /* R22 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2525252525252525ULL;        /* R25 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2424242424242424ULL;        /* R24 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2727272727272727ULL;        /* R27 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2626262626262626ULL;        /* R26 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2929292929292929ULL;        /* R29 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2828282828282828ULL;        /* R28 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00;         /* R30 - procedure call link register. */

    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_PSTATE;

    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ; /* Exception return address. */

    #إذا ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = پورٹ_NO_CRITICAL_NESTING;

        /* The task will start without a floating point context.  A task that
         * uses the floating point hardware must call vPortTaskUsesFPU() before
         * executing any floating point instructions. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = پورٹ_NO_FLOATING_نقطہ_CONTEXT;
    }
    #وإلاإذا ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_چوٹی_دا_ڈھیر -= پورٹ_FPU_رجسٹر_الفاظ;
        memset( px_چوٹی_دا_ڈھیر, 0x00, پورٹ_FPU_رجسٹر_الفاظ * حجم( ڈھیر_Type_t ) );

        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = پورٹ_NO_CRITICAL_NESTING;

        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = pdTRUE;
        ull_پورٹ_Task_Has_FPUContext = pdTRUE;
    }
    #وإلا /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #غلطی "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #جے_انت /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    uint32_t ulAPSR;

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_ترجیح;
        متطاير uint8_t * ثابت puc_پہلا_User_ترجیح_رجسٹر = ( متطاير uint8_t * ثابت ) ( config_رکاوٹ_CONTROLLER_ادھار_پتہ + پورٹ_رکاوٹ_ترجیح_رجسٹر_وتھ );
        متطاير uint8_t uc_Max_ترجیح_قدر;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ترجیح = *puc_پہلا_User_ترجیح_رجسٹر;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_پہلا_User_ترجیح_رجسٹر = پورٹ_MAX_8_ثنائی_ہندسہ_قدر;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ترجیح_قدر = *puc_پہلا_User_ترجیح_رجسٹر;

        /* Shift to the least significant bits. */
        طالما( ( uc_Max_ترجیح_قدر & پورٹ_ثنائی_ہندسہ_0_سیٹ ) != پورٹ_ثنائی_ہندسہ_0_سیٹ )
        {
            uc_Max_ترجیح_قدر >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */

        configASSERT( uc_Max_ترجیح_قدر >= پورٹ_سبھ_توں_نیواں_رکاوٹ_ترجیح );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_پہلا_User_ترجیح_رجسٹر = uc_Original_ترجیح;
    }
    #جے_انت /* configASSERT_DEFINED */


    /* At the time of writing, the BSP only supports EL3. */
    __asm متطاير ( "MRS %0, CurrentEL" : "=r" ( ulAPSR ) );
    ulAPSR &= پورٹ_APSR_منوال_بٹ_نقاب;

    #إذا defined( GUEST )
    #warning "Building for execution as a guest under XEN. THIS IS NOT A FULLY TESTED PATH."
        configASSERT( ulAPSR == پورٹ_EL1 );

        إذا( ulAPSR == پورٹ_EL1 )
    #وإلا
        configASSERT( ulAPSR == پورٹ_EL3 );

        إذا( ulAPSR == پورٹ_EL3 )
    #جے_انت
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر & پورٹ_ثنائی_نقطہ_بٹ ) <= پورٹ_MAX_ثنائی_نقطہ_قدر );

        إذا( ( پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر & پورٹ_ثنائی_نقطہ_بٹ ) <= پورٹ_MAX_ثنائی_نقطہ_قدر )
        {
            /* Interrupts are turned off in the CPU itself to ensure a tick does
             * not execute while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing. */
            پورٹ_DISABLE_INTERRUPTS();

            /* Start the timer that generates the tick ISR. */
            config_تیاری_TICK_رکاوٹ();

            /* Start the first task executing. */
            v_پورٹ_Restore_Task_Context();
        }
    }

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ullCriticalNesting == 1000ULL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Enter_Critical( فراغ )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ux_پورٹ_سیٹ_رکاوٹ_نقاب();

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
        configASSERT( ull_پورٹ_رکاوٹ_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Exit_Critical( فراغ )
{
    إذا( ullCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ullCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ullCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورٹ_CLEAR_رکاوٹ_نقاب();
        }
    }
}
/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    /* Must be the lowest possible priority. */
    #إذا !defined( QEMU )
    {
        configASSERT( پورٹ_ICCRPR_RUNNING_ترجیح_رجسٹر == ( uint32_t ) ( پورٹ_سبھ_توں_نیواں_USABLE_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ ) );
    }
    #جے_انت

    /* Interrupts should not be enabled before this point. */
    #إذا ( configASSERT_DEFINED == 1 )
    {
        uint32_t ul_نقاب_بٹ;

        __asm متطاير ( "mrs %0, daif" : "=r" ( ul_نقاب_بٹ )::"memory" );
        configASSERT( ( ul_نقاب_بٹ & پورٹ_DAIF_I ) != 0 );
    }
    #جے_انت /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر = ( uint32_t ) ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ );
    __asm متطاير ( "dsb sy     \n"
                     "isb sy     \n" ::: "memory" );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_رکاوٹ();
    پورٹ_ENABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ull_پورٹ_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    پورٹ_CLEAR_رکاوٹ_نقاب();
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_FPU_SUPPORT != 2 )

    فراغ v_پورٹ_Task_ورتدا_FPU( فراغ )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ull_پورٹ_Task_Has_FPUContext = pdTRUE;

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#جے_انت /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Clear_رکاوٹ_نقاب( UBaseType_t ux_New_نقاب_قدر )
{
    إذا( ux_New_نقاب_قدر == pdFALSE )
    {
        پورٹ_CLEAR_رکاوٹ_نقاب();
    }
}
/*-----------------------------------------------------------*/

UBaseType_t ux_پورٹ_سیٹ_رکاوٹ_نقاب( فراغ )
{
    uint32_t ulReturn;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    پورٹ_DISABLE_INTERRUPTS();

    إذا( پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر == ( uint32_t ) ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    وإلا
    {
        ulReturn = pdFALSE;
        پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر = ( uint32_t ) ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ );
        __asm متطاير ( "dsb sy     \n"
                         "isb sy     \n" ::: "memory" );
    }

    پورٹ_ENABLE_INTERRUPTS();

    أرجع ulReturn;
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ )
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
        configASSERT( پورٹ_ICCRPR_RUNNING_ترجیح_رجسٹر >= ( uint32_t ) ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ ) );

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
        configASSERT( ( پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر & پورٹ_ثنائی_نقطہ_بٹ ) <= پورٹ_MAX_ثنائی_نقطہ_قدر );
    }

#جے_انت /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/
