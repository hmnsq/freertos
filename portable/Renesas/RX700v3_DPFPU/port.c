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
* Implementation of functions defined in portable.h for the RXv3 DPFPU port.
*----------------------------------------------------------*/

#warning Testing ಗಾಗಿ DFPU support ಒಳ this ಪೋರ್ಟ್ is not yet complete

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Library includes. */
#ಅನ್ತರ್ಭಾವ "string.h"

/* Hardware specifics. */
#ಆದರೆ ( config_INCLUDE_PLATFORM_H_INSTEAD_ದ_IODEFINE_H == 1 )

    #ಅನ್ತರ್ಭಾವ "platform.h"

#ಇಲ್ಲದಿದ್ದರೆ /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    #ಅನ್ತರ್ಭಾವ "iodefine.h"

#ಆದರೆ_ಅಂತ್ಯ /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSW     ( ( ರಾಶಿ_Type_t ) 0x00030000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_FPSW    ( ( ರಾಶಿ_Type_t ) 0x00000100 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_DPSW    ( ( ರಾಶಿ_Type_t ) 0x00000100 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_DCMR    ( ( ರಾಶಿ_Type_t ) 0x00000000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_DECNT   ( ( ರಾಶಿ_Type_t ) 0x00000001 )

/* Tasks are not created with a DPFPU context, but can be given a DPFPU context
 * after they have been created.  A variable is stored as part of the tasks context
 * that holds portNO_DPFPU_CONTEXT if the task does not have a DPFPU context, or
 * any other value if the task does have a DPFPU context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_DPFPU_CONTEXT    ( ( ರಾಶಿ_Type_t ) 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_HAS_DPFPU_CONTEXT   ( ( ರಾಶಿ_Type_t ) 1 )

/* The space on the stack required to hold the DPFPU data registers.  This is 16
 * 64-bit registers. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DPFPU_ದತ್ತಾಂಶ_ರಿಜಿಸ್ಟರ್_ಪದಗಳು   ( 16 * 2 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 * and therefore installed in the vector table, when the FreeRTOS code is built
 * as a library. */
ಬಾಹ್ಯ ತಳ_Type_t v_Software_ಅಡಚಣೆ_ನಮೂದು;
ಸ್ಥಿರಾಂಕ ತಳ_Type_t * p_v_Software_ಅಡಚಣೆ_ನಮೂದು = &v_Software_ಅಡಚಣೆ_ನಮೂದು;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvYieldHandler( ಶೂನ್ಯ );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
ಶೂನ್ಯ v_Software_ಅಡಚಣೆ_ISR( ಶೂನ್ಯ );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  If ulPortTaskHasDPFPUContext is non-zero
 * then a DPFPU context must be saved and restored for the task. */
#ಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    ರಾಶಿ_Type_t ul_ಪೋರ್ಟ್_Task_Has_DPFPUContext = ಪೋರ್ಟ್_NO_DPFPU_CONTEXT;

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TASK_DPFPU_SUPPORT */

/* This is accessed by the inline assembler functions so is file scope for
 * convenience. */
ಬಾಹ್ಯ ಶೂನ್ಯ * pxCurrentTCB;
ಬಾಹ್ಯ ಶೂನ್ಯ vTaskSwitchContext( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_PSW;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ತುಂಬಿದ_ರಿಜಿಸ್ಟರ್_INITIALISATION
        {
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0xffffffff; /* r15. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0xeeeeeeee;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0xdddddddd;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0xcccccccc;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0xbbbbbbbb;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0xaaaaaaaa;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0x99999999;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0x88888888;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0x77777777;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0x66666666;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0x55555555;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0x44444444;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0x33333333;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = 0x22222222;
            px_ತುದಿ_ದ_ರಾಶಿ--;
        }
    #ಇಲ್ಲದಿದ್ದರೆ /* ifdef USE_FULL_REGISTER_INITIALISATION */
        {
            px_ತುದಿ_ದ_ರಾಶಿ -= 15;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_FPSW;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x11111111; /* Accumulator 1. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x22222222; /* Accumulator 1. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x33333333; /* Accumulator 1. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x44444444; /* Accumulator 0. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x55555555; /* Accumulator 0. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x66666666; /* Accumulator 0. */

    #ಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 1 )
        {
            /* The task will start without a DPFPU context.  A task that
             * uses the DPFPU hardware must call vPortTaskUsesDPFPU() before
             * executing any floating point instructions. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_DPFPU_CONTEXT;
        }
    #ಅಥವಾಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 2 )
        {
            /* The task will start with a DPFPU context.  Leave enough
             * space for the registers - and ensure they are initialised if desired. */
            #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ತುಂಬಿದ_ರಿಜಿಸ್ಟರ್_INITIALISATION
                {
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ = 1515.1515; /* DR15. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ = 1414.1414; /* DR14. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ = 1313.1313; /* DR13. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ = 1212.1212; /* DR12. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ = 1111.1111; /* DR11. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ = 1010.1010; /* DR10. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ =  909.0909; /* DR9. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ =  808.0808; /* DR8. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ =  707.0707; /* DR7. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ =  606.0606; /* DR6. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ =  505.0505; /* DR5. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ =  404.0404; /* DR4. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ =  303.0303; /* DR3. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ =  202.0202; /* DR2. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ =  101.0101; /* DR1. */
                    px_ತುದಿ_ದ_ರಾಶಿ -= 2;
                    *(ದ್ವಿಗುಣ *)px_ತುದಿ_ದ_ರಾಶಿ = 9876.54321;/* DR0. */
                }
            #ಇಲ್ಲದಿದ್ದರೆ /* ifdef USE_FULL_REGISTER_INITIALISATION */
                {
                    px_ತುದಿ_ದ_ರಾಶಿ -= ಪೋರ್ಟ್_DPFPU_ದತ್ತಾಂಶ_ರಿಜಿಸ್ಟರ್_ಪದಗಳು;
                    memset( px_ತುದಿ_ದ_ರಾಶಿ, 0x00, ಪೋರ್ಟ್_DPFPU_ದತ್ತಾಂಶ_ರಿಜಿಸ್ಟರ್_ಪದಗಳು * ಗಾತ್ರ( ರಾಶಿ_Type_t ) );
                }
            #ಆದರೆ_ಅಂತ್ಯ /* ifdef USE_FULL_REGISTER_INITIALISATION */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_DECNT; /* DECNT. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_DCMR;  /* DCMR. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_DPSW;  /* DPSW. */
        }
    #ಅಥವಾಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 0 )
        {
            /* Omit DPFPU support. */
        }
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */
        {
            #ದೋಷ Invalid configUSE_TASK_DPFPU_SUPPORT setting - configUSE_TASK_DPFPU_SUPPORT must be ಗಣ ಗಮ್ಯ 0, 1, 2, or ಎಡ undefined.
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_DPFPU( ಶೂನ್ಯ )
    {
        /* A task is registering the fact that it needs a DPFPU context.  Set the
         * DPFPU flag (which is saved as part of the task context). */
        ul_ಪೋರ್ಟ್_Task_Has_DPFPUContext = ಪೋರ್ಟ್_HAS_DPFPU_CONTEXT;
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TASK_DPFPU_SUPPORT */
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    ಆದರೆ( pxCurrentTCB != ಖಾಲಿ )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ;

        /* Start the first task. */
        prv_ಆರಂಭ_ಮೊದಲ_Task();
    }

    /* Just to make sure the function is not optimised away. */
    ( ಶೂನ್ಯ ) v_Software_ಅಡಚಣೆ_ISR();

    /* Should not get here. */
    ಹಿಂತಿರುಗಿ pdFAIL;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == ಖಾಲಿ );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( ಶೂನ್ಯ ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ inline_asm prv_ಆರಂಭ_ಮೊದಲ_Task
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ )
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __CDT_PARSER__

    /* When starting the scheduler there is nothing that needs moving to the
     * interrupt stack because the function is not called from an interrupt.
     * Just ensure the current stack is the user stack. */
    SETPSW U


    /* Obtain the location of the stack associated with which ever task
     * pxCurrentTCB is currently pointing to. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L [ R15 ], R0


    /* Restore the registers from the stack of the task pointed to by
     * pxCurrentTCB. */

    #ಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* The restored ulPortTaskHasDPFPUContext is to be zero here.
         * So, it is never necessary to restore the DPFPU context here. */
        ತೆಗೆ_3 R15
        MOV.L # ul_ಪೋರ್ಟ್_Task_Has_DPFPUContext_2, R14
        MOV.L R15, [ R14 ]

    #ಅಥವಾಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Restore the DPFPU context. */
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    ತೆಗೆ_3 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    ತೆಗೆ_3 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    ತೆಗೆ_3 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    ತೆಗೆ_3 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    ತೆಗೆ_3 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    ತೆಗೆ_3 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    ತೆಗೆ_3 R15

    /* Floating point status word. */
    MVTC R15, FPSW

    /* R1 to R15 - R0 is not included as it is the SP. */
    POPM R1-R15

    /* This pops the remaining registers. */
    RTE
    NOP
    NOP

#ಆದರೆ_ಅಂತ್ಯ /* ifndef __CDT_PARSER__ */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_Software_ಅಡಚಣೆ_ISR( ಶೂನ್ಯ )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ inline_asm prvYieldHandler
ಸ್ಥಿರ ಶೂನ್ಯ prvYieldHandler( ಶೂನ್ಯ )
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __CDT_PARSER__

    /* Re-enable interrupts. */
    SETPSW I


    /* Move the data that was automatically pushed onto the interrupt stack when
     * the interrupt occurred from the interrupt stack to the user stack.
     *
     * R15 is saved before it is clobbered. */
    ತಳ್ಳು_2.L R15

    /* Read the user stack pointer. */
    MVFC USP, R15

    /* Move the address down to the data being moved. */
    SUB # 12, R15
    MVTC R15, USP

    /* Copy the data across, R15, then PC, then PSW. */
    MOV.L [ R0 ], [ R15 ]
    MOV.L 4[ R0 ], 4[ R15 ]
    MOV.L 8[ R0 ], 8[ R15 ]

    /* Move the interrupt stack pointer to its new correct position. */
    ಕೂಡಿಸು_2 # 12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM R1-R14

    /* Save the FPSW and accumulators. */
    MVFC FPSW, R15
    ತಳ್ಳು_2.L R15
    MVFACGU # 0, A1, R15
    ತಳ್ಳು_2.L R15
    MVFACHI # 0, A1, R15
    ತಳ್ಳು_2.L R15
    MVFACLO # 0, A1, R15 /* Low order word. */
    ತಳ್ಳು_2.L R15
    MVFACGU # 0, A0, R15
    ತಳ್ಳು_2.L R15
    MVFACHI # 0, A0, R15
    ತಳ್ಳು_2.L R15
    MVFACLO # 0, A0, R15 /* Low order word. */
    ತಳ್ಳು_2.L R15

    #ಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* Does the task have a DPFPU context that needs saving?  If
         * ulPortTaskHasDPFPUContext is 0 then no. */
        MOV.L # ul_ಪೋರ್ಟ್_Task_Has_DPFPUContext_2, R15
        MOV.L [ R15 ], R15
        CMP # 0, R15

        /* Save the DPFPU context, if any. */
        BEQ.B ?+
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT
        ?:

        /* Save ulPortTaskHasDPFPUContext itself. */
        ತಳ್ಳು_2.L R15

    #ಅಥವಾಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Save the DPFPU context, always. */
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */


    /* Save the stack pointer to the TCB. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L R0, [ R15 ]


    /* Ensure the interrupt mask is set to the syscall priority while the kernel
     * structures are being accessed. */
    MVTIPL # config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ

    /* Select the next task to run. */
    BSR.A _vTaskSwitchContext

    /* Reset the interrupt mask as no more data structure access is required. */
    MVTIPL # config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ


    /* Load the stack pointer of the task that is now selected as the Running
     * state task from its TCB. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L [ R15 ], R0


    /* Restore the context of the new task.  The PSW (Program Status Word) and
     * PC will be popped by the RTE instruction. */

    #ಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* Is there a DPFPU context to restore?  If the restored
         * ulPortTaskHasDPFPUContext is zero then no. */
        ತೆಗೆ_3 R15
        MOV.L # ul_ಪೋರ್ಟ್_Task_Has_DPFPUContext_2, R14
        MOV.L R15, [ R14 ]
        CMP # 0, R15

        /* Restore the DPFPU context, if any. */
        BEQ.B ?+
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15
        ?:

    #ಅಥವಾಆದರೆ ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Restore the DPFPU context, always. */
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    ತೆಗೆ_3 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    ತೆಗೆ_3 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    ತೆಗೆ_3 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    ತೆಗೆ_3 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    ತೆಗೆ_3 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    ತೆಗೆ_3 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    ತೆಗೆ_3 R15
    MVTC R15, FPSW
    POPM R1-R15
    RTE
    NOP
    NOP

#ಆದರೆ_ಅಂತ್ಯ /* ifndef __CDT_PARSER__ */
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ ಅಡಚಣೆ ( vTickISR( vect = _VECT( config_TICK_ಸದಿಶ ), enable ) )
ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ )
{
    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    ಗಣ_ipl( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ );
    {
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    ಗಣ_ipl( config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ );
}
/*-----------------------------------------------------------*/
