/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ RTOS_SUPPORT_RTOS_CONFIG_H_
#ವ್ಯಾಖ್ಯಾನಿಸು RTOS_SUPPORT_RTOS_CONFIG_H_

/**
 * Lets the application know that the RTOS in use is FreeRTOS.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು RTOS_FREERTOS                              1

/**
 * The number of words to extend the stack by when entering an ISR.
 *
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು RTOS_SUPPORT_ಅಡಚಣೆ_ರಾಶಿ_GROWTH        ( 44 + 1 )

/**
 * The word offset into the stack where R1 is to be stored after it
 * is extended when saving a thread's context.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು RTOS_SUPPORT_ಅಡಚಣೆ_R1_ರಾಶಿ_ಸ್ಥಾನಾಂತರ     9

/**
 * The word offset into the stack where R11 is to be stored after it
 * is extended when saving a thread's context.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು RTOS_SUPPORT_ಅಡಚಣೆ_R11_ರಾಶಿ_ಸ್ಥಾನಾಂತರ    19

/**
 * The RTOS provided handler that should run when a
 * core receives an intercore interrupt request.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು RTOS_INTERCORE_ಅಡಚಣೆ_ISR()       \
    ಮಾಡು {                                     \
        ಶೂನ್ಯ v_Intercore_ಅಡಚಣೆ_ISR( ಶೂನ್ಯ ); \
        v_Intercore_ಅಡಚಣೆ_ISR();            \
    } ಆಗ( 0 )

/**
 * The number of hardware locks that the RTOS
 * requires. For a single core RTOS this could be
 * zero. Locks are recursive.
 *
 * Note that the IRQ routines require a lock and
 * will share the first one with the RTOS.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು RTOS_ಬೀಗ_ಎಣಿಕೆ            2

/**
 * Remaps all calls to debug_printf() to rtos_printf().
 * When this is on, files should not include both rtos_support.h
 * and debug_print.h.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು RTOS_DEBUG_PRINTF_REMAP    1


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ configENABLE_DEBUG_PRINTF
    #ಆದರೆ configENABLE_DEBUG_PRINTF

/* ensure that debug_printf is enabled */
        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_PRINT_ENABLE
            #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು DEBUG_PRINT_ENABLE
        #ಆದರೆ_ಅಂತ್ಯ
        #ವ್ಯಾಖ್ಯಾನಿಸು DEBUG_PRINT_ENABLE                        1

        #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configTASKS_DEBUG
            #ವ್ಯಾಖ್ಯಾನಿಸು configTASKS_DEBUG                     0
        #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ configTASKS_DEBUG == 1
            #ವ್ಯಾಖ್ಯಾನಿಸು DEBUG_PRINT_ENABLE_FREERTOS_TASKS     1
        #ಇಲ್ಲದಿದ್ದರೆ
            #ವ್ಯಾಖ್ಯಾನಿಸು DEBUG_PRINT_DISABLE_FREERTOS_TASKS    1
        #ಆದರೆ_ಅಂತ್ಯ

    #ಇಲ್ಲದಿದ್ದರೆ /* configENABLE_DEBUG_PRINTF */

/* ensure that debug_printf is disabled */
        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_UNIT
            #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು DEBUG_UNIT
        #ಆದರೆ_ಅಂತ್ಯ
        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_PRINT_ENABLE
            #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು DEBUG_PRINT_ENABLE
        #ಆದರೆ_ಅಂತ್ಯ

        #ವ್ಯಾಖ್ಯಾನಿಸು DEBUG_PRINT_ENABLE    0

    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_DEBUG_PRINTF */
#ಆದರೆ_ಅಂತ್ಯ /* ifdef configENABLE_DEBUG_PRINTF */

#ಆದರೆ_ಅಂತ್ಯ /* RTOS_SUPPORT_RTOS_CONFIG_H_ */
