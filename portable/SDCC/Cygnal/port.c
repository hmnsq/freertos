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

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the Cygnal port.
 *----------------------------------------------------------*/

/* Standard includes. */
#అన్తర్భావ <string.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Constants required to setup timer 2 to produce the RTOS tick. */
#నిర్వచించు పోర్టు_CLOCK_భాజకం                               ( ( uint32_t ) 12 )
#నిర్వచించు పోర్టు_MAX_TIMER_విలువ                             ( ( uint32_t ) 0xffff )
#నిర్వచించు పోర్టు_ENABLE_TIMER                                ( ( uint8_t ) 0x04 )
#నిర్వచించు పోర్టు_TIMER_2_అంతరాయం_ENABLE                    ( ( uint8_t ) 0x20 )

/* The value used in the IE register when a task first starts. */
#నిర్వచించు పోర్టు_GLOBAL_అంతరాయం_బిట్టు                        ( ( దొంతర_Type_t ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#నిర్వచించు పోర్టు_INITIAL_PSW                                 ( ( దొంతర_Type_t ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_FLAG()                      TMR2CN &= ~0x80;

/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
దత్తాంశం_2 స్థిర uint8_t uc_దొంతర_బైట్లు;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
xdata స్థిర దొంతర_Type_t * దత్తాంశం_2 pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
దత్తాంశం_2 స్థిర దొంతర_Type_t * దత్తాంశం_2 pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
రకనిర్వచనం శూన్య TCB_t;
బాహ్య అస్థిర TCB_t * అస్థిర pxCurrentTCB;

/*
 * Setup the hardware to generate an interrupt off timer 2 at the required
 * frequency.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/*-----------------------------------------------------------*/
/*
 * Macro that copies the current stack from internal RAM to XRAM.  This is
 * required as the 8051 only contains enough internal RAM for a single stack,
 * but we have a stack for every task.
 */
#నిర్వచించు పోర్టు_COPY_దొంతర_గమ్యం_XRAM()                                                            \
{                                                                                           \
        /* pxCurrentTCB points to a TCB which itself points to the location into            \
        which the first stack byte should be copied. Set pxXRAMStack to point               \
        to the location into which the first stack byte is to be copied. */                 \
        pxXRAMStack = ( xdata దొంతర_Type_t * ) *( ( xdata దొంతర_Type_t ** ) pxCurrentTCB );   \
                                                                                            \
        /* Set pxRAMStack to point to the first byte to be coped from the stack. */         \
        pxRAMStack = ( దత్తాంశం_2 దొంతర_Type_t * దత్తాంశం_2 ) config_దొంతర_ప్రారంభం;                         \
                                                                                            \
        /* Calculate the size of the stack we are about to copy from the current            \
        stack pointer value. */                                                             \
        uc_దొంతర_బైట్లు = SP - ( config_దొంతర_ప్రారంభం - 1 );                                      \
                                                                                            \
        /* Before starting to copy the stack, store the calculated stack size so            \
        the stack can be restored when the task is resumed. */                              \
        *pxXRAMStack = uc_దొంతర_బైట్లు;                                                        \
                                                                                            \
        /* Copy each stack byte in turn.  pxXRAMStack is incremented first as we            \
        have already stored the stack size into XRAM. */                                    \
        అయితే( uc_దొంతర_బైట్లు )                                                               \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                *pxXRAMStack = *pxRAMStack;                                                 \
                pxRAMStack++;                                                               \
                uc_దొంతర_బైట్లు--;                                                             \
        }                                                                                   \
}
/*-----------------------------------------------------------*/

/*
 * Macro that copies the stack of the task being resumed from XRAM into
 * internal RAM.
 */
#నిర్వచించు పోర్టు_COPY_XRAM_గమ్యం_దొంతర()                                                            \
{                                                                                           \
        /* Setup the pointers as per portCOPY_STACK_TO_XRAM(), but this time to             \
        copy the data back out of XRAM and into the stack. */                               \
        pxXRAMStack = ( xdata దొంతర_Type_t * ) *( ( xdata దొంతర_Type_t ** ) pxCurrentTCB );   \
        pxRAMStack = ( దత్తాంశం_2 దొంతర_Type_t * దత్తాంశం_2 ) ( config_దొంతర_ప్రారంభం - 1 );                 \
                                                                                            \
        /* The first value stored in XRAM was the size of the stack - i.e. the              \
        number of bytes we need to copy back. */                                            \
        uc_దొంతర_బైట్లు = pxXRAMStack[ 0 ];                                                    \
                                                                                            \
        /* Copy the required number of bytes back into the stack. */                        \
        చేయి                                                                                  \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                pxRAMStack++;                                                               \
                *pxRAMStack = *pxXRAMStack;                                                 \
                uc_దొంతర_బైట్లు--;                                                             \
        } అయితే( uc_దొంతర_బైట్లు );                                                            \
                                                                                            \
        /* Restore the stack pointer ready to use the restored stack. */                    \
        SP = ( uint8_t ) pxRAMStack;                                                        \
}
/*-----------------------------------------------------------*/

/*
 * Macro to push the current execution context onto the stack, before the stack
 * is moved to XRAM.
 */
#నిర్వచించు పోర్టు_SAVE_CONTEXT()                                                                  \
{                                                                                           \
        _asm                                                                                \
                /* Push ACC first, as when restoring the context it must be restored        \
                last (it is used to set the IE register). */                                \
                నెట్టు        ACC                                                             \
                /* Store the IE register then disable interrupts. */                        \
                నెట్టు        IE                                                              \
                clr                _EA                                                      \
                నెట్టు        DPL                                                             \
                నెట్టు        DPH                                                             \
                నెట్టు        b                                                               \
                నెట్టు        ar2                                                             \
                నెట్టు        ar3                                                             \
                నెట్టు        ar4                                                             \
                నెట్టు        ar5                                                             \
                నెట్టు        ar6                                                             \
                నెట్టు        ar7                                                             \
                నెట్టు        ar0                                                             \
                నెట్టు        ar1                                                             \
                నెట్టు        PSW                                                             \
        _endasm;                                                                            \
                PSW = 0;                                                                    \
        _asm                                                                                \
                నెట్టు        _bp                                                             \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * Macro that restores the execution context from the stack.  The execution
 * context was saved into the stack before the stack was copied into XRAM.
 */
#నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                                               \
{                                                                                           \
        _asm                                                                                \
                తీయి                _bp                                                      \
                తీయి                PSW                                                      \
                తీయి                ar1                                                      \
                తీయి                ar0                                                      \
                తీయి                ar7                                                      \
                తీయి                ar6                                                      \
                తీయి                ar5                                                      \
                తీయి                ar4                                                      \
                తీయి                ar3                                                      \
                తీయి                ar2                                                      \
                తీయి                b                                                        \
                తీయి                DPH                                                      \
                తీయి                DPL                                                      \
                /* The next byte of the stack is the IE register.  Only the global          \
                enable bit forms part of the task context.  Pop off the IE then set         \
                the global enable bit to match that of the stored IE register. */           \
                తీయి                ACC                                                      \
                JB                ACC.7,0098$                                               \
                CLR                IE.7                                                     \
                LJMP        0099$                                                           \
        0098$:                                                                              \
                SETB        IE.7                                                            \
        0099$:                                                                              \
                /* Finally pop off the ACC, which was the first register saved. */          \
                తీయి                ACC                                                      \
                reti                                                                        \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t *px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t *px_శిఖరం_యొక్క_దొంతర, TaskFunction_t px_సంకేతం, శూన్య *pvParameters )
{
uint32_t ul_చిరునామా;
దొంతర_Type_t *px_ప్రారంభం_యొక్క_దొంతర;

        /* Leave space to write the size of the stack as the first byte. */
        px_ప్రారంభం_యొక్క_దొంతర = px_శిఖరం_యొక్క_దొంతర;
        px_శిఖరం_యొక్క_దొంతర++;

        /* Place a few bytes of known values on the bottom of the stack.
        This is just useful for debugging and can be uncommented if required.
        *pxTopOfStack = 0x11;
        pxTopOfStack++;
        *pxTopOfStack = 0x22;
        pxTopOfStack++;
        *pxTopOfStack = 0x33;
        pxTopOfStack++;
        */

        /* Simulate how the stack would look after a call to the scheduler tick
        ISR.

        The return address that would have been pushed by the MCU. */
        ul_చిరునామా = ( uint32_t ) px_సంకేతం;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ul_చిరునామా;
        ul_చిరునామా >>= 8;
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( ul_చిరునామా );
        px_శిఖరం_యొక్క_దొంతర++;

        /* Next all the registers will have been pushed by portSAVE_CONTEXT(). */
        *px_శిఖరం_యొక్క_దొంతర = 0xaa;        /* acc */
        px_శిఖరం_యొక్క_దొంతర++;

        /* We want tasks to start with interrupts enabled. */
        *px_శిఖరం_యొక్క_దొంతర = పోర్టు_GLOBAL_అంతరాయం_బిట్టు;
        px_శిఖరం_యొక్క_దొంతర++;

        /* The function parameters will be passed in the DPTR and B register as
        a three byte generic pointer is used. */
        ul_చిరునామా = ( uint32_t ) pvParameters;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ul_చిరునామా;        /* DPL */
        ul_చిరునామా >>= 8;
        *px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ul_చిరునామా;        /* DPH */
        ul_చిరునామా >>= 8;
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ul_చిరునామా;        /* b */
        px_శిఖరం_యొక్క_దొంతర++;

        /* The remaining registers are straight forward. */
        *px_శిఖరం_యొక్క_దొంతర = 0x02;        /* R2 */
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = 0x03;        /* R3 */
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = 0x04;        /* R4 */
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = 0x05;        /* R5 */
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = 0x06;        /* R6 */
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = 0x07;        /* R7 */
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = 0x00;        /* R0 */
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = 0x01;        /* R1 */
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = 0x00;        /* PSW */
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = 0xbb;        /* BP */

        /* Dont increment the stack size here as we don't want to include
        the stack size byte as part of the stack size count.

        Finally we place the stack size at the beginning. */
        *px_ప్రారంభం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( px_శిఖరం_యొక్క_దొంతర - px_ప్రారంభం_యొక్క_దొంతర );

        /* Unlike most ports, we return the start of the stack as this is where the
        size of the stack is stored. */
        తిరిగి px_ప్రారంభం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
        /* Setup timer 2 to generate the RTOS tick. */
        prv_అమరిక_Timer_అంతరాయం();

        /* Make sure we start with the expected SFR page.  This line should not
        really be required. */
        SFRPAGE = 0;

        /* Copy the stack for the first task to execute from XRAM into the stack,
        restore the task context from the new stack, then start running the task. */
        పోర్టు_COPY_XRAM_గమ్యం_దొంతర();
        పోర్టు_RESTORE_CONTEXT();

        /* Should never get here! */
        తిరిగి pdTRUE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
        /* Not implemented for this port. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
శూన్య v_పోర్టు_Yield( శూన్య ) _naked
{
        /* Save the execution context onto the stack, then copy the entire stack
        to XRAM.  This is necessary as the internal RAM is only large enough to
        hold one stack, and we want one per task.

        PERFORMANCE COULD BE IMPROVED BY ONLY COPYING TO XRAM IF A TASK SWITCH
        IS REQUIRED. */
        పోర్టు_SAVE_CONTEXT();
        పోర్టు_COPY_దొంతర_గమ్యం_XRAM();

        /* Call the standard scheduler context switch function. */
        vTaskSwitchContext();

        /* Copy the stack of the task about to execute from XRAM into RAM and
        restore it's context ready to run on exiting. */
        పోర్టు_COPY_XRAM_గమ్యం_దొంతర();
        పోర్టు_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

#ఒకవేళ configUSE_PREEMPTION == 1
        శూన్య vTimer2ISR( శూన్య ) అంతరాయం 5 _naked
        {
                /* Preemptive context switch function triggered by the timer 2 ISR.
                This does the same as vPortYield() (see above) with the addition
                of incrementing the RTOS tick count. */

                పోర్టు_SAVE_CONTEXT();
                పోర్టు_COPY_దొంతర_గమ్యం_XRAM();

                ఒకవేళ( xTaskIncrementTick() != pdFALSE )
                {
                        vTaskSwitchContext();
                }

                పోర్టు_CLEAR_అంతరాయం_FLAG();
                పోర్టు_COPY_XRAM_గమ్యం_దొంతర();
                పోర్టు_RESTORE_CONTEXT();
        }
#లేకపోతే
        శూన్య vTimer2ISR( శూన్య ) అంతరాయం 5
        {
                /* When using the cooperative scheduler the timer 2 ISR is only
                required to increment the RTOS tick count. */

                xTaskIncrementTick();
                పోర్టు_CLEAR_అంతరాయం_FLAG();
        }
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
uint8_t ucOriginalSFRPage;

/* Constants calculated to give the required timer capture values. */
స్థిరరాశి uint32_t ul_Ticks_చొప్పున_రెండవ = configCPU_CLOCK_HZ / పోర్టు_CLOCK_భాజకం;
స్థిరరాశి uint32_t ul_Capture_సమయం = ul_Ticks_చొప్పున_రెండవ / config_TICK_రేటు_HZ;
స్థిరరాశి uint32_t ul_Capture_విలువ = పోర్టు_MAX_TIMER_విలువ - ul_Capture_సమయం;
స్థిరరాశి uint8_t uc_దిగువ_Capture_Byte = ( uint8_t ) ( ul_Capture_విలువ & ( uint32_t ) 0xff );
స్థిరరాశి uint8_t uc_ఎగువ_Capture_Byte = ( uint8_t ) ( ul_Capture_విలువ >> ( uint32_t ) 8 );

        /* NOTE:  This uses a timer only present on 8052 architecture. */

        /* Remember the current SFR page so we can restore it at the end of the
        function. */
        ucOriginalSFRPage = SFRPAGE;
        SFRPAGE = 0;

        /* TMR2CF can be left in its default state. */
        TMR2CF = ( uint8_t ) 0;

        /* Setup the overflow reload value. */
        RCAP2L = uc_దిగువ_Capture_Byte;
        RCAP2H = uc_ఎగువ_Capture_Byte;

        /* The initial load is performed manually. */
        TMR2L = uc_దిగువ_Capture_Byte;
        TMR2H = uc_ఎగువ_Capture_Byte;

        /* Enable the timer 2 interrupts. */
        IE |= పోర్టు_TIMER_2_అంతరాయం_ENABLE;

        /* Interrupts are disabled when this is called so the timer can be started
        here. */
        TMR2CN = పోర్టు_ENABLE_TIMER;

        /* Restore the original SFR page. */
        SFRPAGE = ucOriginalSFRPage;
}
