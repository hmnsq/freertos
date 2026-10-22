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
#ಅನ್ತರ್ಭಾವ <string.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Constants required to setup timer 2 to produce the RTOS tick. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ                               ( ( uint32_t ) 12 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_TIMER_ಮೌಲ್ಯ                             ( ( uint32_t ) 0xffff )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_TIMER                                ( ( uint8_t ) 0x04 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_2_ಅಡಚಣೆ_ENABLE                    ( ( uint8_t ) 0x20 )

/* The value used in the IE register when a task first starts. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GLOBAL_ಅಡಚಣೆ_ಬಿಟ್                        ( ( ರಾಶಿ_Type_t ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSW                                 ( ( ರಾಶಿ_Type_t ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_FLAG()                      TMR2CN &= ~0x80;

/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
ದತ್ತಾಂಶ_2 ಸ್ಥಿರ uint8_t uc_ರಾಶಿ_ಬೈಟುಗಳು;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
xdata ಸ್ಥಿರ ರಾಶಿ_Type_t * ದತ್ತಾಂಶ_2 pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
ದತ್ತಾಂಶ_2 ಸ್ಥಿರ ರಾಶಿ_Type_t * ದತ್ತಾಂಶ_2 pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ TCB_t;
ಬಾಹ್ಯ ಅಸ್ಥಿರ TCB_t * ಅಸ್ಥಿರ pxCurrentTCB;

/*
 * Setup the hardware to generate an interrupt off timer 2 at the required
 * frequency.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/
/*
 * Macro that copies the current stack from internal RAM to XRAM.  This is
 * required as the 8051 only contains enough internal RAM for a single stack,
 * but we have a stack for every task.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_COPY_ರಾಶಿ_ಗಮ್ಯ_XRAM()                                                            \
{                                                                                           \
        /* pxCurrentTCB points to a TCB which itself points to the location into            \
        which the first stack byte should be copied. Set pxXRAMStack to point               \
        to the location into which the first stack byte is to be copied. */                 \
        pxXRAMStack = ( xdata ರಾಶಿ_Type_t * ) *( ( xdata ರಾಶಿ_Type_t ** ) pxCurrentTCB );   \
                                                                                            \
        /* Set pxRAMStack to point to the first byte to be coped from the stack. */         \
        pxRAMStack = ( ದತ್ತಾಂಶ_2 ರಾಶಿ_Type_t * ದತ್ತಾಂಶ_2 ) config_ರಾಶಿ_ಆರಂಭ;                         \
                                                                                            \
        /* Calculate the size of the stack we are about to copy from the current            \
        stack pointer value. */                                                             \
        uc_ರಾಶಿ_ಬೈಟುಗಳು = SP - ( config_ರಾಶಿ_ಆರಂಭ - 1 );                                      \
                                                                                            \
        /* Before starting to copy the stack, store the calculated stack size so            \
        the stack can be restored when the task is resumed. */                              \
        *pxXRAMStack = uc_ರಾಶಿ_ಬೈಟುಗಳು;                                                        \
                                                                                            \
        /* Copy each stack byte in turn.  pxXRAMStack is incremented first as we            \
        have already stored the stack size into XRAM. */                                    \
        ಆಗ( uc_ರಾಶಿ_ಬೈಟುಗಳು )                                                               \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                *pxXRAMStack = *pxRAMStack;                                                 \
                pxRAMStack++;                                                               \
                uc_ರಾಶಿ_ಬೈಟುಗಳು--;                                                             \
        }                                                                                   \
}
/*-----------------------------------------------------------*/

/*
 * Macro that copies the stack of the task being resumed from XRAM into
 * internal RAM.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_COPY_XRAM_ಗಮ್ಯ_ರಾಶಿ()                                                            \
{                                                                                           \
        /* Setup the pointers as per portCOPY_STACK_TO_XRAM(), but this time to             \
        copy the data back out of XRAM and into the stack. */                               \
        pxXRAMStack = ( xdata ರಾಶಿ_Type_t * ) *( ( xdata ರಾಶಿ_Type_t ** ) pxCurrentTCB );   \
        pxRAMStack = ( ದತ್ತಾಂಶ_2 ರಾಶಿ_Type_t * ದತ್ತಾಂಶ_2 ) ( config_ರಾಶಿ_ಆರಂಭ - 1 );                 \
                                                                                            \
        /* The first value stored in XRAM was the size of the stack - i.e. the              \
        number of bytes we need to copy back. */                                            \
        uc_ರಾಶಿ_ಬೈಟುಗಳು = pxXRAMStack[ 0 ];                                                    \
                                                                                            \
        /* Copy the required number of bytes back into the stack. */                        \
        ಮಾಡು                                                                                  \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                pxRAMStack++;                                                               \
                *pxRAMStack = *pxXRAMStack;                                                 \
                uc_ರಾಶಿ_ಬೈಟುಗಳು--;                                                             \
        } ಆಗ( uc_ರಾಶಿ_ಬೈಟುಗಳು );                                                            \
                                                                                            \
        /* Restore the stack pointer ready to use the restored stack. */                    \
        SP = ( uint8_t ) pxRAMStack;                                                        \
}
/*-----------------------------------------------------------*/

/*
 * Macro to push the current execution context onto the stack, before the stack
 * is moved to XRAM.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SAVE_CONTEXT()                                                                  \
{                                                                                           \
        _asm                                                                                \
                /* Push ACC first, as when restoring the context it must be restored        \
                last (it is used to set the IE register). */                                \
                ತಳ್ಳು        ACC                                                             \
                /* Store the IE register then disable interrupts. */                        \
                ತಳ್ಳು        IE                                                              \
                clr                _EA                                                      \
                ತಳ್ಳು        DPL                                                             \
                ತಳ್ಳು        DPH                                                             \
                ತಳ್ಳು        b                                                               \
                ತಳ್ಳು        ar2                                                             \
                ತಳ್ಳು        ar3                                                             \
                ತಳ್ಳು        ar4                                                             \
                ತಳ್ಳು        ar5                                                             \
                ತಳ್ಳು        ar6                                                             \
                ತಳ್ಳು        ar7                                                             \
                ತಳ್ಳು        ar0                                                             \
                ತಳ್ಳು        ar1                                                             \
                ತಳ್ಳು        PSW                                                             \
        _endasm;                                                                            \
                PSW = 0;                                                                    \
        _asm                                                                                \
                ತಳ್ಳು        _bp                                                             \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * Macro that restores the execution context from the stack.  The execution
 * context was saved into the stack before the stack was copied into XRAM.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESTORE_CONTEXT()                                                               \
{                                                                                           \
        _asm                                                                                \
                ತೆಗೆ_2                _bp                                                      \
                ತೆಗೆ_2                PSW                                                      \
                ತೆಗೆ_2                ar1                                                      \
                ತೆಗೆ_2                ar0                                                      \
                ತೆಗೆ_2                ar7                                                      \
                ತೆಗೆ_2                ar6                                                      \
                ತೆಗೆ_2                ar5                                                      \
                ತೆಗೆ_2                ar4                                                      \
                ತೆಗೆ_2                ar3                                                      \
                ತೆಗೆ_2                ar2                                                      \
                ತೆಗೆ_2                b                                                        \
                ತೆಗೆ_2                DPH                                                      \
                ತೆಗೆ_2                DPL                                                      \
                /* The next byte of the stack is the IE register.  Only the global          \
                enable bit forms part of the task context.  Pop off the IE then set         \
                the global enable bit to match that of the stored IE register. */           \
                ತೆಗೆ_2                ACC                                                      \
                JB                ACC.7,0098$                                               \
                CLR                IE.7                                                     \
                LJMP        0099$                                                           \
        0098$:                                                                              \
                SETB        IE.7                                                            \
        0099$:                                                                              \
                /* Finally pop off the ACC, which was the first register saved. */          \
                ತೆಗೆ_2                ACC                                                      \
                reti                                                                        \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t *px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_ದ_ರಾಶಿ, TaskFunction_t px_ಸಂಕೇತ, ಶೂನ್ಯ *pvParameters )
{
uint32_t ul_ವಿಳಾಸ;
ರಾಶಿ_Type_t *px_ಆರಂಭ_ದ_ರಾಶಿ;

        /* Leave space to write the size of the stack as the first byte. */
        px_ಆರಂಭ_ದ_ರಾಶಿ = px_ತುದಿ_ದ_ರಾಶಿ;
        px_ತುದಿ_ದ_ರಾಶಿ++;

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
        ul_ವಿಳಾಸ = ( uint32_t ) px_ಸಂಕೇತ;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ul_ವಿಳಾಸ;
        ul_ವಿಳಾಸ >>= 8;
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ವಿಳಾಸ );
        px_ತುದಿ_ದ_ರಾಶಿ++;

        /* Next all the registers will have been pushed by portSAVE_CONTEXT(). */
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xaa;        /* acc */
        px_ತುದಿ_ದ_ರಾಶಿ++;

        /* We want tasks to start with interrupts enabled. */
        *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_GLOBAL_ಅಡಚಣೆ_ಬಿಟ್;
        px_ತುದಿ_ದ_ರಾಶಿ++;

        /* The function parameters will be passed in the DPTR and B register as
        a three byte generic pointer is used. */
        ul_ವಿಳಾಸ = ( uint32_t ) pvParameters;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ul_ವಿಳಾಸ;        /* DPL */
        ul_ವಿಳಾಸ >>= 8;
        *px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ul_ವಿಳಾಸ;        /* DPH */
        ul_ವಿಳಾಸ >>= 8;
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ul_ವಿಳಾಸ;        /* b */
        px_ತುದಿ_ದ_ರಾಶಿ++;

        /* The remaining registers are straight forward. */
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x02;        /* R2 */
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x03;        /* R3 */
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x04;        /* R4 */
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x05;        /* R5 */
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x06;        /* R6 */
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x07;        /* R7 */
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x00;        /* R0 */
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x01;        /* R1 */
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x00;        /* PSW */
        px_ತುದಿ_ದ_ರಾಶಿ++;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xbb;        /* BP */

        /* Dont increment the stack size here as we don't want to include
        the stack size byte as part of the stack size count.

        Finally we place the stack size at the beginning. */
        *px_ಆರಂಭ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( px_ತುದಿ_ದ_ರಾಶಿ - px_ಆರಂಭ_ದ_ರಾಶಿ );

        /* Unlike most ports, we return the start of the stack as this is where the
        size of the stack is stored. */
        ಹಿಂತಿರುಗಿ px_ಆರಂಭ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
        /* Setup timer 2 to generate the RTOS tick. */
        prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

        /* Make sure we start with the expected SFR page.  This line should not
        really be required. */
        SFRPAGE = 0;

        /* Copy the stack for the first task to execute from XRAM into the stack,
        restore the task context from the new stack, then start running the task. */
        ಪೋರ್ಟ್_COPY_XRAM_ಗಮ್ಯ_ರಾಶಿ();
        ಪೋರ್ಟ್_RESTORE_CONTEXT();

        /* Should never get here! */
        ಹಿಂತಿರುಗಿ pdTRUE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
        /* Not implemented for this port. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ ) _naked
{
        /* Save the execution context onto the stack, then copy the entire stack
        to XRAM.  This is necessary as the internal RAM is only large enough to
        hold one stack, and we want one per task.

        PERFORMANCE COULD BE IMPROVED BY ONLY COPYING TO XRAM IF A TASK SWITCH
        IS REQUIRED. */
        ಪೋರ್ಟ್_SAVE_CONTEXT();
        ಪೋರ್ಟ್_COPY_ರಾಶಿ_ಗಮ್ಯ_XRAM();

        /* Call the standard scheduler context switch function. */
        vTaskSwitchContext();

        /* Copy the stack of the task about to execute from XRAM into RAM and
        restore it's context ready to run on exiting. */
        ಪೋರ್ಟ್_COPY_XRAM_ಗಮ್ಯ_ರಾಶಿ();
        ಪೋರ್ಟ್_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

#ಆದರೆ configUSE_PREEMPTION == 1
        ಶೂನ್ಯ vTimer2ISR( ಶೂನ್ಯ ) ಅಡಚಣೆ 5 _naked
        {
                /* Preemptive context switch function triggered by the timer 2 ISR.
                This does the same as vPortYield() (see above) with the addition
                of incrementing the RTOS tick count. */

                ಪೋರ್ಟ್_SAVE_CONTEXT();
                ಪೋರ್ಟ್_COPY_ರಾಶಿ_ಗಮ್ಯ_XRAM();

                ಆದರೆ( xTaskIncrementTick() != pdFALSE )
                {
                        vTaskSwitchContext();
                }

                ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_FLAG();
                ಪೋರ್ಟ್_COPY_XRAM_ಗಮ್ಯ_ರಾಶಿ();
                ಪೋರ್ಟ್_RESTORE_CONTEXT();
        }
#ಇಲ್ಲದಿದ್ದರೆ
        ಶೂನ್ಯ vTimer2ISR( ಶೂನ್ಯ ) ಅಡಚಣೆ 5
        {
                /* When using the cooperative scheduler the timer 2 ISR is only
                required to increment the RTOS tick count. */

                xTaskIncrementTick();
                ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_FLAG();
        }
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
uint8_t ucOriginalSFRPage;

/* Constants calculated to give the required timer capture values. */
ಸ್ಥಿರಾಂಕ uint32_t ul_Ticks_ಪ್ರತಿ_ಎರಡನೇ = configCPU_CLOCK_HZ / ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ;
ಸ್ಥಿರಾಂಕ uint32_t ul_Capture_ಸಮಯ = ul_Ticks_ಪ್ರತಿ_ಎರಡನೇ / config_TICK_ದರ_HZ;
ಸ್ಥಿರಾಂಕ uint32_t ul_Capture_ಮೌಲ್ಯ = ಪೋರ್ಟ್_MAX_TIMER_ಮೌಲ್ಯ - ul_Capture_ಸಮಯ;
ಸ್ಥಿರಾಂಕ uint8_t uc_ಕೆಳಗಿನ_Capture_Byte = ( uint8_t ) ( ul_Capture_ಮೌಲ್ಯ & ( uint32_t ) 0xff );
ಸ್ಥಿರಾಂಕ uint8_t uc_ಮೇಲಿನ_Capture_Byte = ( uint8_t ) ( ul_Capture_ಮೌಲ್ಯ >> ( uint32_t ) 8 );

        /* NOTE:  This uses a timer only present on 8052 architecture. */

        /* Remember the current SFR page so we can restore it at the end of the
        function. */
        ucOriginalSFRPage = SFRPAGE;
        SFRPAGE = 0;

        /* TMR2CF can be left in its default state. */
        TMR2CF = ( uint8_t ) 0;

        /* Setup the overflow reload value. */
        RCAP2L = uc_ಕೆಳಗಿನ_Capture_Byte;
        RCAP2H = uc_ಮೇಲಿನ_Capture_Byte;

        /* The initial load is performed manually. */
        TMR2L = uc_ಕೆಳಗಿನ_Capture_Byte;
        TMR2H = uc_ಮೇಲಿನ_Capture_Byte;

        /* Enable the timer 2 interrupts. */
        IE |= ಪೋರ್ಟ್_TIMER_2_ಅಡಚಣೆ_ENABLE;

        /* Interrupts are disabled when this is called so the timer can be started
        here. */
        TMR2CN = ಪೋರ್ಟ್_ENABLE_TIMER;

        /* Restore the original SFR page. */
        SFRPAGE = ucOriginalSFRPage;
}
