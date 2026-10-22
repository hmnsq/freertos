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
#تعریف_کړه پورټ_CLOCK_وېشونکی                               ( ( uint32_t ) 12 )
#تعریف_کړه پورټ_MAX_TIMER_ارزښت                             ( ( uint32_t ) 0xffff )
#تعریف_کړه پورټ_ENABLE_TIMER                                ( ( uint8_t ) 0x04 )
#تعریف_کړه پورټ_TIMER_2_مداخله_ENABLE                    ( ( uint8_t ) 0x20 )

/* The value used in the IE register when a task first starts. */
#تعریف_کړه پورټ_GLOBAL_مداخله_بټ                        ( ( ډېری_Type_t ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#تعریف_کړه پورټ_INITIAL_PSW                                 ( ( ډېری_Type_t ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#تعریف_کړه پورټ_CLEAR_مداخله_FLAG()                      TMR2CN &= ~0x80;

/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
معلومات_2 ساكن uint8_t uc_ډېری_بایټونه;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
xdata ساكن ډېری_Type_t * معلومات_2 pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
معلومات_2 ساكن ډېری_Type_t * معلومات_2 pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

/*
 * Setup the hardware to generate an interrupt off timer 2 at the required
 * frequency.
 */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

/*-----------------------------------------------------------*/
/*
 * Macro that copies the current stack from internal RAM to XRAM.  This is
 * required as the 8051 only contains enough internal RAM for a single stack,
 * but we have a stack for every task.
 */
#تعریف_کړه پورټ_COPY_ډېری_منزل_XRAM()                                                            \
{                                                                                           \
        /* pxCurrentTCB points to a TCB which itself points to the location into            \
        which the first stack byte should be copied. Set pxXRAMStack to point               \
        to the location into which the first stack byte is to be copied. */                 \
        pxXRAMStack = ( xdata ډېری_Type_t * ) *( ( xdata ډېری_Type_t ** ) pxCurrentTCB );   \
                                                                                            \
        /* Set pxRAMStack to point to the first byte to be coped from the stack. */         \
        pxRAMStack = ( معلومات_2 ډېری_Type_t * معلومات_2 ) config_ډېری_پیل;                         \
                                                                                            \
        /* Calculate the size of the stack we are about to copy from the current            \
        stack pointer value. */                                                             \
        uc_ډېری_بایټونه = SP - ( config_ډېری_پیل - 1 );                                      \
                                                                                            \
        /* Before starting to copy the stack, store the calculated stack size so            \
        the stack can be restored when the task is resumed. */                              \
        *pxXRAMStack = uc_ډېری_بایټونه;                                                        \
                                                                                            \
        /* Copy each stack byte in turn.  pxXRAMStack is incremented first as we            \
        have already stored the stack size into XRAM. */                                    \
        طالما( uc_ډېری_بایټونه )                                                               \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                *pxXRAMStack = *pxRAMStack;                                                 \
                pxRAMStack++;                                                               \
                uc_ډېری_بایټونه--;                                                             \
        }                                                                                   \
}
/*-----------------------------------------------------------*/

/*
 * Macro that copies the stack of the task being resumed from XRAM into
 * internal RAM.
 */
#تعریف_کړه پورټ_COPY_XRAM_منزل_ډېری()                                                            \
{                                                                                           \
        /* Setup the pointers as per portCOPY_STACK_TO_XRAM(), but this time to             \
        copy the data back out of XRAM and into the stack. */                               \
        pxXRAMStack = ( xdata ډېری_Type_t * ) *( ( xdata ډېری_Type_t ** ) pxCurrentTCB );   \
        pxRAMStack = ( معلومات_2 ډېری_Type_t * معلومات_2 ) ( config_ډېری_پیل - 1 );                 \
                                                                                            \
        /* The first value stored in XRAM was the size of the stack - i.e. the              \
        number of bytes we need to copy back. */                                            \
        uc_ډېری_بایټونه = pxXRAMStack[ 0 ];                                                    \
                                                                                            \
        /* Copy the required number of bytes back into the stack. */                        \
        افعل                                                                                  \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                pxRAMStack++;                                                               \
                *pxRAMStack = *pxXRAMStack;                                                 \
                uc_ډېری_بایټونه--;                                                             \
        } طالما( uc_ډېری_بایټونه );                                                            \
                                                                                            \
        /* Restore the stack pointer ready to use the restored stack. */                    \
        SP = ( uint8_t ) pxRAMStack;                                                        \
}
/*-----------------------------------------------------------*/

/*
 * Macro to push the current execution context onto the stack, before the stack
 * is moved to XRAM.
 */
#تعریف_کړه پورټ_SAVE_CONTEXT()                                                                  \
{                                                                                           \
        _asm                                                                                \
                /* Push ACC first, as when restoring the context it must be restored        \
                last (it is used to set the IE register). */                                \
                ټېل        ACC                                                             \
                /* Store the IE register then disable interrupts. */                        \
                ټېل        IE                                                              \
                clr                _EA                                                      \
                ټېل        DPL                                                             \
                ټېل        DPH                                                             \
                ټېل        b                                                               \
                ټېل        ar2                                                             \
                ټېل        ar3                                                             \
                ټېل        ar4                                                             \
                ټېل        ar5                                                             \
                ټېل        ar6                                                             \
                ټېل        ar7                                                             \
                ټېل        ar0                                                             \
                ټېل        ar1                                                             \
                ټېل        PSW                                                             \
        _endasm;                                                                            \
                PSW = 0;                                                                    \
        _asm                                                                                \
                ټېل        _bp                                                             \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * Macro that restores the execution context from the stack.  The execution
 * context was saved into the stack before the stack was copied into XRAM.
 */
#تعریف_کړه پورټ_RESTORE_CONTEXT()                                                               \
{                                                                                           \
        _asm                                                                                \
                راوباسه                _bp                                                      \
                راوباسه                PSW                                                      \
                راوباسه                ar1                                                      \
                راوباسه                ar0                                                      \
                راوباسه                ar7                                                      \
                راوباسه                ar6                                                      \
                راوباسه                ar5                                                      \
                راوباسه                ar4                                                      \
                راوباسه                ar3                                                      \
                راوباسه                ar2                                                      \
                راوباسه                b                                                        \
                راوباسه                DPH                                                      \
                راوباسه                DPL                                                      \
                /* The next byte of the stack is the IE register.  Only the global          \
                enable bit forms part of the task context.  Pop off the IE then set         \
                the global enable bit to match that of the stored IE register. */           \
                راوباسه                ACC                                                      \
                JB                ACC.7,0098$                                               \
                CLR                IE.7                                                     \
                LJMP        0099$                                                           \
        0098$:                                                                              \
                SETB        IE.7                                                            \
        0099$:                                                                              \
                /* Finally pop off the ACC, which was the first register saved. */          \
                راوباسه                ACC                                                      \
                reti                                                                        \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t *px_پورټ_Initialise_ډېری( ډېری_Type_t *px_سر_د_ډېری, TaskFunction_t px_کوډ, فراغ *pvParameters )
{
uint32_t ul_پته;
ډېری_Type_t *px_پیل_د_ډېری;

        /* Leave space to write the size of the stack as the first byte. */
        px_پیل_د_ډېری = px_سر_د_ډېری;
        px_سر_د_ډېری++;

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
        ul_پته = ( uint32_t ) px_کوډ;
        *px_سر_د_ډېری = ( ډېری_Type_t ) ul_پته;
        ul_پته >>= 8;
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = ( ډېری_Type_t ) ( ul_پته );
        px_سر_د_ډېری++;

        /* Next all the registers will have been pushed by portSAVE_CONTEXT(). */
        *px_سر_د_ډېری = 0xaa;        /* acc */
        px_سر_د_ډېری++;

        /* We want tasks to start with interrupts enabled. */
        *px_سر_د_ډېری = پورټ_GLOBAL_مداخله_بټ;
        px_سر_د_ډېری++;

        /* The function parameters will be passed in the DPTR and B register as
        a three byte generic pointer is used. */
        ul_پته = ( uint32_t ) pvParameters;
        *px_سر_د_ډېری = ( ډېری_Type_t ) ul_پته;        /* DPL */
        ul_پته >>= 8;
        *px_سر_د_ډېری++;
        *px_سر_د_ډېری = ( ډېری_Type_t ) ul_پته;        /* DPH */
        ul_پته >>= 8;
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = ( ډېری_Type_t ) ul_پته;        /* b */
        px_سر_د_ډېری++;

        /* The remaining registers are straight forward. */
        *px_سر_د_ډېری = 0x02;        /* R2 */
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = 0x03;        /* R3 */
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = 0x04;        /* R4 */
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = 0x05;        /* R5 */
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = 0x06;        /* R6 */
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = 0x07;        /* R7 */
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = 0x00;        /* R0 */
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = 0x01;        /* R1 */
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = 0x00;        /* PSW */
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = 0xbb;        /* BP */

        /* Dont increment the stack size here as we don't want to include
        the stack size byte as part of the stack size count.

        Finally we place the stack size at the beginning. */
        *px_پیل_د_ډېری = ( ډېری_Type_t ) ( px_سر_د_ډېری - px_پیل_د_ډېری );

        /* Unlike most ports, we return the start of the stack as this is where the
        size of the stack is stored. */
        أرجع px_پیل_د_ډېری;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
        /* Setup timer 2 to generate the RTOS tick. */
        prv_تیاری_Timer_مداخله();

        /* Make sure we start with the expected SFR page.  This line should not
        really be required. */
        SFRPAGE = 0;

        /* Copy the stack for the first task to execute from XRAM into the stack,
        restore the task context from the new stack, then start running the task. */
        پورټ_COPY_XRAM_منزل_ډېری();
        پورټ_RESTORE_CONTEXT();

        /* Should never get here! */
        أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
        /* Not implemented for this port. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
فراغ v_پورټ_Yield( فراغ ) _naked
{
        /* Save the execution context onto the stack, then copy the entire stack
        to XRAM.  This is necessary as the internal RAM is only large enough to
        hold one stack, and we want one per task.

        PERFORMANCE COULD BE IMPROVED BY ONLY COPYING TO XRAM IF A TASK SWITCH
        IS REQUIRED. */
        پورټ_SAVE_CONTEXT();
        پورټ_COPY_ډېری_منزل_XRAM();

        /* Call the standard scheduler context switch function. */
        vTaskSwitchContext();

        /* Copy the stack of the task about to execute from XRAM into RAM and
        restore it's context ready to run on exiting. */
        پورټ_COPY_XRAM_منزل_ډېری();
        پورټ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 1
        فراغ vTimer2ISR( فراغ ) مداخله 5 _naked
        {
                /* Preemptive context switch function triggered by the timer 2 ISR.
                This does the same as vPortYield() (see above) with the addition
                of incrementing the RTOS tick count. */

                پورټ_SAVE_CONTEXT();
                پورټ_COPY_ډېری_منزل_XRAM();

                إذا( xTaskIncrementTick() != pdFALSE )
                {
                        vTaskSwitchContext();
                }

                پورټ_CLEAR_مداخله_FLAG();
                پورټ_COPY_XRAM_منزل_ډېری();
                پورټ_RESTORE_CONTEXT();
        }
#وإلا
        فراغ vTimer2ISR( فراغ ) مداخله 5
        {
                /* When using the cooperative scheduler the timer 2 ISR is only
                required to increment the RTOS tick count. */

                xTaskIncrementTick();
                پورټ_CLEAR_مداخله_FLAG();
        }
#د_که_پای
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
uint8_t ucOriginalSFRPage;

/* Constants calculated to give the required timer capture values. */
ثابت uint32_t ul_Ticks_فی_دوهم = configCPU_CLOCK_HZ / پورټ_CLOCK_وېشونکی;
ثابت uint32_t ul_Capture_وخت = ul_Ticks_فی_دوهم / config_TICK_شرح_HZ;
ثابت uint32_t ul_Capture_ارزښت = پورټ_MAX_TIMER_ارزښت - ul_Capture_وخت;
ثابت uint8_t uc_ټیټ_Capture_Byte = ( uint8_t ) ( ul_Capture_ارزښت & ( uint32_t ) 0xff );
ثابت uint8_t uc_لوړ_Capture_Byte = ( uint8_t ) ( ul_Capture_ارزښت >> ( uint32_t ) 8 );

        /* NOTE:  This uses a timer only present on 8052 architecture. */

        /* Remember the current SFR page so we can restore it at the end of the
        function. */
        ucOriginalSFRPage = SFRPAGE;
        SFRPAGE = 0;

        /* TMR2CF can be left in its default state. */
        TMR2CF = ( uint8_t ) 0;

        /* Setup the overflow reload value. */
        RCAP2L = uc_ټیټ_Capture_Byte;
        RCAP2H = uc_لوړ_Capture_Byte;

        /* The initial load is performed manually. */
        TMR2L = uc_ټیټ_Capture_Byte;
        TMR2H = uc_لوړ_Capture_Byte;

        /* Enable the timer 2 interrupts. */
        IE |= پورټ_TIMER_2_مداخله_ENABLE;

        /* Interrupts are disabled when this is called so the timer can be started
        here. */
        TMR2CN = پورټ_ENABLE_TIMER;

        /* Restore the original SFR page. */
        SFRPAGE = ucOriginalSFRPage;
}
