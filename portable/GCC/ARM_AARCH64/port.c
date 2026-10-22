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
#అన్తర్భావ <stdlib.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#నిర్వచితం_కాకపోతే config_అంతరాయం_CONTROLLER_పునాది_చిరునామా
    #దోషం "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined. See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_అంతరాయం_CONTROLLER_CPU_INTERFACE_స్థానభ్రంశం
    #దోషం "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_UNIQUE_అంతరాయం_PRIORITIES
    #దోషం "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_అమరిక_TICK_అంతరాయం
    #దోషం "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు /* configSETUP_TICK_INTERRUPT */

#నిర్వచితం_కాకపోతే config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు

#ఒకవేళ config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత == 0
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#అయితే_ముగింపు

#ఒకవేళ config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత > config_UNIQUE_అంతరాయం_PRIORITIES
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#అయితే_ముగింపు

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ఒకవేళ ( configMAX_PRIORITIES > 32 )
        #దోషం "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #అయితే_ముగింపు
#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#ఒకవేళ config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత <= ( config_UNIQUE_అంతరాయం_PRIORITIES / 2 )
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#అయితే_ముగింపు

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h. */
#నిర్వచితం_కాకపోతే config_CLEAR_TICK_అంతరాయం
    #నిర్వచించు config_CLEAR_TICK_అంతరాయం()
#అయితే_ముగింపు

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING          ( ( size_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#నిర్వచించు పోర్టు_UNMASK_విలువ                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#నిర్వచించు పోర్టు_NO_FLOATING_బిందువు_CONTEXT    ( ( దొంతర_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#నిర్వచించు పోర్టు_SP_ELx                       ( ( దొంతర_Type_t ) 0x01 )
#నిర్వచించు పోర్టు_SP_EL0                       ( ( దొంతర_Type_t ) 0x00 )

#ఒకవేళ defined( GUEST )
    #నిర్వచించు పోర్టు_EL1                      ( ( దొంతర_Type_t ) 0x04 )
    #నిర్వచించు పోర్టు_INITIAL_PSTATE           ( పోర్టు_EL1 | పోర్టు_SP_EL0 )
#లేకపోతే
    #నిర్వచించు పోర్టు_EL3                      ( ( దొంతర_Type_t ) 0x0c )
    /* At the time of writing, the BSP only supports EL3. */
    #నిర్వచించు పోర్టు_INITIAL_PSTATE           ( పోర్టు_EL3 | పోర్టు_SP_EL0 )
#అయితే_ముగింపు


/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#నిర్వచించు పోర్టు_ద్విమాన_బిందువు_బిట్లు      ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#నిర్వచించు పోర్టు_APSR_బహుళకం_బిట్లు_ముసుగు    ( 0x0C )

/* The I bit in the DAIF bits. */
#నిర్వచించు పోర్టు_DAIF_I                 ( 0x80 )

/* Macro to unmask all interrupt priorities. */
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు()                            \
    {                                                         \
        పోర్టు_DISABLE_INTERRUPTS();                             \
        పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు = పోర్టు_UNMASK_విలువ; \
        __asm అస్థిర ( "DSB SY     \n"                      \
                         "ISB SY     \n" );                   \
        పోర్టు_ENABLE_INTERRUPTS();                              \
    }

/* Hardware specifics used when sanity checking the configuration. */
#నిర్వచించు పోర్టు_అంతరాయం_ప్రాధాన్యత_రిజిస్టరు_స్థానభ్రంశం    0x400UL
#నిర్వచించు పోర్టు_MAX_8_బిట్టు_విలువ                       ( ( uint8_t ) 0xff )
#నిర్వచించు పోర్టు_బిట్టు_0_సమితి                             ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit registers.*/
#నిర్వచించు పోర్టు_FPU_రిజిస్టరు_పదాలు     ( 32 * 2 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
బాహ్య శూన్య v_పోర్టు_Restore_Task_Context( శూన్య );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
అస్థిర uint64_t ullCriticalNesting = 9999ULL;

/* Saved as part of the task context.  If ullPortTaskHasFPUContext is non-zero
 * then floating point context must be saved and restored for the task. */
uint64_t ull_పోర్టు_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint64_t ull_పోర్టు_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint64_t ull_పోర్టు_అంతరాయం_Nesting = 0;

/* Used in the ASM code. */
__attribute__( ( వాడిన ) ) స్థిరరాశి uint64_t ullICCEOIR = పోర్టు_ICCEOIR_చివర_యొక్క_అంతరాయం_రిజిస్టరు_చిరునామా;
__attribute__( ( వాడిన ) ) స్థిరరాశి uint64_t ullICCIAR = పోర్టు_ICCIAR_అంతరాయం_ACKNOWLEDGE_రిజిస్టరు_చిరునామా;
__attribute__( ( వాడిన ) ) స్థిరరాశి uint64_t ullICCPMR = పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు_చిరునామా;
__attribute__( ( వాడిన ) ) స్థిరరాశి uint64_t ull_Max_APIPriority_ముసుగు = ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First all the general purpose registers. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x0101010101010101ULL;        /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x0303030303030303ULL;        /* R3 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x0202020202020202ULL;        /* R2 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x0505050505050505ULL;        /* R5 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x0404040404040404ULL;        /* R4 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x0707070707070707ULL;        /* R7 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x0606060606060606ULL;        /* R6 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x0909090909090909ULL;        /* R9 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x0808080808080808ULL;        /* R8 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1111111111111111ULL;        /* R11 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1010101010101010ULL;        /* R10 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1313131313131313ULL;        /* R13 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1212121212121212ULL;        /* R12 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1515151515151515ULL;        /* R15 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1414141414141414ULL;        /* R14 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1717171717171717ULL;        /* R17 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1616161616161616ULL;        /* R16 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1919191919191919ULL;        /* R19 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x1818181818181818ULL;        /* R18 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2121212121212121ULL;        /* R21 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2020202020202020ULL;        /* R20 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2323232323232323ULL;        /* R23 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2222222222222222ULL;        /* R22 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2525252525252525ULL;        /* R25 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2424242424242424ULL;        /* R24 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2727272727272727ULL;        /* R27 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2626262626262626ULL;        /* R26 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2929292929292929ULL;        /* R29 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2828282828282828ULL;        /* R28 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00;         /* R30 - procedure call link register. */

    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_PSTATE;

    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం; /* Exception return address. */

    #ఒకవేళ ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_NESTING;

        /* The task will start without a floating point context.  A task that
         * uses the floating point hardware must call vPortTaskUsesFPU() before
         * executing any floating point instructions. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_FLOATING_బిందువు_CONTEXT;
    }
    #లేదావేళ ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_శిఖరం_యొక్క_దొంతర -= పోర్టు_FPU_రిజిస్టరు_పదాలు;
        memset( px_శిఖరం_యొక్క_దొంతర, 0x00, పోర్టు_FPU_రిజిస్టరు_పదాలు * పరిమాణం( దొంతర_Type_t ) );

        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_NESTING;

        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = pdTRUE;
        ull_పోర్టు_Task_Has_FPUContext = pdTRUE;
    }
    #లేకపోతే /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #దోషం "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #అయితే_ముగింపు /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    uint32_t ulAPSR;

    #ఒకవేళ ( configASSERT_DEFINED == 1 )
    {
        అస్థిర uint8_t uc_Original_ప్రాధాన్యత;
        అస్థిర uint8_t * స్థిరరాశి puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = ( అస్థిర uint8_t * స్థిరరాశి ) ( config_అంతరాయం_CONTROLLER_పునాది_చిరునామా + పోర్టు_అంతరాయం_ప్రాధాన్యత_రిజిస్టరు_స్థానభ్రంశం );
        అస్థిర uint8_t uc_Max_ప్రాధాన్యత_విలువ;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ప్రాధాన్యత = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = పోర్టు_MAX_8_బిట్టు_విలువ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ప్రాధాన్యత_విలువ = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Shift to the least significant bits. */
        అయితే( ( uc_Max_ప్రాధాన్యత_విలువ & పోర్టు_బిట్టు_0_సమితి ) != పోర్టు_బిట్టు_0_సమితి )
        {
            uc_Max_ప్రాధాన్యత_విలువ >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */

        configASSERT( uc_Max_ప్రాధాన్యత_విలువ >= పోర్టు_అత్యల్ప_అంతరాయం_ప్రాధాన్యత );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = uc_Original_ప్రాధాన్యత;
    }
    #అయితే_ముగింపు /* configASSERT_DEFINED */


    /* At the time of writing, the BSP only supports EL3. */
    __asm అస్థిర ( "MRS %0, CurrentEL" : "=r" ( ulAPSR ) );
    ulAPSR &= పోర్టు_APSR_బహుళకం_బిట్లు_ముసుగు;

    #ఒకవేళ defined( GUEST )
    #warning "Building for execution as a guest under XEN. THIS IS NOT A FULLY TESTED PATH."
        configASSERT( ulAPSR == పోర్టు_EL1 );

        ఒకవేళ( ulAPSR == పోర్టు_EL1 )
    #లేకపోతే
        configASSERT( ulAPSR == పోర్టు_EL3 );

        ఒకవేళ( ulAPSR == పోర్టు_EL3 )
    #అయితే_ముగింపు
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( పోర్టు_ICCBPR_ద్విమాన_బిందువు_రిజిస్టరు & పోర్టు_ద్విమాన_బిందువు_బిట్లు ) <= పోర్టు_MAX_ద్విమాన_బిందువు_విలువ );

        ఒకవేళ( ( పోర్టు_ICCBPR_ద్విమాన_బిందువు_రిజిస్టరు & పోర్టు_ద్విమాన_బిందువు_బిట్లు ) <= పోర్టు_MAX_ద్విమాన_బిందువు_విలువ )
        {
            /* Interrupts are turned off in the CPU itself to ensure a tick does
             * not execute while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing. */
            పోర్టు_DISABLE_INTERRUPTS();

            /* Start the timer that generates the tick ISR. */
            config_అమరిక_TICK_అంతరాయం();

            /* Start the first task executing. */
            v_పోర్టు_Restore_Task_Context();
        }
    }

    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ullCriticalNesting == 1000ULL );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ux_పోర్టు_సమితి_అంతరాయం_ముసుగు();

    /* Now interrupts are disabled ullCriticalNesting can be accessed
     * directly.  Increment ullCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ullCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ఒకవేళ( ullCriticalNesting == 1ULL )
    {
        configASSERT( ull_పోర్టు_అంతరాయం_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ullCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ullCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ఒకవేళ( ullCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            పోర్టు_CLEAR_అంతరాయం_ముసుగు();
        }
    }
}
/*-----------------------------------------------------------*/

శూన్య FreeRTOS_Tick_Handler( శూన్య )
{
    /* Must be the lowest possible priority. */
    #ఒకవేళ !defined( QEMU )
    {
        configASSERT( పోర్టు_ICCRPR_RUNNING_ప్రాధాన్యత_రిజిస్టరు == ( uint32_t ) ( పోర్టు_అత్యల్ప_USABLE_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) );
    }
    #అయితే_ముగింపు

    /* Interrupts should not be enabled before this point. */
    #ఒకవేళ ( configASSERT_DEFINED == 1 )
    {
        uint32_t ul_ముసుగు_బిట్లు;

        __asm అస్థిర ( "mrs %0, daif" : "=r" ( ul_ముసుగు_బిట్లు )::"memory" );
        configASSERT( ( ul_ముసుగు_బిట్లు & పోర్టు_DAIF_I ) != 0 );
    }
    #అయితే_ముగింపు /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు = ( uint32_t ) ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు );
    __asm అస్థిర ( "dsb sy     \n"
                     "isb sy     \n" ::: "memory" );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_అంతరాయం();
    పోర్టు_ENABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        ull_పోర్టు_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    పోర్టు_CLEAR_అంతరాయం_ముసుగు();
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_FPU_SUPPORT != 2 )

    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ull_పోర్టు_Task_Has_FPUContext = pdTRUE;

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#అయితే_ముగింపు /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( UBaseType_t ux_New_ముసుగు_విలువ )
{
    ఒకవేళ( ux_New_ముసుగు_విలువ == pdFALSE )
    {
        పోర్టు_CLEAR_అంతరాయం_ముసుగు();
    }
}
/*-----------------------------------------------------------*/

UBaseType_t ux_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య )
{
    uint32_t ulReturn;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    పోర్టు_DISABLE_INTERRUPTS();

    ఒకవేళ( పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు == ( uint32_t ) ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    లేకపోతే
    {
        ulReturn = pdFALSE;
        పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు = ( uint32_t ) ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు );
        __asm అస్థిర ( "dsb sy     \n"
                         "isb sy     \n" ::: "memory" );
    }

    పోర్టు_ENABLE_INTERRUPTS();

    తిరిగి ulReturn;
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configASSERT_DEFINED == 1 )

    శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య )
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
        configASSERT( పోర్టు_ICCRPR_RUNNING_ప్రాధాన్యత_రిజిస్టరు >= ( uint32_t ) ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) );

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
        configASSERT( ( పోర్టు_ICCBPR_ద్విమాన_బిందువు_రిజిస్టరు & పోర్టు_ద్విమాన_బిందువు_బిట్లు ) <= పోర్టు_MAX_ద్విమాన_బిందువు_విలువ );
    }

#అయితే_ముగింపు /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/
