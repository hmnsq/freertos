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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ FREERTOS_SDK_CONFIG_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FREERTOS_SDK_CONFIG_H

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ASSEMBLER__
    #ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOSConfig.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "rp2040_config.h"
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PICO_USE_MALLOC_MUTEX    1
    #ਜੇ_ਅੰਤ /* PICO_USE_MALLOC_MUTEX */
    #ਜੇ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PICO_ਸਮਾਂ_SLEEP_OVERHEAD_ADJUST_US
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PICO_ਸਮਾਂ_SLEEP_OVERHEAD_ADJUST_US    150
        #ਜੇ_ਅੰਤ

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਤਾਲਾ_owner_id_t                           uint32_t
        ਬਾਹਰੀ uint32_t ul_ਪੋਰਟ_ਤਾਲਾ_Get_Current_Owner_Id( ਖਾਲੀ );
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਤਾਲਾ_get_caller_owner_id()    ul_ਪੋਰਟ_ਤਾਲਾ_Get_Current_Owner_Id()
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਤਾਲਾ_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        ਬਣਤਰ ਤਾਲਾ_core;
        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਤਾਲਾ_ਅੰਦਰੂਨੀ_spin_unlock_with_wait
            ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਤਾਲਾ_ਅੰਦਰੂਨੀ_Spin_Unlock_With_Wait( ਬਣਤਰ ਤਾਲਾ_core * px_ਤਾਲਾ,
                                                             uint32_t ulSave );
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਤਾਲਾ_ਅੰਦਰੂਨੀ_spin_unlock_with_wait( ਤਾਲਾ_2, save )    v_ਪੋਰਟ_ਤਾਲਾ_ਅੰਦਰੂਨੀ_Spin_Unlock_With_Wait( ਤਾਲਾ_2, save )
        #ਜੇ_ਅੰਤ

        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਤਾਲਾ_ਅੰਦਰੂਨੀ_spin_unlock_with_notify
            ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਤਾਲਾ_ਅੰਦਰੂਨੀ_Spin_Unlock_With_Notify( ਬਣਤਰ ਤਾਲਾ_core * px_ਤਾਲਾ,
                                                               uint32_t save );
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਤਾਲਾ_ਅੰਦਰੂਨੀ_spin_unlock_with_notify( ਤਾਲਾ_2, save )    v_ਪੋਰਟ_ਤਾਲਾ_ਅੰਦਰੂਨੀ_Spin_Unlock_With_Notify( ਤਾਲਾ_2, save );
        #ਜੇ_ਅੰਤ

        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਤਾਲਾ_ਅੰਦਰੂਨੀ_spin_unlock_with_ਉੱਤਮ_effort_wait_or_timeout
            ਬਾਹਰੀ bool x_ਪੋਰਟ_ਤਾਲਾ_ਅੰਦਰੂਨੀ_Spin_Unlock_With_ਉੱਤਮ_Effort_Wait_Or_Timeout( ਬਣਤਰ ਤਾਲਾ_core * px_ਤਾਲਾ,
                                                                                uint32_t ulSave,
                                                                                absolute_ਸਮਾਂ_t uxUntil );
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਤਾਲਾ_ਅੰਦਰੂਨੀ_spin_unlock_with_ਉੱਤਮ_effort_wait_or_timeout( ਤਾਲਾ_2, save, until ) \
    x_ਪੋਰਟ_ਤਾਲਾ_ਅੰਦਰੂਨੀ_Spin_Unlock_With_ਉੱਤਮ_Effort_Wait_Or_Timeout( ਤਾਲਾ_2, save, until )
        #ਜੇ_ਅੰਤ
    #ਜੇ_ਅੰਤ /* configSUPPORT_PICO_SYNC_INTEROP */

    #ਜੇ ( config_SUPPORT_PICO_ਸਮਾਂ_INTEROP == 1 )
        ਬਾਹਰੀ ਖਾਲੀ x_ਪੋਰਟ_Sync_ਅੰਦਰੂਨੀ_Yield_Until_Before( absolute_ਸਮਾਂ_t t );
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sync_ਅੰਦਰੂਨੀ_yield_until_before( t )    x_ਪੋਰਟ_Sync_ਅੰਦਰੂਨੀ_Yield_Until_Before( t )
    #ਜੇ_ਅੰਤ /* configSUPPORT_PICO_TIME_INTEROP */
#ਜੇ_ਅੰਤ /* __ASSEMBLER__ */
#ਜੇ_ਅੰਤ /* ifndef FREERTOS_SDK_CONFIG_H */
