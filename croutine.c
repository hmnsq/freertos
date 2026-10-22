/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
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
 *
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "croutine.h"

/* Remove the whole file if co-routines are not being used. */
#ਜੇ ( configUSE_CO_ROUTINES != 0 )

/*
 * Some kernel aware debuggers require data to be viewed to be global, rather
 * than file scope.
 */
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_REMOVE_STATIC_QUALIFIER
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STATIC
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STATIC    ਸਥਿਰ
    #ਜੇ_ਅੰਤ


/* Lists for ready and blocked co-routines. --------------------*/
    STATIC List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ]; /**< Prioritised ready co-routines. */
    STATIC List_t xDelayedCoRoutineList1;                                   /**< Delayed co-routines. */
    STATIC List_t xDelayedCoRoutineList2;                                   /**< Delayed co-routines (two lists are used - one for delays that have overflowed the current tick count. */
    STATIC List_t * pxDelayedCoRoutineList = ਨਿਰਾ;                          /**< Points to the delayed co-routine list currently being used. */
    STATIC List_t * px_ਉਛਾਲ_Delayed_Co_Routine_List = ਨਿਰਾ;                  /**< Points to the delayed co-routine list currently being used to hold co-routines that have overflowed the current tick count. */
    STATIC List_t xPendingReadyCoRoutineList;                               /**< Holds co-routines that have been readied by an external event.  They cannot be added directly to the ready lists as the ready lists cannot be accessed by interrupts. */

/* Other file private variables. --------------------------------*/
    CRCB_t * pxCurrentCoRoutine = ਨਿਰਾ;
    STATIC UBaseType_t ux_ਸਿਖਰ_Co_Routine_Ready_ਤਰਜੀਹ = ( UBaseType_t ) 0U;
    STATIC TickType_t x_Co_Routine_Tick_ਗਿਣਤੀ = ( TickType_t ) 0U;
    STATIC TickType_t x_ਆਖਰੀ_Tick_ਗਿਣਤੀ = ( TickType_t ) 0U;
    STATIC TickType_t xPassedTicks = ( TickType_t ) 0U;

/* The initial state of the co-routine when it is created. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ corINITIAL_STATE    ( 0 )

/*
 * Place the co-routine represented by pxCRCB into the appropriate ready queue
 * for the priority.  It is inserted at the end of the list.
 *
 * This macro accesses the co-routine ready lists and therefore must not be
 * used from within an ISR.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ prv_ਜੋੜੋ_Co_Routine_ਮੰਜ਼ਿਲ_Ready_ਕਤਾਰ( pxCRCB )                                                                               \
    ਕਰੋ {                                                                                                                        \
        ਜੇ( ( pxCRCB )->ux_ਤਰਜੀਹ > ux_ਸਿਖਰ_Co_Routine_Ready_ਤਰਜੀਹ )                                                              \
        {                                                                                                                       \
            ux_ਸਿਖਰ_Co_Routine_Ready_ਤਰਜੀਹ = ( pxCRCB )->ux_ਤਰਜੀਹ;                                                               \
        }                                                                                                                       \
        v_List_ਪਾਓ_ਸਿਰਾ( ( List_t * ) &( pxReadyCoRoutineLists[ ( pxCRCB )->ux_ਤਰਜੀਹ ] ), &( ( pxCRCB )->x_Generic_List_ਵਸਤੂ ) ); \
    } ਜਦੋਂ( 0 )

/*
 * Utility to ready all the lists used by the scheduler.  This is called
 * automatically upon the creation of the first co-routine.
 */
    STATIC ਖਾਲੀ prvInitialiseCoRoutineLists( ਖਾਲੀ );

/*
 * Co-routines that are readied by an interrupt cannot be placed directly into
 * the ready lists (there is no mutual exclusion).  Instead they are placed in
 * in the pending ready list in order that they can later be moved to the ready
 * list by the co-routine scheduler.
 */
    STATIC ਖਾਲੀ prvCheckPendingReadyList( ਖਾਲੀ );

/*
 * Macro that looks at the list of co-routines that are currently delayed to
 * see if any require waking.
 *
 * Co-routines are stored in the queue in the order of their wake time -
 * meaning once one co-routine has been found whose timer has not expired
 * we need not look any further down the list.
 */
    STATIC ਖਾਲੀ prvCheckDelayedList( ਖਾਲੀ );

/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t xCoRoutineCreate( cr_COROUTINE_ਕੋਡ px_Co_Routine_ਕੋਡ,
                                 UBaseType_t ux_ਤਰਜੀਹ,
                                 UBaseType_t ux_ਸੂਚਕਾਂਕ )
    {
        ਅਧਾਰ_Type_t xReturn;
        CRCB_t * pxCoRoutine;

        traceENTER_xCoRoutineCreate( px_Co_Routine_ਕੋਡ, ux_ਤਰਜੀਹ, ux_ਸੂਚਕਾਂਕ );

        /* Allocate the memory that will store the co-routine control block. */
        /* MISRA Ref 11.5.1 [Malloc memory assignment] */
        /* More details at: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/MISRA.md#rule-115 */
        /* coverity[misra_c_2012_rule_11_5_violation] */
        pxCoRoutine = ( CRCB_t * ) pv_ਪੋਰਟ_Malloc( ਆਕਾਰ( CRCB_t ) );

        ਜੇ( pxCoRoutine )
        {
            /* If pxCurrentCoRoutine is NULL then this is the first co-routine to
            * be created and the co-routine data structures need initialising. */
            ਜੇ( pxCurrentCoRoutine == ਨਿਰਾ )
            {
                pxCurrentCoRoutine = pxCoRoutine;
                prvInitialiseCoRoutineLists();
            }

            /* Check the priority is within limits. */
            ਜੇ( ux_ਤਰਜੀਹ >= configMAX_CO_ROUTINE_PRIORITIES )
            {
                ux_ਤਰਜੀਹ = configMAX_CO_ROUTINE_PRIORITIES - 1;
            }

            /* Fill out the co-routine control block from the function parameters. */
            pxCoRoutine->uxState = corINITIAL_STATE;
            pxCoRoutine->ux_ਤਰਜੀਹ = ux_ਤਰਜੀਹ;
            pxCoRoutine->ux_ਸੂਚਕਾਂਕ = ux_ਸੂਚਕਾਂਕ;
            pxCoRoutine->pxCoRoutineFunction = px_Co_Routine_ਕੋਡ;

            /* Initialise all the other co-routine control block parameters. */
            v_List_Initialise_ਵਸਤੂ( &( pxCoRoutine->x_Generic_List_ਵਸਤੂ ) );
            v_List_Initialise_ਵਸਤੂ( &( pxCoRoutine->x_Event_List_ਵਸਤੂ ) );

            /* Set the co-routine control block as a link back from the ListItem_t.
             * This is so we can get back to the containing CRCB from a generic item
             * in a list. */
            list_ਸੈੱਟ_LIST_ਵਸਤੂ_OWNER( &( pxCoRoutine->x_Generic_List_ਵਸਤੂ ), pxCoRoutine );
            list_ਸੈੱਟ_LIST_ਵਸਤੂ_OWNER( &( pxCoRoutine->x_Event_List_ਵਸਤੂ ), pxCoRoutine );

            /* Event lists are always in priority order. */
            list_ਸੈੱਟ_LIST_ਵਸਤੂ_ਮੁੱਲ( &( pxCoRoutine->x_Event_List_ਵਸਤੂ ), ( ( TickType_t ) configMAX_CO_ROUTINE_PRIORITIES - ( TickType_t ) ux_ਤਰਜੀਹ ) );

            /* Now the co-routine has been initialised it can be added to the ready
             * list at the correct priority. */
            prv_ਜੋੜੋ_Co_Routine_ਮੰਜ਼ਿਲ_Ready_ਕਤਾਰ( pxCoRoutine );

            xReturn = pdPASS;
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = err_COULD_NOT_ALLOCATE_REQUIRED_ਸਮ੍ਰਿਤੀ;
        }

        traceRETURN_xCoRoutineCreate( xReturn );

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    ਖਾਲੀ v_Co_Routine_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Delayed_List( TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay,
                                     List_t * pxEventList )
    {
        TickType_t x_ਸਮਾਂ_ਮੰਜ਼ਿਲ_Wake;

        trace_ENTER_v_Co_Routine_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Delayed_List( x_Ticks_ਮੰਜ਼ਿਲ_Delay, pxEventList );

        /* Calculate the time to wake - this may overflow but this is
         * not a problem. */
        x_ਸਮਾਂ_ਮੰਜ਼ਿਲ_Wake = x_Co_Routine_Tick_ਗਿਣਤੀ + x_Ticks_ਮੰਜ਼ਿਲ_Delay;

        /* We must remove ourselves from the ready list before adding
         * ourselves to the blocked list as the same list item is used for
         * both lists. */
        ( ਖਾਲੀ ) uxListRemove( ( List_ਵਸਤੂ_t * ) &( pxCurrentCoRoutine->x_Generic_List_ਵਸਤੂ ) );

        /* The list item will be inserted in wake time order. */
        list_ਸੈੱਟ_LIST_ਵਸਤੂ_ਮੁੱਲ( &( pxCurrentCoRoutine->x_Generic_List_ਵਸਤੂ ), x_ਸਮਾਂ_ਮੰਜ਼ਿਲ_Wake );

        ਜੇ( x_ਸਮਾਂ_ਮੰਜ਼ਿਲ_Wake < x_Co_Routine_Tick_ਗਿਣਤੀ )
        {
            /* Wake time has overflowed.  Place this item in the
             * overflow list. */
            v_List_ਪਾਓ( ( List_t * ) px_ਉਛਾਲ_Delayed_Co_Routine_List, ( List_ਵਸਤੂ_t * ) &( pxCurrentCoRoutine->x_Generic_List_ਵਸਤੂ ) );
        }
        ਨਹੀਂਤਾਂ
        {
            /* The wake time has not overflowed, so we can use the
             * current block list. */
            v_List_ਪਾਓ( ( List_t * ) pxDelayedCoRoutineList, ( List_ਵਸਤੂ_t * ) &( pxCurrentCoRoutine->x_Generic_List_ਵਸਤੂ ) );
        }

        ਜੇ( pxEventList )
        {
            /* Also add the co-routine to an event list.  If this is done then the
             * function must be called with interrupts disabled. */
            v_List_ਪਾਓ( pxEventList, &( pxCurrentCoRoutine->x_Event_List_ਵਸਤੂ ) );
        }

        trace_RETURN_v_Co_Routine_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Delayed_List();
    }
/*-----------------------------------------------------------*/

    STATIC ਖਾਲੀ prvCheckPendingReadyList( ਖਾਲੀ )
    {
        /* Are there any co-routines waiting to get moved to the ready list?  These
         * are co-routines that have been readied by an ISR.  The ISR cannot access
         * the ready lists itself. */
        ਜਦੋਂ( list_LIST_IS_ਖਾਲੀ_ਥਾਵਾਂ( &xPendingReadyCoRoutineList ) == pdFALSE )
        {
            CRCB_t * pxUnblockedCRCB;

            /* The pending ready list can be accessed by an ISR. */
            ਪੋਰਟ_DISABLE_INTERRUPTS();
            {
                pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_ਦਾ_ਸਿਰ_ਇੰਦਰਾਜ( ( &xPendingReadyCoRoutineList ) );
                ( ਖਾਲੀ ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_ਵਸਤੂ ) );
            }
            ਪੋਰਟ_ENABLE_INTERRUPTS();

            ( ਖਾਲੀ ) uxListRemove( &( pxUnblockedCRCB->x_Generic_List_ਵਸਤੂ ) );
            prv_ਜੋੜੋ_Co_Routine_ਮੰਜ਼ਿਲ_Ready_ਕਤਾਰ( pxUnblockedCRCB );
        }
    }
/*-----------------------------------------------------------*/

    STATIC ਖਾਲੀ prvCheckDelayedList( ਖਾਲੀ )
    {
        CRCB_t * pxCRCB;

        xPassedTicks = x_Task_Get_Tick_ਗਿਣਤੀ() - x_ਆਖਰੀ_Tick_ਗਿਣਤੀ;

        ਜਦੋਂ( xPassedTicks )
        {
            x_Co_Routine_Tick_ਗਿਣਤੀ++;
            xPassedTicks--;

            /* If the tick count has overflowed we need to swap the ready lists. */
            ਜੇ( x_Co_Routine_Tick_ਗਿਣਤੀ == 0 )
            {
                List_t * px_ਆਰਜ਼ੀ;

                /* Tick count has overflowed so we need to swap the delay lists.  If there are
                 * any items in pxDelayedCoRoutineList here then there is an error! */
                px_ਆਰਜ਼ੀ = pxDelayedCoRoutineList;
                pxDelayedCoRoutineList = px_ਉਛਾਲ_Delayed_Co_Routine_List;
                px_ਉਛਾਲ_Delayed_Co_Routine_List = px_ਆਰਜ਼ੀ;
            }

            /* See if this tick has made a timeout expire. */
            ਜਦੋਂ( list_LIST_IS_ਖਾਲੀ_ਥਾਵਾਂ( pxDelayedCoRoutineList ) == pdFALSE )
            {
                pxCRCB = ( CRCB_t * ) list_GET_OWNER_ਦਾ_ਸਿਰ_ਇੰਦਰਾਜ( pxDelayedCoRoutineList );

                ਜੇ( x_Co_Routine_Tick_ਗਿਣਤੀ < list_GET_LIST_ਵਸਤੂ_ਮੁੱਲ( &( pxCRCB->x_Generic_List_ਵਸਤੂ ) ) )
                {
                    /* Timeout not yet expired. */
                    ਰੋਕੋ;
                }

                ਪੋਰਟ_DISABLE_INTERRUPTS();
                {
                    /* The event could have occurred just before this critical
                     *  section.  If this is the case then the generic list item will
                     *  have been moved to the pending ready list and the following
                     *  line is still valid.  Also the pvContainer parameter will have
                     *  been set to NULL so the following lines are also valid. */
                    ( ਖਾਲੀ ) uxListRemove( &( pxCRCB->x_Generic_List_ਵਸਤੂ ) );

                    /* Is the co-routine waiting on an event also? */
                    ਜੇ( pxCRCB->x_Event_List_ਵਸਤੂ.pxContainer )
                    {
                        ( ਖਾਲੀ ) uxListRemove( &( pxCRCB->x_Event_List_ਵਸਤੂ ) );
                    }
                }
                ਪੋਰਟ_ENABLE_INTERRUPTS();

                prv_ਜੋੜੋ_Co_Routine_ਮੰਜ਼ਿਲ_Ready_ਕਤਾਰ( pxCRCB );
            }
        }

        x_ਆਖਰੀ_Tick_ਗਿਣਤੀ = x_Co_Routine_Tick_ਗਿਣਤੀ;
    }
/*-----------------------------------------------------------*/

    ਖਾਲੀ v_Co_Routine_ਸਮਾਂ_ਸਾਰਣੀ( ਖਾਲੀ )
    {
        trace_ENTER_v_Co_Routine_ਸਮਾਂ_ਸਾਰਣੀ();

        /* Only run a co-routine after prvInitialiseCoRoutineLists() has been
         * called.  prvInitialiseCoRoutineLists() is called automatically when a
         * co-routine is created. */
        ਜੇ( pxDelayedCoRoutineList != ਨਿਰਾ )
        {
            /* See if any co-routines readied by events need moving to the ready lists. */
            prvCheckPendingReadyList();

            /* See if any delayed co-routines have timed out. */
            prvCheckDelayedList();

            /* Find the highest priority queue that contains ready co-routines. */
            ਜਦੋਂ( list_LIST_IS_ਖਾਲੀ_ਥਾਵਾਂ( &( pxReadyCoRoutineLists[ ux_ਸਿਖਰ_Co_Routine_Ready_ਤਰਜੀਹ ] ) ) )
            {
                ਜੇ( ux_ਸਿਖਰ_Co_Routine_Ready_ਤਰਜੀਹ == 0 )
                {
                    /* No more co-routines to check. */
                    ਵਾਪਸ;
                }

                --ux_ਸਿਖਰ_Co_Routine_Ready_ਤਰਜੀਹ;
            }

            /* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
             * of the same priority get an equal share of the processor time. */
            list_GET_OWNER_ਦਾ_ਅਗਲਾ_ਇੰਦਰਾਜ( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ ux_ਸਿਖਰ_Co_Routine_Ready_ਤਰਜੀਹ ] ) );

            /* Call the co-routine. */
            ( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->ux_ਸੂਚਕਾਂਕ );
        }

        trace_RETURN_v_Co_Routine_ਸਮਾਂ_ਸਾਰਣੀ();
    }
/*-----------------------------------------------------------*/

    STATIC ਖਾਲੀ prvInitialiseCoRoutineLists( ਖਾਲੀ )
    {
        UBaseType_t ux_ਤਰਜੀਹ;

        ਲਈ( ux_ਤਰਜੀਹ = 0; ux_ਤਰਜੀਹ < configMAX_CO_ROUTINE_PRIORITIES; ux_ਤਰਜੀਹ++ )
        {
            vListInitialise( ( List_t * ) &( pxReadyCoRoutineLists[ ux_ਤਰਜੀਹ ] ) );
        }

        vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
        vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
        vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );

        /* Start with pxDelayedCoRoutineList using list1 and the
         * pxOverflowDelayedCoRoutineList using list2. */
        pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
        px_ਉਛਾਲ_Delayed_Co_Routine_List = &xDelayedCoRoutineList2;
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t xCoRoutineRemoveFromEventList( ਅਚਲ List_t * pxEventList )
    {
        CRCB_t * pxUnblockedCRCB;
        ਅਧਾਰ_Type_t xReturn;

        traceENTER_xCoRoutineRemoveFromEventList( pxEventList );

        /* This function is called from within an interrupt.  It can only access
         * event lists and the pending ready list.  This function assumes that a
         * check has already been made to ensure pxEventList is not empty. */
        pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_ਦਾ_ਸਿਰ_ਇੰਦਰਾਜ( pxEventList );
        ( ਖਾਲੀ ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_ਵਸਤੂ ) );
        v_List_ਪਾਓ_ਸਿਰਾ( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->x_Event_List_ਵਸਤੂ ) );

        ਜੇ( pxUnblockedCRCB->ux_ਤਰਜੀਹ >= pxCurrentCoRoutine->ux_ਤਰਜੀਹ )
        {
            xReturn = pdTRUE;
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = pdFALSE;
        }

        traceRETURN_xCoRoutineRemoveFromEventList( xReturn );

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

/*
 * Reset state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
    ਖਾਲੀ vCoRoutineResetState( ਖਾਲੀ )
    {
        /* Lists for ready and blocked co-routines. */
        pxDelayedCoRoutineList = ਨਿਰਾ;
        px_ਉਛਾਲ_Delayed_Co_Routine_List = ਨਿਰਾ;

        /* Other file private variables. */
        pxCurrentCoRoutine = ਨਿਰਾ;
        ux_ਸਿਖਰ_Co_Routine_Ready_ਤਰਜੀਹ = ( UBaseType_t ) 0U;
        x_Co_Routine_Tick_ਗਿਣਤੀ = ( TickType_t ) 0U;
        x_ਆਖਰੀ_Tick_ਗਿਣਤੀ = ( TickType_t ) 0U;
        xPassedTicks = ( TickType_t ) 0U;
    }
/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* configUSE_CO_ROUTINES != 0 */
