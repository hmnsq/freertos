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
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

/* TriCore specific includes. */
#अन्तर्भाव <tc1782.h>
#अन्तर्भाव <machine/intrinsics.h>
#अन्तर्भाव <machine/cint.h>
#अन्तर्भाव <machine/wdtcon.h>

/* Kernel includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "list.h"

#यदि config_CHECK_FOR_राशिः_अतिप्रवाहः > 0
    #दोषः "Stack checking cannot be used with this port, as, unlike most ports, the pxTopOfStack member of the TCB is consumed CSA.  CSA starvation, loosely equivalent to stack overflow, will result in a trap exception."
    /* The stack pointer is accessible using portCSA_TO_ADDRESS( portCSA_TO_ADDRESS( pxCurrentTCB->pxTopOfStack )[ 0 ] )[ 2 ]; */
#यदि_अन्तः /* configCHECK_FOR_STACK_OVERFLOW */


/*-----------------------------------------------------------*/

/* System register Definitions. */
#परिभाषय पत्तनम्_SYSTEM_क्रमादेशः_स्थितिः_WORD                  ( 0x000008FFUL ) /* Supervisor Mode, MPU Register Set 0 and Call Depth Counting disabled. */
#परिभाषय पत्तनम्_INITIAL_PRIVILEGED_क्रमादेशः_स्थितिः_WORD      ( 0x000014FFUL ) /* IO Level 1, MPU Register Set 1 and Call Depth Counting disabled. */
#परिभाषय पत्तनम्_INITIAL_UNPRIVILEGED_क्रमादेशः_स्थितिः_WORD    ( 0x000010FFUL ) /* IO Level 0, MPU Register Set 1 and Call Depth Counting disabled. */
#परिभाषय पत्तनम्_INITIAL_PCXI_ऊर्ध्वस्थम्_CONTEXT_WORD             ( 0x00C00000UL ) /* The lower 20 bits identify the CSA address. */
#परिभाषय पत्तनम्_INITIAL_SYSCON                              ( 0x00000000UL ) /* MPU Disable. */

/* CSA manipulation macros. */
#परिभाषय पत्तनम्_CSA_FCX_आवरणम्                                ( 0x000FFFFFUL )

/* OS Interrupt and Trap mechanisms. */
#परिभाषय पत्तनम्_RESTORE_PSW_आवरणम्                            ( ~( 0x000000FFUL ) )
#परिभाषय पत्तनम्_SYSCALL_TRAP                                ( 6 )

/* Each CSA contains 16 words of data. */
#परिभाषय पत्तनम्_अङ्कः_शब्दाः_अन्तर्_CSA                            ( 16 )

/* The interrupt enable bit in the PCP_SRC register. */
#परिभाषय पत्तनम्_ENABLE_CPU_व्यवधानम्                        ( 1U << 12U )
/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
स्थिर शून्य prvSystemTickHandler( पूर्णाङ्क ) __attribute__( ( longcall ) );
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/*
 * Trap handler for yields.
 */
स्थिर शून्य prvTrapYield( पूर्णाङ्क iTrapIdentification );

/*
 * Priority 1 interrupt handler for yields pended from an interrupt.
 */
स्थिर शून्य prv_व्यवधानम्_Yield( पूर्णाङ्क iTrapIdentification );

/*-----------------------------------------------------------*/

/* This reference is required by the save/restore context macros. */
बाह्य चञ्चल uint32_t * pxCurrentTCB;

/* Precalculate the compare match value at compile time. */
स्थिर ध्रुव uint32_t ul_Compare_मेलनम्_मानम् = ( configPERIPHERAL_CLOCK_HZ / config_TICK_दरः_HZ );

/*-----------------------------------------------------------*/

राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    uint32_t * pul_ऊर्ध्वस्थम्_CSA = रिक्त;
    uint32_t * pul_अधस्तनम्_CSA = रिक्त;

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
    पत्तनम्_ENTER_CRITICAL();
    {
        /* DSync to ensure that buffering is not a problem. */
        _dsync();

        /* Consume two free CSAs. */
        pul_अधस्तनम्_CSA = पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( __MFCR( $FCX ) );

        यदि( रिक्त != pul_अधस्तनम्_CSA )
        {
            /* The Lower Links to the Upper. */
            pul_ऊर्ध्वस्थम्_CSA = पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( pul_अधस्तनम्_CSA[ 0 ] );
        }

        /* Check that we have successfully reserved two CSAs. */
        यदि( ( रिक्त != pul_अधस्तनम्_CSA ) && ( रिक्त != pul_ऊर्ध्वस्थम्_CSA ) )
        {
            /* Remove the two consumed CSAs from the free CSA list. */
            _disable();
            _dsync();
            _mtcr( $FCX, pul_ऊर्ध्वस्थम्_CSA[ 0 ] );
            _isync();
            _enable();
        }
        अन्यथा
        {
            /* Simply trigger a context list depletion trap. */
            _svlcx();
        }
    }
    पत्तनम्_EXIT_CRITICAL();

    /* Clear the upper CSA. */
    स्मृतिं_पूरय( pul_ऊर्ध्वस्थम्_CSA, 0, पत्तनम्_अङ्कः_शब्दाः_अन्तर्_CSA * परिमाण( uint32_t ) );

    /* Upper Context. */
    pul_ऊर्ध्वस्थम्_CSA[ 2 ] = ( uint32_t ) px_शिखरम्_सम्बन्धि_राशिः;      /* A10; Stack Return aka Stack Pointer */
    pul_ऊर्ध्वस्थम्_CSA[ 1 ] = पत्तनम्_SYSTEM_क्रमादेशः_स्थितिः_WORD; /* PSW  */

    /* Clear the lower CSA. */
    स्मृतिं_पूरय( pul_अधस्तनम्_CSA, 0, पत्तनम्_अङ्कः_शब्दाः_अन्तर्_CSA * परिमाण( uint32_t ) );

    /* Lower Context. */
    pul_अधस्तनम्_CSA[ 8 ] = ( uint32_t ) pvParameters; /* A4;  Address Type Parameter Register */
    pul_अधस्तनम्_CSA[ 1 ] = ( uint32_t ) px_संहिता;       /* A11; Return Address aka RA */

    /* PCXI pointing to the Upper context. */
    pul_अधस्तनम्_CSA[ 0 ] = ( पत्तनम्_INITIAL_PCXI_ऊर्ध्वस्थम्_CONTEXT_WORD | ( uint32_t ) पत्तनम्_स्थानाङ्कः_गन्तव्यम्_CSA( pul_ऊर्ध्वस्थम्_CSA ) );

    /* Save the link to the CSA in the top of stack. */
    px_शिखरम्_सम्बन्धि_राशिः = ( uint32_t * ) पत्तनम्_स्थानाङ्कः_गन्तव्यम्_CSA( pul_अधस्तनम्_CSA );

    /* DSync to ensure that buffering is not a problem. */
    _dsync();

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

int32_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    बाह्य शून्य vTrapInstallHandlers( शून्य );
    uint32_t ulMFCR = 0UL;
    uint32_t * pul_ऊर्ध्वस्थम्_CSA = रिक्त;
    uint32_t * pul_अधस्तनम्_CSA = रिक्त;

    /* Interrupts at or below configMAX_SYSCALL_INTERRUPT_PRIORITY are disable
     * when this function is called. */

    /* Set-up the timer interrupt. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Install the Trap Handlers. */
    vTrapInstallHandlers();

    /* Install the Syscall Handler for yield calls. */
    यदि( 0 == _install_trap_handler( पत्तनम्_SYSCALL_TRAP, prvTrapYield ) )
    {
        /* Failed to install the yield handler, force an assert. */
        configASSERT( ( ( चञ्चल शून्य * ) रिक्त ) );
    }

    /* Enable then install the priority 1 interrupt for pending context
     * switches from an ISR.  See mod_SRC in the TriCore manual. */
    CPU_SRC0.reg = ( पत्तनम्_ENABLE_CPU_व्यवधानम् ) | ( config_KERNEL_YIELD_प्राथमिकता );

    यदि( 0 == _install_int_handler( config_KERNEL_YIELD_प्राथमिकता, prv_व्यवधानम्_Yield, 0 ) )
    {
        /* Failed to install the yield handler, force an assert. */
        configASSERT( ( ( चञ्चल शून्य * ) रिक्त ) );
    }

    _disable();

    /* Load the initial SYSCON. */
    _mtcr( $SYSCON, पत्तनम्_INITIAL_SYSCON );
    _isync();

    /* ENDINIT has already been applied in the 'cstart.c' code. */

    /* Clear the PSW.CDC to enable the use of an RFE without it generating an
     * exception because this code is not genuinely in an exception. */
    ulMFCR = __MFCR( $PSW );
    ulMFCR &= पत्तनम्_RESTORE_PSW_आवरणम्;
    _dsync();
    _mtcr( $PSW, ulMFCR );
    _isync();

    /* Finally, perform the equivalent of a portRESTORE_CONTEXT() */
    pul_अधस्तनम्_CSA = पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( ( *pxCurrentTCB ) );
    pul_ऊर्ध्वस्थम्_CSA = पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( pul_अधस्तनम्_CSA[ 0 ] );
    _dsync();
    _mtcr( $PCXI, *pxCurrentTCB );
    _isync();
    _nop();
    _rslcx();
    _nop();

    /* Return to the first task selected to execute. */
    __asm चञ्चल ( "rfe" );

    /* Will not get here. */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    /* Set-up the clock divider. */
    unlock_wdtcon();
    {
        /* Wait until access to Endint protected register is enabled. */
        यावत्( 0 != ( WDT_CON0.reg & 0x1UL ) )
        {
        }

        /* RMC == 1 so STM Clock == FPI */
        STM_CLC.reg = ( 1UL << 8 );
    }
    तालकम्_wdtcon();

    /* Determine how many bits are used without changing other bits in the CMCON register. */
    STM_CMCON.reg &= ~( 0x1fUL );
    STM_CMCON.reg |= ( 0x1fUL - __CLZ( configPERIPHERAL_CLOCK_HZ / config_TICK_दरः_HZ ) );

    /* Take into account the current time so a tick doesn't happen immediately. */
    STM_CMP0.reg = ul_Compare_मेलनम्_मानम् + STM_TIM0.reg;

    यदि( 0 != _install_int_handler( config_KERNEL_व्यवधानम्_प्राथमिकता, prvSystemTickHandler, 0 ) )
    {
        /* Set-up the interrupt. */
        STM_SRC0.reg = ( config_KERNEL_व्यवधानम्_प्राथमिकता | 0x00005000UL );

        /* Enable the Interrupt. */
        STM_ISRR.reg &= ~( 0x03UL );
        STM_ISRR.reg |= 0x1UL;
        STM_ISRR.reg &= ~( 0x07UL );
        STM_ICR.reg |= 0x1UL;
    }
    अन्यथा
    {
        /* Failed to install the Tick Interrupt. */
        configASSERT( ( ( चञ्चल शून्य * ) रिक्त ) );
    }
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvSystemTickHandler( पूर्णाङ्क iArg )
{
    uint32_t ul_Saved_व्यवधानम्_आवरणम्;
    uint32_t * px_ऊर्ध्वस्थम्_CSA = रिक्त;
    uint32_t x_ऊर्ध्वस्थम्_CSA = 0UL;
    बाह्य चञ्चल uint32_t * pxCurrentTCB;
    int32_t lYieldRequired;

    /* Just to avoid compiler warnings about unused parameters. */
    ( शून्य ) iArg;

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
    STM_CMP0.reg += ul_Compare_मेलनम्_मानम्;

    /* Kernel API calls require Critical Sections. */
    ul_Saved_व्यवधानम्_आवरणम् = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
    {
        /* Increment the Tick. */
        lYieldRequired = xTaskIncrementTick();
    }
    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ul_Saved_व्यवधानम्_आवरणम् );

    यदि( lYieldRequired != pdFALSE )
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
        x_ऊर्ध्वस्थम्_CSA = __MFCR( $PCXI );
        px_ऊर्ध्वस्थम्_CSA = पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( x_ऊर्ध्वस्थम्_CSA );
        *pxCurrentTCB = px_ऊर्ध्वस्थम्_CSA[ 0 ];
        vTaskSwitchContext();
        px_ऊर्ध्वस्थम्_CSA[ 0 ] = *pxCurrentTCB;
        CPU_SRC0.द्वयङ्काः_2.SETR = 0;
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
शून्य v_पत्तनम्_Reclaim_CSA( uint32_t * pxTCB )
{
    uint32_t px_शीर्ष_CSA, px_पुच्छ_CSA, pxFreeCSA;
    uint32_t * pul_अग्र_CSA;

    /* A pointer to the first CSA in the list of CSAs consumed by the task is
     * stored in the first element of the tasks TCB structure (where the stack
     * pointer would be on a traditional stack based architecture). */
    px_शीर्ष_CSA = ( *pxTCB ) & पत्तनम्_CSA_FCX_आवरणम्;

    /* Mask off everything in the CSA link field other than the address.  If
     * the address is NULL, then the CSA is not linking anywhere and there is
     * nothing to do. */
    px_पुच्छ_CSA = px_शीर्ष_CSA;

    /* Convert the link value to contain just a raw address and store this
     * in a local variable. */
    pul_अग्र_CSA = पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( px_पुच्छ_CSA );

    /* Iterate over the CSAs that were consumed as part of the task.  The
     * first field in the CSA is the pointer to then next CSA.  Mask off
     * everything in the pointer to the next CSA, other than the link address.
     * If this is NULL, then the CSA currently being pointed to is the last in
     * the chain. */
    यावत्( 0UL != ( pul_अग्र_CSA[ 0 ] & पत्तनम्_CSA_FCX_आवरणम् ) )
    {
        /* Clear all bits of the pointer to the next in the chain, other
         * than the address bits themselves. */
        pul_अग्र_CSA[ 0 ] = pul_अग्र_CSA[ 0 ] & पत्तनम्_CSA_FCX_आवरणम्;

        /* Move the pointer to point to the next CSA in the list. */
        px_पुच्छ_CSA = pul_अग्र_CSA[ 0 ];

        /* Update the local pointer to the CSA. */
        pul_अग्र_CSA = पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( px_पुच्छ_CSA );
    }

    _disable();
    {
        /* Look up the current free CSA head. */
        _dsync();
        pxFreeCSA = __MFCR( $FCX );

        /* Join the current Free onto the Tail of what is being reclaimed. */
        पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( px_पुच्छ_CSA )[ 0 ] = pxFreeCSA;

        /* Move the head of the reclaimed into the Free. */
        _dsync();
        _mtcr( $FCX, px_शीर्ष_CSA );
        _isync();
    }
    _enable();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvTrapYield( पूर्णाङ्क iTrapIdentification )
{
    uint32_t * px_ऊर्ध्वस्थम्_CSA = रिक्त;
    uint32_t x_ऊर्ध्वस्थम्_CSA = 0UL;
    बाह्य चञ्चल uint32_t * pxCurrentTCB;

    विकल्प( iTrapIdentification )
    {
        पक्ष पत्तनम्_SYSCALL_TASK_YIELD:

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
            x_ऊर्ध्वस्थम्_CSA = __MFCR( $PCXI );
            px_ऊर्ध्वस्थम्_CSA = पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( x_ऊर्ध्वस्थम्_CSA );
            *pxCurrentTCB = px_ऊर्ध्वस्थम्_CSA[ 0 ];
            vTaskSwitchContext();
            px_ऊर्ध्वस्थम्_CSA[ 0 ] = *pxCurrentTCB;
            CPU_SRC0.द्वयङ्काः_2.SETR = 0;
            _isync();
            भङ्ग;

        स्वभाव:
            /* Unimplemented trap called. */
            configASSERT( ( ( चञ्चल शून्य * ) रिक्त ) );
            भङ्ग;
    }
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_व्यवधानम्_Yield( पूर्णाङ्क iId )
{
    uint32_t * px_ऊर्ध्वस्थम्_CSA = रिक्त;
    uint32_t x_ऊर्ध्वस्थम्_CSA = 0UL;
    बाह्य चञ्चल uint32_t * pxCurrentTCB;

    /* Just to remove compiler warnings. */
    ( शून्य ) iId;

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
    x_ऊर्ध्वस्थम्_CSA = __MFCR( $PCXI );
    px_ऊर्ध्वस्थम्_CSA = पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( x_ऊर्ध्वस्थम्_CSA );
    *pxCurrentTCB = px_ऊर्ध्वस्थम्_CSA[ 0 ];
    vTaskSwitchContext();
    px_ऊर्ध्वस्थम्_CSA[ 0 ] = *pxCurrentTCB;
    CPU_SRC0.द्वयङ्काः_2.SETR = 0;
    _isync();
}
/*-----------------------------------------------------------*/

uint32_t ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR( शून्य )
{
    uint32_t uxReturn = 0UL;

    _disable();
    uxReturn = __MFCR( $ICR );
    _mtcr( $ICR, ( ( uxReturn & ~पत्तनम्_CCPN_आवरणम् ) | config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ) );
    _isync();
    _enable();

    /* Return just the interrupt mask bits. */
    प्रत्यागम( uxReturn & पत्तनम्_CCPN_आवरणम् );
}
/*-----------------------------------------------------------*/
