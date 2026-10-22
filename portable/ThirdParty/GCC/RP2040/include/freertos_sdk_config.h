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

#جيڪڏهن_وصف_نه_ٿيل FREERTOS_SDK_CONFIG_H
#وصف_ڪريو FREERTOS_SDK_CONFIG_H

#جيڪڏهن_وصف_نه_ٿيل __ASSEMBLER__
    #ضمن "FreeRTOSConfig.h"
    #ضمن "rp2040_config.h"
    #جيڪڏهن_وصف_نه_ٿيل PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #وصف_ڪريو PICO_USE_MALLOC_MUTEX    1
    #جيڪڏهن_پورو /* PICO_USE_MALLOC_MUTEX */
    #إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #جيڪڏهن_وصف_نه_ٿيل PICO_وقت_SLEEP_OVERHEAD_ADJUST_US
            #وصف_ڪريو PICO_وقت_SLEEP_OVERHEAD_ADJUST_US    150
        #جيڪڏهن_پورو

        #وصف_ڪريو تالو_owner_id_t                           uint32_t
        خارجي uint32_t ul_پورٽ_تالو_Get_Current_Owner_Id( فراغ );
        #وصف_ڪريو تالو_get_caller_owner_id()    ul_پورٽ_تالو_Get_Current_Owner_Id()
        #وصف_ڪريو تالو_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        بنية تالو_core;
        #جيڪڏهن_وصف_نه_ٿيل تالو_اندروني_spin_unlock_with_wait
            خارجي فراغ v_پورٽ_تالو_اندروني_Spin_Unlock_With_Wait( بنية تالو_core * px_تالو,
                                                             uint32_t ulSave );
            #وصف_ڪريو تالو_اندروني_spin_unlock_with_wait( تالو_2, save )    v_پورٽ_تالو_اندروني_Spin_Unlock_With_Wait( تالو_2, save )
        #جيڪڏهن_پورو

        #جيڪڏهن_وصف_نه_ٿيل تالو_اندروني_spin_unlock_with_notify
            خارجي فراغ v_پورٽ_تالو_اندروني_Spin_Unlock_With_Notify( بنية تالو_core * px_تالو,
                                                               uint32_t save );
            #وصف_ڪريو تالو_اندروني_spin_unlock_with_notify( تالو_2, save )    v_پورٽ_تالو_اندروني_Spin_Unlock_With_Notify( تالو_2, save );
        #جيڪڏهن_پورو

        #جيڪڏهن_وصف_نه_ٿيل تالو_اندروني_spin_unlock_with_بهترين_effort_wait_or_timeout
            خارجي bool x_پورٽ_تالو_اندروني_Spin_Unlock_With_بهترين_Effort_Wait_Or_Timeout( بنية تالو_core * px_تالو,
                                                                                uint32_t ulSave,
                                                                                absolute_وقت_t uxUntil );
            #وصف_ڪريو تالو_اندروني_spin_unlock_with_بهترين_effort_wait_or_timeout( تالو_2, save, until ) \
    x_پورٽ_تالو_اندروني_Spin_Unlock_With_بهترين_Effort_Wait_Or_Timeout( تالو_2, save, until )
        #جيڪڏهن_پورو
    #جيڪڏهن_پورو /* configSUPPORT_PICO_SYNC_INTEROP */

    #إذا ( config_SUPPORT_PICO_وقت_INTEROP == 1 )
        خارجي فراغ x_پورٽ_Sync_اندروني_Yield_Until_Before( absolute_وقت_t t );
        #وصف_ڪريو sync_اندروني_yield_until_before( t )    x_پورٽ_Sync_اندروني_Yield_Until_Before( t )
    #جيڪڏهن_پورو /* configSUPPORT_PICO_TIME_INTEROP */
#جيڪڏهن_پورو /* __ASSEMBLER__ */
#جيڪڏهن_پورو /* ifndef FREERTOS_SDK_CONFIG_H */
