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
#अन्तर्भाव <string.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Constants required to setup timer 2 to produce the RTOS tick. */
#परिभाषय पत्तनम्_CLOCK_भाजकः                               ( ( uint32_t ) 12 )
#परिभाषय पत्तनम्_MAX_TIMER_मानम्                             ( ( uint32_t ) 0xffff )
#परिभाषय पत्तनम्_ENABLE_TIMER                                ( ( uint8_t ) 0x04 )
#परिभाषय पत्तनम्_TIMER_2_व्यवधानम्_ENABLE                    ( ( uint8_t ) 0x20 )

/* The value used in the IE register when a task first starts. */
#परिभाषय पत्तनम्_GLOBAL_व्यवधानम्_BIT                        ( ( राशिः_Type_t ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#परिभाषय पत्तनम्_INITIAL_PSW                                 ( ( राशिः_Type_t ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_FLAG()                      TMR2CN &= ~0x80;

/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
दत्त_2 स्थिर uint8_t uc_राशिः_अष्टकानि;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
xdata स्थिर राशिः_Type_t * दत्त_2 pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
दत्त_2 स्थिर राशिः_Type_t * दत्त_2 pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
प्रकारनिर्देश शून्य TCB_t;
बाह्य चञ्चल TCB_t * चञ्चल pxCurrentTCB;

/*
 * Setup the hardware to generate an interrupt off timer 2 at the required
 * frequency.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/*-----------------------------------------------------------*/
/*
 * Macro that copies the current stack from internal RAM to XRAM.  This is
 * required as the 8051 only contains enough internal RAM for a single stack,
 * but we have a stack for every task.
 */
#परिभाषय पत्तनम्_COPY_राशिः_गन्तव्यम्_XRAM()                                                            \
{                                                                                           \
        /* pxCurrentTCB points to a TCB which itself points to the location into            \
        which the first stack byte should be copied. Set pxXRAMStack to point               \
        to the location into which the first stack byte is to be copied. */                 \
        pxXRAMStack = ( xdata राशिः_Type_t * ) *( ( xdata राशिः_Type_t ** ) pxCurrentTCB );   \
                                                                                            \
        /* Set pxRAMStack to point to the first byte to be coped from the stack. */         \
        pxRAMStack = ( दत्त_2 राशिः_Type_t * दत्त_2 ) config_राशिः_START;                         \
                                                                                            \
        /* Calculate the size of the stack we are about to copy from the current            \
        stack pointer value. */                                                             \
        uc_राशिः_अष्टकानि = SP - ( config_राशिः_START - 1 );                                      \
                                                                                            \
        /* Before starting to copy the stack, store the calculated stack size so            \
        the stack can be restored when the task is resumed. */                              \
        *pxXRAMStack = uc_राशिः_अष्टकानि;                                                        \
                                                                                            \
        /* Copy each stack byte in turn.  pxXRAMStack is incremented first as we            \
        have already stored the stack size into XRAM. */                                    \
        यावत्( uc_राशिः_अष्टकानि )                                                               \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                *pxXRAMStack = *pxRAMStack;                                                 \
                pxRAMStack++;                                                               \
                uc_राशिः_अष्टकानि--;                                                             \
        }                                                                                   \
}
/*-----------------------------------------------------------*/

/*
 * Macro that copies the stack of the task being resumed from XRAM into
 * internal RAM.
 */
#परिभाषय पत्तनम्_COPY_XRAM_गन्तव्यम्_राशिः()                                                            \
{                                                                                           \
        /* Setup the pointers as per portCOPY_STACK_TO_XRAM(), but this time to             \
        copy the data back out of XRAM and into the stack. */                               \
        pxXRAMStack = ( xdata राशिः_Type_t * ) *( ( xdata राशिः_Type_t ** ) pxCurrentTCB );   \
        pxRAMStack = ( दत्त_2 राशिः_Type_t * दत्त_2 ) ( config_राशिः_START - 1 );                 \
                                                                                            \
        /* The first value stored in XRAM was the size of the stack - i.e. the              \
        number of bytes we need to copy back. */                                            \
        uc_राशिः_अष्टकानि = pxXRAMStack[ 0 ];                                                    \
                                                                                            \
        /* Copy the required number of bytes back into the stack. */                        \
        कुरु                                                                                  \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                pxRAMStack++;                                                               \
                *pxRAMStack = *pxXRAMStack;                                                 \
                uc_राशिः_अष्टकानि--;                                                             \
        } यावत्( uc_राशिः_अष्टकानि );                                                            \
                                                                                            \
        /* Restore the stack pointer ready to use the restored stack. */                    \
        SP = ( uint8_t ) pxRAMStack;                                                        \
}
/*-----------------------------------------------------------*/

/*
 * Macro to push the current execution context onto the stack, before the stack
 * is moved to XRAM.
 */
#परिभाषय पत्तनम्_SAVE_CONTEXT()                                                                  \
{                                                                                           \
        _asm                                                                                \
                /* Push ACC first, as when restoring the context it must be restored        \
                last (it is used to set the IE register). */                                \
                प्रक्षिप        ACC                                                             \
                /* Store the IE register then disable interrupts. */                        \
                प्रक्षिप        IE                                                              \
                clr                _EA                                                      \
                प्रक्षिप        DPL                                                             \
                प्रक्षिप        DPH                                                             \
                प्रक्षिप        b                                                               \
                प्रक्षिप        ar2                                                             \
                प्रक्षिप        ar3                                                             \
                प्रक्षिप        ar4                                                             \
                प्रक्षिप        ar5                                                             \
                प्रक्षिप        ar6                                                             \
                प्रक्षिप        ar7                                                             \
                प्रक्षिप        ar0                                                             \
                प्रक्षिप        ar1                                                             \
                प्रक्षिप        PSW                                                             \
        _endasm;                                                                            \
                PSW = 0;                                                                    \
        _asm                                                                                \
                प्रक्षिप        _bp                                                             \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * Macro that restores the execution context from the stack.  The execution
 * context was saved into the stack before the stack was copied into XRAM.
 */
#परिभाषय पत्तनम्_RESTORE_CONTEXT()                                                               \
{                                                                                           \
        _asm                                                                                \
                निष्कासय                _bp                                                      \
                निष्कासय                PSW                                                      \
                निष्कासय                ar1                                                      \
                निष्कासय                ar0                                                      \
                निष्कासय                ar7                                                      \
                निष्कासय                ar6                                                      \
                निष्कासय                ar5                                                      \
                निष्कासय                ar4                                                      \
                निष्कासय                ar3                                                      \
                निष्कासय                ar2                                                      \
                निष्कासय                b                                                        \
                निष्कासय                DPH                                                      \
                निष्कासय                DPL                                                      \
                /* The next byte of the stack is the IE register.  Only the global          \
                enable bit forms part of the task context.  Pop off the IE then set         \
                the global enable bit to match that of the stored IE register. */           \
                निष्कासय                ACC                                                      \
                JB                ACC.7,0098$                                               \
                CLR                IE.7                                                     \
                LJMP        0099$                                                           \
        0098$:                                                                              \
                SETB        IE.7                                                            \
        0099$:                                                                              \
                /* Finally pop off the ACC, which was the first register saved. */          \
                निष्कासय                ACC                                                      \
                reti                                                                        \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t *px_पत्तनम्_Initialise_राशिः( राशिः_Type_t *px_शिखरम्_सम्बन्धि_राशिः, TaskFunction_t px_संहिता, शून्य *pvParameters )
{
uint32_t ul_स्थानाङ्कः;
राशिः_Type_t *px_Start_सम्बन्धि_राशिः;

        /* Leave space to write the size of the stack as the first byte. */
        px_Start_सम्बन्धि_राशिः = px_शिखरम्_सम्बन्धि_राशिः;
        px_शिखरम्_सम्बन्धि_राशिः++;

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
        ul_स्थानाङ्कः = ( uint32_t ) px_संहिता;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ul_स्थानाङ्कः;
        ul_स्थानाङ्कः >>= 8;
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( ul_स्थानाङ्कः );
        px_शिखरम्_सम्बन्धि_राशिः++;

        /* Next all the registers will have been pushed by portSAVE_CONTEXT(). */
        *px_शिखरम्_सम्बन्धि_राशिः = 0xaa;        /* acc */
        px_शिखरम्_सम्बन्धि_राशिः++;

        /* We want tasks to start with interrupts enabled. */
        *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_GLOBAL_व्यवधानम्_BIT;
        px_शिखरम्_सम्बन्धि_राशिः++;

        /* The function parameters will be passed in the DPTR and B register as
        a three byte generic pointer is used. */
        ul_स्थानाङ्कः = ( uint32_t ) pvParameters;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ul_स्थानाङ्कः;        /* DPL */
        ul_स्थानाङ्कः >>= 8;
        *px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ul_स्थानाङ्कः;        /* DPH */
        ul_स्थानाङ्कः >>= 8;
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ul_स्थानाङ्कः;        /* b */
        px_शिखरम्_सम्बन्धि_राशिः++;

        /* The remaining registers are straight forward. */
        *px_शिखरम्_सम्बन्धि_राशिः = 0x02;        /* R2 */
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x03;        /* R3 */
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x04;        /* R4 */
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x05;        /* R5 */
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x06;        /* R6 */
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x07;        /* R7 */
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x00;        /* R0 */
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x01;        /* R1 */
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x00;        /* PSW */
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = 0xbb;        /* BP */

        /* Dont increment the stack size here as we don't want to include
        the stack size byte as part of the stack size count.

        Finally we place the stack size at the beginning. */
        *px_Start_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( px_शिखरम्_सम्बन्धि_राशिः - px_Start_सम्बन्धि_राशिः );

        /* Unlike most ports, we return the start of the stack as this is where the
        size of the stack is stored. */
        प्रत्यागम px_Start_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
        /* Setup timer 2 to generate the RTOS tick. */
        prv_सज्जता_Timer_व्यवधानम्();

        /* Make sure we start with the expected SFR page.  This line should not
        really be required. */
        SFRPAGE = 0;

        /* Copy the stack for the first task to execute from XRAM into the stack,
        restore the task context from the new stack, then start running the task. */
        पत्तनम्_COPY_XRAM_गन्तव्यम्_राशिः();
        पत्तनम्_RESTORE_CONTEXT();

        /* Should never get here! */
        प्रत्यागम pdTRUE;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
        /* Not implemented for this port. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
शून्य v_पत्तनम्_Yield( शून्य ) _naked
{
        /* Save the execution context onto the stack, then copy the entire stack
        to XRAM.  This is necessary as the internal RAM is only large enough to
        hold one stack, and we want one per task.

        PERFORMANCE COULD BE IMPROVED BY ONLY COPYING TO XRAM IF A TASK SWITCH
        IS REQUIRED. */
        पत्तनम्_SAVE_CONTEXT();
        पत्तनम्_COPY_राशिः_गन्तव्यम्_XRAM();

        /* Call the standard scheduler context switch function. */
        vTaskSwitchContext();

        /* Copy the stack of the task about to execute from XRAM into RAM and
        restore it's context ready to run on exiting. */
        पत्तनम्_COPY_XRAM_गन्तव्यम्_राशिः();
        पत्तनम्_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

#यदि configUSE_PREEMPTION == 1
        शून्य vTimer2ISR( शून्य ) व्यवधानम् 5 _naked
        {
                /* Preemptive context switch function triggered by the timer 2 ISR.
                This does the same as vPortYield() (see above) with the addition
                of incrementing the RTOS tick count. */

                पत्तनम्_SAVE_CONTEXT();
                पत्तनम्_COPY_राशिः_गन्तव्यम्_XRAM();

                यदि( xTaskIncrementTick() != pdFALSE )
                {
                        vTaskSwitchContext();
                }

                पत्तनम्_CLEAR_व्यवधानम्_FLAG();
                पत्तनम्_COPY_XRAM_गन्तव्यम्_राशिः();
                पत्तनम्_RESTORE_CONTEXT();
        }
#अन्यथा
        शून्य vTimer2ISR( शून्य ) व्यवधानम् 5
        {
                /* When using the cooperative scheduler the timer 2 ISR is only
                required to increment the RTOS tick count. */

                xTaskIncrementTick();
                पत्तनम्_CLEAR_व्यवधानम्_FLAG();
        }
#यदि_अन्तः
/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
uint8_t ucOriginalSFRPage;

/* Constants calculated to give the required timer capture values. */
ध्रुव uint32_t ul_Ticks_प्रत्येकम्_Second = configCPU_CLOCK_HZ / पत्तनम्_CLOCK_भाजकः;
ध्रुव uint32_t ulCaptureTime = ul_Ticks_प्रत्येकम्_Second / config_TICK_दरः_HZ;
ध्रुव uint32_t ul_Capture_मानम् = पत्तनम्_MAX_TIMER_मानम् - ulCaptureTime;
ध्रुव uint8_t uc_नीचः_Capture_Byte = ( uint8_t ) ( ul_Capture_मानम् & ( uint32_t ) 0xff );
ध्रुव uint8_t uc_उच्चः_Capture_Byte = ( uint8_t ) ( ul_Capture_मानम् >> ( uint32_t ) 8 );

        /* NOTE:  This uses a timer only present on 8052 architecture. */

        /* Remember the current SFR page so we can restore it at the end of the
        function. */
        ucOriginalSFRPage = SFRPAGE;
        SFRPAGE = 0;

        /* TMR2CF can be left in its default state. */
        TMR2CF = ( uint8_t ) 0;

        /* Setup the overflow reload value. */
        RCAP2L = uc_नीचः_Capture_Byte;
        RCAP2H = uc_उच्चः_Capture_Byte;

        /* The initial load is performed manually. */
        TMR2L = uc_नीचः_Capture_Byte;
        TMR2H = uc_उच्चः_Capture_Byte;

        /* Enable the timer 2 interrupts. */
        IE |= पत्तनम्_TIMER_2_व्यवधानम्_ENABLE;

        /* Interrupts are disabled when this is called so the timer can be started
        here. */
        TMR2CN = पत्तनम्_ENABLE_TIMER;

        /* Restore the original SFR page. */
        SFRPAGE = ucOriginalSFRPage;
}
