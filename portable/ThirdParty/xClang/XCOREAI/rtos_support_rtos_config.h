/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#यदि_अपरिभाषितम् RTOS_SUPPORT_RTOS_CONFIG_H_
#परिभाषय RTOS_SUPPORT_RTOS_CONFIG_H_

/**
 * Lets the application know that the RTOS in use is FreeRTOS.
 */
#परिभाषय RTOS_FREERTOS                              1

/**
 * The number of words to extend the stack by when entering an ISR.
 *
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
#परिभाषय RTOS_SUPPORT_व्यवधानम्_राशिः_GROWTH        ( 44 + 1 )

/**
 * The word offset into the stack where R1 is to be stored after it
 * is extended when saving a thread's context.
 */
#परिभाषय RTOS_SUPPORT_व्यवधानम्_R1_राशिः_विस्थापनम्     9

/**
 * The word offset into the stack where R11 is to be stored after it
 * is extended when saving a thread's context.
 */
#परिभाषय RTOS_SUPPORT_व्यवधानम्_R11_राशिः_विस्थापनम्    19

/**
 * The RTOS provided handler that should run when a
 * core receives an intercore interrupt request.
 */
#परिभाषय RTOS_INTERCORE_व्यवधानम्_ISR()       \
    कुरु {                                     \
        शून्य v_Intercore_व्यवधानम्_ISR( शून्य ); \
        v_Intercore_व्यवधानम्_ISR();            \
    } यावत्( 0 )

/**
 * The number of hardware locks that the RTOS
 * requires. For a single core RTOS this could be
 * zero. Locks are recursive.
 *
 * Note that the IRQ routines require a lock and
 * will share the first one with the RTOS.
 */
#परिभाषय RTOS_तालकम्_गणनम्            2

/**
 * Remaps all calls to debug_printf() to rtos_printf().
 * When this is on, files should not include both rtos_support.h
 * and debug_print.h.
 */
#परिभाषय RTOS_DEBUG_PRINTF_REMAP    1


#यदि_परिभाषितम् configENABLE_DEBUG_PRINTF
    #यदि configENABLE_DEBUG_PRINTF

/* ensure that debug_printf is enabled */
        #यदि_परिभाषितम् DEBUG_PRINT_ENABLE
            #अपरिभाषय DEBUG_PRINT_ENABLE
        #यदि_अन्तः
        #परिभाषय DEBUG_PRINT_ENABLE                        1

        #यदि_अपरिभाषितम् configTASKS_DEBUG
            #परिभाषय configTASKS_DEBUG                     0
        #यदि_अन्तः
        #यदि configTASKS_DEBUG == 1
            #परिभाषय DEBUG_PRINT_ENABLE_FREERTOS_TASKS     1
        #अन्यथा
            #परिभाषय DEBUG_PRINT_DISABLE_FREERTOS_TASKS    1
        #यदि_अन्तः

    #अन्यथा /* configENABLE_DEBUG_PRINTF */

/* ensure that debug_printf is disabled */
        #यदि_परिभाषितम् DEBUG_UNIT
            #अपरिभाषय DEBUG_UNIT
        #यदि_अन्तः
        #यदि_परिभाषितम् DEBUG_PRINT_ENABLE
            #अपरिभाषय DEBUG_PRINT_ENABLE
        #यदि_अन्तः

        #परिभाषय DEBUG_PRINT_ENABLE    0

    #यदि_अन्तः /* configENABLE_DEBUG_PRINTF */
#यदि_अन्तः /* ifdef configENABLE_DEBUG_PRINTF */

#यदि_अन्तः /* RTOS_SUPPORT_RTOS_CONFIG_H_ */
