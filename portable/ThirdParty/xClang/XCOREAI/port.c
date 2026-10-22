/* Copyright (c) 2019, XMOS Ltd, All rights reserved */

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <xs1.h>
#অন্তর্ভাব <xcore/hwtimer.h>
#অন্তর্ভাব <xcore/triggerable.h>

স্থির hwtimer_t xKernelTimer;

uint32_t ulPortYieldRequired[ port_MAX_CORE_গুনতি ] = { pdFALSE };

/* When this port was designed, it was assumed that pxCurrentTCBs would always
   exist and that it would always be an array containing pointers to the current
   TCBs for each core. In v11, this is not the case; if we are only running one
   core, the symbol is pxCurrentTCB instead. Therefore, this port adds a layer
   of indirection - we populate this pointer-to-pointer in the RTOS kernel entry
   function below. This makes this port agnostic to whether it is running on SMP
   or singlecore RTOS. */
শূন্য ** xcorePvtTCBContainer;

/*-----------------------------------------------------------*/

শূন্য vIntercoreInterruptISR( শূন্য )
{
    পূর্ণাঙ্ক xCoreID;

/*	debug_printf( "In KCALL: %u\n", ulData ); */
    xCoreID = rtos_core_id_get();
    ulPortYieldRequired[ xCoreID ] = pdTRUE;
}
/*-----------------------------------------------------------*/

DEFINE_RTOS_INTERRUPT_CALLBACK( pxKernelTimerISR, pvData )
{
    uint32_t ulLastTrigger;
    uint32_t ulNow;
    পূর্ণাঙ্ক xCoreID;
    UBaseType_t uxSavedInterruptStatus;

    xCoreID = 0;

    configASSERT( xCoreID == rtos_core_id_get() );

    /* Need the next interrupt to be scheduled relative to
     * the current trigger time, rather than the current
     * time. */
    ulLastTrigger = hwtimer_get_trigger_time( xKernelTimer );

    /* Check to see if the ISR is late. If it is, we don't
     * want to schedule the next interrupt to be in the past. */
    ulNow = hwtimer_get_time( xKernelTimer );

    যদি( ulNow - ulLastTrigger >= configCPU_CLOCK_HZ / configTICK_RATE_HZ )
    {
        ulLastTrigger = ulNow;
    }

    ulLastTrigger += configCPU_CLOCK_HZ / configTICK_RATE_HZ;
    hwtimer_change_trigger_time( xKernelTimer, ulLastTrigger );

    #যদি configUPDATE_RTOS_TIME_FROM_TICK_ISR == 1
        rtos_time_increment( RTOS_TICK_PERIOD( configTICK_RATE_HZ ) );
    #endif

    uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();

    যদি( xTaskIncrementTick() != pdFALSE )
    {
        ulPortYieldRequired[ xCoreID ] = pdTRUE;
    }

    taskEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
}
/*-----------------------------------------------------------*/

শূন্য vPortYieldOtherCore( পূর্ণাঙ্ক xOtherCoreID )
{
    পূর্ণাঙ্ক xCoreID;

    /*
     * This function must be called from within a critical section.
     */

    xCoreID = rtos_core_id_get();

/*	debug_printf("%d->%d\n", xCoreID, xOtherCoreID); */

/*	debug_printf("Yield core %d from %d\n", xOtherCoreID, xCoreID ); */

    rtos_irq( xOtherCoreID, xCoreID );
}
/*-----------------------------------------------------------*/

স্থির পূর্ণাঙ্ক prvCoreInit( শূন্য )
{
    পূর্ণাঙ্ক xCoreID;

    xCoreID = rtos_core_register();
    debug_printf( "Logical Core %d initializing as FreeRTOS Core %d\n", get_logical_core_id(), xCoreID );

    asm চঞ্চল (
        "ldap r11, kexcept\n\t"
        "set kep, r11\n\t"
        :
        :
        : "r11"
        );

    rtos_irq_enable( config_সংখ্যা_OF_CORES );

    /*
     * All threads wait here until all have enabled IRQs
     */
    যাবত্( rtos_irq_ready() == pdFALSE )
    {
    }

    যদি( xCoreID == 0 )
    {
        uint32_t ulNow;
        ulNow = hwtimer_get_time( xKernelTimer );
/*		debug_printf( "The time is now (%u)\n", ulNow ); */

        ulNow += configCPU_CLOCK_HZ / configTICK_RATE_HZ;

        triggerable_setup_interrupt_callback( xKernelTimer, রিক্ত, RTOS_INTERRUPT_CALLBACK( pxKernelTimerISR ) );
        hwtimer_set_trigger_time( xKernelTimer, ulNow );
        triggerable_enable_trigger( xKernelTimer );
    }

    প্রত্যাগম xCoreID;
}
/*-----------------------------------------------------------*/

DEFINE_RTOS_KERNEL_ENTRY( শূন্য, vPortStartSchedulerOnCore, শূন্য )
{
    পূর্ণাঙ্ক xCoreID;

    xCoreID = prvCoreInit();

    #যদি ( configUSE_CORE_INIT_HOOK == 1 )
    {
        বাহ্য শূন্য vApplicationCoreInitHook( BaseType_t xCoreID );

        vApplicationCoreInitHook( xCoreID );
    }
    #endif

    /* Populate the TCBContainer depending on whether we're singlecore or SMP */
    #যদি ( config_সংখ্যা_OF_CORES == 1 )
    {
        asm চঞ্চল (
            "ldaw %0, dp[pxCurrentTCB]\n\t"
            : "=r"(xcorePvtTCBContainer)
            : /* no inputs */
            : /* no clobbers */
            );
    }
    #অন্যথা
    {
        asm চঞ্চল (
            "ldaw %0, dp[pxCurrentTCBs]\n\t"
            : "=r"(xcorePvtTCBContainer)
            : /* no inputs */
            : /* no clobbers */
            );
    }

    #endif

    debug_printf( "FreeRTOS Core %d initialized\n", xCoreID );

    /*
     * Restore the context of the first thread
     * to run and jump into it.
     */
    asm চঞ্চল (
        "mov r6, %0\n\t"                       /* R6 must be the FreeRTOS core ID. In singlecore this is always 0. */
        "ldw r5, dp[xcorePvtTCBContainer]\n\t" /* R5 must be the TCB list which is indexed by R6 */
        "bu _freertos_restore_ctx\n\t"
        :                                /* no outputs */
        : "r" ( xCoreID )
        : "r5", "r6"
        );
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/* Public functions required by all ports below:             */
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    /*debug_printf( "Top of stack was %p for task %p\n", pxTopOfStack, pxCode ); */

    /*
     * Grow the thread's stack by portTHREAD_CONTEXT_STACK_GROWTH
     * so we can push the context onto it.
     */
    px_শীর্ষ_Of_স্তূপ -= port_THREAD_CONTEXT_স্তূপ_GROWTH;

    uint32_t dp;
    uint32_t cp;

    /*
     * We need to get the current CP and DP pointers.
     */
    asm চঞ্চল (
        "ldaw r11, cp[0]\n\t"      /* get CP into R11 */
        "mov %0, r11\n\t"          /* get R11 (CP) into cp */
        "ldaw r11, dp[0]\n\t"      /* get DP into R11 */
        "mov %1, r11\n\t"          /* get R11 (DP) into dp */
        : "=r" ( cp ), "=r" ( dp ) /* output 0 is cp, output 1 is dp */
        :                          /* there are no inputs */
        : "r11"                    /* R11 gets clobbered */
        );

    /*
     * Push the thread context onto the stack.
     * Saved PC will point to the new thread's
     * entry pointer.
     * Interrupts will default to enabled.
     * KEDI is also set to enable dual issue mode
     * upon kernel entry.
     */
    px_শীর্ষ_Of_স্তূপ[ 1 ] = ( স্তূপ_Type_t ) pxCode;       /* SP[1]  := SPC */
    px_শীর্ষ_Of_স্তূপ[ 2 ] = XS1_SR_IEBLE_MASK
                        | XS1_SR_KEDI_MASK;           /* SP[2]  := SSR */
    px_শীর্ষ_Of_স্তূপ[ 3 ] = 0x00000000;                   /* SP[3]  := SED */
    px_শীর্ষ_Of_স্তূপ[ 4 ] = 0x00000000;                   /* SP[4]  := ET */
    px_শীর্ষ_Of_স্তূপ[ 5 ] = dp;                           /* SP[5]  := DP */
    px_শীর্ষ_Of_স্তূপ[ 6 ] = cp;                           /* SP[6]  := CP */
    px_শীর্ষ_Of_স্তূপ[ 7 ] = 0x00000000;                   /* SP[7]  := LR */
    px_শীর্ষ_Of_স্তূপ[ 8 ] = ( স্তূপ_Type_t ) pvParameters; /* SP[8]  := R0 */
    px_শীর্ষ_Of_স্তূপ[ 9 ] = 0x01010101;                   /* SP[9]  := R1 */
    px_শীর্ষ_Of_স্তূপ[ 10 ] = 0x02020202;                  /* SP[10] := R2 */
    px_শীর্ষ_Of_স্তূপ[ 11 ] = 0x03030303;                  /* SP[11] := R3 */
    px_শীর্ষ_Of_স্তূপ[ 12 ] = 0x04040404;                  /* SP[12] := R4 */
    px_শীর্ষ_Of_স্তূপ[ 13 ] = 0x05050505;                  /* SP[13] := R5 */
    px_শীর্ষ_Of_স্তূপ[ 14 ] = 0x06060606;                  /* SP[14] := R6 */
    px_শীর্ষ_Of_স্তূপ[ 15 ] = 0x07070707;                  /* SP[15] := R7 */
    px_শীর্ষ_Of_স্তূপ[ 16 ] = 0x08080808;                  /* SP[16] := R8 */
    px_শীর্ষ_Of_স্তূপ[ 17 ] = 0x09090909;                  /* SP[17] := R9 */
    px_শীর্ষ_Of_স্তূপ[ 18 ] = 0x10101010;                  /* SP[18] := R10 */
    px_শীর্ষ_Of_স্তূপ[ 19 ] = 0x11111111;                  /* SP[19] := R11 */
    px_শীর্ষ_Of_স্তূপ[ 20 ] = 0x00000000;                  /* SP[20] := vH and vSR */
    memset( &px_শীর্ষ_Of_স্তূপ[ 21 ], 0, 32 );             /* SP[21 - 28] := vR   */
    memset( &px_শীর্ষ_Of_স্তূপ[ 29 ], 1, 32 );             /* SP[29 - 36] := vD   */
    memset( &px_শীর্ষ_Of_স্তূপ[ 37 ], 2, 32 );             /* SP[37 - 44] := vC   */

    /*debug_printf( "Top of stack is now %p for task %p\n", pxTopOfStack, pxCode ); */

    /*
     * Returns the new top of the stack
     */
    প্রত্যাগম px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

শূন্য vPortStartSMPScheduler( শূন্য );

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( শূন্য )
{
    যদি( ( config_সংখ্যা_OF_CORES > port_MAX_CORE_গুনতি ) || ( config_সংখ্যা_OF_CORES <= 0 ) )
    {
        প্রত্যাগম pdFAIL;
    }

    rtos_locks_initialize();
    xKernelTimer = hwtimer_alloc();

    vPortStartSMPScheduler();

    প্রত্যাগম pdPASS;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Do not implement. */
}
/*-----------------------------------------------------------*/
