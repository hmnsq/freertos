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
#ضمن <string.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Constants required to setup timer 2 to produce the RTOS tick. */
#وصف_ڪريو پورٽ_CLOCK_ورهائيندڙ                               ( ( uint32_t ) 12 )
#وصف_ڪريو پورٽ_MAX_TIMER_قدر                             ( ( uint32_t ) 0xffff )
#وصف_ڪريو پورٽ_ENABLE_TIMER                                ( ( uint8_t ) 0x04 )
#وصف_ڪريو پورٽ_TIMER_2_مداخلت_ENABLE                    ( ( uint8_t ) 0x20 )

/* The value used in the IE register when a task first starts. */
#وصف_ڪريو پورٽ_GLOBAL_مداخلت_ٻٽو_انگ                        ( ( ڍير_Type_t ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#وصف_ڪريو پورٽ_INITIAL_PSW                                 ( ( ڍير_Type_t ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#وصف_ڪريو پورٽ_CLEAR_مداخلت_FLAG()                      TMR2CN &= ~0x80;

/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
معلومات_2 ساكن uint8_t uc_ڍير_بائيٽون;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
xdata ساكن ڍير_Type_t * معلومات_2 pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
معلومات_2 ساكن ڍير_Type_t * معلومات_2 pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

/*
 * Setup the hardware to generate an interrupt off timer 2 at the required
 * frequency.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

/*-----------------------------------------------------------*/
/*
 * Macro that copies the current stack from internal RAM to XRAM.  This is
 * required as the 8051 only contains enough internal RAM for a single stack,
 * but we have a stack for every task.
 */
#وصف_ڪريو پورٽ_COPY_ڍير_منزل_XRAM()                                                            \
{                                                                                           \
        /* pxCurrentTCB points to a TCB which itself points to the location into            \
        which the first stack byte should be copied. Set pxXRAMStack to point               \
        to the location into which the first stack byte is to be copied. */                 \
        pxXRAMStack = ( xdata ڍير_Type_t * ) *( ( xdata ڍير_Type_t ** ) pxCurrentTCB );   \
                                                                                            \
        /* Set pxRAMStack to point to the first byte to be coped from the stack. */         \
        pxRAMStack = ( معلومات_2 ڍير_Type_t * معلومات_2 ) config_ڍير_شروعات;                         \
                                                                                            \
        /* Calculate the size of the stack we are about to copy from the current            \
        stack pointer value. */                                                             \
        uc_ڍير_بائيٽون = SP - ( config_ڍير_شروعات - 1 );                                      \
                                                                                            \
        /* Before starting to copy the stack, store the calculated stack size so            \
        the stack can be restored when the task is resumed. */                              \
        *pxXRAMStack = uc_ڍير_بائيٽون;                                                        \
                                                                                            \
        /* Copy each stack byte in turn.  pxXRAMStack is incremented first as we            \
        have already stored the stack size into XRAM. */                                    \
        طالما( uc_ڍير_بائيٽون )                                                               \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                *pxXRAMStack = *pxRAMStack;                                                 \
                pxRAMStack++;                                                               \
                uc_ڍير_بائيٽون--;                                                             \
        }                                                                                   \
}
/*-----------------------------------------------------------*/

/*
 * Macro that copies the stack of the task being resumed from XRAM into
 * internal RAM.
 */
#وصف_ڪريو پورٽ_COPY_XRAM_منزل_ڍير()                                                            \
{                                                                                           \
        /* Setup the pointers as per portCOPY_STACK_TO_XRAM(), but this time to             \
        copy the data back out of XRAM and into the stack. */                               \
        pxXRAMStack = ( xdata ڍير_Type_t * ) *( ( xdata ڍير_Type_t ** ) pxCurrentTCB );   \
        pxRAMStack = ( معلومات_2 ڍير_Type_t * معلومات_2 ) ( config_ڍير_شروعات - 1 );                 \
                                                                                            \
        /* The first value stored in XRAM was the size of the stack - i.e. the              \
        number of bytes we need to copy back. */                                            \
        uc_ڍير_بائيٽون = pxXRAMStack[ 0 ];                                                    \
                                                                                            \
        /* Copy the required number of bytes back into the stack. */                        \
        افعل                                                                                  \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                pxRAMStack++;                                                               \
                *pxRAMStack = *pxXRAMStack;                                                 \
                uc_ڍير_بائيٽون--;                                                             \
        } طالما( uc_ڍير_بائيٽون );                                                            \
                                                                                            \
        /* Restore the stack pointer ready to use the restored stack. */                    \
        SP = ( uint8_t ) pxRAMStack;                                                        \
}
/*-----------------------------------------------------------*/

/*
 * Macro to push the current execution context onto the stack, before the stack
 * is moved to XRAM.
 */
#وصف_ڪريو پورٽ_SAVE_CONTEXT()                                                                  \
{                                                                                           \
        _asm                                                                                \
                /* Push ACC first, as when restoring the context it must be restored        \
                last (it is used to set the IE register). */                                \
                ڌڪو        ACC                                                             \
                /* Store the IE register then disable interrupts. */                        \
                ڌڪو        IE                                                              \
                clr                _EA                                                      \
                ڌڪو        DPL                                                             \
                ڌڪو        DPH                                                             \
                ڌڪو        b                                                               \
                ڌڪو        ar2                                                             \
                ڌڪو        ar3                                                             \
                ڌڪو        ar4                                                             \
                ڌڪو        ar5                                                             \
                ڌڪو        ar6                                                             \
                ڌڪو        ar7                                                             \
                ڌڪو        ar0                                                             \
                ڌڪو        ar1                                                             \
                ڌڪو        PSW                                                             \
        _endasm;                                                                            \
                PSW = 0;                                                                    \
        _asm                                                                                \
                ڌڪو        _bp                                                             \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * Macro that restores the execution context from the stack.  The execution
 * context was saved into the stack before the stack was copied into XRAM.
 */
#وصف_ڪريو پورٽ_RESTORE_CONTEXT()                                                               \
{                                                                                           \
        _asm                                                                                \
                ڪڍو                _bp                                                      \
                ڪڍو                PSW                                                      \
                ڪڍو                ar1                                                      \
                ڪڍو                ar0                                                      \
                ڪڍو                ar7                                                      \
                ڪڍو                ar6                                                      \
                ڪڍو                ar5                                                      \
                ڪڍو                ar4                                                      \
                ڪڍو                ar3                                                      \
                ڪڍو                ar2                                                      \
                ڪڍو                b                                                        \
                ڪڍو                DPH                                                      \
                ڪڍو                DPL                                                      \
                /* The next byte of the stack is the IE register.  Only the global          \
                enable bit forms part of the task context.  Pop off the IE then set         \
                the global enable bit to match that of the stored IE register. */           \
                ڪڍو                ACC                                                      \
                JB                ACC.7,0098$                                               \
                CLR                IE.7                                                     \
                LJMP        0099$                                                           \
        0098$:                                                                              \
                SETB        IE.7                                                            \
        0099$:                                                                              \
                /* Finally pop off the ACC, which was the first register saved. */          \
                ڪڍو                ACC                                                      \
                reti                                                                        \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t *px_پورٽ_Initialise_ڍير( ڍير_Type_t *px_چوٽي_جو_ڍير, TaskFunction_t px_ڪوڊ, فراغ *pvParameters )
{
uint32_t ul_پتو;
ڍير_Type_t *px_شروعات_جو_ڍير;

        /* Leave space to write the size of the stack as the first byte. */
        px_شروعات_جو_ڍير = px_چوٽي_جو_ڍير;
        px_چوٽي_جو_ڍير++;

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
        ul_پتو = ( uint32_t ) px_ڪوڊ;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ul_پتو;
        ul_پتو >>= 8;
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( ul_پتو );
        px_چوٽي_جو_ڍير++;

        /* Next all the registers will have been pushed by portSAVE_CONTEXT(). */
        *px_چوٽي_جو_ڍير = 0xaa;        /* acc */
        px_چوٽي_جو_ڍير++;

        /* We want tasks to start with interrupts enabled. */
        *px_چوٽي_جو_ڍير = پورٽ_GLOBAL_مداخلت_ٻٽو_انگ;
        px_چوٽي_جو_ڍير++;

        /* The function parameters will be passed in the DPTR and B register as
        a three byte generic pointer is used. */
        ul_پتو = ( uint32_t ) pvParameters;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ul_پتو;        /* DPL */
        ul_پتو >>= 8;
        *px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ul_پتو;        /* DPH */
        ul_پتو >>= 8;
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ul_پتو;        /* b */
        px_چوٽي_جو_ڍير++;

        /* The remaining registers are straight forward. */
        *px_چوٽي_جو_ڍير = 0x02;        /* R2 */
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = 0x03;        /* R3 */
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = 0x04;        /* R4 */
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = 0x05;        /* R5 */
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = 0x06;        /* R6 */
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = 0x07;        /* R7 */
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = 0x00;        /* R0 */
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = 0x01;        /* R1 */
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = 0x00;        /* PSW */
        px_چوٽي_جو_ڍير++;
        *px_چوٽي_جو_ڍير = 0xbb;        /* BP */

        /* Dont increment the stack size here as we don't want to include
        the stack size byte as part of the stack size count.

        Finally we place the stack size at the beginning. */
        *px_شروعات_جو_ڍير = ( ڍير_Type_t ) ( px_چوٽي_جو_ڍير - px_شروعات_جو_ڍير );

        /* Unlike most ports, we return the start of the stack as this is where the
        size of the stack is stored. */
        أرجع px_شروعات_جو_ڍير;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
        /* Setup timer 2 to generate the RTOS tick. */
        prv_تياري_Timer_مداخلت();

        /* Make sure we start with the expected SFR page.  This line should not
        really be required. */
        SFRPAGE = 0;

        /* Copy the stack for the first task to execute from XRAM into the stack,
        restore the task context from the new stack, then start running the task. */
        پورٽ_COPY_XRAM_منزل_ڍير();
        پورٽ_RESTORE_CONTEXT();

        /* Should never get here! */
        أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
        /* Not implemented for this port. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
فراغ v_پورٽ_Yield( فراغ ) _naked
{
        /* Save the execution context onto the stack, then copy the entire stack
        to XRAM.  This is necessary as the internal RAM is only large enough to
        hold one stack, and we want one per task.

        PERFORMANCE COULD BE IMPROVED BY ONLY COPYING TO XRAM IF A TASK SWITCH
        IS REQUIRED. */
        پورٽ_SAVE_CONTEXT();
        پورٽ_COPY_ڍير_منزل_XRAM();

        /* Call the standard scheduler context switch function. */
        vTaskSwitchContext();

        /* Copy the stack of the task about to execute from XRAM into RAM and
        restore it's context ready to run on exiting. */
        پورٽ_COPY_XRAM_منزل_ڍير();
        پورٽ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 1
        فراغ vTimer2ISR( فراغ ) مداخلت 5 _naked
        {
                /* Preemptive context switch function triggered by the timer 2 ISR.
                This does the same as vPortYield() (see above) with the addition
                of incrementing the RTOS tick count. */

                پورٽ_SAVE_CONTEXT();
                پورٽ_COPY_ڍير_منزل_XRAM();

                إذا( xTaskIncrementTick() != pdFALSE )
                {
                        vTaskSwitchContext();
                }

                پورٽ_CLEAR_مداخلت_FLAG();
                پورٽ_COPY_XRAM_منزل_ڍير();
                پورٽ_RESTORE_CONTEXT();
        }
#وإلا
        فراغ vTimer2ISR( فراغ ) مداخلت 5
        {
                /* When using the cooperative scheduler the timer 2 ISR is only
                required to increment the RTOS tick count. */

                xTaskIncrementTick();
                پورٽ_CLEAR_مداخلت_FLAG();
        }
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
uint8_t ucOriginalSFRPage;

/* Constants calculated to give the required timer capture values. */
ثابت uint32_t ul_Ticks_في_ٻيو = configCPU_CLOCK_HZ / پورٽ_CLOCK_ورهائيندڙ;
ثابت uint32_t ul_Capture_وقت = ul_Ticks_في_ٻيو / config_TICK_شرح_HZ;
ثابت uint32_t ul_Capture_قدر = پورٽ_MAX_TIMER_قدر - ul_Capture_وقت;
ثابت uint8_t uc_هيٺيون_Capture_Byte = ( uint8_t ) ( ul_Capture_قدر & ( uint32_t ) 0xff );
ثابت uint8_t uc_مٿاهون_Capture_Byte = ( uint8_t ) ( ul_Capture_قدر >> ( uint32_t ) 8 );

        /* NOTE:  This uses a timer only present on 8052 architecture. */

        /* Remember the current SFR page so we can restore it at the end of the
        function. */
        ucOriginalSFRPage = SFRPAGE;
        SFRPAGE = 0;

        /* TMR2CF can be left in its default state. */
        TMR2CF = ( uint8_t ) 0;

        /* Setup the overflow reload value. */
        RCAP2L = uc_هيٺيون_Capture_Byte;
        RCAP2H = uc_مٿاهون_Capture_Byte;

        /* The initial load is performed manually. */
        TMR2L = uc_هيٺيون_Capture_Byte;
        TMR2H = uc_مٿاهون_Capture_Byte;

        /* Enable the timer 2 interrupts. */
        IE |= پورٽ_TIMER_2_مداخلت_ENABLE;

        /* Interrupts are disabled when this is called so the timer can be started
        here. */
        TMR2CN = پورٽ_ENABLE_TIMER;

        /* Restore the original SFR page. */
        SFRPAGE = ucOriginalSFRPage;
}
