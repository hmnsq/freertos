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
* Implementation of functions defined in portable.h for the PPC440 port.
*----------------------------------------------------------*/


/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Library includes. */
#अन्तर्भाव "xtime_l.h"
#अन्तर्भाव "xintc.h"
#अन्तर्भाव "xintc_i.h"

/*-----------------------------------------------------------*/

/* Definitions to set the initial MSR of each task. */
#परिभाषय पत्तनम्_CRITICAL_व्यवधानम्_ENABLE    ( 1UL << 17UL )
#परिभाषय पत्तनम्_EXTERNAL_व्यवधानम्_ENABLE    ( 1UL << 15UL )
#परिभाषय पत्तनम्_MACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#यदि configUSE_FPU == 1
    #परिभाषय पत्तनम्_APU_PRESENT              ( 1UL << 25UL )
    #परिभाषय पत्तनम्_FCM_FPU_PRESENT          ( 1UL << 13UL )
#अन्यथा
    #परिभाषय पत्तनम्_APU_PRESENT              ( 0UL )
    #परिभाषय पत्तनम्_FCM_FPU_PRESENT          ( 0UL )
#यदि_अन्तः

#परिभाषय पत्तनम्_INITIAL_MSR                  ( पत्तनम्_CRITICAL_व्यवधानम्_ENABLE | पत्तनम्_EXTERNAL_व्यवधानम्_ENABLE | पत्तनम्_MACHINE_CHECK_ENABLE | पत्तनम्_APU_PRESENT | पत्तनम्_FCM_FPU_PRESENT )


बाह्य ध्रुव अचिह्नित SDA_आधारः;
बाह्य ध्रुव अचिह्नित SDA2_आधारः;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
बाह्य शून्य v_पत्तनम्_Tick_ISR( शून्य );

/*
 * The handler for the yield function - defined in portasm.s.
 */
बाह्य शून्य v_पत्तनम्_Yield( शून्य );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
बाह्य शून्य v_पत्तनम्_Start_First_Task( शून्य );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
स्थिर XIntc x_व्यवधानम्_Controller;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_शिखरम्_सम्बन्धि_राशिः = 0xDEADBEEF;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* EABI stack frame. */
    px_शिखरम्_सम्बन्धि_राशिः -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) &SDA_आधारः; /* address of the first small data area */
    px_शिखरम्_सम्बन्धि_राशिः -= 10;

    /* Parameters in R3. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Parameters in R2. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) &SDA2_आधारः; /* address of the second small data area */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R1 is the stack pointer so is omitted. */

    *px_शिखरम्_सम्बन्धि_राशिः = 0x10000001UL;                      /* R0. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x00000000UL;                      /* USPRG0. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x00000000UL;                      /* CR. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x00000000UL;                      /* XER. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x00000000UL;                      /* CTR. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) v_पत्तनम्_अन्तः_Scheduler; /* LR. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;            /* SRR0. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_MSR;                   /* SRR1. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) v_पत्तनम्_अन्तः_Scheduler; /* Next LR. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x00000000UL;                      /* Backchain. */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    prv_सज्जता_Timer_व्यवधानम्();
    XExc_पञ्जिकाकोशः_Handler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) v_पत्तनम्_Yield, ( शून्य * ) 0 );
    v_पत्तनम्_Start_First_Task();

    /* Should not get here as the tasks are now running! */
    प्रत्यागम pdFALSE;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented. */
    प्रति( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    ध्रुव uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / config_TICK_दरः_HZ ) - 1UL );

    XTime_DECClear_व्यवधानम्();
    XTime_FITClear_व्यवधानम्();
    XTime_WDTClear_व्यवधानम्();
    XTime_WDTDisable_व्यवधानम्();
    XTime_FITDisable_व्यवधानम्();

    XExc_पञ्जिकाकोशः_Handler( XEXC_ID_DEC_INT, ( XExceptionHandler ) v_पत्तनम्_Tick_ISR, ( शून्य * ) 0 );

    XTime_DECEnableAutoReload();
    XTime_DECSetInterval( ulInterval );
    XTime_DECEnable_व्यवधानम्();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_ISRHandler( शून्य * pvNullDoNotUse )
{
    uint32_t ul_व्यवधानम्_स्थितिः, ul_व्यवधानम्_आवरणम् = 1UL;
    आधारः_Type_t x_व्यवधानम्_सङ्ख्या;
    XIntc_Config * px_व्यवधानम्_Controller;
    XIntc_सदिशम्_सारणी_प्रविष्टिः * px_सारणी;

    /* Just to remove compiler warning. */
    ( शून्य ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    px_व्यवधानम्_Controller = &XIntc_Config_सारणी[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ul_व्यवधानम्_स्थितिः = XIntc_m_Get_Intr_स्थितिः( px_व्यवधानम्_Controller->आधारः_स्थानाङ्कः );

    प्रति( x_व्यवधानम्_सङ्ख्या = 0; x_व्यवधानम्_सङ्ख्या < XPAR_INTC_MAX_अङ्कः_INTR_INPUTS; x_व्यवधानम्_सङ्ख्या++ )
    {
        यदि( ul_व्यवधानम्_स्थितिः & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( px_व्यवधानम्_Controller->आधारः_स्थानाङ्कः, ul_व्यवधानम्_आवरणम् );

            /* Call the registered handler. */
            px_सारणी = &( px_व्यवधानम्_Controller->Handler_सारणी[ x_व्यवधानम्_सङ्ख्या ] );
            px_सारणी->Handler( px_सारणी->Call_पृष्ठभागः_Ref );
        }

        /* Check the next interrupt. */
        ul_व्यवधानम्_आवरणम् <<= 0x01UL;
        ul_व्यवधानम्_स्थितिः >>= 0x01UL;

        /* Have we serviced all interrupts? */
        यदि( ul_व्यवधानम्_स्थितिः == 0UL )
        {
            भङ्ग;
        }
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_सज्जता_व्यवधानम्_Controller( शून्य )
{
    बाह्य शून्य v_पत्तनम्_ISRWrapper( शून्य );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_पञ्जिकाकोशः_Handler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) v_पत्तनम्_ISRWrapper, रिक्त );
    XIntc_Initialize( &x_व्यवधानम्_Controller, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_Start( &x_व्यवधानम्_Controller, XIN_REAL_बहुलकम् );
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Install_व्यवधानम्_Handler( uint8_t uc_व्यवधानम्_ID,
                                         XInterruptHandler pxHandler,
                                         शून्य * pv_Call_पृष्ठभागः_Ref )
{
    आधारः_Type_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    यदि( XST_SUCCESS == XIntc_Connect( &x_व्यवधानम्_Controller, uc_व्यवधानम्_ID, pxHandler, pv_Call_पृष्ठभागः_Ref ) )
    {
        XIntc_Enable( &x_व्यवधानम्_Controller, uc_व्यवधानम्_ID );
        xReturn = pdPASS;
    }

    प्रत्यागम xReturn;
}
