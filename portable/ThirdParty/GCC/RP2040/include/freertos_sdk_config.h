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

#اگر_غیر_تعریف_شدہ FREERTOS_SDK_CONFIG_H
#تعریف_کرو FREERTOS_SDK_CONFIG_H

#اگر_غیر_تعریف_شدہ __ASSEMBLER__
    #شامل "FreeRTOSConfig.h"
    #شامل "rp2040_config.h"
    #اگر_غیر_تعریف_شدہ PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #تعریف_کرو PICO_USE_MALLOC_MUTEX    1
    #اگر_ختم /* PICO_USE_MALLOC_MUTEX */
    #اگر ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #اگر_غیر_تعریف_شدہ PICO_وقت_SLEEP_OVERHEAD_ADJUST_US
            #تعریف_کرو PICO_وقت_SLEEP_OVERHEAD_ADJUST_US    150
        #اگر_ختم

        #تعریف_کرو تالا_owner_id_t                           uint32_t
        خارجی uint32_t ul_پورٹ_تالا_Get_Current_Owner_Id( خالی );
        #تعریف_کرو تالا_get_caller_owner_id()    ul_پورٹ_تالا_Get_Current_Owner_Id()
        #تعریف_کرو تالا_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        ساخت تالا_core;
        #اگر_غیر_تعریف_شدہ تالا_اندرونی_spin_unlock_with_wait
            خارجی خالی v_پورٹ_تالا_اندرونی_Spin_Unlock_With_Wait( ساخت تالا_core * px_تالا,
                                                             uint32_t ulSave );
            #تعریف_کرو تالا_اندرونی_spin_unlock_with_wait( تالا_3, save )    v_پورٹ_تالا_اندرونی_Spin_Unlock_With_Wait( تالا_3, save )
        #اگر_ختم

        #اگر_غیر_تعریف_شدہ تالا_اندرونی_spin_unlock_with_notify
            خارجی خالی v_پورٹ_تالا_اندرونی_Spin_Unlock_With_Notify( ساخت تالا_core * px_تالا,
                                                               uint32_t save );
            #تعریف_کرو تالا_اندرونی_spin_unlock_with_notify( تالا_3, save )    v_پورٹ_تالا_اندرونی_Spin_Unlock_With_Notify( تالا_3, save );
        #اگر_ختم

        #اگر_غیر_تعریف_شدہ تالا_اندرونی_spin_unlock_with_بہترین_effort_wait_or_timeout
            خارجی bool x_پورٹ_تالا_اندرونی_Spin_Unlock_With_بہترین_Effort_Wait_Or_Timeout( ساخت تالا_core * px_تالا,
                                                                                uint32_t ulSave,
                                                                                absolute_وقت_t uxUntil );
            #تعریف_کرو تالا_اندرونی_spin_unlock_with_بہترین_effort_wait_or_timeout( تالا_3, save, until ) \
    x_پورٹ_تالا_اندرونی_Spin_Unlock_With_بہترین_Effort_Wait_Or_Timeout( تالا_3, save, until )
        #اگر_ختم
    #اگر_ختم /* configSUPPORT_PICO_SYNC_INTEROP */

    #اگر ( config_SUPPORT_PICO_وقت_INTEROP == 1 )
        خارجی خالی x_پورٹ_Sync_اندرونی_Yield_Until_Before( absolute_وقت_t t );
        #تعریف_کرو sync_اندرونی_yield_until_before( t )    x_پورٹ_Sync_اندرونی_Yield_Until_Before( t )
    #اگر_ختم /* configSUPPORT_PICO_TIME_INTEROP */
#اگر_ختم /* __ASSEMBLER__ */
#اگر_ختم /* ifndef FREERTOS_SDK_CONFIG_H */
