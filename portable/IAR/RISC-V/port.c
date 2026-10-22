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
 * Implementation of functions defined in portable.h for the RISC-V port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "portmacro.h"

/* Standard includes. */
#ضمن "string.h"

#اگر_تعریف_شده config_CLINT_پایه_آدرس
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#پایان_اگر

#اگر_تعریف_نشده config_MTIME_پایه_آدرس
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#پایان_اگر

#اگر_تعریف_نشده config_MTIMECMP_پایه_آدرس
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#پایان_اگر

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#اگر_تعریف_شده config_TASK_RETURN_آدرس
    #تعریف_کن پورت_TASK_RETURN_آدرس    config_TASK_RETURN_آدرس
#وإلا
    #تعریف_کن پورت_TASK_RETURN_آدرس    prvTaskExitError
#پایان_اگر

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#اگر_تعریف_شده config_ISR_پشته_اندازه_واژگان
ساكن __attribute__( ( aligned( 16 ) ) ) پشته_Type_t xISRStack[ config_ISR_پشته_اندازه_واژگان ] = { 0 };
ثابت پشته_Type_t x_ISRStack_بالاترین = ( پشته_Type_t ) &( xISRStack[ config_ISR_پشته_اندازه_واژگان & ~پورت_BYTE_ALIGNMENT_ماسک ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #تعریف_کن پورت_ISR_پشته_FILL_BYTE    0xee
#وإلا
    خارجي ثابت uint32_t __freertos_irq_stack_top[];
    ثابت پشته_Type_t x_ISRStack_بالاترین = ( پشته_Type_t ) __freertos_irq_stack_top;
#پایان_اگر

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ull_بعدی_زمان = 0ULL;
ثابت uint64_t * pull_بعدی_زمان = &ull_بعدی_زمان;
ثابت size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( config_TICK_نرخ_HZ ) ); /* Assumes increment won't go over 32-bits. */
متطاير uint64_t * pull_Machine_Timer_Compare_ثبات = عدم;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
size_t xCriticalNesting = ( size_t ) 0xaaaaaaaa;
size_t * pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
size_t x_Task_Return_آدرس = ( size_t ) پورت_TASK_RETURN_آدرس;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#إذا defined( config_ISR_پشته_اندازه_واژگان ) && ( config_CHECK_FOR_پشته_سرریز > 2 )
    #warning "This path not tested, or even compiled yet."

    ساكن ثابت uint8_t uc_Expected_پشته_بایتها[] =
    {
        پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, \
        پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, \
        پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, \
        پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, \
        پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE
    }; \

    #تعریف_کن پورت_CHECK_ISR_پشته()    configASSERT( ( memcmp( ( فراغ * ) xISRStack, ( فراغ * ) uc_Expected_پشته_بایتها, حجم( uc_Expected_پشته_بایتها ) ) == 0 ) )
#وإلا /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #تعریف_کن پورت_CHECK_ISR_پشته()
#پایان_اگر /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    متطاير uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( xCriticalNesting == ~0UL );
    پورت_DISABLE_INTERRUPTS();

    طالما( ulDummy == 0 )
    {
        /* This file calls prvTaskExitError() after the scheduler has been
         * started to remove a compiler warning about the function being
         * defined but never called.  ulDummy is used purely to quieten other
         * warnings about code appearing after this function is called - making
         * ulDummy volatile makes the compiler think the function could return
         * and therefore not output an 'unreachable code' warning for code that
         * appears after it. */
    }
}
/*-----------------------------------------------------------*/

#إذا ( config_MTIME_پایه_آدرس != 0 ) && ( config_MTIMECMP_پایه_آدرس != 0 )

    فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ )
    {
        uint32_t ul_Current_زمان_بالا, ul_Current_زمان_کم;
        متطاير uint32_t * ثابت pul_زمان_بالا = ( uint32_t * ) ( ( config_MTIME_پایه_آدرس ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        متطاير uint32_t * ثابت pul_زمان_کم = ( uint32_t * ) ( config_MTIME_پایه_آدرس );
        متطاير uint32_t ulHartId;

        __asm متطاير ( "csrr %0, 0xf14" : "=r" ( ulHartId ) ); /* 0xf14 is HART ID. */

        pull_Machine_Timer_Compare_ثبات = ( متطاير uint64_t * ) ( config_MTIMECMP_پایه_آدرس + ( ulHartId * حجم( uint64_t ) ) );

        افعل
        {
            ul_Current_زمان_بالا = *pul_زمان_بالا;
            ul_Current_زمان_کم = *pul_زمان_کم;
        } طالما( ul_Current_زمان_بالا != *pul_زمان_بالا );

        ull_بعدی_زمان = ( uint64_t ) ul_Current_زمان_بالا;
        ull_بعدی_زمان <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ull_بعدی_زمان |= ( uint64_t ) ul_Current_زمان_کم;
        ull_بعدی_زمان += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pull_Machine_Timer_Compare_ثبات = ull_بعدی_زمان;

        /* Prepare the time to use after the next tick interrupt. */
        ull_بعدی_زمان += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#پایان_اگر /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    خارجي فراغ x_پورت_شروع_اولی_Task( فراغ );

    #إذا ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_بالاترین & پورت_BYTE_ALIGNMENT_ماسک ) == 0 );

        #اگر_تعریف_شده config_ISR_پشته_اندازه_واژگان
        {
            memset( ( فراغ * ) xISRStack, پورت_ISR_پشته_FILL_BYTE, حجم( xISRStack ) );
        }
        #پایان_اگر /* configISR_STACK_SIZE_WORDS */
    }
    #پایان_اگر /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    v_پورت_راهاندازی_Timer_وقفه();

    #إذا ( ( config_MTIME_پایه_آدرس != 0 ) && ( config_MTIMECMP_پایه_آدرس != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm متطاير ( "csrs 0x304, %0" ::"r" ( 0x880 ) ); /* 0x304 is mie. */
    }
    #پایان_اگر /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    x_پورت_شروع_اولی_Task();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented. */
    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
