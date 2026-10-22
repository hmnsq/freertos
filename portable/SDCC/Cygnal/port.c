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
#समावेश <string.h>

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"

/* Constants required to setup timer 2 to produce the RTOS tick. */
#घोषणा port_CLOCK_भाजक                               ( ( uint32_t ) 12 )
#घोषणा port_MAX_TIMER_मूल्य                             ( ( uint32_t ) 0xffff )
#घोषणा portENABLE_TIMER                                ( ( uint8_t ) 0x04 )
#घोषणा portTIMER_2_INTERRUPT_ENABLE                    ( ( uint8_t ) 0x20 )

/* The value used in the IE register when a task first starts. */
#घोषणा portGLOBAL_INTERRUPT_BIT                        ( ( ढेर_Type_t ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#घोषणा portINITIAL_PSW                                 ( ( ढेर_Type_t ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#घोषणा portCLEAR_INTERRUPT_FLAG()                      TMR2CN &= ~0x80;

/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
तथ्य_2 अटल uint8_t uc_ढेर_Bytes;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
xdata अटल ढेर_Type_t * तथ्य_2 pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
तथ्य_2 अटल ढेर_Type_t * तथ्य_2 pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
प्रकार व्योम TCB_t;
बाह्य अस्थिर TCB_t * अस्थिर pxCurrentTCB;

/*
 * Setup the hardware to generate an interrupt off timer 2 at the required
 * frequency.
 */
अटल व्योम prvSetupTimerInterrupt( व्योम );

/*-----------------------------------------------------------*/
/*
 * Macro that copies the current stack from internal RAM to XRAM.  This is
 * required as the 8051 only contains enough internal RAM for a single stack,
 * but we have a stack for every task.
 */
#घोषणा port_COPY_ढेर_TO_XRAM()                                                            \
{                                                                                           \
        /* pxCurrentTCB points to a TCB which itself points to the location into            \
        which the first stack byte should be copied. Set pxXRAMStack to point               \
        to the location into which the first stack byte is to be copied. */                 \
        pxXRAMStack = ( xdata ढेर_Type_t * ) *( ( xdata ढेर_Type_t ** ) pxCurrentTCB );   \
                                                                                            \
        /* Set pxRAMStack to point to the first byte to be coped from the stack. */         \
        pxRAMStack = ( तथ्य_2 ढेर_Type_t * तथ्य_2 ) config_ढेर_START;                         \
                                                                                            \
        /* Calculate the size of the stack we are about to copy from the current            \
        stack pointer value. */                                                             \
        uc_ढेर_Bytes = SP - ( config_ढेर_START - 1 );                                      \
                                                                                            \
        /* Before starting to copy the stack, store the calculated stack size so            \
        the stack can be restored when the task is resumed. */                              \
        *pxXRAMStack = uc_ढेर_Bytes;                                                        \
                                                                                            \
        /* Copy each stack byte in turn.  pxXRAMStack is incremented first as we            \
        have already stored the stack size into XRAM. */                                    \
        जबतक( uc_ढेर_Bytes )                                                               \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                *pxXRAMStack = *pxRAMStack;                                                 \
                pxRAMStack++;                                                               \
                uc_ढेर_Bytes--;                                                             \
        }                                                                                   \
}
/*-----------------------------------------------------------*/

/*
 * Macro that copies the stack of the task being resumed from XRAM into
 * internal RAM.
 */
#घोषणा port_COPY_XRAM_TO_ढेर()                                                            \
{                                                                                           \
        /* Setup the pointers as per portCOPY_STACK_TO_XRAM(), but this time to             \
        copy the data back out of XRAM and into the stack. */                               \
        pxXRAMStack = ( xdata ढेर_Type_t * ) *( ( xdata ढेर_Type_t ** ) pxCurrentTCB );   \
        pxRAMStack = ( तथ्य_2 ढेर_Type_t * तथ्य_2 ) ( config_ढेर_START - 1 );                 \
                                                                                            \
        /* The first value stored in XRAM was the size of the stack - i.e. the              \
        number of bytes we need to copy back. */                                            \
        uc_ढेर_Bytes = pxXRAMStack[ 0 ];                                                    \
                                                                                            \
        /* Copy the required number of bytes back into the stack. */                        \
        करो                                                                                  \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                pxRAMStack++;                                                               \
                *pxRAMStack = *pxXRAMStack;                                                 \
                uc_ढेर_Bytes--;                                                             \
        } जबतक( uc_ढेर_Bytes );                                                            \
                                                                                            \
        /* Restore the stack pointer ready to use the restored stack. */                    \
        SP = ( uint8_t ) pxRAMStack;                                                        \
}
/*-----------------------------------------------------------*/

/*
 * Macro to push the current execution context onto the stack, before the stack
 * is moved to XRAM.
 */
#घोषणा portSAVE_CONTEXT()                                                                  \
{                                                                                           \
        _asm                                                                                \
                /* Push ACC first, as when restoring the context it must be restored        \
                last (it is used to set the IE register). */                                \
                धकेलो        ACC                                                             \
                /* Store the IE register then disable interrupts. */                        \
                धकेलो        IE                                                              \
                clr                _EA                                                      \
                धकेलो        DPL                                                             \
                धकेलो        DPH                                                             \
                धकेलो        b                                                               \
                धकेलो        ar2                                                             \
                धकेलो        ar3                                                             \
                धकेलो        ar4                                                             \
                धकेलो        ar5                                                             \
                धकेलो        ar6                                                             \
                धकेलो        ar7                                                             \
                धकेलो        ar0                                                             \
                धकेलो        ar1                                                             \
                धकेलो        PSW                                                             \
        _endasm;                                                                            \
                PSW = 0;                                                                    \
        _asm                                                                                \
                धकेलो        _bp                                                             \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * Macro that restores the execution context from the stack.  The execution
 * context was saved into the stack before the stack was copied into XRAM.
 */
#घोषणा portRESTORE_CONTEXT()                                                               \
{                                                                                           \
        _asm                                                                                \
                निकालो                _bp                                                      \
                निकालो                PSW                                                      \
                निकालो                ar1                                                      \
                निकालो                ar0                                                      \
                निकालो                ar7                                                      \
                निकालो                ar6                                                      \
                निकालो                ar5                                                      \
                निकालो                ar4                                                      \
                निकालो                ar3                                                      \
                निकालो                ar2                                                      \
                निकालो                b                                                        \
                निकालो                DPH                                                      \
                निकालो                DPL                                                      \
                /* The next byte of the stack is the IE register.  Only the global          \
                enable bit forms part of the task context.  Pop off the IE then set         \
                the global enable bit to match that of the stored IE register. */           \
                निकालो                ACC                                                      \
                JB                ACC.7,0098$                                               \
                CLR                IE.7                                                     \
                LJMP        0099$                                                           \
        0098$:                                                                              \
                SETB        IE.7                                                            \
        0099$:                                                                              \
                /* Finally pop off the ACC, which was the first register saved. */          \
                निकालो                ACC                                                      \
                reti                                                                        \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t *px_Port_Initialise_ढेर( ढेर_Type_t *px_शीर्ष_Of_ढेर, TaskFunction_t pxCode, व्योम *pvParameters )
{
uint32_t ulAddress;
ढेर_Type_t *px_Start_Of_ढेर;

        /* Leave space to write the size of the stack as the first byte. */
        px_Start_Of_ढेर = px_शीर्ष_Of_ढेर;
        px_शीर्ष_Of_ढेर++;

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
        ulAddress = ( uint32_t ) pxCode;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ulAddress;
        ulAddress >>= 8;
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( ulAddress );
        px_शीर्ष_Of_ढेर++;

        /* Next all the registers will have been pushed by portSAVE_CONTEXT(). */
        *px_शीर्ष_Of_ढेर = 0xaa;        /* acc */
        px_शीर्ष_Of_ढेर++;

        /* We want tasks to start with interrupts enabled. */
        *px_शीर्ष_Of_ढेर = portGLOBAL_INTERRUPT_BIT;
        px_शीर्ष_Of_ढेर++;

        /* The function parameters will be passed in the DPTR and B register as
        a three byte generic pointer is used. */
        ulAddress = ( uint32_t ) pvParameters;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ulAddress;        /* DPL */
        ulAddress >>= 8;
        *px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ulAddress;        /* DPH */
        ulAddress >>= 8;
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ulAddress;        /* b */
        px_शीर्ष_Of_ढेर++;

        /* The remaining registers are straight forward. */
        *px_शीर्ष_Of_ढेर = 0x02;        /* R2 */
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = 0x03;        /* R3 */
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = 0x04;        /* R4 */
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = 0x05;        /* R5 */
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = 0x06;        /* R6 */
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = 0x07;        /* R7 */
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = 0x00;        /* R0 */
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = 0x01;        /* R1 */
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = 0x00;        /* PSW */
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = 0xbb;        /* BP */

        /* Dont increment the stack size here as we don't want to include
        the stack size byte as part of the stack size count.

        Finally we place the stack size at the beginning. */
        *px_Start_Of_ढेर = ( ढेर_Type_t ) ( px_शीर्ष_Of_ढेर - px_Start_Of_ढेर );

        /* Unlike most ports, we return the start of the stack as this is where the
        size of the stack is stored. */
        वापस px_Start_Of_ढेर;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( व्योम )
{
        /* Setup timer 2 to generate the RTOS tick. */
        prvSetupTimerInterrupt();

        /* Make sure we start with the expected SFR page.  This line should not
        really be required. */
        SFRPAGE = 0;

        /* Copy the stack for the first task to execute from XRAM into the stack,
        restore the task context from the new stack, then start running the task. */
        port_COPY_XRAM_TO_ढेर();
        portRESTORE_CONTEXT();

        /* Should never get here! */
        वापस pdTRUE;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
        /* Not implemented for this port. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
व्योम vPortYield( व्योम ) _naked
{
        /* Save the execution context onto the stack, then copy the entire stack
        to XRAM.  This is necessary as the internal RAM is only large enough to
        hold one stack, and we want one per task.

        PERFORMANCE COULD BE IMPROVED BY ONLY COPYING TO XRAM IF A TASK SWITCH
        IS REQUIRED. */
        portSAVE_CONTEXT();
        port_COPY_ढेर_TO_XRAM();

        /* Call the standard scheduler context switch function. */
        vTaskSwitchContext();

        /* Copy the stack of the task about to execute from XRAM into RAM and
        restore it's context ready to run on exiting. */
        port_COPY_XRAM_TO_ढेर();
        portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

#अगर configUSE_PREEMPTION == 1
        व्योम vTimer2ISR( व्योम ) interrupt 5 _naked
        {
                /* Preemptive context switch function triggered by the timer 2 ISR.
                This does the same as vPortYield() (see above) with the addition
                of incrementing the RTOS tick count. */

                portSAVE_CONTEXT();
                port_COPY_ढेर_TO_XRAM();

                अगर( xTaskIncrementTick() != pdFALSE )
                {
                        vTaskSwitchContext();
                }

                portCLEAR_INTERRUPT_FLAG();
                port_COPY_XRAM_TO_ढेर();
                portRESTORE_CONTEXT();
        }
#अन्यथा
        व्योम vTimer2ISR( व्योम ) interrupt 5
        {
                /* When using the cooperative scheduler the timer 2 ISR is only
                required to increment the RTOS tick count. */

                xTaskIncrementTick();
                portCLEAR_INTERRUPT_FLAG();
        }
#पूर्ण_अगर
/*-----------------------------------------------------------*/

अटल व्योम prvSetupTimerInterrupt( व्योम )
{
uint8_t ucOriginalSFRPage;

/* Constants calculated to give the required timer capture values. */
स्थिर uint32_t ulTicksPerSecond = configCPU_CLOCK_HZ / port_CLOCK_भाजक;
स्थिर uint32_t ulCaptureTime = ulTicksPerSecond / configTICK_RATE_HZ;
स्थिर uint32_t ul_Capture_मूल्य = port_MAX_TIMER_मूल्य - ulCaptureTime;
स्थिर uint8_t uc_निचला_Capture_Byte = ( uint8_t ) ( ul_Capture_मूल्य & ( uint32_t ) 0xff );
स्थिर uint8_t uc_ऊपरी_Capture_Byte = ( uint8_t ) ( ul_Capture_मूल्य >> ( uint32_t ) 8 );

        /* NOTE:  This uses a timer only present on 8052 architecture. */

        /* Remember the current SFR page so we can restore it at the end of the
        function. */
        ucOriginalSFRPage = SFRPAGE;
        SFRPAGE = 0;

        /* TMR2CF can be left in its default state. */
        TMR2CF = ( uint8_t ) 0;

        /* Setup the overflow reload value. */
        RCAP2L = uc_निचला_Capture_Byte;
        RCAP2H = uc_ऊपरी_Capture_Byte;

        /* The initial load is performed manually. */
        TMR2L = uc_निचला_Capture_Byte;
        TMR2H = uc_ऊपरी_Capture_Byte;

        /* Enable the timer 2 interrupts. */
        IE |= portTIMER_2_INTERRUPT_ENABLE;

        /* Interrupts are disabled when this is called so the timer can be started
        here. */
        TMR2CN = portENABLE_TIMER;

        /* Restore the original SFR page. */
        SFRPAGE = ucOriginalSFRPage;
}
