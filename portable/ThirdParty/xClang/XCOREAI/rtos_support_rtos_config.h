/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#నిర్వచితం_కాకపోతే RTOS_SUPPORT_RTOS_CONFIG_H_
#నిర్వచించు RTOS_SUPPORT_RTOS_CONFIG_H_

/**
 * Lets the application know that the RTOS in use is FreeRTOS.
 */
#నిర్వచించు RTOS_FREERTOS                              1

/**
 * The number of words to extend the stack by when entering an ISR.
 *
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
#నిర్వచించు RTOS_SUPPORT_అంతరాయం_దొంతర_GROWTH        ( 44 + 1 )

/**
 * The word offset into the stack where R1 is to be stored after it
 * is extended when saving a thread's context.
 */
#నిర్వచించు RTOS_SUPPORT_అంతరాయం_R1_దొంతర_స్థానభ్రంశం     9

/**
 * The word offset into the stack where R11 is to be stored after it
 * is extended when saving a thread's context.
 */
#నిర్వచించు RTOS_SUPPORT_అంతరాయం_R11_దొంతర_స్థానభ్రంశం    19

/**
 * The RTOS provided handler that should run when a
 * core receives an intercore interrupt request.
 */
#నిర్వచించు RTOS_INTERCORE_అంతరాయం_ISR()       \
    చేయి {                                     \
        శూన్య v_Intercore_అంతరాయం_ISR( శూన్య ); \
        v_Intercore_అంతరాయం_ISR();            \
    } అయితే( 0 )

/**
 * The number of hardware locks that the RTOS
 * requires. For a single core RTOS this could be
 * zero. Locks are recursive.
 *
 * Note that the IRQ routines require a lock and
 * will share the first one with the RTOS.
 */
#నిర్వచించు RTOS_తాళం_లెక్క            2

/**
 * Remaps all calls to debug_printf() to rtos_printf().
 * When this is on, files should not include both rtos_support.h
 * and debug_print.h.
 */
#నిర్వచించు RTOS_DEBUG_PRINTF_REMAP    1


#నిర్వచితమైతే configENABLE_DEBUG_PRINTF
    #ఒకవేళ configENABLE_DEBUG_PRINTF

/* ensure that debug_printf is enabled */
        #నిర్వచితమైతే DEBUG_PRINT_ENABLE
            #నిర్వచనం_రద్దు DEBUG_PRINT_ENABLE
        #అయితే_ముగింపు
        #నిర్వచించు DEBUG_PRINT_ENABLE                        1

        #నిర్వచితం_కాకపోతే configTASKS_DEBUG
            #నిర్వచించు configTASKS_DEBUG                     0
        #అయితే_ముగింపు
        #ఒకవేళ configTASKS_DEBUG == 1
            #నిర్వచించు DEBUG_PRINT_ENABLE_FREERTOS_TASKS     1
        #లేకపోతే
            #నిర్వచించు DEBUG_PRINT_DISABLE_FREERTOS_TASKS    1
        #అయితే_ముగింపు

    #లేకపోతే /* configENABLE_DEBUG_PRINTF */

/* ensure that debug_printf is disabled */
        #నిర్వచితమైతే DEBUG_UNIT
            #నిర్వచనం_రద్దు DEBUG_UNIT
        #అయితే_ముగింపు
        #నిర్వచితమైతే DEBUG_PRINT_ENABLE
            #నిర్వచనం_రద్దు DEBUG_PRINT_ENABLE
        #అయితే_ముగింపు

        #నిర్వచించు DEBUG_PRINT_ENABLE    0

    #అయితే_ముగింపు /* configENABLE_DEBUG_PRINTF */
#అయితే_ముగింపు /* ifdef configENABLE_DEBUG_PRINTF */

#అయితే_ముగింపు /* RTOS_SUPPORT_RTOS_CONFIG_H_ */
