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

#که_نه_تعریف_شوی FREERTOS_SDK_CONFIG_H
#تعریف_کړه FREERTOS_SDK_CONFIG_H

#که_نه_تعریف_شوی __ASSEMBLER__
    #ضمن "FreeRTOSConfig.h"
    #ضمن "rp2040_config.h"
    #که_نه_تعریف_شوی PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #تعریف_کړه PICO_USE_MALLOC_MUTEX    1
    #د_که_پای /* PICO_USE_MALLOC_MUTEX */
    #إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #که_نه_تعریف_شوی PICO_وخت_SLEEP_OVERHEAD_ADJUST_US
            #تعریف_کړه PICO_وخت_SLEEP_OVERHEAD_ADJUST_US    150
        #د_که_پای

        #تعریف_کړه قلف_owner_id_t                           uint32_t
        خارجي uint32_t ul_پورټ_قلف_Get_Current_Owner_Id( فراغ );
        #تعریف_کړه قلف_get_caller_owner_id()    ul_پورټ_قلف_Get_Current_Owner_Id()
        #تعریف_کړه قلف_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        بنية قلف_core;
        #که_نه_تعریف_شوی قلف_دننی_spin_unlock_with_wait
            خارجي فراغ v_پورټ_قلف_دننی_Spin_Unlock_With_Wait( بنية قلف_core * px_قلف,
                                                             uint32_t ulSave );
            #تعریف_کړه قلف_دننی_spin_unlock_with_wait( قلف_2, save )    v_پورټ_قلف_دننی_Spin_Unlock_With_Wait( قلف_2, save )
        #د_که_پای

        #که_نه_تعریف_شوی قلف_دننی_spin_unlock_with_notify
            خارجي فراغ v_پورټ_قلف_دننی_Spin_Unlock_With_Notify( بنية قلف_core * px_قلف,
                                                               uint32_t save );
            #تعریف_کړه قلف_دننی_spin_unlock_with_notify( قلف_2, save )    v_پورټ_قلف_دننی_Spin_Unlock_With_Notify( قلف_2, save );
        #د_که_پای

        #که_نه_تعریف_شوی قلف_دننی_spin_unlock_with_غوره_effort_wait_or_timeout
            خارجي bool x_پورټ_قلف_دننی_Spin_Unlock_With_غوره_Effort_Wait_Or_Timeout( بنية قلف_core * px_قلف,
                                                                                uint32_t ulSave,
                                                                                absolute_وخت_t uxUntil );
            #تعریف_کړه قلف_دننی_spin_unlock_with_غوره_effort_wait_or_timeout( قلف_2, save, until ) \
    x_پورټ_قلف_دننی_Spin_Unlock_With_غوره_Effort_Wait_Or_Timeout( قلف_2, save, until )
        #د_که_پای
    #د_که_پای /* configSUPPORT_PICO_SYNC_INTEROP */

    #إذا ( config_SUPPORT_PICO_وخت_INTEROP == 1 )
        خارجي فراغ x_پورټ_Sync_دننی_Yield_Until_Before( absolute_وخت_t t );
        #تعریف_کړه sync_دننی_yield_until_before( t )    x_پورټ_Sync_دننی_Yield_Until_Before( t )
    #د_که_پای /* configSUPPORT_PICO_TIME_INTEROP */
#د_که_پای /* __ASSEMBLER__ */
#د_که_پای /* ifndef FREERTOS_SDK_CONFIG_H */
