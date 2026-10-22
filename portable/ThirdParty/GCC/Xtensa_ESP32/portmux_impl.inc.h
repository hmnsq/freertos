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



ਸਥਿਰ ਸਤਰਅੰਦਰ bool __attribute__( ( always_inline ) )
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( ਪੋਰਟ_MUX_TYPE * mux,
                                ਪੂਰਨ timeout_ਚੱਕਰਾਂ,
                                ਅਚਲ ਅੱਖਰ * fnName,
                                ਪੂਰਨ ਸਤਰ )
    {
#ਨਹੀਂਤਾਂ
    PORTMUX_AQUIRE_MUX_FN_NAME( ਪੋਰਟ_MUX_TYPE * mux, ਪੂਰਨ timeout_ਚੱਕਰਾਂ )
    {
        #ਜੇ_ਅੰਤ


        #ਜੇ !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            ਪੋਰਟ_ਅਧਾਰ_TYPE coreID, otherCoreID;
            uint32_t ccount_ਸ਼ੁਰੂ;
            bool ਸੈੱਟ_timeout = timeout_ਚੱਕਰਾਂ > ਪੋਰਟ_MUX_NO_TIMEOUT;
            #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
                ਜੇ( !ਸੈੱਟ_timeout )
                {
                    timeout_ਚੱਕਰਾਂ = 10000; /* Always set a timeout in debug mode */
                    ਸੈੱਟ_timeout = true;
                }
            #ਜੇ_ਅੰਤ

            ਜੇ( ਸੈੱਟ_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_ਸ਼ੁਰੂ );
            }

            #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ < ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )
                    ਜੇ( ( owner != ਪੋਰਟ_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #ਨਹੀਂਤਾਂ
                    ਜੇ( ( owner != ਪੋਰਟ_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #ਜੇ_ਅੰਤ
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, ਸਤਰ );
                    mux->owner = ਪੋਰਟ_MUX_FREE_VAL;
                }
            #ਜੇ_ਅੰਤ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ < ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_ਅਦਲਾ_ਬਦਲੀ ^ coreID;
            #ਨਹੀਂਤਾਂ
                otherCoreID = CORE_ID_REGVAL_XOR_ਅਦਲਾ_ਬਦਲੀ ^ coreID;
            #ਜੇ_ਅੰਤ

            ਕਰੋ
            {
                /* mux->owner should be one of portMUX_FREE_VAL, CORE_ID_PRO,
                 * CORE_ID_APP:
                 *
                 * - If portMUX_FREE_VAL, we want to atomically set to 'coreID'.
                 * - If "our" coreID, we can drop through immediately.
                 * - If "otherCoreID", we spin here.
                 */
                res = coreID;
                PORTMUX_COMPARE_ਸੈੱਟ_FN_NAME( &mux->owner, ਪੋਰਟ_MUX_FREE_VAL, &res );

                ਜੇ( res != otherCoreID )
                {
                    ਰੋਕੋ; /* mux->owner is "our" coreID */
                }

                ਜੇ( ਸੈੱਟ_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    ਜੇ( ccount_now - ccount_ਸ਼ੁਰੂ > ( ਬਿਨਾਨਿਸ਼ਾਨੀ ) timeout_ਚੱਕਰਾਂ )
                    {
                        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->ਆਖਰੀ_Locked_Fn, mux->ਆਖਰੀ_Locked_ਸਤਰ, fnName, ਸਤਰ );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->ਗਿਣਤੀ_2 );
                        #ਜੇ_ਅੰਤ
                        ਵਾਪਸ false;
                    }
                }
            } ਜਦੋਂ( 1 );

            ਪ੍ਰਤਿਜ੍ਞਾ( res == coreID || res == ਪੋਰਟ_MUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            ਪ੍ਰਤਿਜ੍ਞਾ( ( res == ਪੋਰਟ_MUX_FREE_VAL ) == ( mux->ਗਿਣਤੀ_2 == 0 ) ); /* we're first to lock iff count is zero */
            ਪ੍ਰਤਿਜ੍ਞਾ( mux->ਗਿਣਤੀ_2 < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->ਗਿਣਤੀ_2++;


            #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
                ਜੇ( res == ਪੋਰਟ_MUX_FREE_VAL ) /*initial lock */
                {
                    mux->ਆਖਰੀ_Locked_Fn = fnName;
                    mux->ਆਖਰੀ_Locked_ਸਤਰ = ਸਤਰ;
                }
                ਨਹੀਂਤਾਂ
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->ਗਿਣਤੀ_2 - 1,
                                mux->ਆਖਰੀ_Locked_Fn, mux->ਆਖਰੀ_Locked_ਸਤਰ, fnName, ਸਤਰ );
                }
            #ਜੇ_ਅੰਤ /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #ਜੇ_ਅੰਤ /* CONFIG_FREERTOS_UNICORE */
        ਵਾਪਸ true;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
        ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ PORTMUX_RELEASE_MUX_FN_NAME( ਪੋਰਟ_MUX_TYPE * mux,
                                                        ਅਚਲ ਅੱਖਰ * fnName,
                                                        ਪੂਰਨ ਸਤਰ )
        {
#ਨਹੀਂਤਾਂ
        ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ PORTMUX_RELEASE_MUX_FN_NAME( ਪੋਰਟ_MUX_TYPE * mux )
        {
            #ਜੇ_ਅੰਤ


            #ਜੇ !CONFIG_FREERTOS_UNICORE
                ਪੋਰਟ_ਅਧਾਰ_TYPE coreID;
                #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
                    ਅਚਲ ਅੱਖਰ * ਆਖਰੀ_Locked_Fn = mux->ਆਖਰੀ_Locked_Fn;
                    ਪੂਰਨ ਆਖਰੀ_Locked_ਸਤਰ = mux->ਆਖਰੀ_Locked_ਸਤਰ;
                    mux->ਆਖਰੀ_Locked_Fn = fnName;
                    mux->ਆਖਰੀ_Locked_ਸਤਰ = ਸਤਰ;
                    uint32_t owner = mux->owner;

                    #ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ < ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )
                        ਜੇ( ( owner != ਪੋਰਟ_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #ਨਹੀਂਤਾਂ
                        ਜੇ( ( owner != ਪੋਰਟ_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #ਜੇ_ਅੰਤ
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #ਜੇ_ਅੰਤ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #ਜੇ CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( NDEBUG )
                    RSR( PRID, coreID );
                #ਜੇ_ਅੰਤ

                #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
                    ਜੇ( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", ਆਖਰੀ_Locked_Fn, ਆਖਰੀ_Locked_ਸਤਰ, fnName, ਸਤਰ );
                    }
                #ਜੇ_ਅੰਤ

                ਪ੍ਰਤਿਜ੍ਞਾ( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->ਗਿਣਤੀ_2--;

                ਜੇ( mux->ਗਿਣਤੀ_2 == 0 )
                {
                    mux->owner = ਪੋਰਟ_MUX_FREE_VAL;
                }
                ਨਹੀਂਤਾਂ
                {
                    ਪ੍ਰਤਿਜ੍ਞਾ( mux->ਗਿਣਤੀ_2 < 0x100 ); /* Indicates memory corruption */
                    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->ਗਿਣਤੀ_2, ਆਖਰੀ_Locked_Fn, ਆਖਰੀ_Locked_ਸਤਰ, fnName, ਸਤਰ );
                    #ਜੇ_ਅੰਤ
                }
            #ਜੇ_ਅੰਤ //!CONFIG_FREERTOS_UNICORE
        }
