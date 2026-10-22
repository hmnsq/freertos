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

#اگر_تعریف_نشده FREERTOS_SDK_CONFIG_H
#تعریف_کن FREERTOS_SDK_CONFIG_H

#اگر_تعریف_نشده __ASSEMBLER__
    #ضمن "FreeRTOSConfig.h"
    #ضمن "rp2040_config.h"
    #اگر_تعریف_نشده PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #تعریف_کن PICO_USE_MALLOC_MUTEX    1
    #پایان_اگر /* PICO_USE_MALLOC_MUTEX */
    #إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #اگر_تعریف_نشده PICO_زمان_SLEEP_OVERHEAD_ADJUST_US
            #تعریف_کن PICO_زمان_SLEEP_OVERHEAD_ADJUST_US    150
        #پایان_اگر

        #تعریف_کن قفل_owner_id_t                           uint32_t
        خارجي uint32_t ul_پورت_قفل_Get_Current_Owner_Id( فراغ );
        #تعریف_کن قفل_get_caller_owner_id()    ul_پورت_قفل_Get_Current_Owner_Id()
        #تعریف_کن قفل_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        بنية قفل_core;
        #اگر_تعریف_نشده قفل_داخلی_spin_unlock_with_wait
            خارجي فراغ v_پورت_قفل_داخلی_Spin_Unlock_With_Wait( بنية قفل_core * px_قفل,
                                                             uint32_t ulSave );
            #تعریف_کن قفل_داخلی_spin_unlock_with_wait( قفل_3, save )    v_پورت_قفل_داخلی_Spin_Unlock_With_Wait( قفل_3, save )
        #پایان_اگر

        #اگر_تعریف_نشده قفل_داخلی_spin_unlock_with_notify
            خارجي فراغ v_پورت_قفل_داخلی_Spin_Unlock_With_Notify( بنية قفل_core * px_قفل,
                                                               uint32_t save );
            #تعریف_کن قفل_داخلی_spin_unlock_with_notify( قفل_3, save )    v_پورت_قفل_داخلی_Spin_Unlock_With_Notify( قفل_3, save );
        #پایان_اگر

        #اگر_تعریف_نشده قفل_داخلی_spin_unlock_with_بهترین_effort_wait_or_timeout
            خارجي bool x_پورت_قفل_داخلی_Spin_Unlock_With_بهترین_Effort_Wait_Or_Timeout( بنية قفل_core * px_قفل,
                                                                                uint32_t ulSave,
                                                                                absolute_زمان_t uxUntil );
            #تعریف_کن قفل_داخلی_spin_unlock_with_بهترین_effort_wait_or_timeout( قفل_3, save, until ) \
    x_پورت_قفل_داخلی_Spin_Unlock_With_بهترین_Effort_Wait_Or_Timeout( قفل_3, save, until )
        #پایان_اگر
    #پایان_اگر /* configSUPPORT_PICO_SYNC_INTEROP */

    #إذا ( config_SUPPORT_PICO_زمان_INTEROP == 1 )
        خارجي فراغ x_پورت_Sync_داخلی_Yield_Until_Before( absolute_زمان_t t );
        #تعریف_کن sync_داخلی_yield_until_before( t )    x_پورت_Sync_داخلی_Yield_Until_Before( t )
    #پایان_اگر /* configSUPPORT_PICO_TIME_INTEROP */
#پایان_اگر /* __ASSEMBLER__ */
#پایان_اگر /* ifndef FREERTOS_SDK_CONFIG_H */
