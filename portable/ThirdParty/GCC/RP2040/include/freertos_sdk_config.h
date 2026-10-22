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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ FREERTOS_SDK_CONFIG_H
#ವ್ಯಾಖ್ಯಾನಿಸು FREERTOS_SDK_CONFIG_H

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __ASSEMBLER__
    #ಅನ್ತರ್ಭಾವ "FreeRTOSConfig.h"
    #ಅನ್ತರ್ಭಾವ "rp2040_config.h"
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #ವ್ಯಾಖ್ಯಾನಿಸು PICO_USE_MALLOC_MUTEX    1
    #ಆದರೆ_ಅಂತ್ಯ /* PICO_USE_MALLOC_MUTEX */
    #ಆದರೆ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PICO_ಸಮಯ_SLEEP_OVERHEAD_ADJUST_US
            #ವ್ಯಾಖ್ಯಾನಿಸು PICO_ಸಮಯ_SLEEP_OVERHEAD_ADJUST_US    150
        #ಆದರೆ_ಅಂತ್ಯ

        #ವ್ಯಾಖ್ಯಾನಿಸು ಬೀಗ_owner_id_t                           uint32_t
        ಬಾಹ್ಯ uint32_t ul_ಪೋರ್ಟ್_ಬೀಗ_Get_Current_Owner_Id( ಶೂನ್ಯ );
        #ವ್ಯಾಖ್ಯಾನಿಸು ಬೀಗ_get_caller_owner_id()    ul_ಪೋರ್ಟ್_ಬೀಗ_Get_Current_Owner_Id()
        #ವ್ಯಾಖ್ಯಾನಿಸು ಬೀಗ_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        ರಚನೆ ಬೀಗ_core;
        #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಬೀಗ_ಆಂತರಿಕ_spin_unlock_with_wait
            ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಬೀಗ_ಆಂತರಿಕ_Spin_Unlock_With_Wait( ರಚನೆ ಬೀಗ_core * px_ಬೀಗ,
                                                             uint32_t ulSave );
            #ವ್ಯಾಖ್ಯಾನಿಸು ಬೀಗ_ಆಂತರಿಕ_spin_unlock_with_wait( ಬೀಗ_3, save )    v_ಪೋರ್ಟ್_ಬೀಗ_ಆಂತರಿಕ_Spin_Unlock_With_Wait( ಬೀಗ_3, save )
        #ಆದರೆ_ಅಂತ್ಯ

        #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಬೀಗ_ಆಂತರಿಕ_spin_unlock_with_notify
            ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಬೀಗ_ಆಂತರಿಕ_Spin_Unlock_With_Notify( ರಚನೆ ಬೀಗ_core * px_ಬೀಗ,
                                                               uint32_t save );
            #ವ್ಯಾಖ್ಯಾನಿಸು ಬೀಗ_ಆಂತರಿಕ_spin_unlock_with_notify( ಬೀಗ_3, save )    v_ಪೋರ್ಟ್_ಬೀಗ_ಆಂತರಿಕ_Spin_Unlock_With_Notify( ಬೀಗ_3, save );
        #ಆದರೆ_ಅಂತ್ಯ

        #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಬೀಗ_ಆಂತರಿಕ_spin_unlock_with_ಉತ್ತಮ_effort_wait_or_timeout
            ಬಾಹ್ಯ bool x_ಪೋರ್ಟ್_ಬೀಗ_ಆಂತರಿಕ_Spin_Unlock_With_ಉತ್ತಮ_Effort_Wait_Or_Timeout( ರಚನೆ ಬೀಗ_core * px_ಬೀಗ,
                                                                                uint32_t ulSave,
                                                                                absolute_ಸಮಯ_t uxUntil );
            #ವ್ಯಾಖ್ಯಾನಿಸು ಬೀಗ_ಆಂತರಿಕ_spin_unlock_with_ಉತ್ತಮ_effort_wait_or_timeout( ಬೀಗ_3, save, until ) \
    x_ಪೋರ್ಟ್_ಬೀಗ_ಆಂತರಿಕ_Spin_Unlock_With_ಉತ್ತಮ_Effort_Wait_Or_Timeout( ಬೀಗ_3, save, until )
        #ಆದರೆ_ಅಂತ್ಯ
    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_PICO_SYNC_INTEROP */

    #ಆದರೆ ( config_SUPPORT_PICO_ಸಮಯ_INTEROP == 1 )
        ಬಾಹ್ಯ ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sync_ಆಂತರಿಕ_Yield_Until_Before( absolute_ಸಮಯ_t t );
        #ವ್ಯಾಖ್ಯಾನಿಸು sync_ಆಂತರಿಕ_yield_until_before( t )    x_ಪೋರ್ಟ್_Sync_ಆಂತರಿಕ_Yield_Until_Before( t )
    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_PICO_TIME_INTEROP */
#ಆದರೆ_ಅಂತ್ಯ /* __ASSEMBLER__ */
#ಆದರೆ_ಅಂತ್ಯ /* ifndef FREERTOS_SDK_CONFIG_H */
