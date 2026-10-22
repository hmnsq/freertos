/* Copyright (c) 2019, XMOS Ltd, All rights reserved */

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن <string.h>
#ضمن <xs1.h>
#ضمن <xcore/hwtimer.h>
#ضمن <xcore/triggerable.h>

ساكن hwtimer_t xKernelTimer;

uint32_t ul_پورٽ_Yield_Required[ پورٽ_MAX_CORE_ڳڻپ ] = { pdFALSE };

/* When this port was designed, it was assumed that pxCurrentTCBs would always
   exist and that it would always be an array containing pointers to the current
   TCBs for each core. In v11, this is not the case; if we are only running one
   core, the symbol is pxCurrentTCB instead. Therefore, this port adds a layer
   of indirection - we populate this pointer-to-pointer in the RTOS kernel entry
   function below. This makes this port agnostic to whether it is running on SMP
   or singlecore RTOS. */
فراغ ** xcorePvtTCBContainer;

/*-----------------------------------------------------------*/

فراغ v_Intercore_مداخلت_ISR( فراغ )
{
    صحيح xCoreID;

/*	debug_printf( "In KCALL: %u\n", ulData ); */
    xCoreID = rtos_core_id_get();
    ul_پورٽ_Yield_Required[ xCoreID ] = pdTRUE;
}
/*-----------------------------------------------------------*/

DEFINE_RTOS_مداخلت_CALLBACK( pxKernelTimerISR, pv_معلومات )
{
    uint32_t ul_آخري_Trigger;
    uint32_t ulNow;
    صحيح xCoreID;
    UBaseType_t ux_Saved_مداخلت_حالت;

    xCoreID = 0;

    configASSERT( xCoreID == rtos_core_id_get() );

    /* Need the next interrupt to be scheduled relative to
     * the current trigger time, rather than the current
     * time. */
    ul_آخري_Trigger = hwtimer_get_trigger_وقت( xKernelTimer );

    /* Check to see if the ISR is late. If it is, we don't
     * want to schedule the next interrupt to be in the past. */
    ulNow = hwtimer_get_وقت( xKernelTimer );

    إذا( ulNow - ul_آخري_Trigger >= configCPU_CLOCK_HZ / config_TICK_شرح_HZ )
    {
        ul_آخري_Trigger = ulNow;
    }

    ul_آخري_Trigger += configCPU_CLOCK_HZ / config_TICK_شرح_HZ;
    hwtimer_change_trigger_وقت( xKernelTimer, ul_آخري_Trigger );

    #إذا config_UPDATE_RTOS_وقت_FROM_TICK_ISR == 1
        rtos_وقت_increment( RTOS_TICK_PERIOD( config_TICK_شرح_HZ ) );
    #جيڪڏهن_پورو

    ux_Saved_مداخلت_حالت = taskENTER_CRITICAL_FROM_ISR();

    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ul_پورٽ_Yield_Required[ xCoreID ] = pdTRUE;
    }

    taskEXIT_CRITICAL_FROM_ISR( ux_Saved_مداخلت_حالت );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Yield_Other_Core( صحيح xOtherCoreID )
{
    صحيح xCoreID;

    /*
     * This function must be called from within a critical section.
     */

    xCoreID = rtos_core_id_get();

/*	debug_printf("%d->%d\n", xCoreID, xOtherCoreID); */

/*	debug_printf("Yield core %d from %d\n", xOtherCoreID, xCoreID ); */

    rtos_irq( xOtherCoreID, xCoreID );
}
/*-----------------------------------------------------------*/

ساكن صحيح prvCoreInit( فراغ )
{
    صحيح xCoreID;

    xCoreID = rtos_core_رجسٽر();
    debug_printf( "Logical Core %d initializing as FreeRTOS Core %d\n", get_logical_core_id(), xCoreID );

    asm متطاير (
        "ldap r11, kexcept\n\t"
        "set kep, r11\n\t"
        :
        :
        : "r11"
        );

    rtos_irq_enable( config_عدد_جو_CORES );

    /*
     * All threads wait here until all have enabled IRQs
     */
    طالما( rtos_irq_ready() == pdFALSE )
    {
    }

    إذا( xCoreID == 0 )
    {
        uint32_t ulNow;
        ulNow = hwtimer_get_وقت( xKernelTimer );
/*		debug_printf( "The time is now (%u)\n", ulNow ); */

        ulNow += configCPU_CLOCK_HZ / config_TICK_شرح_HZ;

        triggerable_تياري_مداخلت_callback( xKernelTimer, عدم, RTOS_مداخلت_CALLBACK( pxKernelTimerISR ) );
        hwtimer_سيٽ_trigger_وقت( xKernelTimer, ulNow );
        triggerable_enable_trigger( xKernelTimer );
    }

    أرجع xCoreID;
}
/*-----------------------------------------------------------*/

DEFINE_RTOS_KERNEL_داخلا( فراغ, v_پورٽ_شروعات_Scheduler_On_Core, فراغ )
{
    صحيح xCoreID;

    xCoreID = prvCoreInit();

    #إذا ( configUSE_CORE_INIT_HOOK == 1 )
    {
        خارجي فراغ vApplicationCoreInitHook( بنياد_Type_t xCoreID );

        vApplicationCoreInitHook( xCoreID );
    }
    #جيڪڏهن_پورو

    /* Populate the TCBContainer depending on whether we're singlecore or SMP */
    #إذا ( config_عدد_جو_CORES == 1 )
    {
        asm متطاير (
            "ldaw %0, dp[pxCurrentTCB]\n\t"
            : "=r"(xcorePvtTCBContainer)
            : /* no inputs */
            : /* no clobbers */
            );
    }
    #وإلا
    {
        asm متطاير (
            "ldaw %0, dp[pxCurrentTCBs]\n\t"
            : "=r"(xcorePvtTCBContainer)
            : /* no inputs */
            : /* no clobbers */
            );
    }

    #جيڪڏهن_پورو

    debug_printf( "FreeRTOS Core %d initialized\n", xCoreID );

    /*
     * Restore the context of the first thread
     * to run and jump into it.
     */
    asm متطاير (
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
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /*debug_printf( "Top of stack was %p for task %p\n", pxTopOfStack, pxCode ); */

    /*
     * Grow the thread's stack by portTHREAD_CONTEXT_STACK_GROWTH
     * so we can push the context onto it.
     */
    px_چوٽي_جو_ڍير -= پورٽ_THREAD_CONTEXT_ڍير_GROWTH;

    uint32_t dp;
    uint32_t cp;

    /*
     * We need to get the current CP and DP pointers.
     */
    asm متطاير (
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
    px_چوٽي_جو_ڍير[ 1 ] = ( ڍير_Type_t ) px_ڪوڊ;       /* SP[1]  := SPC */
    px_چوٽي_جو_ڍير[ 2 ] = XS1_SR_IEBLE_نقاب
                        | XS1_SR_KEDI_نقاب;           /* SP[2]  := SSR */
    px_چوٽي_جو_ڍير[ 3 ] = 0x00000000;                   /* SP[3]  := SED */
    px_چوٽي_جو_ڍير[ 4 ] = 0x00000000;                   /* SP[4]  := ET */
    px_چوٽي_جو_ڍير[ 5 ] = dp;                           /* SP[5]  := DP */
    px_چوٽي_جو_ڍير[ 6 ] = cp;                           /* SP[6]  := CP */
    px_چوٽي_جو_ڍير[ 7 ] = 0x00000000;                   /* SP[7]  := LR */
    px_چوٽي_جو_ڍير[ 8 ] = ( ڍير_Type_t ) pvParameters; /* SP[8]  := R0 */
    px_چوٽي_جو_ڍير[ 9 ] = 0x01010101;                   /* SP[9]  := R1 */
    px_چوٽي_جو_ڍير[ 10 ] = 0x02020202;                  /* SP[10] := R2 */
    px_چوٽي_جو_ڍير[ 11 ] = 0x03030303;                  /* SP[11] := R3 */
    px_چوٽي_جو_ڍير[ 12 ] = 0x04040404;                  /* SP[12] := R4 */
    px_چوٽي_جو_ڍير[ 13 ] = 0x05050505;                  /* SP[13] := R5 */
    px_چوٽي_جو_ڍير[ 14 ] = 0x06060606;                  /* SP[14] := R6 */
    px_چوٽي_جو_ڍير[ 15 ] = 0x07070707;                  /* SP[15] := R7 */
    px_چوٽي_جو_ڍير[ 16 ] = 0x08080808;                  /* SP[16] := R8 */
    px_چوٽي_جو_ڍير[ 17 ] = 0x09090909;                  /* SP[17] := R9 */
    px_چوٽي_جو_ڍير[ 18 ] = 0x10101010;                  /* SP[18] := R10 */
    px_چوٽي_جو_ڍير[ 19 ] = 0x11111111;                  /* SP[19] := R11 */
    px_چوٽي_جو_ڍير[ 20 ] = 0x00000000;                  /* SP[20] := vH and vSR */
    memset( &px_چوٽي_جو_ڍير[ 21 ], 0, 32 );             /* SP[21 - 28] := vR   */
    memset( &px_چوٽي_جو_ڍير[ 29 ], 1, 32 );             /* SP[29 - 36] := vD   */
    memset( &px_چوٽي_جو_ڍير[ 37 ], 2, 32 );             /* SP[37 - 44] := vC   */

    /*debug_printf( "Top of stack is now %p for task %p\n", pxTopOfStack, pxCode ); */

    /*
     * Returns the new top of the stack
     */
    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_شروعات_SMPScheduler( فراغ );

/*
 * See header file for description.
 */
بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    إذا( ( config_عدد_جو_CORES > پورٽ_MAX_CORE_ڳڻپ ) || ( config_عدد_جو_CORES <= 0 ) )
    {
        أرجع pdFAIL;
    }

    rtos_locks_initialize();
    xKernelTimer = hwtimer_alloc();

    v_پورٽ_شروعات_SMPScheduler();

    أرجع pdPASS;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Do not implement. */
}
/*-----------------------------------------------------------*/
