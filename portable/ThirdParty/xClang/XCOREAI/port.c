/* Copyright (c) 2019, XMOS Ltd, All rights reserved */

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xs1.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xcore/hwtimer.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xcore/triggerable.h>

ਸਥਿਰ hwtimer_t xKernelTimer;

uint32_t ul_ਪੋਰਟ_Yield_Required[ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ ] = { pdFALSE };

/* When this port was designed, it was assumed that pxCurrentTCBs would always
   exist and that it would always be an array containing pointers to the current
   TCBs for each core. In v11, this is not the case; if we are only running one
   core, the symbol is pxCurrentTCB instead. Therefore, this port adds a layer
   of indirection - we populate this pointer-to-pointer in the RTOS kernel entry
   function below. This makes this port agnostic to whether it is running on SMP
   or singlecore RTOS. */
ਖਾਲੀ ** xcorePvtTCBContainer;

/*-----------------------------------------------------------*/

ਖਾਲੀ v_Intercore_ਰੁਕਾਵਟ_ISR( ਖਾਲੀ )
{
    ਪੂਰਨ xCoreID;

/*	debug_printf( "In KCALL: %u\n", ulData ); */
    xCoreID = rtos_core_id_get();
    ul_ਪੋਰਟ_Yield_Required[ xCoreID ] = pdTRUE;
}
/*-----------------------------------------------------------*/

DEFINE_RTOS_ਰੁਕਾਵਟ_CALLBACK( pxKernelTimerISR, pv_ਅੰਕੜੇ )
{
    uint32_t ul_ਆਖਰੀ_Trigger;
    uint32_t ulNow;
    ਪੂਰਨ xCoreID;
    UBaseType_t ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ;

    xCoreID = 0;

    configASSERT( xCoreID == rtos_core_id_get() );

    /* Need the next interrupt to be scheduled relative to
     * the current trigger time, rather than the current
     * time. */
    ul_ਆਖਰੀ_Trigger = hwtimer_get_trigger_ਸਮਾਂ( xKernelTimer );

    /* Check to see if the ISR is late. If it is, we don't
     * want to schedule the next interrupt to be in the past. */
    ulNow = hwtimer_get_ਸਮਾਂ( xKernelTimer );

    ਜੇ( ulNow - ul_ਆਖਰੀ_Trigger >= configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ )
    {
        ul_ਆਖਰੀ_Trigger = ulNow;
    }

    ul_ਆਖਰੀ_Trigger += configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ;
    hwtimer_change_trigger_ਸਮਾਂ( xKernelTimer, ul_ਆਖਰੀ_Trigger );

    #ਜੇ config_UPDATE_RTOS_ਸਮਾਂ_FROM_TICK_ISR == 1
        rtos_ਸਮਾਂ_increment( RTOS_TICK_PERIOD( config_TICK_ਦਰ_HZ ) );
    #ਜੇ_ਅੰਤ

    ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ = taskENTER_CRITICAL_FROM_ISR();

    ਜੇ( xTaskIncrementTick() != pdFALSE )
    {
        ul_ਪੋਰਟ_Yield_Required[ xCoreID ] = pdTRUE;
    }

    taskEXIT_CRITICAL_FROM_ISR( ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Yield_Other_Core( ਪੂਰਨ xOtherCoreID )
{
    ਪੂਰਨ xCoreID;

    /*
     * This function must be called from within a critical section.
     */

    xCoreID = rtos_core_id_get();

/*	debug_printf("%d->%d\n", xCoreID, xOtherCoreID); */

/*	debug_printf("Yield core %d from %d\n", xOtherCoreID, xCoreID ); */

    rtos_irq( xOtherCoreID, xCoreID );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਪੂਰਨ prvCoreInit( ਖਾਲੀ )
{
    ਪੂਰਨ xCoreID;

    xCoreID = rtos_core_ਰਜਿਸਟਰ();
    debug_printf( "Logical Core %d initializing as FreeRTOS Core %d\n", get_logical_core_id(), xCoreID );

    asm ਅਸਥਿਰ (
        "ldap r11, kexcept\n\t"
        "set kep, r11\n\t"
        :
        :
        : "r11"
        );

    rtos_irq_enable( config_ਸੰਖਿਆ_ਦਾ_CORES );

    /*
     * All threads wait here until all have enabled IRQs
     */
    ਜਦੋਂ( rtos_irq_ready() == pdFALSE )
    {
    }

    ਜੇ( xCoreID == 0 )
    {
        uint32_t ulNow;
        ulNow = hwtimer_get_ਸਮਾਂ( xKernelTimer );
/*		debug_printf( "The time is now (%u)\n", ulNow ); */

        ulNow += configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ;

        triggerable_ਤਿਆਰੀ_ਰੁਕਾਵਟ_callback( xKernelTimer, ਨਿਰਾ, RTOS_ਰੁਕਾਵਟ_CALLBACK( pxKernelTimerISR ) );
        hwtimer_ਸੈੱਟ_trigger_ਸਮਾਂ( xKernelTimer, ulNow );
        triggerable_enable_trigger( xKernelTimer );
    }

    ਵਾਪਸ xCoreID;
}
/*-----------------------------------------------------------*/

DEFINE_RTOS_KERNEL_ਇੰਦਰਾਜ( ਖਾਲੀ, v_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler_On_Core, ਖਾਲੀ )
{
    ਪੂਰਨ xCoreID;

    xCoreID = prvCoreInit();

    #ਜੇ ( configUSE_CORE_INIT_HOOK == 1 )
    {
        ਬਾਹਰੀ ਖਾਲੀ vApplicationCoreInitHook( ਅਧਾਰ_Type_t xCoreID );

        vApplicationCoreInitHook( xCoreID );
    }
    #ਜੇ_ਅੰਤ

    /* Populate the TCBContainer depending on whether we're singlecore or SMP */
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    {
        asm ਅਸਥਿਰ (
            "ldaw %0, dp[pxCurrentTCB]\n\t"
            : "=r"(xcorePvtTCBContainer)
            : /* no inputs */
            : /* no clobbers */
            );
    }
    #ਨਹੀਂਤਾਂ
    {
        asm ਅਸਥਿਰ (
            "ldaw %0, dp[pxCurrentTCBs]\n\t"
            : "=r"(xcorePvtTCBContainer)
            : /* no inputs */
            : /* no clobbers */
            );
    }

    #ਜੇ_ਅੰਤ

    debug_printf( "FreeRTOS Core %d initialized\n", xCoreID );

    /*
     * Restore the context of the first thread
     * to run and jump into it.
     */
    asm ਅਸਥਿਰ (
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
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /*debug_printf( "Top of stack was %p for task %p\n", pxTopOfStack, pxCode ); */

    /*
     * Grow the thread's stack by portTHREAD_CONTEXT_STACK_GROWTH
     * so we can push the context onto it.
     */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= ਪੋਰਟ_THREAD_CONTEXT_ਢੇਰ_GROWTH;

    uint32_t dp;
    uint32_t cp;

    /*
     * We need to get the current CP and DP pointers.
     */
    asm ਅਸਥਿਰ (
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
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 1 ] = ( ਢੇਰ_Type_t ) px_ਕੋਡ;       /* SP[1]  := SPC */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 2 ] = XS1_SR_IEBLE_ਨਕਾਬ
                        | XS1_SR_KEDI_ਨਕਾਬ;           /* SP[2]  := SSR */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 3 ] = 0x00000000;                   /* SP[3]  := SED */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 4 ] = 0x00000000;                   /* SP[4]  := ET */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 5 ] = dp;                           /* SP[5]  := DP */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 6 ] = cp;                           /* SP[6]  := CP */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 7 ] = 0x00000000;                   /* SP[7]  := LR */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 8 ] = ( ਢੇਰ_Type_t ) pvParameters; /* SP[8]  := R0 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 9 ] = 0x01010101;                   /* SP[9]  := R1 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 10 ] = 0x02020202;                  /* SP[10] := R2 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 11 ] = 0x03030303;                  /* SP[11] := R3 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 12 ] = 0x04040404;                  /* SP[12] := R4 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 13 ] = 0x05050505;                  /* SP[13] := R5 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 14 ] = 0x06060606;                  /* SP[14] := R6 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 15 ] = 0x07070707;                  /* SP[15] := R7 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 16 ] = 0x08080808;                  /* SP[16] := R8 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 17 ] = 0x09090909;                  /* SP[17] := R9 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 18 ] = 0x10101010;                  /* SP[18] := R10 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 19 ] = 0x11111111;                  /* SP[19] := R11 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 20 ] = 0x00000000;                  /* SP[20] := vH and vSR */
    memset( &px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 21 ], 0, 32 );             /* SP[21 - 28] := vR   */
    memset( &px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 29 ], 1, 32 );             /* SP[29 - 36] := vD   */
    memset( &px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 37 ], 2, 32 );             /* SP[37 - 44] := vC   */

    /*debug_printf( "Top of stack is now %p for task %p\n", pxTopOfStack, pxCode ); */

    /*
     * Returns the new top of the stack
     */
    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_SMPScheduler( ਖਾਲੀ );

/*
 * See header file for description.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਜੇ( ( config_ਸੰਖਿਆ_ਦਾ_CORES > ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ ) || ( config_ਸੰਖਿਆ_ਦਾ_CORES <= 0 ) )
    {
        ਵਾਪਸ pdFAIL;
    }

    rtos_locks_initialize();
    xKernelTimer = hwtimer_alloc();

    v_ਪੋਰਟ_ਸ਼ੁਰੂ_SMPScheduler();

    ਵਾਪਸ pdPASS;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Do not implement. */
}
/*-----------------------------------------------------------*/
