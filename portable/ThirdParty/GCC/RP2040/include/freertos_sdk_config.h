/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
 */

#यदि_अपरिभाषितम् FREERTOS_SDK_CONFIG_H
#परिभाषय FREERTOS_SDK_CONFIG_H

#यदि_अपरिभाषितम् __ASSEMBLER__
    #अन्तर्भाव "FreeRTOSConfig.h"
    #अन्तर्भाव "rp2040_config.h"
    #यदि_अपरिभाषितम् PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #परिभाषय PICO_USE_MALLOC_MUTEX    1
    #यदि_अन्तः /* PICO_USE_MALLOC_MUTEX */
    #यदि ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #यदि_अपरिभाषितम् PICO_TIME_SLEEP_OVERHEAD_ADJUST_US
            #परिभाषय PICO_TIME_SLEEP_OVERHEAD_ADJUST_US    150
        #यदि_अन्तः

        #परिभाषय तालकम्_owner_id_t                           uint32_t
        बाह्य uint32_t ul_पत्तनम्_तालकम्_Get_Current_Owner_Id( शून्य );
        #परिभाषय तालकम्_get_caller_owner_id()    ul_पत्तनम्_तालकम्_Get_Current_Owner_Id()
        #परिभाषय तालकम्_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        संरचना तालकम्_core;
        #यदि_अपरिभाषितम् तालकम्_आन्तरिकम्_spin_unlock_with_wait
            बाह्य शून्य v_पत्तनम्_तालकम्_आन्तरिकम्_Spin_Unlock_With_Wait( संरचना तालकम्_core * px_तालकम्,
                                                             uint32_t ulSave );
            #परिभाषय तालकम्_आन्तरिकम्_spin_unlock_with_wait( तालकम्_2, save )    v_पत्तनम्_तालकम्_आन्तरिकम्_Spin_Unlock_With_Wait( तालकम्_2, save )
        #यदि_अन्तः

        #यदि_अपरिभाषितम् तालकम्_आन्तरिकम्_spin_unlock_with_notify
            बाह्य शून्य v_पत्तनम्_तालकम्_आन्तरिकम्_Spin_Unlock_With_Notify( संरचना तालकम्_core * px_तालकम्,
                                                               uint32_t save );
            #परिभाषय तालकम्_आन्तरिकम्_spin_unlock_with_notify( तालकम्_2, save )    v_पत्तनम्_तालकम्_आन्तरिकम्_Spin_Unlock_With_Notify( तालकम्_2, save );
        #यदि_अन्तः

        #यदि_अपरिभाषितम् तालकम्_आन्तरिकम्_spin_unlock_with_best_effort_wait_or_timeout
            बाह्य bool x_पत्तनम्_तालकम्_आन्तरिकम्_Spin_Unlock_With_Best_Effort_Wait_Or_Timeout( संरचना तालकम्_core * px_तालकम्,
                                                                                uint32_t ulSave,
                                                                                absolute_time_t uxUntil );
            #परिभाषय तालकम्_आन्तरिकम्_spin_unlock_with_best_effort_wait_or_timeout( तालकम्_2, save, until ) \
    x_पत्तनम्_तालकम्_आन्तरिकम्_Spin_Unlock_With_Best_Effort_Wait_Or_Timeout( तालकम्_2, save, until )
        #यदि_अन्तः
    #यदि_अन्तः /* configSUPPORT_PICO_SYNC_INTEROP */

    #यदि ( configSUPPORT_PICO_TIME_INTEROP == 1 )
        बाह्य शून्य x_पत्तनम्_Sync_आन्तरिकम्_Yield_Until_Before( absolute_time_t t );
        #परिभाषय sync_आन्तरिकम्_yield_until_before( t )    x_पत्तनम्_Sync_आन्तरिकम्_Yield_Until_Before( t )
    #यदि_अन्तः /* configSUPPORT_PICO_TIME_INTEROP */
#यदि_अन्तः /* __ASSEMBLER__ */
#यदि_अन्तः /* ifndef FREERTOS_SDK_CONFIG_H */
