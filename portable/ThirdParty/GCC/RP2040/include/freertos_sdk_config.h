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

#جے_بنا_تعریف FREERTOS_SDK_CONFIG_H
#تعریف_کرو FREERTOS_SDK_CONFIG_H

#جے_بنا_تعریف __ASSEMBLER__
    #ضمن "FreeRTOSConfig.h"
    #ضمن "rp2040_config.h"
    #جے_بنا_تعریف PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #تعریف_کرو PICO_USE_MALLOC_MUTEX    1
    #جے_انت /* PICO_USE_MALLOC_MUTEX */
    #إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #جے_بنا_تعریف PICO_ویلا_SLEEP_OVERHEAD_ADJUST_US
            #تعریف_کرو PICO_ویلا_SLEEP_OVERHEAD_ADJUST_US    150
        #جے_انت

        #تعریف_کرو جندرا_owner_id_t                           uint32_t
        خارجي uint32_t ul_پورٹ_جندرا_Get_Current_Owner_Id( فراغ );
        #تعریف_کرو جندرا_get_caller_owner_id()    ul_پورٹ_جندرا_Get_Current_Owner_Id()
        #تعریف_کرو جندرا_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        بنية جندرا_core;
        #جے_بنا_تعریف جندرا_اندرونی_spin_unlock_with_wait
            خارجي فراغ v_پورٹ_جندرا_اندرونی_Spin_Unlock_With_Wait( بنية جندرا_core * px_جندرا,
                                                             uint32_t ulSave );
            #تعریف_کرو جندرا_اندرونی_spin_unlock_with_wait( جندرا_2, save )    v_پورٹ_جندرا_اندرونی_Spin_Unlock_With_Wait( جندرا_2, save )
        #جے_انت

        #جے_بنا_تعریف جندرا_اندرونی_spin_unlock_with_notify
            خارجي فراغ v_پورٹ_جندرا_اندرونی_Spin_Unlock_With_Notify( بنية جندرا_core * px_جندرا,
                                                               uint32_t save );
            #تعریف_کرو جندرا_اندرونی_spin_unlock_with_notify( جندرا_2, save )    v_پورٹ_جندرا_اندرونی_Spin_Unlock_With_Notify( جندرا_2, save );
        #جے_انت

        #جے_بنا_تعریف جندرا_اندرونی_spin_unlock_with_بہترین_effort_wait_or_timeout
            خارجي bool x_پورٹ_جندرا_اندرونی_Spin_Unlock_With_بہترین_Effort_Wait_Or_Timeout( بنية جندرا_core * px_جندرا,
                                                                                uint32_t ulSave,
                                                                                absolute_ویلا_t uxUntil );
            #تعریف_کرو جندرا_اندرونی_spin_unlock_with_بہترین_effort_wait_or_timeout( جندرا_2, save, until ) \
    x_پورٹ_جندرا_اندرونی_Spin_Unlock_With_بہترین_Effort_Wait_Or_Timeout( جندرا_2, save, until )
        #جے_انت
    #جے_انت /* configSUPPORT_PICO_SYNC_INTEROP */

    #إذا ( config_SUPPORT_PICO_ویلا_INTEROP == 1 )
        خارجي فراغ x_پورٹ_Sync_اندرونی_Yield_Until_Before( absolute_ویلا_t t );
        #تعریف_کرو sync_اندرونی_yield_until_before( t )    x_پورٹ_Sync_اندرونی_Yield_Until_Before( t )
    #جے_انت /* configSUPPORT_PICO_TIME_INTEROP */
#جے_انت /* __ASSEMBLER__ */
#جے_انت /* ifndef FREERTOS_SDK_CONFIG_H */
