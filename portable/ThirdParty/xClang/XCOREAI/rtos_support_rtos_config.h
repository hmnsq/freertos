/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#که_نه_تعریف_شوی RTOS_SUPPORT_RTOS_CONFIG_H_
#تعریف_کړه RTOS_SUPPORT_RTOS_CONFIG_H_

/**
 * Lets the application know that the RTOS in use is FreeRTOS.
 */
#تعریف_کړه RTOS_FREERTOS                              1

/**
 * The number of words to extend the stack by when entering an ISR.
 *
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
#تعریف_کړه RTOS_SUPPORT_مداخله_ډېری_GROWTH        ( 44 + 1 )

/**
 * The word offset into the stack where R1 is to be stored after it
 * is extended when saving a thread's context.
 */
#تعریف_کړه RTOS_SUPPORT_مداخله_R1_ډېری_دننه_واټن     9

/**
 * The word offset into the stack where R11 is to be stored after it
 * is extended when saving a thread's context.
 */
#تعریف_کړه RTOS_SUPPORT_مداخله_R11_ډېری_دننه_واټن    19

/**
 * The RTOS provided handler that should run when a
 * core receives an intercore interrupt request.
 */
#تعریف_کړه RTOS_INTERCORE_مداخله_ISR()       \
    افعل {                                     \
        فراغ v_Intercore_مداخله_ISR( فراغ ); \
        v_Intercore_مداخله_ISR();            \
    } طالما( 0 )

/**
 * The number of hardware locks that the RTOS
 * requires. For a single core RTOS this could be
 * zero. Locks are recursive.
 *
 * Note that the IRQ routines require a lock and
 * will share the first one with the RTOS.
 */
#تعریف_کړه RTOS_قلف_شمېر            2

/**
 * Remaps all calls to debug_printf() to rtos_printf().
 * When this is on, files should not include both rtos_support.h
 * and debug_print.h.
 */
#تعریف_کړه RTOS_DEBUG_PRINTF_REMAP    1


#که_تعریف_شوی configENABLE_DEBUG_PRINTF
    #إذا configENABLE_DEBUG_PRINTF

/* ensure that debug_printf is enabled */
        #که_تعریف_شوی DEBUG_PRINT_ENABLE
            #تعریف_لغوه DEBUG_PRINT_ENABLE
        #د_که_پای
        #تعریف_کړه DEBUG_PRINT_ENABLE                        1

        #که_نه_تعریف_شوی configTASKS_DEBUG
            #تعریف_کړه configTASKS_DEBUG                     0
        #د_که_پای
        #إذا configTASKS_DEBUG == 1
            #تعریف_کړه DEBUG_PRINT_ENABLE_FREERTOS_TASKS     1
        #وإلا
            #تعریف_کړه DEBUG_PRINT_DISABLE_FREERTOS_TASKS    1
        #د_که_پای

    #وإلا /* configENABLE_DEBUG_PRINTF */

/* ensure that debug_printf is disabled */
        #که_تعریف_شوی DEBUG_UNIT
            #تعریف_لغوه DEBUG_UNIT
        #د_که_پای
        #که_تعریف_شوی DEBUG_PRINT_ENABLE
            #تعریف_لغوه DEBUG_PRINT_ENABLE
        #د_که_پای

        #تعریف_کړه DEBUG_PRINT_ENABLE    0

    #د_که_پای /* configENABLE_DEBUG_PRINTF */
#د_که_پای /* ifdef configENABLE_DEBUG_PRINTF */

#د_که_پای /* RTOS_SUPPORT_RTOS_CONFIG_H_ */
