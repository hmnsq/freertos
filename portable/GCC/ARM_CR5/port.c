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

/* Standard includes. */
#ضمن <stdlib.h>
#ضمن <string.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#جے_بنا_تعریف config_رکاوٹ_CONTROLLER_ادھار_پتہ
    #غلطی config_رکاوٹ_CONTROLLER_ادھار_پتہ must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جے_انت

#جے_بنا_تعریف config_رکاوٹ_CONTROLLER_CPU_INTERFACE_وتھ
    #غلطی config_رکاوٹ_CONTROLLER_CPU_INTERFACE_وتھ must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جے_انت

#جے_بنا_تعریف config_UNIQUE_رکاوٹ_PRIORITIES
    #غلطی config_UNIQUE_رکاوٹ_PRIORITIES must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جے_انت

#جے_بنا_تعریف config_تیاری_TICK_رکاوٹ
    #غلطی config_تیاری_TICK_رکاوٹ() must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جے_انت /* configSETUP_TICK_INTERRUPT */

#جے_بنا_تعریف config_MAX_API_CALL_رکاوٹ_ترجیح
    #غلطی config_MAX_API_CALL_رکاوٹ_ترجیح must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جے_انت

#إذا config_MAX_API_CALL_رکاوٹ_ترجیح == 0
    #غلطی config_MAX_API_CALL_رکاوٹ_ترجیح must not be سیٹ منزل 0
#جے_انت

#إذا config_MAX_API_CALL_رکاوٹ_ترجیح > config_UNIQUE_رکاوٹ_PRIORITIES
    #غلطی config_MAX_API_CALL_رکاوٹ_ترجیح must be less than or equal منزل config_UNIQUE_رکاوٹ_PRIORITIES as the ہیٹھلا the numeric ترجیح قدر the higher the logical رکاوٹ ترجیح
#جے_انت

#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires ہور than 10 منزل 15 difference priorities as tasks that share a ترجیح will time ٹکڑا.
    #جے_انت
#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#إذا config_MAX_API_CALL_رکاوٹ_ترجیح <= ( config_UNIQUE_رکاوٹ_PRIORITIES / 2 )
    #غلطی config_MAX_API_CALL_رکاوٹ_ترجیح must be greater than ( config_UNIQUE_رکاوٹ_PRIORITIES / 2 )
#جے_انت

/*
 * __ARM_FP is defined by the c preprocessor when FPU support is enabled,
 * usually with the -mfpu= argument and -mfloat-abi=.
 *
 * Note: Some implementations of the c standard library may use FPU registers
 *       for generic memory operations (memcpy, etc).
 *       When setting configUSE_TASK_FPU_SUPPORT == 1, care must be taken to
 *       ensure that the FPU registers are not used without an FPU context.
 */
#إذا ( configUSE_TASK_FPU_SUPPORT == 0 )
    #جے_تعریف_شدہ __ARM_FP
        #غلطی __ARM_FP is defined, so configUSE_TASK_FPU_SUPPORT must be سیٹ منزل either منزل 1 or 2.
    #جے_انت /* __ARM_FP */
#وإلاإذا ( configUSE_TASK_FPU_SUPPORT == 1 ) || ( configUSE_TASK_FPU_SUPPORT == 2 )
    #جے_بنا_تعریف __ARM_FP
        #غلطی __ARM_FP is not defined, so configUSE_TASK_FPU_SUPPORT must be سیٹ منزل 0.
    #جے_انت /* __ARM_FP */
#جے_انت /* configUSE_TASK_FPU_SUPPORT */

/*
 * Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h.
 */
#جے_بنا_تعریف config_CLEAR_TICK_رکاوٹ
    #تعریف_کرو config_CLEAR_TICK_رکاوٹ()
#جے_انت

/*
 * A critical section is exited when the critical section nesting count reaches
 * this value.
 */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/*
 * In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority.
 */
#تعریف_کرو پورٹ_UNMASK_قدر                 ( 0xFFUL )

/*
 * Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context.
 */
#تعریف_کرو پورٹ_NO_FLOATING_نقطہ_CONTEXT    ( ( ڈھیر_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#تعریف_کرو پورٹ_INITIAL_SPSR                 ( ( ڈھیر_Type_t ) 0x1f ) /* System mode, ARM mode, IRQ enabled FIQ enabled. */
#تعریف_کرو پورٹ_THUMB_منوال_ثنائی_ہندسہ               ( ( ڈھیر_Type_t ) 0x20 )
#تعریف_کرو پورٹ_رکاوٹ_ENABLE_ثنائی_ہندسہ         ( 0x80UL )
#تعریف_کرو پورٹ_THUMB_منوال_پتہ           ( 0x01UL )

/*
 * Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero.
 */
#تعریف_کرو پورٹ_ثنائی_نقطہ_بٹ            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#تعریف_کرو پورٹ_APSR_منوال_بٹ_نقاب          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#تعریف_کرو پورٹ_APSR_USER_منوال               ( 0x10 )

/* The critical section macros only mask interrupts up to an application
 * determined priority level.  Sometimes it is necessary to turn interrupt off in
 * the CPU itself before modifying certain hardware registers. */
#تعریف_کرو پورٹ_CPU_IRQ_DISABLE()                  \
    __asm متطاير ( "CPSID i" ::: "memory" ); \
    __asm متطاير ( "DSB" );                  \
    __asm متطاير ( "ISB" );

#تعریف_کرو پورٹ_CPU_IRQ_ENABLE()                   \
    __asm متطاير ( "CPSIE i" ::: "memory" ); \
    __asm متطاير ( "DSB" );                  \
    __asm متطاير ( "ISB" );


/* Macro to unmask all interrupt priorities. */
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب()                            \
    {                                                         \
        پورٹ_CPU_IRQ_DISABLE();                                \
        پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر = پورٹ_UNMASK_قدر; \
        __asm متطاير ( "DSB       \n"                       \
                         "ISB       \n" );                    \
        پورٹ_CPU_IRQ_ENABLE();                                 \
    }

#تعریف_کرو پورٹ_رکاوٹ_ترجیح_رجسٹر_وتھ    0x400UL
#تعریف_کرو پورٹ_MAX_8_ثنائی_ہندسہ_قدر                       ( ( uint8_t ) 0xff )
#تعریف_کرو پورٹ_ثنائی_ہندسہ_0_سیٹ                             ( ( uint8_t ) 0x01 )

/*
 * Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case is messes up unwinding of the stack in the
 * debugger.
 */
#جے_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    config_TASK_RETURN_پتہ
#وإلا
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    prvTaskExitError
#جے_انت

#إذا ( configUSE_TASK_FPU_SUPPORT != 0 )

/*
 * The space on the stack required to hold the FPU registers.
 *
 * The ARM Cortex R5 processor implements the VFPv3-D16 FPU
 * architecture. This includes only 16 double-precision registers,
 * instead of 32 as is in VFPv3. The register bank can be viewed
 * either as sixteen 64-bit double-word registers (D0-D15) or
 * thirty-two 32-bit single-word registers (S0-S31), in both cases
 * the size of the bank remains the same. The FPU has also a 32-bit
 * status register.
 */
    #تعریف_کرو پورٹ_FPU_رجسٹر_الفاظ    ( ( 16 * 2 ) + 1 )
#جے_انت /* configUSE_TASK_FPU_SUPPORT != 0 */

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورٹ_Restore_Task_Context( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

#إذا ( configUSE_TASK_FPU_SUPPORT != 0 )

/*
 * If the application provides an implementation of vApplicationIRQHandler(),
 * then it will get called directly without saving the FPU registers on
 * interrupt entry, and this weak implementation of
 * vApplicationFPUSafeIRQHandler() is just provided to remove linkage errors -
 * it should never actually get called so its implementation contains a
 * call to configASSERT() that will always fail.
 *
 * If the application provides its own implementation of
 * vApplicationFPUSafeIRQHandler() then the implementation of
 * vApplicationIRQHandler() provided in portASM.S will save the FPU registers
 * before calling it.
 *
 * Therefore, if the application writer wants FPU registers to be saved on
 * interrupt entry their IRQ handler must be called
 * vApplicationFPUSafeIRQHandler(), and if the application writer does not want
 * FPU registers to be saved on interrupt entry their IRQ handler must be
 * called vApplicationIRQHandler().
 */
    فراغ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) __attribute__( ( weak ) );
#جے_انت /* configUSE_TASK_FPU_SUPPORT != 0 */

/*-----------------------------------------------------------*/

/*
 * A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started.
 */
متطاير uint32_t ulCriticalNesting = 9999UL;

#إذا ( configUSE_TASK_FPU_SUPPORT != 0 )

/*
 * Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task.
 */
    uint32_t ul_پورٹ_Task_Has_FPUContext = pdFALSE;
#جے_انت /* configUSE_TASK_FPU_SUPPORT != 0 */

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_پورٹ_Yield_Required = pdFALSE;

/*
 * Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0.
 */
uint32_t ul_پورٹ_رکاوٹ_Nesting = 0UL;

/* Used in asm code. */
__attribute__( ( ورتیا ) ) ثابت uint32_t ulICCIAR = پورٹ_ICCIAR_رکاوٹ_ACKNOWLEDGE_رجسٹر_پتہ;
__attribute__( ( ورتیا ) ) ثابت uint32_t ulICCEOIR = پورٹ_ICCEOIR_سرا_دا_رکاوٹ_رجسٹر_پتہ;
__attribute__( ( ورتیا ) ) ثابت uint32_t ulICCPMR = پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر_پتہ;
__attribute__( ( ورتیا ) ) ثابت uint32_t ul_Max_APIPriority_نقاب = ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    /*
     * Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address.
     */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) عدم;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) عدم;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) عدم;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_INITIAL_SPSR;

    إذا( ( ( uint32_t ) px_کوڈ & پورٹ_THUMB_منوال_پتہ ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_چوٹی_دا_ڈھیر |= پورٹ_THUMB_منوال_ثنائی_ہندسہ;
    }

    px_چوٹی_دا_ڈھیر--;

    /* Next the return address, which in this case is the start of the task. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ;
    px_چوٹی_دا_ڈھیر--;

    /* Next all the registers other than the stack pointer. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ; /* R14 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x12121212;              /* R12 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111;              /* R11 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x10101010;              /* R10 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x09090909;              /* R9 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x08080808;              /* R8 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x07070707;              /* R7 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x06060606;              /* R6 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x05050505;              /* R5 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x04040404;              /* R4 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x03030303;              /* R3 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x02020202;              /* R2 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x01010101;              /* R1 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;            /* R0 */

    /*
     * The task will start with a critical nesting count of 0 as interrupts are
     * enabled.
     */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = پورٹ_NO_CRITICAL_NESTING;

    #إذا ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /*
         * The task will start without a floating point context.
         * A task that uses the floating point hardware must call
         * vPortTaskUsesFPU() before executing any floating point
         * instructions.
         */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = پورٹ_NO_FLOATING_نقطہ_CONTEXT;
    }
    #وإلاإذا ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /*
         * The task will start with a floating point context. Leave enough
         * space for the registers and ensure they are initialized to 0.
         */
        px_چوٹی_دا_ڈھیر -= پورٹ_FPU_رجسٹر_الفاظ;
        memset( px_چوٹی_دا_ڈھیر, 0x00, پورٹ_FPU_رجسٹر_الفاظ * حجم( ڈھیر_Type_t ) );

        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = pdTRUE;
        ul_پورٹ_Task_Has_FPUContext = pdTRUE;
    }
    #وإلاإذا ( configUSE_TASK_FPU_SUPPORT != 0 )
    {
        #غلطی Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be سیٹ منزل 0, 1, or 2.
    }
    #جے_انت /* configUSE_TASK_FPU_SUPPORT */

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    /*
     * A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error.
     */
    configASSERT( ul_پورٹ_رکاوٹ_Nesting == ~0UL );
    پورٹ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_FPU_SUPPORT != 0 )

    فراغ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) /* __attribute__( ( weak ) ) */
    {
        ( فراغ ) ulICCIAR;
        configASSERT( ( متطاير فراغ * ) عدم );
    }

#جے_انت /* configUSE_TASK_FPU_SUPPORT != 0 */
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    uint32_t ulAPSR, ul_چکراں = 8; /* 8 bits per byte. */

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_ترجیح;
        متطاير uint8_t * ثابت puc_پہلا_User_ترجیح_رجسٹر = ( متطاير uint8_t * ثابت ) ( config_رکاوٹ_CONTROLLER_ادھار_پتہ + پورٹ_رکاوٹ_ترجیح_رجسٹر_وتھ );
        متطاير uint8_t uc_Max_ترجیح_قدر;

        /*
         * Determine how many priority bits are implemented in the GIC.
         * Save the interrupt priority value that is about to be clobbered.
         */
        uc_Original_ترجیح = *puc_پہلا_User_ترجیح_رجسٹر;

        /*
         * Determine the number of priority bits available.  First write to
         * all possible bits.
         */
        *puc_پہلا_User_ترجیح_رجسٹر = پورٹ_MAX_8_ثنائی_ہندسہ_قدر;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ترجیح_قدر = *puc_پہلا_User_ترجیح_رجسٹر;

        /* Shift to the least significant bits. */
        طالما( ( uc_Max_ترجیح_قدر & پورٹ_ثنائی_ہندسہ_0_سیٹ ) != پورٹ_ثنائی_ہندسہ_0_سیٹ )
        {
            uc_Max_ترجیح_قدر >>= ( uint8_t ) 0x01;

            /*
             * If ulCycles reaches 0 then ucMaxPriorityValue must have been
             * read as 0, indicating a misconfiguration.
             */
            ul_چکراں--;

            إذا( ul_چکراں == 0 )
            {
                اكسر;
            }
        }

        /*
         * Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value.
         */
        configASSERT( uc_Max_ترجیح_قدر == پورٹ_سبھ_توں_نیواں_رکاوٹ_ترجیح );

        /*
         * Restore the clobbered interrupt priority register to its original
         * value.
         */
        *puc_پہلا_User_ترجیح_رجسٹر = uc_Original_ترجیح;
    }
    #جے_انت /* configASSERT_DEFINED */

    /*
     * Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start.
     */
    __asm متطاير ( "MRS %0, APSR" : "=r" ( ulAPSR )::"memory" );
    ulAPSR &= پورٹ_APSR_منوال_بٹ_نقاب;
    configASSERT( ulAPSR != پورٹ_APSR_USER_منوال );

    إذا( ulAPSR != پورٹ_APSR_USER_منوال )
    {
        /*
         * Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information.
         */
        configASSERT( ( پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر & پورٹ_ثنائی_نقطہ_بٹ ) <= پورٹ_MAX_ثنائی_نقطہ_قدر );

        إذا( ( پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر & پورٹ_ثنائی_نقطہ_بٹ ) <= پورٹ_MAX_ثنائی_نقطہ_قدر )
        {
            /*
             * Interrupts are turned off in the CPU itself to ensure tick does
             * not execute  while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing.
             */
            پورٹ_CPU_IRQ_DISABLE();

            /* Start the timer that generates the tick ISR. */
            config_تیاری_TICK_رکاوٹ();

            /* Start the first task executing. */
            v_پورٹ_Restore_Task_Context();
        }
    }

    /*
     * Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address.
     */
    ( فراغ ) prvTaskExitError;

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /*
     * Not implemented in ports where there is nothing to return to.
     * Artificially force an assert.
     */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Enter_Critical( فراغ )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ul_پورٹ_سیٹ_رکاوٹ_نقاب();

    /*
     * Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called.
     */
    ulCriticalNesting++;

    /*
     * This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section.
     */
    إذا( ulCriticalNesting == 1 )
    {
        configASSERT( ul_پورٹ_رکاوٹ_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being exited. */
        ulCriticalNesting--;

        /*
         * If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled.
         */
        إذا( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            /*
             * Critical nesting has reached zero so all interrupt priorities
             * should be unmasked.
             */
            پورٹ_CLEAR_رکاوٹ_نقاب();
        }
    }
}
/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    /*
     * Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    پورٹ_CPU_IRQ_DISABLE();
    پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر = ( uint32_t ) ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ );
    __asm متطاير ( "dsb       \n"
                     "isb       \n" ::: "memory" );
    پورٹ_CPU_IRQ_ENABLE();

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ul_پورٹ_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    پورٹ_CLEAR_رکاوٹ_نقاب();
    config_CLEAR_TICK_رکاوٹ();
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_FPU_SUPPORT == 1 )

    فراغ v_پورٹ_Task_ورتدا_FPU( فراغ )
    {
        uint32_t ulInitialFPSCR = 0;

        /*
         * A task is registering the fact that it needs an FPU context. Set the
         * FPU flag (which is saved as part of the task context).
         */
        ul_پورٹ_Task_Has_FPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        __asm متطاير ( "FMXR  FPSCR, %0" ::"r" ( ulInitialFPSCR ) : "memory" );
    }

#جے_انت /* configUSE_TASK_FPU_SUPPORT == 1 */
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Clear_رکاوٹ_نقاب( uint32_t ul_New_نقاب_قدر )
{
    إذا( ul_New_نقاب_قدر == pdFALSE )
    {
        پورٹ_CLEAR_رکاوٹ_نقاب();
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورٹ_سیٹ_رکاوٹ_نقاب( فراغ )
{
    uint32_t ulReturn;

    /* Interrupts must be masked while ICCPMR is updated. */
    پورٹ_CPU_IRQ_DISABLE();

    إذا( پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر == ( uint32_t ) ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    وإلا
    {
        ulReturn = pdFALSE;
        پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر = ( uint32_t ) ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ );
        __asm متطاير ( "dsb       \n"
                         "isb       \n" ::: "memory" );
    }

    پورٹ_CPU_IRQ_ENABLE();

    أرجع ulReturn;
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ )
    {
        /*
         * The following assertion will fail if a service routine (ISR) for
         * an interrupt that has been assigned a priority above
         * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
         * function.  ISR safe FreeRTOS API functions must *only* be called
         * from interrupts that have been assigned a priority at or below
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * Numerically low interrupt priority numbers represent logically high
         * interrupt priorities, therefore the priority of the interrupt must
         * be set to a value equal to or numerically *higher* than
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * FreeRTOS maintains separate thread and ISR API functions to ensure
         * interrupt entry is as fast and simple as possible.
         */

        configASSERT( پورٹ_ICCRPR_RUNNING_ترجیح_رجسٹر >= ( uint32_t ) ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ ) );

        /*
         * Priority grouping:  The interrupt controller (GIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * The priority grouping is configured by the GIC's binary point register
         * (ICCBPR).  Writing 0 to ICCBPR will ensure it is set to its lowest
         * possible value (which may be above 0).
         */
        configASSERT( ( پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر & پورٹ_ثنائی_نقطہ_بٹ ) <= پورٹ_MAX_ثنائی_نقطہ_قدر );
    }

#جے_انت /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/
