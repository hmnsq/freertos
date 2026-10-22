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

#अगर_अघोषित FREERTOS_SDK_CONFIG_H
#घोषणा FREERTOS_SDK_CONFIG_H

#अगर_अघोषित __ASSEMBLER__
    #समावेश "FreeRTOSConfig.h"
    #समावेश "rp2040_config.h"
    #अगर_अघोषित PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #घोषणा PICO_USE_MALLOC_MUTEX    1
    #पूर्ण_अगर /* PICO_USE_MALLOC_MUTEX */
    #अगर ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #अगर_अघोषित PICO_TIME_SLEEP_OVERHEAD_ADJUST_US
            #घोषणा PICO_TIME_SLEEP_OVERHEAD_ADJUST_US    150
        #पूर्ण_अगर

        #घोषणा lock_owner_id_t                           uint32_t
        बाह्य uint32_t ulPortLockGetCurrentOwnerId( व्योम );
        #घोषणा lock_get_caller_owner_id()    ulPortLockGetCurrentOwnerId()
        #घोषणा LOCK_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        काष्ठा lock_core;
        #अगर_अघोषित lock_internal_spin_unlock_with_wait
            बाह्य व्योम vPortLockInternalSpinUnlockWithWait( काष्ठा lock_core * pxLock,
                                                             uint32_t ulSave );
            #घोषणा lock_internal_spin_unlock_with_wait( lock, save )    vPortLockInternalSpinUnlockWithWait( lock, save )
        #पूर्ण_अगर

        #अगर_अघोषित lock_internal_spin_unlock_with_notify
            बाह्य व्योम vPortLockInternalSpinUnlockWithNotify( काष्ठा lock_core * pxLock,
                                                               uint32_t save );
            #घोषणा lock_internal_spin_unlock_with_notify( lock, save )    vPortLockInternalSpinUnlockWithNotify( lock, save );
        #पूर्ण_अगर

        #अगर_अघोषित lock_internal_spin_unlock_with_best_effort_wait_or_timeout
            बाह्य bool xPortLockInternalSpinUnlockWithBestEffortWaitOrTimeout( काष्ठा lock_core * pxLock,
                                                                                uint32_t ulSave,
                                                                                absolute_time_t uxUntil );
            #घोषणा lock_internal_spin_unlock_with_best_effort_wait_or_timeout( lock, save, until ) \
    xPortLockInternalSpinUnlockWithBestEffortWaitOrTimeout( lock, save, until )
        #पूर्ण_अगर
    #पूर्ण_अगर /* configSUPPORT_PICO_SYNC_INTEROP */

    #अगर ( configSUPPORT_PICO_TIME_INTEROP == 1 )
        बाह्य व्योम xPortSyncInternalYieldUntilBefore( absolute_time_t t );
        #घोषणा sync_internal_yield_until_before( t )    xPortSyncInternalYieldUntilBefore( t )
    #पूर्ण_अगर /* configSUPPORT_PICO_TIME_INTEROP */
#पूर्ण_अगर /* __ASSEMBLER__ */
#पूर्ण_अगर /* ifndef FREERTOS_SDK_CONFIG_H */
