/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#جيڪڏهن_وصف_نه_ٿيل RTOS_SUPPORT_RTOS_CONFIG_H_
#وصف_ڪريو RTOS_SUPPORT_RTOS_CONFIG_H_

/**
 * Lets the application know that the RTOS in use is FreeRTOS.
 */
#وصف_ڪريو RTOS_FREERTOS                              1

/**
 * The number of words to extend the stack by when entering an ISR.
 *
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
#وصف_ڪريو RTOS_SUPPORT_مداخلت_ڍير_GROWTH        ( 44 + 1 )

/**
 * The word offset into the stack where R1 is to be stored after it
 * is extended when saving a thread's context.
 */
#وصف_ڪريو RTOS_SUPPORT_مداخلت_R1_ڍير_وٿي     9

/**
 * The word offset into the stack where R11 is to be stored after it
 * is extended when saving a thread's context.
 */
#وصف_ڪريو RTOS_SUPPORT_مداخلت_R11_ڍير_وٿي    19

/**
 * The RTOS provided handler that should run when a
 * core receives an intercore interrupt request.
 */
#وصف_ڪريو RTOS_INTERCORE_مداخلت_ISR()       \
    افعل {                                     \
        فراغ v_Intercore_مداخلت_ISR( فراغ ); \
        v_Intercore_مداخلت_ISR();            \
    } طالما( 0 )

/**
 * The number of hardware locks that the RTOS
 * requires. For a single core RTOS this could be
 * zero. Locks are recursive.
 *
 * Note that the IRQ routines require a lock and
 * will share the first one with the RTOS.
 */
#وصف_ڪريو RTOS_تالو_ڳڻپ            2

/**
 * Remaps all calls to debug_printf() to rtos_printf().
 * When this is on, files should not include both rtos_support.h
 * and debug_print.h.
 */
#وصف_ڪريو RTOS_DEBUG_PRINTF_REMAP    1


#جيڪڏهن_وصف_ٿيل configENABLE_DEBUG_PRINTF
    #إذا configENABLE_DEBUG_PRINTF

/* ensure that debug_printf is enabled */
        #جيڪڏهن_وصف_ٿيل DEBUG_PRINT_ENABLE
            #وصف_رد DEBUG_PRINT_ENABLE
        #جيڪڏهن_پورو
        #وصف_ڪريو DEBUG_PRINT_ENABLE                        1

        #جيڪڏهن_وصف_نه_ٿيل configTASKS_DEBUG
            #وصف_ڪريو configTASKS_DEBUG                     0
        #جيڪڏهن_پورو
        #إذا configTASKS_DEBUG == 1
            #وصف_ڪريو DEBUG_PRINT_ENABLE_FREERTOS_TASKS     1
        #وإلا
            #وصف_ڪريو DEBUG_PRINT_DISABLE_FREERTOS_TASKS    1
        #جيڪڏهن_پورو

    #وإلا /* configENABLE_DEBUG_PRINTF */

/* ensure that debug_printf is disabled */
        #جيڪڏهن_وصف_ٿيل DEBUG_UNIT
            #وصف_رد DEBUG_UNIT
        #جيڪڏهن_پورو
        #جيڪڏهن_وصف_ٿيل DEBUG_PRINT_ENABLE
            #وصف_رد DEBUG_PRINT_ENABLE
        #جيڪڏهن_پورو

        #وصف_ڪريو DEBUG_PRINT_ENABLE    0

    #جيڪڏهن_پورو /* configENABLE_DEBUG_PRINTF */
#جيڪڏهن_پورو /* ifdef configENABLE_DEBUG_PRINTF */

#جيڪڏهن_پورو /* RTOS_SUPPORT_RTOS_CONFIG_H_ */
