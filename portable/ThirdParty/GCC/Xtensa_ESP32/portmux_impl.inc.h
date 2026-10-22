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
#که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( پورټ_MUX_TYPE * mux,
                                صحيح timeout_دورې,
                                ثابت حرف * fnName,
                                صحيح کرښه )
    {
#وإلا
    PORTMUX_AQUIRE_MUX_FN_NAME( پورټ_MUX_TYPE * mux, صحيح timeout_دورې )
    {
        #د_که_پای


        #إذا !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            پورټ_بنسټ_TYPE coreID, otherCoreID;
            uint32_t ccount_پیل;
            bool سېټ_timeout = timeout_دورې > پورټ_MUX_NO_TIMEOUT;
            #که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
                إذا( !سېټ_timeout )
                {
                    timeout_دورې = 10000; /* Always set a timeout in debug mode */
                    سېټ_timeout = true;
                }
            #د_که_پای

            إذا( سېټ_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_پیل );
            }

            #که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
                    إذا( ( owner != پورټ_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #وإلا
                    إذا( ( owner != پورټ_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #د_که_پای
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, کرښه );
                    mux->owner = پورټ_MUX_FREE_VAL;
                }
            #د_که_پای /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_بدلون ^ coreID;
            #وإلا
                otherCoreID = CORE_ID_REGVAL_XOR_بدلون ^ coreID;
            #د_که_پای

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
                PORTMUX_COMPARE_سېټ_FN_NAME( &mux->owner, پورټ_MUX_FREE_VAL, &res );

                إذا( res != otherCoreID )
                {
                    اكسر; /* mux->owner is "our" coreID */
                }

                إذا( سېټ_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    إذا( ccount_now - ccount_پیل > ( بینښه ) timeout_دورې )
                    {
                        #که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->وروستی_Locked_Fn, mux->وروستی_Locked_کرښه, fnName, کرښه );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->شمېر );
                        #د_که_پای
                        أرجع false;
                    }
                }
            } طالما( 1 );

            أكد( res == coreID || res == پورټ_MUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            أكد( ( res == پورټ_MUX_FREE_VAL ) == ( mux->شمېر == 0 ) ); /* we're first to lock iff count is zero */
            أكد( mux->شمېر < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->شمېر++;


            #که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
                إذا( res == پورټ_MUX_FREE_VAL ) /*initial lock */
                {
                    mux->وروستی_Locked_Fn = fnName;
                    mux->وروستی_Locked_کرښه = کرښه;
                }
                وإلا
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->شمېر - 1,
                                mux->وروستی_Locked_Fn, mux->وروستی_Locked_کرښه, fnName, کرښه );
                }
            #د_که_پای /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #د_که_پای /* CONFIG_FREERTOS_UNICORE */
        أرجع true;
    }

#که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
        ساكن مضمن فراغ PORTMUX_RELEASE_MUX_FN_NAME( پورټ_MUX_TYPE * mux,
                                                        ثابت حرف * fnName,
                                                        صحيح کرښه )
        {
#وإلا
        ساكن مضمن فراغ PORTMUX_RELEASE_MUX_FN_NAME( پورټ_MUX_TYPE * mux )
        {
            #د_که_پای


            #إذا !CONFIG_FREERTOS_UNICORE
                پورټ_بنسټ_TYPE coreID;
                #که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
                    ثابت حرف * وروستی_Locked_Fn = mux->وروستی_Locked_Fn;
                    صحيح وروستی_Locked_کرښه = mux->وروستی_Locked_کرښه;
                    mux->وروستی_Locked_Fn = fnName;
                    mux->وروستی_Locked_کرښه = کرښه;
                    uint32_t owner = mux->owner;

                    #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
                        إذا( ( owner != پورټ_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #وإلا
                        إذا( ( owner != پورټ_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #د_که_پای
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #د_که_پای /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #إذا CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( NDEBUG )
                    RSR( PRID, coreID );
                #د_که_پای

                #که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
                    إذا( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", وروستی_Locked_Fn, وروستی_Locked_کرښه, fnName, کرښه );
                    }
                #د_که_پای

                أكد( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->شمېر--;

                إذا( mux->شمېر == 0 )
                {
                    mux->owner = پورټ_MUX_FREE_VAL;
                }
                وإلا
                {
                    أكد( mux->شمېر < 0x100 ); /* Indicates memory corruption */
                    #که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->شمېر, وروستی_Locked_Fn, وروستی_Locked_کرښه, fnName, کرښه );
                    #د_که_پای
                }
            #د_که_پای //!CONFIG_FREERTOS_UNICORE
        }
