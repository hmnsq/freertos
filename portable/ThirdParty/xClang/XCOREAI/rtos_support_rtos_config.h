/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#اگر_تعریف_نشده RTOS_SUPPORT_RTOS_CONFIG_H_
#تعریف_کن RTOS_SUPPORT_RTOS_CONFIG_H_

/**
 * Lets the application know that the RTOS in use is FreeRTOS.
 */
#تعریف_کن RTOS_FREERTOS                              1

/**
 * The number of words to extend the stack by when entering an ISR.
 *
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
#تعریف_کن RTOS_SUPPORT_وقفه_پشته_GROWTH        ( 44 + 1 )

/**
 * The word offset into the stack where R1 is to be stored after it
 * is extended when saving a thread's context.
 */
#تعریف_کن RTOS_SUPPORT_وقفه_R1_پشته_جابه_جایی     9

/**
 * The word offset into the stack where R11 is to be stored after it
 * is extended when saving a thread's context.
 */
#تعریف_کن RTOS_SUPPORT_وقفه_R11_پشته_جابه_جایی    19

/**
 * The RTOS provided handler that should run when a
 * core receives an intercore interrupt request.
 */
#تعریف_کن RTOS_INTERCORE_وقفه_ISR()       \
    افعل {                                     \
        فراغ v_Intercore_وقفه_ISR( فراغ ); \
        v_Intercore_وقفه_ISR();            \
    } طالما( 0 )

/**
 * The number of hardware locks that the RTOS
 * requires. For a single core RTOS this could be
 * zero. Locks are recursive.
 *
 * Note that the IRQ routines require a lock and
 * will share the first one with the RTOS.
 */
#تعریف_کن RTOS_قفل_شمار            2

/**
 * Remaps all calls to debug_printf() to rtos_printf().
 * When this is on, files should not include both rtos_support.h
 * and debug_print.h.
 */
#تعریف_کن RTOS_DEBUG_PRINTF_REMAP    1


#اگر_تعریف_شده configENABLE_DEBUG_PRINTF
    #إذا configENABLE_DEBUG_PRINTF

/* ensure that debug_printf is enabled */
        #اگر_تعریف_شده DEBUG_PRINT_ENABLE
            #لغو_تعریف DEBUG_PRINT_ENABLE
        #پایان_اگر
        #تعریف_کن DEBUG_PRINT_ENABLE                        1

        #اگر_تعریف_نشده configTASKS_DEBUG
            #تعریف_کن configTASKS_DEBUG                     0
        #پایان_اگر
        #إذا configTASKS_DEBUG == 1
            #تعریف_کن DEBUG_PRINT_ENABLE_FREERTOS_TASKS     1
        #وإلا
            #تعریف_کن DEBUG_PRINT_DISABLE_FREERTOS_TASKS    1
        #پایان_اگر

    #وإلا /* configENABLE_DEBUG_PRINTF */

/* ensure that debug_printf is disabled */
        #اگر_تعریف_شده DEBUG_UNIT
            #لغو_تعریف DEBUG_UNIT
        #پایان_اگر
        #اگر_تعریف_شده DEBUG_PRINT_ENABLE
            #لغو_تعریف DEBUG_PRINT_ENABLE
        #پایان_اگر

        #تعریف_کن DEBUG_PRINT_ENABLE    0

    #پایان_اگر /* configENABLE_DEBUG_PRINTF */
#پایان_اگر /* ifdef configENABLE_DEBUG_PRINTF */

#پایان_اگر /* RTOS_SUPPORT_RTOS_CONFIG_H_ */
