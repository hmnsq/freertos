/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#अगर_अघोषित RTOS_SUPPORT_RTOS_CONFIG_H_
#घोषणा RTOS_SUPPORT_RTOS_CONFIG_H_

/**
 * Lets the application know that the RTOS in use is FreeRTOS.
 */
#घोषणा RTOS_FREERTOS                              1

/**
 * The number of words to extend the stack by when entering an ISR.
 *
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
#घोषणा RTOS_SUPPORT_INTERRUPT_ढेर_GROWTH        ( 44 + 1 )

/**
 * The word offset into the stack where R1 is to be stored after it
 * is extended when saving a thread's context.
 */
#घोषणा RTOS_SUPPORT_INTERRUPT_R1_ढेर_OFFSET     9

/**
 * The word offset into the stack where R11 is to be stored after it
 * is extended when saving a thread's context.
 */
#घोषणा RTOS_SUPPORT_INTERRUPT_R11_ढेर_OFFSET    19

/**
 * The RTOS provided handler that should run when a
 * core receives an intercore interrupt request.
 */
#घोषणा RTOS_INTERCORE_INTERRUPT_ISR()       \
    करो {                                     \
        व्योम vIntercoreInterruptISR( व्योम ); \
        vIntercoreInterruptISR();            \
    } जबतक( 0 )

/**
 * The number of hardware locks that the RTOS
 * requires. For a single core RTOS this could be
 * zero. Locks are recursive.
 *
 * Note that the IRQ routines require a lock and
 * will share the first one with the RTOS.
 */
#घोषणा RTOS_LOCK_गिनती            2

/**
 * Remaps all calls to debug_printf() to rtos_printf().
 * When this is on, files should not include both rtos_support.h
 * and debug_print.h.
 */
#घोषणा RTOS_DEBUG_PRINTF_REMAP    1


#अगर_घोषित configENABLE_DEBUG_PRINTF
    #अगर configENABLE_DEBUG_PRINTF

/* ensure that debug_printf is enabled */
        #अगर_घोषित DEBUG_PRINT_ENABLE
            #अघोषित DEBUG_PRINT_ENABLE
        #पूर्ण_अगर
        #घोषणा DEBUG_PRINT_ENABLE                        1

        #अगर_अघोषित configTASKS_DEBUG
            #घोषणा configTASKS_DEBUG                     0
        #पूर्ण_अगर
        #अगर configTASKS_DEBUG == 1
            #घोषणा DEBUG_PRINT_ENABLE_FREERTOS_TASKS     1
        #अन्यथा
            #घोषणा DEBUG_PRINT_DISABLE_FREERTOS_TASKS    1
        #पूर्ण_अगर

    #अन्यथा /* configENABLE_DEBUG_PRINTF */

/* ensure that debug_printf is disabled */
        #अगर_घोषित DEBUG_UNIT
            #अघोषित DEBUG_UNIT
        #पूर्ण_अगर
        #अगर_घोषित DEBUG_PRINT_ENABLE
            #अघोषित DEBUG_PRINT_ENABLE
        #पूर्ण_अगर

        #घोषणा DEBUG_PRINT_ENABLE    0

    #पूर्ण_अगर /* configENABLE_DEBUG_PRINTF */
#पूर्ण_अगर /* ifdef configENABLE_DEBUG_PRINTF */

#पूर्ण_अगर /* RTOS_SUPPORT_RTOS_CONFIG_H_ */
