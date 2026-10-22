/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#جے_بنا_تعریف RTOS_SUPPORT_RTOS_CONFIG_H_
#تعریف_کرو RTOS_SUPPORT_RTOS_CONFIG_H_

/**
 * Lets the application know that the RTOS in use is FreeRTOS.
 */
#تعریف_کرو RTOS_FREERTOS                              1

/**
 * The number of words to extend the stack by when entering an ISR.
 *
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
#تعریف_کرو RTOS_SUPPORT_رکاوٹ_ڈھیر_GROWTH        ( 44 + 1 )

/**
 * The word offset into the stack where R1 is to be stored after it
 * is extended when saving a thread's context.
 */
#تعریف_کرو RTOS_SUPPORT_رکاوٹ_R1_ڈھیر_وتھ     9

/**
 * The word offset into the stack where R11 is to be stored after it
 * is extended when saving a thread's context.
 */
#تعریف_کرو RTOS_SUPPORT_رکاوٹ_R11_ڈھیر_وتھ    19

/**
 * The RTOS provided handler that should run when a
 * core receives an intercore interrupt request.
 */
#تعریف_کرو RTOS_INTERCORE_رکاوٹ_ISR()       \
    افعل {                                     \
        فراغ v_Intercore_رکاوٹ_ISR( فراغ ); \
        v_Intercore_رکاوٹ_ISR();            \
    } طالما( 0 )

/**
 * The number of hardware locks that the RTOS
 * requires. For a single core RTOS this could be
 * zero. Locks are recursive.
 *
 * Note that the IRQ routines require a lock and
 * will share the first one with the RTOS.
 */
#تعریف_کرو RTOS_جندرا_گنتی            2

/**
 * Remaps all calls to debug_printf() to rtos_printf().
 * When this is on, files should not include both rtos_support.h
 * and debug_print.h.
 */
#تعریف_کرو RTOS_DEBUG_PRINTF_REMAP    1


#جے_تعریف_شدہ configENABLE_DEBUG_PRINTF
    #إذا configENABLE_DEBUG_PRINTF

/* ensure that debug_printf is enabled */
        #جے_تعریف_شدہ DEBUG_PRINT_ENABLE
            #تعریف_رد DEBUG_PRINT_ENABLE
        #جے_انت
        #تعریف_کرو DEBUG_PRINT_ENABLE                        1

        #جے_بنا_تعریف configTASKS_DEBUG
            #تعریف_کرو configTASKS_DEBUG                     0
        #جے_انت
        #إذا configTASKS_DEBUG == 1
            #تعریف_کرو DEBUG_PRINT_ENABLE_FREERTOS_TASKS     1
        #وإلا
            #تعریف_کرو DEBUG_PRINT_DISABLE_FREERTOS_TASKS    1
        #جے_انت

    #وإلا /* configENABLE_DEBUG_PRINTF */

/* ensure that debug_printf is disabled */
        #جے_تعریف_شدہ DEBUG_UNIT
            #تعریف_رد DEBUG_UNIT
        #جے_انت
        #جے_تعریف_شدہ DEBUG_PRINT_ENABLE
            #تعریف_رد DEBUG_PRINT_ENABLE
        #جے_انت

        #تعریف_کرو DEBUG_PRINT_ENABLE    0

    #جے_انت /* configENABLE_DEBUG_PRINTF */
#جے_انت /* ifdef configENABLE_DEBUG_PRINTF */

#جے_انت /* RTOS_SUPPORT_RTOS_CONFIG_H_ */
