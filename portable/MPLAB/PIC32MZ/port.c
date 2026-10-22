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
 * Implementation of functions defined in portable.h for the PIC32MZ port.
  *----------------------------------------------------------*/

/* Microchip specific headers. */
#अन्तर्भाव <xc.h>

/* Standard headers. */
#अन्तर्भाव <string.h>

/* Scheduler include files. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#यदि !defined(__PIC32MZ__)
    #दोषः This पत्तनम् is designed गन्तव्यम् work with XC32 on PIC32MZ MCUs.  Please update your C compiler संस्करणम् or settings.
#यदि_अन्तः

#यदि( ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता >= 0x7 ) || ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता == 0 ) )
    #दोषः config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता must be less than 7 and greater than 0
#यदि_अन्तः

/* Hardware specifics. */
#परिभाषय पत्तनम्_TIMER_PRESCALE  8
#परिभाषय पत्तनम्_PRESCALE_द्वयङ्काः   1

/* Bits within various registers. */
#परिभाषय पत्तनम्_IE_BIT                  ( 0x00000001 )
#परिभाषय पत्तनम्_EXL_BIT                 ( 0x00000002 )
#परिभाषय पत्तनम्_MX_BIT                  ( 0x01000000 ) /* Allow access to DSP instructions. */
#परिभाषय पत्तनम्_CU1_BIT                 ( 0x20000000 ) /* enable CP1 for parts with hardware. */
#परिभाषय पत्तनम्_FR_BIT                  ( 0x04000000 ) /* Enable 64 bit floating point registers. */

/* Bits within the CAUSE register. */
#परिभाषय पत्तनम्_CORE_SW_0               ( 0x00000100 )
#परिभाषय पत्तनम्_CORE_SW_1               ( 0x00000200 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored. */
#यदि ( __mips_hard_float == 1 )
    #परिभाषय पत्तनम्_INITIAL_SR          ( पत्तनम्_IE_BIT | पत्तनम्_EXL_BIT | पत्तनम्_MX_BIT | पत्तनम्_FR_BIT | पत्तनम्_CU1_BIT )
#अन्यथा
    #परिभाषय पत्तनम्_INITIAL_SR          ( पत्तनम्_IE_BIT | पत्तनम्_EXL_BIT | पत्तनम्_MX_BIT )
#यदि_अन्तः

/* The initial value to store into the FPU status and control register. This is
 only used on parts that support a hardware FPU. */
#परिभाषय पत्तनम्_INITIAL_FPSCR           (0x1000000) /* High perf on denormal ops */


/*
By default port.c generates its tick interrupt from TIMER1.  The user can
override this behaviour by:
    1: Providing their own implementation of vApplicationSetupTickTimerInterrupt(),
       which is the function that configures the timer.  The function is defined
       as a weak symbol in this file so if the same function name is used in the
       application code then the version in the application code will be linked
       into the application in preference to the version defined in this file.
    2: Define configTICK_INTERRUPT_VECTOR to the vector number of the timer used
       to generate the tick interrupt.  For example, when timer 1 is used then
       configTICK_INTERRUPT_VECTOR is set to _TIMER_1_VECTOR.
       configTICK_INTERRUPT_VECTOR should be defined in FreeRTOSConfig.h.
    3: Define configCLEAR_TICK_TIMER_INTERRUPT() to clear the interrupt in the
       timer used to generate the tick interrupt.  For example, when timer 1 is
       used configCLEAR_TICK_TIMER_INTERRUPT() is defined to
       IFS0CLR = _IFS0_T1IF_MASK.
*/
#यदि_अपरिभाषितम् config_TICK_व्यवधानम्_सदिशम्
    #परिभाषय config_TICK_व्यवधानम्_सदिशम् TIMER_1_सदिशम्
    #परिभाषय config_CLEAR_TICK_TIMER_व्यवधानम्() IFS0CLR = IFS0_T1_IF_आवरणम्
#अन्यथा
    #यदि_अपरिभाषितम् config_CLEAR_TICK_TIMER_व्यवधानम्
        #दोषः If config_TICK_व्यवधानम्_सदिशम् is defined अन्तर् application संहिता then config_CLEAR_TICK_TIMER_व्यवधानम् must also be defined अन्तर् application संहिता.
    #यदि_अन्तः
#यदि_अन्तः

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger - in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#यदि_परिभाषितम् config_TASK_RETURN_स्थानाङ्कः
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः config_TASK_RETURN_स्थानाङ्कः
#अन्यथा
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः prvTaskExitError
#यदि_अन्तः

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#यदि( config_CHECK_FOR_राशिः_अतिप्रवाहः > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #परिभाषय पत्तनम्_ISR_राशिः_FILL_BYTE 0xee

    स्थिर ध्रुव uint8_t uc_Expected_राशिः_अष्टकानि[] = {
                                    पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE,     \
                                    पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE,     \
                                    पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE,     \
                                    पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE,     \
                                    पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE, पत्तनम्_ISR_राशिः_FILL_BYTE };   \

    #परिभाषय पत्तनम्_CHECK_ISR_राशिः() configASSERT( ( memcmp( ( शून्य * ) xISRStack, ( शून्य * ) uc_Expected_राशिः_अष्टकानि, परिमाण( uc_Expected_राशिः_अष्टकानि ) ) == 0 ) )
#अन्यथा
    /* Define the function away. */
    #परिभाषय पत्तनम्_CHECK_ISR_राशिः()
#यदि_अन्तः /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
चञ्चल UBaseType_t ux_व्यवधानम्_Nesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_राशिः_Pointer = 0;

/* The stack used by interrupt service routines that cause a context switch. */
__attribute__ ((aligned(8))) राशिः_Type_t xISRStack[ config_ISR_राशिः_आकार ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this.  8 byte alignment
is required to allow double word floating point stack pushes generated by the
compiler. */
ध्रुव राशिः_Type_t * ध्रुव x_ISRStack_शिखरम् = &( xISRStack[ ( config_ISR_राशिः_आकार & ~पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) - 8 ] );

/* Saved as part of the task context. Set to pdFALSE if the task does not
 require an FPU context. */
#यदि ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    uint32_t ulTaskHasFPUContext = 0;
#यदि_अन्तः

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t *px_पत्तनम्_Initialise_राशिः( राशिः_Type_t *px_शिखरम्_सम्बन्धि_राशिः, TaskFunction_t px_संहिता, शून्य *pvParameters )
{
    /* Ensure 8 byte alignment is maintained when leaving this function. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) 0xDEADBEEF;
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) _CP0_GET_CAUSE();
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) पत्तनम्_INITIAL_SR;/* CP0_STATUS */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) px_संहिता;       /* CP0_EPC */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) 0x00000000;   /* DSPControl */
    px_शिखरम्_सम्बन्धि_राशिः -= 7;                          /* Includes space for AC1 - AC3. */

    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) पत्तनम्_TASK_RETURN_स्थानाङ्कः;  /* ra */
    px_शिखरम्_सम्बन्धि_राशिः -= 15;

    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) pvParameters; /* Parameters to pass in. */
    px_शिखरम्_सम्बन्धि_राशिः -= 15;

    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) pdFALSE; /*by default disable FPU context save on parts with FPU */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvTaskExitError( शून्य )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( ux_Saved_Task_राशिः_Pointer == 0UL );
    पत्तनम्_DISABLE_INTERRUPTS();
    प्रति( ;; );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.  This function uses peripheral timer 1.
 * The function is declared weak so an application writer can use a different
 * timer by redefining this implementation.  If a different timer is used then
 * configTICK_INTERRUPT_VECTOR must also be defined in FreeRTOSConfig.h to
 * ensure the RTOS provided tick interrupt handler is installed on the correct
 * vector number.  When Timer 1 is used the vector number is defined as
 * _TIMER_1_VECTOR.
 */
__attribute__(( weak )) शून्य v_Application_सज्जता_Tick_Timer_व्यवधानम्( शून्य )
{
ध्रुव uint32_t ul_Compare_मेलनम् = ( (configPERIPHERAL_CLOCK_HZ / पत्तनम्_TIMER_PRESCALE) / config_TICK_दरः_HZ ) - 1UL;

    /* PR1 is 16-bit. Ensure that the configPERIPHERAL_CLOCK_HZ and
     * configTICK_RATE_HZ are defined such that ulCompareMatch value would fit
     * in 16-bits. */
    configASSERT( ( ul_Compare_मेलनम् & 0xFFFF0000 ) == 0 );

    T1CON = 0x0000;
    T1CONbits.TCKPS = पत्तनम्_PRESCALE_द्वयङ्काः;
    PR1 = ul_Compare_मेलनम्;
    IPC1bits.T1IP = config_KERNEL_व्यवधानम्_प्राथमिकता;

    /* Clear the interrupt as a starting condition. */
    IFS0bits.T1IF = 0;

    /* Enable the interrupt. */
    IEC0bits.T1IE = 1;

    /* Start the timer. */
    T1CONbits.TON = 1;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler(शून्य)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ux_व्यवधानम्_Nesting == 1000UL );
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
बाह्य शून्य v_पत्तनम्_Start_First_Task( शून्य );
बाह्य शून्य *pxCurrentTCB;

    #यदि ( config_CHECK_FOR_राशिः_अतिप्रवाहः > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        स्मृतिं_पूरय( ( शून्य * ) xISRStack, पत्तनम्_ISR_राशिः_FILL_BYTE, परिमाण( xISRStack ) );
    }
    #यदि_अन्तः /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    IFS0CLR = IFS0_CS0_IF_आवरणम्;

    /* Set software timer priority. */
    IPC0CLR = IPC0_CS0_IP_आवरणम्;
    IPC0_समुच्चयः = ( config_KERNEL_व्यवधानम्_प्राथमिकता << _IPC0_CS0IP_POSITION );

    /* Enable software interrupt. */
    IEC0CLR = IEC0_CS0_IE_आवरणम्;
    IEC0_समुच्चयः = 1 << _IEC0_CS0IE_POSITION;

    /* Setup the timer to generate the tick.  Interrupts will have been
    disabled by the time we get here. */
    v_Application_सज्जता_Tick_Timer_व्यवधानम्();

    /* Kick off the highest priority task that has been created so far.
    Its stack location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_राशिः_Pointer = *( UBaseType_t * ) pxCurrentTCB;
    v_पत्तनम्_Start_First_Task();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    प्रत्यागम pdFALSE;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Increment_Tick( शून्य )
{
UBaseType_t ux_Saved_स्थितिः;

    ux_Saved_स्थितिः = ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR();
    {
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            _CP0_BIS_CAUSE( पत्तनम्_CORE_SW_0 );
        }
    }
    v_पत्तनम्_Clear_व्यवधानम्_आवरणम्_From_ISR( ux_Saved_स्थितिः );

    /* Look for the ISR stack getting near or past its limit. */
    पत्तनम्_CHECK_ISR_राशिः();

    /* Clear timer interrupt. */
    config_CLEAR_TICK_TIMER_व्यवधानम्();
}
/*-----------------------------------------------------------*/

UBaseType_t ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR( शून्य )
{
UBaseType_t ux_Saved_स्थितिः_पञ्जिकाकोशः;

    __builtin_disable_interrupts();
    ux_Saved_स्थितिः_पञ्जिकाकोशः = CP0_GET_स्थितिः() | 0x01;
    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    CP0_समुच्चयः_स्थितिः( ( ( ux_Saved_स्थितिः_पञ्जिकाकोशः & ( ~पत्तनम्_ALL_IPL_द्वयङ्काः ) ) ) | ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता << पत्तनम्_IPL_सरणम् ) );

    प्रत्यागम ux_Saved_स्थितिः_पञ्जिकाकोशः;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्_From_ISR( UBaseType_t ux_Saved_स्थितिः_पञ्जिकाकोशः )
{
    CP0_समुच्चयः_स्थितिः( ux_Saved_स्थितिः_पञ्जिकाकोशः );
}
/*-----------------------------------------------------------*/

#यदि ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )

    शून्य v_पत्तनम्_Task_उपयुङ्क्ते_FPU(शून्य)
    {
    बाह्य शून्य v_पत्तनम्_Initialise_FPSCR( uint32_t uxFPSCRInit );

        पत्तनम्_ENTER_CRITICAL();

        /* Initialise the floating point status register. */
        v_पत्तनम्_Initialise_FPSCR(पत्तनम्_INITIAL_FPSCR);

        /* A task is registering the fact that it needs a FPU context. Set the
        FPU flag (saved as part of the task context). */
        ulTaskHasFPUContext = pdTRUE;

        पत्तनम्_EXIT_CRITICAL();
    }

#यदि_अन्तः /* __mips_hard_float == 1 */

/*-----------------------------------------------------------*/
