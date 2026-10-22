/*
 * SPDX-FileCopyrightText: 2017-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */


/*
 * Warning: funky preprocessor hackery ahead. Including these headers will generate two
 * functions, which names are defined by the preprocessor macros
 * PORTMUX_AQUIRE_MUX_FN_NAME and PORTMUX_RELEASE_MUX_FN_NAME. In order to do the compare
 * and exchange function, they will use whatever PORTMUX_COMPARE_SET_FN_NAME resolves to.
 *
 * In some scenarios, this header is included *twice* in portmux_impl.h: one time
 * for the 'normal' mux code which uses a compare&exchange routine, another time
 * to generate code for a second set of these routines that use a second mux
 * (in internal ram) to fake a compare&exchange on a variable in external memory.
 */



ساكن مضمن bool __attribute__( ( always_inline ) )
#جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( پورٽ_MUX_TYPE * mux,
                                صحيح timeout_چڪرن,
                                ثابت حرف * fnName,
                                صحيح سٽ )
    {
#وإلا
    PORTMUX_AQUIRE_MUX_FN_NAME( پورٽ_MUX_TYPE * mux, صحيح timeout_چڪرن )
    {
        #جيڪڏهن_پورو


        #إذا !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            پورٽ_بنياد_TYPE coreID, otherCoreID;
            uint32_t ccount_شروعات;
            bool سيٽ_timeout = timeout_چڪرن > پورٽ_MUX_NO_TIMEOUT;
            #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
                إذا( !سيٽ_timeout )
                {
                    timeout_چڪرن = 10000; /* Always set a timeout in debug mode */
                    سيٽ_timeout = true;
                }
            #جيڪڏهن_پورو

            إذا( سيٽ_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_شروعات );
            }

            #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #إذا ( ESP_IDF_نسخو < ESP_IDF_نسخو_VAL( 4, 2, 0 ) )
                    إذا( ( owner != پورٽ_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #وإلا
                    إذا( ( owner != پورٽ_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #جيڪڏهن_پورو
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, سٽ );
                    mux->owner = پورٽ_MUX_FREE_VAL;
                }
            #جيڪڏهن_پورو /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #إذا ( ESP_IDF_نسخو < ESP_IDF_نسخو_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_مٽا_سٽا ^ coreID;
            #وإلا
                otherCoreID = CORE_ID_REGVAL_XOR_مٽا_سٽا ^ coreID;
            #جيڪڏهن_پورو

            افعل
            {
                /* mux->owner should be one of portMUX_FREE_VAL, CORE_ID_PRO,
                 * CORE_ID_APP:
                 *
                 * - If portMUX_FREE_VAL, we want to atomically set to 'coreID'.
                 * - If "our" coreID, we can drop through immediately.
                 * - If "otherCoreID", we spin here.
                 */
                res = coreID;
                PORTMUX_COMPARE_سيٽ_FN_NAME( &mux->owner, پورٽ_MUX_FREE_VAL, &res );

                إذا( res != otherCoreID )
                {
                    اكسر; /* mux->owner is "our" coreID */
                }

                إذا( سيٽ_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    إذا( ccount_now - ccount_شروعات > ( بنانشان ) timeout_چڪرن )
                    {
                        #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->آخري_Locked_Fn, mux->آخري_Locked_سٽ, fnName, سٽ );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->ڳڻپ );
                        #جيڪڏهن_پورو
                        أرجع false;
                    }
                }
            } طالما( 1 );

            أكد( res == coreID || res == پورٽ_MUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            أكد( ( res == پورٽ_MUX_FREE_VAL ) == ( mux->ڳڻپ == 0 ) ); /* we're first to lock iff count is zero */
            أكد( mux->ڳڻپ < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->ڳڻپ++;


            #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
                إذا( res == پورٽ_MUX_FREE_VAL ) /*initial lock */
                {
                    mux->آخري_Locked_Fn = fnName;
                    mux->آخري_Locked_سٽ = سٽ;
                }
                وإلا
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->ڳڻپ - 1,
                                mux->آخري_Locked_Fn, mux->آخري_Locked_سٽ, fnName, سٽ );
                }
            #جيڪڏهن_پورو /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #جيڪڏهن_پورو /* CONFIG_FREERTOS_UNICORE */
        أرجع true;
    }

#جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
        ساكن مضمن فراغ PORTMUX_RELEASE_MUX_FN_NAME( پورٽ_MUX_TYPE * mux,
                                                        ثابت حرف * fnName,
                                                        صحيح سٽ )
        {
#وإلا
        ساكن مضمن فراغ PORTMUX_RELEASE_MUX_FN_NAME( پورٽ_MUX_TYPE * mux )
        {
            #جيڪڏهن_پورو


            #إذا !CONFIG_FREERTOS_UNICORE
                پورٽ_بنياد_TYPE coreID;
                #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
                    ثابت حرف * آخري_Locked_Fn = mux->آخري_Locked_Fn;
                    صحيح آخري_Locked_سٽ = mux->آخري_Locked_سٽ;
                    mux->آخري_Locked_Fn = fnName;
                    mux->آخري_Locked_سٽ = سٽ;
                    uint32_t owner = mux->owner;

                    #إذا ( ESP_IDF_نسخو < ESP_IDF_نسخو_VAL( 4, 2, 0 ) )
                        إذا( ( owner != پورٽ_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #وإلا
                        إذا( ( owner != پورٽ_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #جيڪڏهن_پورو
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #جيڪڏهن_پورو /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #إذا CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( NDEBUG )
                    RSR( PRID, coreID );
                #جيڪڏهن_پورو

                #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
                    إذا( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", آخري_Locked_Fn, آخري_Locked_سٽ, fnName, سٽ );
                    }
                #جيڪڏهن_پورو

                أكد( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->ڳڻپ--;

                إذا( mux->ڳڻپ == 0 )
                {
                    mux->owner = پورٽ_MUX_FREE_VAL;
                }
                وإلا
                {
                    أكد( mux->ڳڻپ < 0x100 ); /* Indicates memory corruption */
                    #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->ڳڻپ, آخري_Locked_Fn, آخري_Locked_سٽ, fnName, سٽ );
                    #جيڪڏهن_پورو
                }
            #جيڪڏهن_پورو //!CONFIG_FREERTOS_UNICORE
        }
