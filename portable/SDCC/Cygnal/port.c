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
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Constants required to setup timer 2 to produce the RTOS tick. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLOCK_ਭਾਜਕ                               ( ( uint32_t ) 12 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_TIMER_ਮੁੱਲ                             ( ( uint32_t ) 0xffff )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_TIMER                                ( ( uint8_t ) 0x04 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_2_ਰੁਕਾਵਟ_ENABLE                    ( ( uint8_t ) 0x20 )

/* The value used in the IE register when a task first starts. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GLOBAL_ਰੁਕਾਵਟ_ਦੋਆਧਾਰੀ_ਅੰਕ                        ( ( ਢੇਰ_Type_t ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_PSW                                 ( ( ਢੇਰ_Type_t ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_FLAG()                      TMR2CN &= ~0x80;

/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
ਅੰਕੜੇ_2 ਸਥਿਰ uint8_t uc_ਢੇਰ_ਬਾਈਟਾਂ;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
xdata ਸਥਿਰ ਢੇਰ_Type_t * ਅੰਕੜੇ_2 pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
ਅੰਕੜੇ_2 ਸਥਿਰ ਢੇਰ_Type_t * ਅੰਕੜੇ_2 pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ TCB_t;
ਬਾਹਰੀ ਅਸਥਿਰ TCB_t * ਅਸਥਿਰ pxCurrentTCB;

/*
 * Setup the hardware to generate an interrupt off timer 2 at the required
 * frequency.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*-----------------------------------------------------------*/
/*
 * Macro that copies the current stack from internal RAM to XRAM.  This is
 * required as the 8051 only contains enough internal RAM for a single stack,
 * but we have a stack for every task.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_COPY_ਢੇਰ_ਮੰਜ਼ਿਲ_XRAM()                                                            \
{                                                                                           \
        /* pxCurrentTCB points to a TCB which itself points to the location into            \
        which the first stack byte should be copied. Set pxXRAMStack to point               \
        to the location into which the first stack byte is to be copied. */                 \
        pxXRAMStack = ( xdata ਢੇਰ_Type_t * ) *( ( xdata ਢੇਰ_Type_t ** ) pxCurrentTCB );   \
                                                                                            \
        /* Set pxRAMStack to point to the first byte to be coped from the stack. */         \
        pxRAMStack = ( ਅੰਕੜੇ_2 ਢੇਰ_Type_t * ਅੰਕੜੇ_2 ) config_ਢੇਰ_ਸ਼ੁਰੂ;                         \
                                                                                            \
        /* Calculate the size of the stack we are about to copy from the current            \
        stack pointer value. */                                                             \
        uc_ਢੇਰ_ਬਾਈਟਾਂ = SP - ( config_ਢੇਰ_ਸ਼ੁਰੂ - 1 );                                      \
                                                                                            \
        /* Before starting to copy the stack, store the calculated stack size so            \
        the stack can be restored when the task is resumed. */                              \
        *pxXRAMStack = uc_ਢੇਰ_ਬਾਈਟਾਂ;                                                        \
                                                                                            \
        /* Copy each stack byte in turn.  pxXRAMStack is incremented first as we            \
        have already stored the stack size into XRAM. */                                    \
        ਜਦੋਂ( uc_ਢੇਰ_ਬਾਈਟਾਂ )                                                               \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                *pxXRAMStack = *pxRAMStack;                                                 \
                pxRAMStack++;                                                               \
                uc_ਢੇਰ_ਬਾਈਟਾਂ--;                                                             \
        }                                                                                   \
}
/*-----------------------------------------------------------*/

/*
 * Macro that copies the stack of the task being resumed from XRAM into
 * internal RAM.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_COPY_XRAM_ਮੰਜ਼ਿਲ_ਢੇਰ()                                                            \
{                                                                                           \
        /* Setup the pointers as per portCOPY_STACK_TO_XRAM(), but this time to             \
        copy the data back out of XRAM and into the stack. */                               \
        pxXRAMStack = ( xdata ਢੇਰ_Type_t * ) *( ( xdata ਢੇਰ_Type_t ** ) pxCurrentTCB );   \
        pxRAMStack = ( ਅੰਕੜੇ_2 ਢੇਰ_Type_t * ਅੰਕੜੇ_2 ) ( config_ਢੇਰ_ਸ਼ੁਰੂ - 1 );                 \
                                                                                            \
        /* The first value stored in XRAM was the size of the stack - i.e. the              \
        number of bytes we need to copy back. */                                            \
        uc_ਢੇਰ_ਬਾਈਟਾਂ = pxXRAMStack[ 0 ];                                                    \
                                                                                            \
        /* Copy the required number of bytes back into the stack. */                        \
        ਕਰੋ                                                                                  \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                pxRAMStack++;                                                               \
                *pxRAMStack = *pxXRAMStack;                                                 \
                uc_ਢੇਰ_ਬਾਈਟਾਂ--;                                                             \
        } ਜਦੋਂ( uc_ਢੇਰ_ਬਾਈਟਾਂ );                                                            \
                                                                                            \
        /* Restore the stack pointer ready to use the restored stack. */                    \
        SP = ( uint8_t ) pxRAMStack;                                                        \
}
/*-----------------------------------------------------------*/

/*
 * Macro to push the current execution context onto the stack, before the stack
 * is moved to XRAM.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SAVE_CONTEXT()                                                                  \
{                                                                                           \
        _asm                                                                                \
                /* Push ACC first, as when restoring the context it must be restored        \
                last (it is used to set the IE register). */                                \
                ਧੱਕੋ        ACC                                                             \
                /* Store the IE register then disable interrupts. */                        \
                ਧੱਕੋ        IE                                                              \
                clr                _EA                                                      \
                ਧੱਕੋ        DPL                                                             \
                ਧੱਕੋ        DPH                                                             \
                ਧੱਕੋ        b                                                               \
                ਧੱਕੋ        ar2                                                             \
                ਧੱਕੋ        ar3                                                             \
                ਧੱਕੋ        ar4                                                             \
                ਧੱਕੋ        ar5                                                             \
                ਧੱਕੋ        ar6                                                             \
                ਧੱਕੋ        ar7                                                             \
                ਧੱਕੋ        ar0                                                             \
                ਧੱਕੋ        ar1                                                             \
                ਧੱਕੋ        PSW                                                             \
        _endasm;                                                                            \
                PSW = 0;                                                                    \
        _asm                                                                                \
                ਧੱਕੋ        _bp                                                             \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * Macro that restores the execution context from the stack.  The execution
 * context was saved into the stack before the stack was copied into XRAM.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESTORE_CONTEXT()                                                               \
{                                                                                           \
        _asm                                                                                \
                ਕੱਢੋ                _bp                                                      \
                ਕੱਢੋ                PSW                                                      \
                ਕੱਢੋ                ar1                                                      \
                ਕੱਢੋ                ar0                                                      \
                ਕੱਢੋ                ar7                                                      \
                ਕੱਢੋ                ar6                                                      \
                ਕੱਢੋ                ar5                                                      \
                ਕੱਢੋ                ar4                                                      \
                ਕੱਢੋ                ar3                                                      \
                ਕੱਢੋ                ar2                                                      \
                ਕੱਢੋ                b                                                        \
                ਕੱਢੋ                DPH                                                      \
                ਕੱਢੋ                DPL                                                      \
                /* The next byte of the stack is the IE register.  Only the global          \
                enable bit forms part of the task context.  Pop off the IE then set         \
                the global enable bit to match that of the stored IE register. */           \
                ਕੱਢੋ                ACC                                                      \
                JB                ACC.7,0098$                                               \
                CLR                IE.7                                                     \
                LJMP        0099$                                                           \
        0098$:                                                                              \
                SETB        IE.7                                                            \
        0099$:                                                                              \
                /* Finally pop off the ACC, which was the first register saved. */          \
                ਕੱਢੋ                ACC                                                      \
                reti                                                                        \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t *px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
uint32_t ul_ਪਤਾ;
ਢੇਰ_Type_t *px_ਸ਼ੁਰੂ_ਦਾ_ਢੇਰ;

        /* Leave space to write the size of the stack as the first byte. */
        px_ਸ਼ੁਰੂ_ਦਾ_ਢੇਰ = px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

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
        ul_ਪਤਾ = ( uint32_t ) px_ਕੋਡ;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ul_ਪਤਾ;
        ul_ਪਤਾ >>= 8;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ( ul_ਪਤਾ );
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

        /* Next all the registers will have been pushed by portSAVE_CONTEXT(). */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xaa;        /* acc */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

        /* We want tasks to start with interrupts enabled. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_GLOBAL_ਰੁਕਾਵਟ_ਦੋਆਧਾਰੀ_ਅੰਕ;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

        /* The function parameters will be passed in the DPTR and B register as
        a three byte generic pointer is used. */
        ul_ਪਤਾ = ( uint32_t ) pvParameters;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ul_ਪਤਾ;        /* DPL */
        ul_ਪਤਾ >>= 8;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ul_ਪਤਾ;        /* DPH */
        ul_ਪਤਾ >>= 8;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ul_ਪਤਾ;        /* b */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

        /* The remaining registers are straight forward. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x02;        /* R2 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x03;        /* R3 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x04;        /* R4 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x05;        /* R5 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x06;        /* R6 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x07;        /* R7 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00;        /* R0 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x01;        /* R1 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00;        /* PSW */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xbb;        /* BP */

        /* Dont increment the stack size here as we don't want to include
        the stack size byte as part of the stack size count.

        Finally we place the stack size at the beginning. */
        *px_ਸ਼ੁਰੂ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ( px_ਸਿਖਰ_ਦਾ_ਢੇਰ - px_ਸ਼ੁਰੂ_ਦਾ_ਢੇਰ );

        /* Unlike most ports, we return the start of the stack as this is where the
        size of the stack is stored. */
        ਵਾਪਸ px_ਸ਼ੁਰੂ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
        /* Setup timer 2 to generate the RTOS tick. */
        prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

        /* Make sure we start with the expected SFR page.  This line should not
        really be required. */
        SFRPAGE = 0;

        /* Copy the stack for the first task to execute from XRAM into the stack,
        restore the task context from the new stack, then start running the task. */
        ਪੋਰਟ_COPY_XRAM_ਮੰਜ਼ਿਲ_ਢੇਰ();
        ਪੋਰਟ_RESTORE_CONTEXT();

        /* Should never get here! */
        ਵਾਪਸ pdTRUE;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
        /* Not implemented for this port. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ ) _naked
{
        /* Save the execution context onto the stack, then copy the entire stack
        to XRAM.  This is necessary as the internal RAM is only large enough to
        hold one stack, and we want one per task.

        PERFORMANCE COULD BE IMPROVED BY ONLY COPYING TO XRAM IF A TASK SWITCH
        IS REQUIRED. */
        ਪੋਰਟ_SAVE_CONTEXT();
        ਪੋਰਟ_COPY_ਢੇਰ_ਮੰਜ਼ਿਲ_XRAM();

        /* Call the standard scheduler context switch function. */
        vTaskSwitchContext();

        /* Copy the stack of the task about to execute from XRAM into RAM and
        restore it's context ready to run on exiting. */
        ਪੋਰਟ_COPY_XRAM_ਮੰਜ਼ਿਲ_ਢੇਰ();
        ਪੋਰਟ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

#ਜੇ configUSE_PREEMPTION == 1
        ਖਾਲੀ vTimer2ISR( ਖਾਲੀ ) ਰੁਕਾਵਟ 5 _naked
        {
                /* Preemptive context switch function triggered by the timer 2 ISR.
                This does the same as vPortYield() (see above) with the addition
                of incrementing the RTOS tick count. */

                ਪੋਰਟ_SAVE_CONTEXT();
                ਪੋਰਟ_COPY_ਢੇਰ_ਮੰਜ਼ਿਲ_XRAM();

                ਜੇ( xTaskIncrementTick() != pdFALSE )
                {
                        vTaskSwitchContext();
                }

                ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_FLAG();
                ਪੋਰਟ_COPY_XRAM_ਮੰਜ਼ਿਲ_ਢੇਰ();
                ਪੋਰਟ_RESTORE_CONTEXT();
        }
#ਨਹੀਂਤਾਂ
        ਖਾਲੀ vTimer2ISR( ਖਾਲੀ ) ਰੁਕਾਵਟ 5
        {
                /* When using the cooperative scheduler the timer 2 ISR is only
                required to increment the RTOS tick count. */

                xTaskIncrementTick();
                ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_FLAG();
        }
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
uint8_t ucOriginalSFRPage;

/* Constants calculated to give the required timer capture values. */
ਅਚਲ uint32_t ul_Ticks_ਪ੍ਰਤੀ_ਦੂਜਾ = configCPU_CLOCK_HZ / ਪੋਰਟ_CLOCK_ਭਾਜਕ;
ਅਚਲ uint32_t ul_Capture_ਸਮਾਂ = ul_Ticks_ਪ੍ਰਤੀ_ਦੂਜਾ / config_TICK_ਦਰ_HZ;
ਅਚਲ uint32_t ul_Capture_ਮੁੱਲ = ਪੋਰਟ_MAX_TIMER_ਮੁੱਲ - ul_Capture_ਸਮਾਂ;
ਅਚਲ uint8_t uc_ਨੀਵਾਂ_Capture_Byte = ( uint8_t ) ( ul_Capture_ਮੁੱਲ & ( uint32_t ) 0xff );
ਅਚਲ uint8_t uc_ਉੱਚਾ_Capture_Byte = ( uint8_t ) ( ul_Capture_ਮੁੱਲ >> ( uint32_t ) 8 );

        /* NOTE:  This uses a timer only present on 8052 architecture. */

        /* Remember the current SFR page so we can restore it at the end of the
        function. */
        ucOriginalSFRPage = SFRPAGE;
        SFRPAGE = 0;

        /* TMR2CF can be left in its default state. */
        TMR2CF = ( uint8_t ) 0;

        /* Setup the overflow reload value. */
        RCAP2L = uc_ਨੀਵਾਂ_Capture_Byte;
        RCAP2H = uc_ਉੱਚਾ_Capture_Byte;

        /* The initial load is performed manually. */
        TMR2L = uc_ਨੀਵਾਂ_Capture_Byte;
        TMR2H = uc_ਉੱਚਾ_Capture_Byte;

        /* Enable the timer 2 interrupts. */
        IE |= ਪੋਰਟ_TIMER_2_ਰੁਕਾਵਟ_ENABLE;

        /* Interrupts are disabled when this is called so the timer can be started
        here. */
        TMR2CN = ਪੋਰਟ_ENABLE_TIMER;

        /* Restore the original SFR page. */
        SFRPAGE = ucOriginalSFRPage;
}
