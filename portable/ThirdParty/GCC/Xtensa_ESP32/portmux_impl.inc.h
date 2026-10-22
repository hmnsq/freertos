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



अटल अंतरभूत bool __attribute__( ( always_inline ) )
#अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( portMUX_TYPE * mux,
                                पूर्णांक timeout_cycles,
                                स्थिर अक्षर * fnName,
                                पूर्णांक पंक्ति )
    {
#अन्यथा
    PORTMUX_AQUIRE_MUX_FN_NAME( portMUX_TYPE * mux, पूर्णांक timeout_cycles )
    {
        #पूर्ण_अगर


        #अगर !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            portBASE_TYPE coreID, otherCoreID;
            uint32_t ccount_start;
            bool set_timeout = timeout_cycles > portMUX_NO_TIMEOUT;
            #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
                अगर( !set_timeout )
                {
                    timeout_cycles = 10000; /* Always set a timeout in debug mode */
                    set_timeout = true;
                }
            #पूर्ण_अगर

            अगर( set_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_start );
            }

            #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #अगर ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
                    अगर( ( owner != portMUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #अन्यथा
                    अगर( ( owner != portMUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #पूर्ण_अगर
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, पंक्ति );
                    mux->owner = portMUX_FREE_VAL;
                }
            #पूर्ण_अगर /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #अगर ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_SWAP ^ coreID;
            #अन्यथा
                otherCoreID = CORE_ID_REGVAL_XOR_SWAP ^ coreID;
            #पूर्ण_अगर

            करो
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

                अगर( res != otherCoreID )
                {
                    अवरोध; /* mux->owner is "our" coreID */
                }

                अगर( set_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    अगर( ccount_now - ccount_start > ( अचिन्हित ) timeout_cycles )
                    {
                        #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->lastLockedFn, mux->last_Locked_पंक्ति, fnName, पंक्ति );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->गिनती );
                        #पूर्ण_अगर
                        वापस false;
                    }
                }
            } जबतक( 1 );

            निश्चित( res == coreID || res == portMUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            निश्चित( ( res == portMUX_FREE_VAL ) == ( mux->गिनती == 0 ) ); /* we're first to lock iff count is zero */
            निश्चित( mux->गिनती < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->गिनती++;


            #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
                अगर( res == portMUX_FREE_VAL ) /*initial lock */
                {
                    mux->lastLockedFn = fnName;
                    mux->last_Locked_पंक्ति = पंक्ति;
                }
                अन्यथा
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->गिनती - 1,
                                mux->lastLockedFn, mux->last_Locked_पंक्ति, fnName, पंक्ति );
                }
            #पूर्ण_अगर /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #पूर्ण_अगर /* CONFIG_FREERTOS_UNICORE */
        वापस true;
    }

#अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
        अटल अंतरभूत व्योम PORTMUX_RELEASE_MUX_FN_NAME( portMUX_TYPE * mux,
                                                        स्थिर अक्षर * fnName,
                                                        पूर्णांक पंक्ति )
        {
#अन्यथा
        अटल अंतरभूत व्योम PORTMUX_RELEASE_MUX_FN_NAME( portMUX_TYPE * mux )
        {
            #पूर्ण_अगर


            #अगर !CONFIG_FREERTOS_UNICORE
                portBASE_TYPE coreID;
                #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
                    स्थिर अक्षर * lastLockedFn = mux->lastLockedFn;
                    पूर्णांक last_Locked_पंक्ति = mux->last_Locked_पंक्ति;
                    mux->lastLockedFn = fnName;
                    mux->last_Locked_पंक्ति = पंक्ति;
                    uint32_t owner = mux->owner;

                    #अगर ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
                        अगर( ( owner != portMUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #अन्यथा
                        अगर( ( owner != portMUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #पूर्ण_अगर
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #पूर्ण_अगर /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #अगर CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( न_संशोधन )
                    RSR( PRID, coreID );
                #पूर्ण_अगर

                #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
                    अगर( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", lastLockedFn, last_Locked_पंक्ति, fnName, पंक्ति );
                    }
                #पूर्ण_अगर

                निश्चित( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->गिनती--;

                अगर( mux->गिनती == 0 )
                {
                    mux->owner = portMUX_FREE_VAL;
                }
                अन्यथा
                {
                    निश्चित( mux->गिनती < 0x100 ); /* Indicates memory corruption */
                    #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->गिनती, lastLockedFn, last_Locked_पंक्ति, fnName, पंक्ति );
                    #पूर्ण_अगर
                }
            #पूर्ण_अगर //!CONFIG_FREERTOS_UNICORE
        }
