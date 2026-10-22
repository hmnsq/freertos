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
#ضمن <string.h>

/* TriCore specific includes. */
#ضمن <tc1782.h>
#ضمن <machine/intrinsics.h>
#ضمن <machine/cint.h>
#ضمن <machine/wdtcon.h>

/* Kernel includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "list.h"

#إذا config_CHECK_FOR_ڈھیر_حد_توں_ودھ > 0
    #غلطی "Stack checking cannot be used with this port, as, unlike most ports, the pxTopOfStack member of the TCB is consumed CSA.  CSA starvation, loosely equivalent to stack overflow, will result in a trap exception."
    /* The stack pointer is accessible using portCSA_TO_ADDRESS( portCSA_TO_ADDRESS( pxCurrentTCB->pxTopOfStack )[ 0 ] )[ 2 ]; */
#جے_انت /* configCHECK_FOR_STACK_OVERFLOW */


/*-----------------------------------------------------------*/

/* System register Definitions. */
#تعریف_کرو پورٹ_SYSTEM_پروگرام_حالت_لفظ                  ( 0x000008FFUL ) /* Supervisor Mode, MPU Register Set 0 and Call Depth Counting disabled. */
#تعریف_کرو پورٹ_INITIAL_PRIVILEGED_پروگرام_حالت_لفظ      ( 0x000014FFUL ) /* IO Level 1, MPU Register Set 1 and Call Depth Counting disabled. */
#تعریف_کرو پورٹ_INITIAL_UNPRIVILEGED_پروگرام_حالت_لفظ    ( 0x000010FFUL ) /* IO Level 0, MPU Register Set 1 and Call Depth Counting disabled. */
#تعریف_کرو پورٹ_INITIAL_PCXI_اتلا_CONTEXT_لفظ             ( 0x00C00000UL ) /* The lower 20 bits identify the CSA address. */
#تعریف_کرو پورٹ_INITIAL_SYSCON                              ( 0x00000000UL ) /* MPU Disable. */

/* CSA manipulation macros. */
#تعریف_کرو پورٹ_CSA_FCX_نقاب                                ( 0x000FFFFFUL )

/* OS Interrupt and Trap mechanisms. */
#تعریف_کرو پورٹ_RESTORE_PSW_نقاب                            ( ~( 0x000000FFUL ) )
#تعریف_کرو پورٹ_SYSCALL_TRAP                                ( 6 )

/* Each CSA contains 16 words of data. */
#تعریف_کرو پورٹ_عدد_الفاظ_وچ_CSA                            ( 16 )

/* The interrupt enable bit in the PCP_SRC register. */
#تعریف_کرو پورٹ_ENABLE_CPU_رکاوٹ                        ( 1U << 12U )
/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
ساكن فراغ prvSystemTickHandler( صحيح ) __attribute__( ( longcall ) );
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );

/*
 * Trap handler for yields.
 */
ساكن فراغ prvTrapYield( صحيح iTrapIdentification );

/*
 * Priority 1 interrupt handler for yields pended from an interrupt.
 */
ساكن فراغ prv_رکاوٹ_Yield( صحيح iTrapIdentification );

/*-----------------------------------------------------------*/

/* This reference is required by the save/restore context macros. */
خارجي متطاير uint32_t * pxCurrentTCB;

/* Precalculate the compare match value at compile time. */
ساكن ثابت uint32_t ul_Compare_میل_قدر = ( configPERIPHERAL_CLOCK_HZ / config_TICK_شرح_HZ );

/*-----------------------------------------------------------*/

ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    uint32_t * pul_اتلا_CSA = عدم;
    uint32_t * pul_ہیٹھلا_CSA = عدم;

    /* 16 Address Registers (4 Address registers are global), 16 Data
     * Registers, and 3 System Registers.
     *
     * There are 3 registers that track the CSAs.
     *  FCX points to the head of globally free set of CSAs.
     *  PCX for the task needs to point to Lower->Upper->NULL arrangement.
     *  LCX points to the last free CSA so that corrective action can be taken.
     *
     * Need two CSAs to store the context of a task.
     *  The upper context contains D8-D15, A10-A15, PSW and PCXI->NULL.
     *  The lower context contains D0-D7, A2-A7, A11 and PCXI->UpperContext.
     *  The pxCurrentTCB->pxTopOfStack points to the Lower Context RSLCX matching the initial BISR.
     *  The Lower Context points to the Upper Context ready for the return from the interrupt handler.
     *
     * The Real stack pointer for the task is stored in the A10 which is restored
     * with the upper context. */

    /* Have to disable interrupts here because the CSAs are going to be
     * manipulated. */
    پورٹ_ENTER_CRITICAL();
    {
        /* DSync to ensure that buffering is not a problem. */
        _dsync();

        /* Consume two free CSAs. */
        pul_ہیٹھلا_CSA = پورٹ_CSA_منزل_پتہ( __MFCR( $FCX ) );

        إذا( عدم != pul_ہیٹھلا_CSA )
        {
            /* The Lower Links to the Upper. */
            pul_اتلا_CSA = پورٹ_CSA_منزل_پتہ( pul_ہیٹھلا_CSA[ 0 ] );
        }

        /* Check that we have successfully reserved two CSAs. */
        إذا( ( عدم != pul_ہیٹھلا_CSA ) && ( عدم != pul_اتلا_CSA ) )
        {
            /* Remove the two consumed CSAs from the free CSA list. */
            _disable();
            _dsync();
            _mtcr( $FCX, pul_اتلا_CSA[ 0 ] );
            _isync();
            _enable();
        }
        وإلا
        {
            /* Simply trigger a context list depletion trap. */
            _svlcx();
        }
    }
    پورٹ_EXIT_CRITICAL();

    /* Clear the upper CSA. */
    memset( pul_اتلا_CSA, 0, پورٹ_عدد_الفاظ_وچ_CSA * حجم( uint32_t ) );

    /* Upper Context. */
    pul_اتلا_CSA[ 2 ] = ( uint32_t ) px_چوٹی_دا_ڈھیر;      /* A10; Stack Return aka Stack Pointer */
    pul_اتلا_CSA[ 1 ] = پورٹ_SYSTEM_پروگرام_حالت_لفظ; /* PSW  */

    /* Clear the lower CSA. */
    memset( pul_ہیٹھلا_CSA, 0, پورٹ_عدد_الفاظ_وچ_CSA * حجم( uint32_t ) );

    /* Lower Context. */
    pul_ہیٹھلا_CSA[ 8 ] = ( uint32_t ) pvParameters; /* A4;  Address Type Parameter Register */
    pul_ہیٹھلا_CSA[ 1 ] = ( uint32_t ) px_کوڈ;       /* A11; Return Address aka RA */

    /* PCXI pointing to the Upper context. */
    pul_ہیٹھلا_CSA[ 0 ] = ( پورٹ_INITIAL_PCXI_اتلا_CONTEXT_لفظ | ( uint32_t ) پورٹ_پتہ_منزل_CSA( pul_اتلا_CSA ) );

    /* Save the link to the CSA in the top of stack. */
    px_چوٹی_دا_ڈھیر = ( uint32_t * ) پورٹ_پتہ_منزل_CSA( pul_ہیٹھلا_CSA );

    /* DSync to ensure that buffering is not a problem. */
    _dsync();

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

int32_t x_پورٹ_شروع_Scheduler( فراغ )
{
    خارجي فراغ vTrapInstallHandlers( فراغ );
    uint32_t ulMFCR = 0UL;
    uint32_t * pul_اتلا_CSA = عدم;
    uint32_t * pul_ہیٹھلا_CSA = عدم;

    /* Interrupts at or below configMAX_SYSCALL_INTERRUPT_PRIORITY are disable
     * when this function is called. */

    /* Set-up the timer interrupt. */
    prv_تیاری_Timer_رکاوٹ();

    /* Install the Trap Handlers. */
    vTrapInstallHandlers();

    /* Install the Syscall Handler for yield calls. */
    إذا( 0 == _install_trap_handler( پورٹ_SYSCALL_TRAP, prvTrapYield ) )
    {
        /* Failed to install the yield handler, force an assert. */
        configASSERT( ( ( متطاير فراغ * ) عدم ) );
    }

    /* Enable then install the priority 1 interrupt for pending context
     * switches from an ISR.  See mod_SRC in the TriCore manual. */
    CPU_SRC0.reg = ( پورٹ_ENABLE_CPU_رکاوٹ ) | ( config_KERNEL_YIELD_ترجیح );

    إذا( 0 == _install_int_handler( config_KERNEL_YIELD_ترجیح, prv_رکاوٹ_Yield, 0 ) )
    {
        /* Failed to install the yield handler, force an assert. */
        configASSERT( ( ( متطاير فراغ * ) عدم ) );
    }

    _disable();

    /* Load the initial SYSCON. */
    _mtcr( $SYSCON, پورٹ_INITIAL_SYSCON );
    _isync();

    /* ENDINIT has already been applied in the 'cstart.c' code. */

    /* Clear the PSW.CDC to enable the use of an RFE without it generating an
     * exception because this code is not genuinely in an exception. */
    ulMFCR = __MFCR( $PSW );
    ulMFCR &= پورٹ_RESTORE_PSW_نقاب;
    _dsync();
    _mtcr( $PSW, ulMFCR );
    _isync();

    /* Finally, perform the equivalent of a portRESTORE_CONTEXT() */
    pul_ہیٹھلا_CSA = پورٹ_CSA_منزل_پتہ( ( *pxCurrentTCB ) );
    pul_اتلا_CSA = پورٹ_CSA_منزل_پتہ( pul_ہیٹھلا_CSA[ 0 ] );
    _dsync();
    _mtcr( $PCXI, *pxCurrentTCB );
    _isync();
    _nop();
    _rslcx();
    _nop();

    /* Return to the first task selected to execute. */
    __asm متطاير ( "rfe" );

    /* Will not get here. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
    /* Set-up the clock divider. */
    unlock_wdtcon();
    {
        /* Wait until access to Endint protected register is enabled. */
        طالما( 0 != ( WDT_CON0.reg & 0x1UL ) )
        {
        }

        /* RMC == 1 so STM Clock == FPI */
        STM_CLC.reg = ( 1UL << 8 );
    }
    جندرا_wdtcon();

    /* Determine how many bits are used without changing other bits in the CMCON register. */
    STM_CMCON.reg &= ~( 0x1fUL );
    STM_CMCON.reg |= ( 0x1fUL - __CLZ( configPERIPHERAL_CLOCK_HZ / config_TICK_شرح_HZ ) );

    /* Take into account the current time so a tick doesn't happen immediately. */
    STM_CMP0.reg = ul_Compare_میل_قدر + STM_TIM0.reg;

    إذا( 0 != _install_int_handler( config_KERNEL_رکاوٹ_ترجیح, prvSystemTickHandler, 0 ) )
    {
        /* Set-up the interrupt. */
        STM_SRC0.reg = ( config_KERNEL_رکاوٹ_ترجیح | 0x00005000UL );

        /* Enable the Interrupt. */
        STM_ISRR.reg &= ~( 0x03UL );
        STM_ISRR.reg |= 0x1UL;
        STM_ISRR.reg &= ~( 0x07UL );
        STM_ICR.reg |= 0x1UL;
    }
    وإلا
    {
        /* Failed to install the Tick Interrupt. */
        configASSERT( ( ( متطاير فراغ * ) عدم ) );
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prvSystemTickHandler( صحيح iArg )
{
    uint32_t ul_Saved_رکاوٹ_نقاب;
    uint32_t * px_اتلا_CSA = عدم;
    uint32_t x_اتلا_CSA = 0UL;
    خارجي متطاير uint32_t * pxCurrentTCB;
    int32_t lYieldRequired;

    /* Just to avoid compiler warnings about unused parameters. */
    ( فراغ ) iArg;

    /* Clear the interrupt source. */
    STM_ISRR.reg = 1UL;

    /* Reload the Compare Match register for X ticks into the future.
     *
     * If critical section or interrupt nesting budgets are exceeded, then
     * it is possible that the calculated next compare match value is in the
     * past.  If this occurs (unlikely), it is possible that the resulting
     * time slippage will exceed a single tick period.  Any adverse effect of
     * this is time bounded by the fact that only the first n bits of the 56 bit
     * STM timer are being used for a compare match, so another compare match
     * will occur after an overflow in just those n bits (not the entire 56 bits).
     * As an example, if the peripheral clock is 75MHz, and the tick rate is 1KHz,
     * a missed tick could result in the next tick interrupt occurring within a
     * time that is 1.7 times the desired period.  The fact that this is greater
     * than a single tick period is an effect of using a timer that cannot be
     * automatically reset, in hardware, by the occurrence of a tick interrupt.
     * Changing the tick source to a timer that has an automatic reset on compare
     * match (such as a GPTA timer) will reduce the maximum possible additional
     * period to exactly 1 times the desired period. */
    STM_CMP0.reg += ul_Compare_میل_قدر;

    /* Kernel API calls require Critical Sections. */
    ul_Saved_رکاوٹ_نقاب = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();
    {
        /* Increment the Tick. */
        lYieldRequired = xTaskIncrementTick();
    }
    پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( ul_Saved_رکاوٹ_نقاب );

    إذا( lYieldRequired != pdFALSE )
    {
        /* Save the context of a task.
         * The upper context is automatically saved when entering a trap or interrupt.
         * Need to save the lower context as well and copy the PCXI CSA ID into
         * pxCurrentTCB->pxTopOfStack. Only Lower Context CSA IDs may be saved to the
         * TCB of a task.
         *
         * Call vTaskSwitchContext to select the next task, note that this changes the
         * value of pxCurrentTCB so that it needs to be reloaded.
         *
         * Call vPortSetMPURegisterSetOne to change the MPU mapping for the task
         * that has just been switched in.
         *
         * Load the context of the task.
         * Need to restore the lower context by loading the CSA from
         * pxCurrentTCB->pxTopOfStack into PCXI (effectively changing the call stack).
         * In the Interrupt handler post-amble, RSLCX will restore the lower context
         * of the task. RFE will restore the upper context of the task, jump to the
         * return address and restore the previous state of interrupts being
         * enabled/disabled. */
        _disable();
        _dsync();
        x_اتلا_CSA = __MFCR( $PCXI );
        px_اتلا_CSA = پورٹ_CSA_منزل_پتہ( x_اتلا_CSA );
        *pxCurrentTCB = px_اتلا_CSA[ 0 ];
        vTaskSwitchContext();
        px_اتلا_CSA[ 0 ] = *pxCurrentTCB;
        CPU_SRC0.بٹ_2.SETR = 0;
        _isync();
    }
}
/*-----------------------------------------------------------*/

/*
 * When a task is deleted, it is yielded permanently until the IDLE task
 * has an opportunity to reclaim the memory that that task was using.
 * Typically, the memory used by a task is the TCB and Stack but in the
 * TriCore this includes the CSAs that were consumed as part of the Call
 * Stack. These CSAs can only be returned to the Globally Free Pool when
 * they are not part of the current Call Stack, hence, delaying the
 * reclamation until the IDLE task is freeing the task's other resources.
 * This function uses the head of the linked list of CSAs (from when the
 * task yielded for the last time) and finds the tail (the very bottom of
 * the call stack) and inserts this list at the head of the Free list,
 * attaching the existing Free List to the tail of the reclaimed call stack.
 *
 * NOTE: the IDLE task needs processing time to complete this function
 * and in heavily loaded systems, the Free CSAs may be consumed faster
 * than they can be freed assuming that tasks are being spawned and
 * deleted frequently.
 */
فراغ v_پورٹ_Reclaim_CSA( uint32_t * pxTCB )
{
    uint32_t px_سر_CSA, px_پوچھ_CSA, pxFreeCSA;
    uint32_t * pul_اگلا_CSA;

    /* A pointer to the first CSA in the list of CSAs consumed by the task is
     * stored in the first element of the tasks TCB structure (where the stack
     * pointer would be on a traditional stack based architecture). */
    px_سر_CSA = ( *pxTCB ) & پورٹ_CSA_FCX_نقاب;

    /* Mask off everything in the CSA link field other than the address.  If
     * the address is NULL, then the CSA is not linking anywhere and there is
     * nothing to do. */
    px_پوچھ_CSA = px_سر_CSA;

    /* Convert the link value to contain just a raw address and store this
     * in a local variable. */
    pul_اگلا_CSA = پورٹ_CSA_منزل_پتہ( px_پوچھ_CSA );

    /* Iterate over the CSAs that were consumed as part of the task.  The
     * first field in the CSA is the pointer to then next CSA.  Mask off
     * everything in the pointer to the next CSA, other than the link address.
     * If this is NULL, then the CSA currently being pointed to is the last in
     * the chain. */
    طالما( 0UL != ( pul_اگلا_CSA[ 0 ] & پورٹ_CSA_FCX_نقاب ) )
    {
        /* Clear all bits of the pointer to the next in the chain, other
         * than the address bits themselves. */
        pul_اگلا_CSA[ 0 ] = pul_اگلا_CSA[ 0 ] & پورٹ_CSA_FCX_نقاب;

        /* Move the pointer to point to the next CSA in the list. */
        px_پوچھ_CSA = pul_اگلا_CSA[ 0 ];

        /* Update the local pointer to the CSA. */
        pul_اگلا_CSA = پورٹ_CSA_منزل_پتہ( px_پوچھ_CSA );
    }

    _disable();
    {
        /* Look up the current free CSA head. */
        _dsync();
        pxFreeCSA = __MFCR( $FCX );

        /* Join the current Free onto the Tail of what is being reclaimed. */
        پورٹ_CSA_منزل_پتہ( px_پوچھ_CSA )[ 0 ] = pxFreeCSA;

        /* Move the head of the reclaimed into the Free. */
        _dsync();
        _mtcr( $FCX, px_سر_CSA );
        _isync();
    }
    _enable();
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prvTrapYield( صحيح iTrapIdentification )
{
    uint32_t * px_اتلا_CSA = عدم;
    uint32_t x_اتلا_CSA = 0UL;
    خارجي متطاير uint32_t * pxCurrentTCB;

    بدل( iTrapIdentification )
    {
        حالة پورٹ_SYSCALL_TASK_YIELD:

            /* Save the context of a task.
             * The upper context is automatically saved when entering a trap or interrupt.
             * Need to save the lower context as well and copy the PCXI CSA ID into
             * pxCurrentTCB->pxTopOfStack. Only Lower Context CSA IDs may be saved to the
             * TCB of a task.
             *
             * Call vTaskSwitchContext to select the next task, note that this changes the
             * value of pxCurrentTCB so that it needs to be reloaded.
             *
             * Call vPortSetMPURegisterSetOne to change the MPU mapping for the task
             * that has just been switched in.
             *
             * Load the context of the task.
             * Need to restore the lower context by loading the CSA from
             * pxCurrentTCB->pxTopOfStack into PCXI (effectively changing the call stack).
             * In the Interrupt handler post-amble, RSLCX will restore the lower context
             * of the task. RFE will restore the upper context of the task, jump to the
             * return address and restore the previous state of interrupts being
             * enabled/disabled. */
            _disable();
            _dsync();
            x_اتلا_CSA = __MFCR( $PCXI );
            px_اتلا_CSA = پورٹ_CSA_منزل_پتہ( x_اتلا_CSA );
            *pxCurrentTCB = px_اتلا_CSA[ 0 ];
            vTaskSwitchContext();
            px_اتلا_CSA[ 0 ] = *pxCurrentTCB;
            CPU_SRC0.بٹ_2.SETR = 0;
            _isync();
            اكسر;

        افتراضي:
            /* Unimplemented trap called. */
            configASSERT( ( ( متطاير فراغ * ) عدم ) );
            اكسر;
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_رکاوٹ_Yield( صحيح iId )
{
    uint32_t * px_اتلا_CSA = عدم;
    uint32_t x_اتلا_CSA = 0UL;
    خارجي متطاير uint32_t * pxCurrentTCB;

    /* Just to remove compiler warnings. */
    ( فراغ ) iId;

    /* Save the context of a task.
     * The upper context is automatically saved when entering a trap or interrupt.
     * Need to save the lower context as well and copy the PCXI CSA ID into
     * pxCurrentTCB->pxTopOfStack. Only Lower Context CSA IDs may be saved to the
     * TCB of a task.
     *
     * Call vTaskSwitchContext to select the next task, note that this changes the
     * value of pxCurrentTCB so that it needs to be reloaded.
     *
     * Call vPortSetMPURegisterSetOne to change the MPU mapping for the task
     * that has just been switched in.
     *
     * Load the context of the task.
     * Need to restore the lower context by loading the CSA from
     * pxCurrentTCB->pxTopOfStack into PCXI (effectively changing the call stack).
     * In the Interrupt handler post-amble, RSLCX will restore the lower context
     * of the task. RFE will restore the upper context of the task, jump to the
     * return address and restore the previous state of interrupts being
     * enabled/disabled. */
    _disable();
    _dsync();
    x_اتلا_CSA = __MFCR( $PCXI );
    px_اتلا_CSA = پورٹ_CSA_منزل_پتہ( x_اتلا_CSA );
    *pxCurrentTCB = px_اتلا_CSA[ 0 ];
    vTaskSwitchContext();
    px_اتلا_CSA[ 0 ] = *pxCurrentTCB;
    CPU_SRC0.بٹ_2.SETR = 0;
    _isync();
}
/*-----------------------------------------------------------*/

uint32_t ux_پورٹ_سیٹ_رکاوٹ_نقاب_From_ISR( فراغ )
{
    uint32_t uxReturn = 0UL;

    _disable();
    uxReturn = __MFCR( $ICR );
    _mtcr( $ICR, ( ( uxReturn & ~پورٹ_CCPN_نقاب ) | config_MAX_SYSCALL_رکاوٹ_ترجیح ) );
    _isync();
    _enable();

    /* Return just the interrupt mask bits. */
    أرجع( uxReturn & پورٹ_CCPN_نقاب );
}
/*-----------------------------------------------------------*/
