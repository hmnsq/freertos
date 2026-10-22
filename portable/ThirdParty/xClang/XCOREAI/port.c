/* Copyright (c) 2019, XMOS Ltd, All rights reserved */

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव <string.h>
#अन्तर्भाव <xs1.h>
#अन्तर्भाव <xcore/hwtimer.h>
#अन्तर्भाव <xcore/triggerable.h>

स्थिर hwtimer_t xKernelTimer;

uint32_t ul_पत्तनम्_Yield_Required[ पत्तनम्_MAX_CORE_गणनम् ] = { pdFALSE };

/* When this port was designed, it was assumed that pxCurrentTCBs would always
   exist and that it would always be an array containing pointers to the current
   TCBs for each core. In v11, this is not the case; if we are only running one
   core, the symbol is pxCurrentTCB instead. Therefore, this port adds a layer
   of indirection - we populate this pointer-to-pointer in the RTOS kernel entry
   function below. This makes this port agnostic to whether it is running on SMP
   or singlecore RTOS. */
शून्य ** xcorePvtTCBContainer;

/*-----------------------------------------------------------*/

शून्य v_Intercore_व्यवधानम्_ISR( शून्य )
{
    पूर्णाङ्क xCoreID;

/*	debug_printf( "In KCALL: %u\n", ulData ); */
    xCoreID = rtos_core_id_get();
    ul_पत्तनम्_Yield_Required[ xCoreID ] = pdTRUE;
}
/*-----------------------------------------------------------*/

DEFINE_RTOS_व्यवधानम्_CALLBACK( pxKernelTimerISR, pv_दत्त )
{
    uint32_t ul_चरमः_Trigger;
    uint32_t ulNow;
    पूर्णाङ्क xCoreID;
    UBaseType_t ux_Saved_व्यवधानम्_स्थितिः;

    xCoreID = 0;

    configASSERT( xCoreID == rtos_core_id_get() );

    /* Need the next interrupt to be scheduled relative to
     * the current trigger time, rather than the current
     * time. */
    ul_चरमः_Trigger = hwtimer_get_trigger_time( xKernelTimer );

    /* Check to see if the ISR is late. If it is, we don't
     * want to schedule the next interrupt to be in the past. */
    ulNow = hwtimer_get_time( xKernelTimer );

    यदि( ulNow - ul_चरमः_Trigger >= configCPU_CLOCK_HZ / config_TICK_दरः_HZ )
    {
        ul_चरमः_Trigger = ulNow;
    }

    ul_चरमः_Trigger += configCPU_CLOCK_HZ / config_TICK_दरः_HZ;
    hwtimer_change_trigger_time( xKernelTimer, ul_चरमः_Trigger );

    #यदि configUPDATE_RTOS_TIME_FROM_TICK_ISR == 1
        rtos_time_increment( RTOS_TICK_PERIOD( config_TICK_दरः_HZ ) );
    #यदि_अन्तः

    ux_Saved_व्यवधानम्_स्थितिः = taskENTER_CRITICAL_FROM_ISR();

    यदि( xTaskIncrementTick() != pdFALSE )
    {
        ul_पत्तनम्_Yield_Required[ xCoreID ] = pdTRUE;
    }

    taskEXIT_CRITICAL_FROM_ISR( ux_Saved_व्यवधानम्_स्थितिः );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Yield_Other_Core( पूर्णाङ्क xOtherCoreID )
{
    पूर्णाङ्क xCoreID;

    /*
     * This function must be called from within a critical section.
     */

    xCoreID = rtos_core_id_get();

/*	debug_printf("%d->%d\n", xCoreID, xOtherCoreID); */

/*	debug_printf("Yield core %d from %d\n", xOtherCoreID, xCoreID ); */

    rtos_irq( xOtherCoreID, xCoreID );
}
/*-----------------------------------------------------------*/

स्थिर पूर्णाङ्क prvCoreInit( शून्य )
{
    पूर्णाङ्क xCoreID;

    xCoreID = rtos_core_पञ्जिकाकोशः();
    debug_printf( "Logical Core %d initializing as FreeRTOS Core %d\n", get_logical_core_id(), xCoreID );

    asm चञ्चल (
        "ldap r11, kexcept\n\t"
        "set kep, r11\n\t"
        :
        :
        : "r11"
        );

    rtos_irq_enable( config_सङ्ख्या_सम्बन्धि_CORES );

    /*
     * All threads wait here until all have enabled IRQs
     */
    यावत्( rtos_irq_ready() == pdFALSE )
    {
    }

    यदि( xCoreID == 0 )
    {
        uint32_t ulNow;
        ulNow = hwtimer_get_time( xKernelTimer );
/*		debug_printf( "The time is now (%u)\n", ulNow ); */

        ulNow += configCPU_CLOCK_HZ / config_TICK_दरः_HZ;

        triggerable_सज्जता_व्यवधानम्_callback( xKernelTimer, रिक्त, RTOS_व्यवधानम्_CALLBACK( pxKernelTimerISR ) );
        hwtimer_समुच्चयः_trigger_time( xKernelTimer, ulNow );
        triggerable_enable_trigger( xKernelTimer );
    }

    प्रत्यागम xCoreID;
}
/*-----------------------------------------------------------*/

DEFINE_RTOS_KERNEL_प्रविष्टिः( शून्य, v_पत्तनम्_Start_Scheduler_On_Core, शून्य )
{
    पूर्णाङ्क xCoreID;

    xCoreID = prvCoreInit();

    #यदि ( configUSE_CORE_INIT_HOOK == 1 )
    {
        बाह्य शून्य vApplicationCoreInitHook( आधारः_Type_t xCoreID );

        vApplicationCoreInitHook( xCoreID );
    }
    #यदि_अन्तः

    /* Populate the TCBContainer depending on whether we're singlecore or SMP */
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    {
        asm चञ्चल (
            "ldaw %0, dp[pxCurrentTCB]\n\t"
            : "=r"(xcorePvtTCBContainer)
            : /* no inputs */
            : /* no clobbers */
            );
    }
    #अन्यथा
    {
        asm चञ्चल (
            "ldaw %0, dp[pxCurrentTCBs]\n\t"
            : "=r"(xcorePvtTCBContainer)
            : /* no inputs */
            : /* no clobbers */
            );
    }

    #यदि_अन्तः

    debug_printf( "FreeRTOS Core %d initialized\n", xCoreID );

    /*
     * Restore the context of the first thread
     * to run and jump into it.
     */
    asm चञ्चल (
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
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /*debug_printf( "Top of stack was %p for task %p\n", pxTopOfStack, pxCode ); */

    /*
     * Grow the thread's stack by portTHREAD_CONTEXT_STACK_GROWTH
     * so we can push the context onto it.
     */
    px_शिखरम्_सम्बन्धि_राशिः -= पत्तनम्_THREAD_CONTEXT_राशिः_GROWTH;

    uint32_t dp;
    uint32_t cp;

    /*
     * We need to get the current CP and DP pointers.
     */
    asm चञ्चल (
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
    px_शिखरम्_सम्बन्धि_राशिः[ 1 ] = ( राशिः_Type_t ) px_संहिता;       /* SP[1]  := SPC */
    px_शिखरम्_सम्बन्धि_राशिः[ 2 ] = XS1_SR_IEBLE_आवरणम्
                        | XS1_SR_KEDI_आवरणम्;           /* SP[2]  := SSR */
    px_शिखरम्_सम्बन्धि_राशिः[ 3 ] = 0x00000000;                   /* SP[3]  := SED */
    px_शिखरम्_सम्बन्धि_राशिः[ 4 ] = 0x00000000;                   /* SP[4]  := ET */
    px_शिखरम्_सम्बन्धि_राशिः[ 5 ] = dp;                           /* SP[5]  := DP */
    px_शिखरम्_सम्बन्धि_राशिः[ 6 ] = cp;                           /* SP[6]  := CP */
    px_शिखरम्_सम्बन्धि_राशिः[ 7 ] = 0x00000000;                   /* SP[7]  := LR */
    px_शिखरम्_सम्बन्धि_राशिः[ 8 ] = ( राशिः_Type_t ) pvParameters; /* SP[8]  := R0 */
    px_शिखरम्_सम्बन्धि_राशिः[ 9 ] = 0x01010101;                   /* SP[9]  := R1 */
    px_शिखरम्_सम्बन्धि_राशिः[ 10 ] = 0x02020202;                  /* SP[10] := R2 */
    px_शिखरम्_सम्बन्धि_राशिः[ 11 ] = 0x03030303;                  /* SP[11] := R3 */
    px_शिखरम्_सम्बन्धि_राशिः[ 12 ] = 0x04040404;                  /* SP[12] := R4 */
    px_शिखरम्_सम्बन्धि_राशिः[ 13 ] = 0x05050505;                  /* SP[13] := R5 */
    px_शिखरम्_सम्बन्धि_राशिः[ 14 ] = 0x06060606;                  /* SP[14] := R6 */
    px_शिखरम्_सम्बन्धि_राशिः[ 15 ] = 0x07070707;                  /* SP[15] := R7 */
    px_शिखरम्_सम्बन्धि_राशिः[ 16 ] = 0x08080808;                  /* SP[16] := R8 */
    px_शिखरम्_सम्बन्धि_राशिः[ 17 ] = 0x09090909;                  /* SP[17] := R9 */
    px_शिखरम्_सम्बन्धि_राशिः[ 18 ] = 0x10101010;                  /* SP[18] := R10 */
    px_शिखरम्_सम्बन्धि_राशिः[ 19 ] = 0x11111111;                  /* SP[19] := R11 */
    px_शिखरम्_सम्बन्धि_राशिः[ 20 ] = 0x00000000;                  /* SP[20] := vH and vSR */
    स्मृतिं_पूरय( &px_शिखरम्_सम्बन्धि_राशिः[ 21 ], 0, 32 );             /* SP[21 - 28] := vR   */
    स्मृतिं_पूरय( &px_शिखरम्_सम्बन्धि_राशिः[ 29 ], 1, 32 );             /* SP[29 - 36] := vD   */
    स्मृतिं_पूरय( &px_शिखरम्_सम्बन्धि_राशिः[ 37 ], 2, 32 );             /* SP[37 - 44] := vC   */

    /*debug_printf( "Top of stack is now %p for task %p\n", pxTopOfStack, pxCode ); */

    /*
     * Returns the new top of the stack
     */
    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Start_SMPScheduler( शून्य );

/*
 * See header file for description.
 */
आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    यदि( ( config_सङ्ख्या_सम्बन्धि_CORES > पत्तनम्_MAX_CORE_गणनम् ) || ( config_सङ्ख्या_सम्बन्धि_CORES <= 0 ) )
    {
        प्रत्यागम pdFAIL;
    }

    rtos_locks_initialize();
    xKernelTimer = hwtimer_alloc();

    v_पत्तनम्_Start_SMPScheduler();

    प्रत्यागम pdPASS;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Do not implement. */
}
/*-----------------------------------------------------------*/
