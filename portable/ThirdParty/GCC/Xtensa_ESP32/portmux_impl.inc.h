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



स्थिर अन्तःस्थ bool __attribute__( ( always_inline ) )
#ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( portMUX_TYPE * mux,
                                पूर्णाङ्क timeout_cycles,
                                ध्रुव वर्ण * fnName,
                                पूर्णाङ्क पंक्ति )
    {
#अन्यथा
    PORTMUX_AQUIRE_MUX_FN_NAME( portMUX_TYPE * mux, पूर्णाङ्क timeout_cycles )
    {
        #endif


        #यदि !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            portBASE_TYPE coreID, otherCoreID;
            uint32_t ccount_start;
            bool set_timeout = timeout_cycles > portMUX_NO_TIMEOUT;
            #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                यदि( !set_timeout )
                {
                    timeout_cycles = 10000; /* Always set a timeout in debug mode */
                    set_timeout = true;
                }
            #endif

            यदि( set_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_start );
            }

            #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #यदि ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
                    यदि( ( owner != portMUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #अन्यथा
                    यदि( ( owner != portMUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #endif
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, पंक्ति );
                    mux->owner = portMUX_FREE_VAL;
                }
            #endif /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #यदि ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_SWAP ^ coreID;
            #अन्यथा
                otherCoreID = CORE_ID_REGVAL_XOR_SWAP ^ coreID;
            #endif

            कुरु
            {
                /* mux->owner should be one of portMUX_FREE_VAL, CORE_ID_PRO,
                 * CORE_ID_APP:
                 *
                 * - If portMUX_FREE_VAL, we want to atomically set to 'coreID'.
                 * - If "our" coreID, we can drop through immediately.
                 * - If "otherCoreID", we spin here.
                 */
                res = coreID;
                PORTMUX_COMPARE_SET_FN_NAME( &mux->owner, portMUX_FREE_VAL, &res );

                यदि( res != otherCoreID )
                {
                    भङ्ग; /* mux->owner is "our" coreID */
                }

                यदि( set_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    यदि( ccount_now - ccount_start > ( unsigned ) timeout_cycles )
                    {
                        #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->lastLockedFn, mux->last_Locked_पंक्ति, fnName, पंक्ति );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->गिनती );
                        #endif
                        प्रत्यागम false;
                    }
                }
            } यावत्( 1 );

            प्रतिज्ञा( res == coreID || res == portMUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            प्रतिज्ञा( ( res == portMUX_FREE_VAL ) == ( mux->गिनती == 0 ) ); /* we're first to lock iff count is zero */
            प्रतिज्ञा( mux->गिनती < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->गिनती++;


            #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                यदि( res == portMUX_FREE_VAL ) /*initial lock */
                {
                    mux->lastLockedFn = fnName;
                    mux->last_Locked_पंक्ति = पंक्ति;
                }
                अन्यथा
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->गिनती - 1,
                                mux->lastLockedFn, mux->last_Locked_पंक्ति, fnName, पंक्ति );
                }
            #endif /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #endif /* CONFIG_FREERTOS_UNICORE */
        प्रत्यागम true;
    }

#ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
        स्थिर अन्तःस्थ शून्य PORTMUX_RELEASE_MUX_FN_NAME( portMUX_TYPE * mux,
                                                        ध्रुव वर्ण * fnName,
                                                        पूर्णाङ्क पंक्ति )
        {
#अन्यथा
        स्थिर अन्तःस्थ शून्य PORTMUX_RELEASE_MUX_FN_NAME( portMUX_TYPE * mux )
        {
            #endif


            #यदि !CONFIG_FREERTOS_UNICORE
                portBASE_TYPE coreID;
                #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                    ध्रुव वर्ण * lastLockedFn = mux->lastLockedFn;
                    पूर्णाङ्क last_Locked_पंक्ति = mux->last_Locked_पंक्ति;
                    mux->lastLockedFn = fnName;
                    mux->last_Locked_पंक्ति = पंक्ति;
                    uint32_t owner = mux->owner;

                    #यदि ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
                        यदि( ( owner != portMUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #अन्यथा
                        यदि( ( owner != portMUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #endif
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #endif /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #यदि CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( NDEBUG )
                    RSR( PRID, coreID );
                #endif

                #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                    यदि( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", lastLockedFn, last_Locked_पंक्ति, fnName, पंक्ति );
                    }
                #endif

                प्रतिज्ञा( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->गिनती--;

                यदि( mux->गिनती == 0 )
                {
                    mux->owner = portMUX_FREE_VAL;
                }
                अन्यथा
                {
                    प्रतिज्ञा( mux->गिनती < 0x100 ); /* Indicates memory corruption */
                    #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->गिनती, lastLockedFn, last_Locked_पंक्ति, fnName, पंक्ति );
                    #endif
                }
            #endif //!CONFIG_FREERTOS_UNICORE
        }
