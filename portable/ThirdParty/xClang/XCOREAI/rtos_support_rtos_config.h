/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ RTOS_SUPPORT_RTOS_CONFIG_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTOS_SUPPORT_RTOS_CONFIG_H_

/**
 * Lets the application know that the RTOS in use is FreeRTOS.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTOS_FREERTOS                              1

/**
 * The number of words to extend the stack by when entering an ISR.
 *
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTOS_SUPPORT_ਰੁਕਾਵਟ_ਢੇਰ_GROWTH        ( 44 + 1 )

/**
 * The word offset into the stack where R1 is to be stored after it
 * is extended when saving a thread's context.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTOS_SUPPORT_ਰੁਕਾਵਟ_R1_ਢੇਰ_ਵਿੱਥ     9

/**
 * The word offset into the stack where R11 is to be stored after it
 * is extended when saving a thread's context.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTOS_SUPPORT_ਰੁਕਾਵਟ_R11_ਢੇਰ_ਵਿੱਥ    19

/**
 * The RTOS provided handler that should run when a
 * core receives an intercore interrupt request.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTOS_INTERCORE_ਰੁਕਾਵਟ_ISR()       \
    ਕਰੋ {                                     \
        ਖਾਲੀ v_Intercore_ਰੁਕਾਵਟ_ISR( ਖਾਲੀ ); \
        v_Intercore_ਰੁਕਾਵਟ_ISR();            \
    } ਜਦੋਂ( 0 )

/**
 * The number of hardware locks that the RTOS
 * requires. For a single core RTOS this could be
 * zero. Locks are recursive.
 *
 * Note that the IRQ routines require a lock and
 * will share the first one with the RTOS.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTOS_ਤਾਲਾ_ਗਿਣਤੀ            2

/**
 * Remaps all calls to debug_printf() to rtos_printf().
 * When this is on, files should not include both rtos_support.h
 * and debug_print.h.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTOS_DEBUG_PRINTF_REMAP    1


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ configENABLE_DEBUG_PRINTF
    #ਜੇ configENABLE_DEBUG_PRINTF

/* ensure that debug_printf is enabled */
        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_PRINT_ENABLE
            #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ DEBUG_PRINT_ENABLE
        #ਜੇ_ਅੰਤ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG_PRINT_ENABLE                        1

        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configTASKS_DEBUG
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configTASKS_DEBUG                     0
        #ਜੇ_ਅੰਤ
        #ਜੇ configTASKS_DEBUG == 1
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG_PRINT_ENABLE_FREERTOS_TASKS     1
        #ਨਹੀਂਤਾਂ
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG_PRINT_DISABLE_FREERTOS_TASKS    1
        #ਜੇ_ਅੰਤ

    #ਨਹੀਂਤਾਂ /* configENABLE_DEBUG_PRINTF */

/* ensure that debug_printf is disabled */
        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_UNIT
            #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ DEBUG_UNIT
        #ਜੇ_ਅੰਤ
        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_PRINT_ENABLE
            #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ DEBUG_PRINT_ENABLE
        #ਜੇ_ਅੰਤ

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG_PRINT_ENABLE    0

    #ਜੇ_ਅੰਤ /* configENABLE_DEBUG_PRINTF */
#ਜੇ_ਅੰਤ /* ifdef configENABLE_DEBUG_PRINTF */

#ਜੇ_ਅੰਤ /* RTOS_SUPPORT_RTOS_CONFIG_H_ */
