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

#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "croutine.h"

/* Remove the whole file if co-routines are not being used. */
#إذا ( configUSE_CO_ROUTINES != 0 )

/*
 * Some kernel aware debuggers require data to be viewed to be global, rather
 * than file scope.
 */
    #جيڪڏهن_وصف_ٿيل پورٽ_REMOVE_STATIC_QUALIFIER
        #وصف_ڪريو STATIC
    #وإلا
        #وصف_ڪريو STATIC    ساكن
    #جيڪڏهن_پورو


/* Lists for ready and blocked co-routines. --------------------*/
    STATIC List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ]; /**< Prioritised ready co-routines. */
    STATIC List_t xDelayedCoRoutineList1;                                   /**< Delayed co-routines. */
    STATIC List_t xDelayedCoRoutineList2;                                   /**< Delayed co-routines (two lists are used - one for delays that have overflowed the current tick count. */
    STATIC List_t * pxDelayedCoRoutineList = عدم;                          /**< Points to the delayed co-routine list currently being used. */
    STATIC List_t * px_حد_کان_مٿي_Delayed_Co_Routine_List = عدم;                  /**< Points to the delayed co-routine list currently being used to hold co-routines that have overflowed the current tick count. */
    STATIC List_t xPendingReadyCoRoutineList;                               /**< Holds co-routines that have been readied by an external event.  They cannot be added directly to the ready lists as the ready lists cannot be accessed by interrupts. */

/* Other file private variables. --------------------------------*/
    CRCB_t * pxCurrentCoRoutine = عدم;
    STATIC UBaseType_t ux_چوٽي_Co_Routine_Ready_ترجيح = ( UBaseType_t ) 0U;
    STATIC TickType_t x_Co_Routine_Tick_ڳڻپ = ( TickType_t ) 0U;
    STATIC TickType_t x_آخري_Tick_ڳڻپ = ( TickType_t ) 0U;
    STATIC TickType_t xPassedTicks = ( TickType_t ) 0U;

/* The initial state of the co-routine when it is created. */
    #وصف_ڪريو corINITIAL_STATE    ( 0 )

/*
 * Place the co-routine represented by pxCRCB into the appropriate ready queue
 * for the priority.  It is inserted at the end of the list.
 *
 * This macro accesses the co-routine ready lists and therefore must not be
 * used from within an ISR.
 */
    #وصف_ڪريو prv_جوڙيو_Co_Routine_منزل_Ready_قطار( pxCRCB )                                                                               \
    افعل {                                                                                                                        \
        إذا( ( pxCRCB )->ux_ترجيح > ux_چوٽي_Co_Routine_Ready_ترجيح )                                                              \
        {                                                                                                                       \
            ux_چوٽي_Co_Routine_Ready_ترجيح = ( pxCRCB )->ux_ترجيح;                                                               \
        }                                                                                                                       \
        v_List_وجهو_پڇاڙي( ( List_t * ) &( pxReadyCoRoutineLists[ ( pxCRCB )->ux_ترجيح ] ), &( ( pxCRCB )->x_Generic_List_شي ) ); \
    } طالما( 0 )

/*
 * Utility to ready all the lists used by the scheduler.  This is called
 * automatically upon the creation of the first co-routine.
 */
    STATIC فراغ prvInitialiseCoRoutineLists( فراغ );

/*
 * Co-routines that are readied by an interrupt cannot be placed directly into
 * the ready lists (there is no mutual exclusion).  Instead they are placed in
 * in the pending ready list in order that they can later be moved to the ready
 * list by the co-routine scheduler.
 */
    STATIC فراغ prvCheckPendingReadyList( فراغ );

/*
 * Macro that looks at the list of co-routines that are currently delayed to
 * see if any require waking.
 *
 * Co-routines are stored in the queue in the order of their wake time -
 * meaning once one co-routine has been found whose timer has not expired
 * we need not look any further down the list.
 */
    STATIC فراغ prvCheckDelayedList( فراغ );

/*-----------------------------------------------------------*/

    بنياد_Type_t xCoRoutineCreate( cr_COROUTINE_ڪوڊ px_Co_Routine_ڪوڊ,
                                 UBaseType_t ux_ترجيح,
                                 UBaseType_t ux_اشاريو )
    {
        بنياد_Type_t xReturn;
        CRCB_t * pxCoRoutine;

        traceENTER_xCoRoutineCreate( px_Co_Routine_ڪوڊ, ux_ترجيح, ux_اشاريو );

        /* Allocate the memory that will store the co-routine control block. */
        /* MISRA Ref 11.5.1 [Malloc memory assignment] */
        /* More details at: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/MISRA.md#rule-115 */
        /* coverity[misra_c_2012_rule_11_5_violation] */
        pxCoRoutine = ( CRCB_t * ) pv_پورٽ_Malloc( حجم( CRCB_t ) );

        إذا( pxCoRoutine )
        {
            /* If pxCurrentCoRoutine is NULL then this is the first co-routine to
            * be created and the co-routine data structures need initialising. */
            إذا( pxCurrentCoRoutine == عدم )
            {
                pxCurrentCoRoutine = pxCoRoutine;
                prvInitialiseCoRoutineLists();
            }

            /* Check the priority is within limits. */
            إذا( ux_ترجيح >= configMAX_CO_ROUTINE_PRIORITIES )
            {
                ux_ترجيح = configMAX_CO_ROUTINE_PRIORITIES - 1;
            }

            /* Fill out the co-routine control block from the function parameters. */
            pxCoRoutine->uxState = corINITIAL_STATE;
            pxCoRoutine->ux_ترجيح = ux_ترجيح;
            pxCoRoutine->ux_اشاريو = ux_اشاريو;
            pxCoRoutine->pxCoRoutineFunction = px_Co_Routine_ڪوڊ;

            /* Initialise all the other co-routine control block parameters. */
            v_List_Initialise_شي( &( pxCoRoutine->x_Generic_List_شي ) );
            v_List_Initialise_شي( &( pxCoRoutine->x_Event_List_شي ) );

            /* Set the co-routine control block as a link back from the ListItem_t.
             * This is so we can get back to the containing CRCB from a generic item
             * in a list. */
            list_سيٽ_LIST_شي_OWNER( &( pxCoRoutine->x_Generic_List_شي ), pxCoRoutine );
            list_سيٽ_LIST_شي_OWNER( &( pxCoRoutine->x_Event_List_شي ), pxCoRoutine );

            /* Event lists are always in priority order. */
            list_سيٽ_LIST_شي_قدر( &( pxCoRoutine->x_Event_List_شي ), ( ( TickType_t ) configMAX_CO_ROUTINE_PRIORITIES - ( TickType_t ) ux_ترجيح ) );

            /* Now the co-routine has been initialised it can be added to the ready
             * list at the correct priority. */
            prv_جوڙيو_Co_Routine_منزل_Ready_قطار( pxCoRoutine );

            xReturn = pdPASS;
        }
        وإلا
        {
            xReturn = err_COULD_NOT_ALLOCATE_REQUIRED_يادگيري;
        }

        traceRETURN_xCoRoutineCreate( xReturn );

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    فراغ v_Co_Routine_جوڙيو_منزل_Delayed_List( TickType_t x_Ticks_منزل_Delay,
                                     List_t * pxEventList )
    {
        TickType_t x_وقت_منزل_Wake;

        trace_ENTER_v_Co_Routine_جوڙيو_منزل_Delayed_List( x_Ticks_منزل_Delay, pxEventList );

        /* Calculate the time to wake - this may overflow but this is
         * not a problem. */
        x_وقت_منزل_Wake = x_Co_Routine_Tick_ڳڻپ + x_Ticks_منزل_Delay;

        /* We must remove ourselves from the ready list before adding
         * ourselves to the blocked list as the same list item is used for
         * both lists. */
        ( فراغ ) uxListRemove( ( List_شي_t * ) &( pxCurrentCoRoutine->x_Generic_List_شي ) );

        /* The list item will be inserted in wake time order. */
        list_سيٽ_LIST_شي_قدر( &( pxCurrentCoRoutine->x_Generic_List_شي ), x_وقت_منزل_Wake );

        إذا( x_وقت_منزل_Wake < x_Co_Routine_Tick_ڳڻپ )
        {
            /* Wake time has overflowed.  Place this item in the
             * overflow list. */
            v_List_وجهو( ( List_t * ) px_حد_کان_مٿي_Delayed_Co_Routine_List, ( List_شي_t * ) &( pxCurrentCoRoutine->x_Generic_List_شي ) );
        }
        وإلا
        {
            /* The wake time has not overflowed, so we can use the
             * current block list. */
            v_List_وجهو( ( List_t * ) pxDelayedCoRoutineList, ( List_شي_t * ) &( pxCurrentCoRoutine->x_Generic_List_شي ) );
        }

        إذا( pxEventList )
        {
            /* Also add the co-routine to an event list.  If this is done then the
             * function must be called with interrupts disabled. */
            v_List_وجهو( pxEventList, &( pxCurrentCoRoutine->x_Event_List_شي ) );
        }

        trace_RETURN_v_Co_Routine_جوڙيو_منزل_Delayed_List();
    }
/*-----------------------------------------------------------*/

    STATIC فراغ prvCheckPendingReadyList( فراغ )
    {
        /* Are there any co-routines waiting to get moved to the ready list?  These
         * are co-routines that have been readied by an ISR.  The ISR cannot access
         * the ready lists itself. */
        طالما( list_LIST_IS_خالي_جايون( &xPendingReadyCoRoutineList ) == pdFALSE )
        {
            CRCB_t * pxUnblockedCRCB;

            /* The pending ready list can be accessed by an ISR. */
            پورٽ_DISABLE_INTERRUPTS();
            {
                pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_جو_سر_داخلا( ( &xPendingReadyCoRoutineList ) );
                ( فراغ ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_شي ) );
            }
            پورٽ_ENABLE_INTERRUPTS();

            ( فراغ ) uxListRemove( &( pxUnblockedCRCB->x_Generic_List_شي ) );
            prv_جوڙيو_Co_Routine_منزل_Ready_قطار( pxUnblockedCRCB );
        }
    }
/*-----------------------------------------------------------*/

    STATIC فراغ prvCheckDelayedList( فراغ )
    {
        CRCB_t * pxCRCB;

        xPassedTicks = x_Task_Get_Tick_ڳڻپ() - x_آخري_Tick_ڳڻپ;

        طالما( xPassedTicks )
        {
            x_Co_Routine_Tick_ڳڻپ++;
            xPassedTicks--;

            /* If the tick count has overflowed we need to swap the ready lists. */
            إذا( x_Co_Routine_Tick_ڳڻپ == 0 )
            {
                List_t * px_عارضي;

                /* Tick count has overflowed so we need to swap the delay lists.  If there are
                 * any items in pxDelayedCoRoutineList here then there is an error! */
                px_عارضي = pxDelayedCoRoutineList;
                pxDelayedCoRoutineList = px_حد_کان_مٿي_Delayed_Co_Routine_List;
                px_حد_کان_مٿي_Delayed_Co_Routine_List = px_عارضي;
            }

            /* See if this tick has made a timeout expire. */
            طالما( list_LIST_IS_خالي_جايون( pxDelayedCoRoutineList ) == pdFALSE )
            {
                pxCRCB = ( CRCB_t * ) list_GET_OWNER_جو_سر_داخلا( pxDelayedCoRoutineList );

                إذا( x_Co_Routine_Tick_ڳڻپ < list_GET_LIST_شي_قدر( &( pxCRCB->x_Generic_List_شي ) ) )
                {
                    /* Timeout not yet expired. */
                    اكسر;
                }

                پورٽ_DISABLE_INTERRUPTS();
                {
                    /* The event could have occurred just before this critical
                     *  section.  If this is the case then the generic list item will
                     *  have been moved to the pending ready list and the following
                     *  line is still valid.  Also the pvContainer parameter will have
                     *  been set to NULL so the following lines are also valid. */
                    ( فراغ ) uxListRemove( &( pxCRCB->x_Generic_List_شي ) );

                    /* Is the co-routine waiting on an event also? */
                    إذا( pxCRCB->x_Event_List_شي.pxContainer )
                    {
                        ( فراغ ) uxListRemove( &( pxCRCB->x_Event_List_شي ) );
                    }
                }
                پورٽ_ENABLE_INTERRUPTS();

                prv_جوڙيو_Co_Routine_منزل_Ready_قطار( pxCRCB );
            }
        }

        x_آخري_Tick_ڳڻپ = x_Co_Routine_Tick_ڳڻپ;
    }
/*-----------------------------------------------------------*/

    فراغ v_Co_Routine_وقت_جدول( فراغ )
    {
        trace_ENTER_v_Co_Routine_وقت_جدول();

        /* Only run a co-routine after prvInitialiseCoRoutineLists() has been
         * called.  prvInitialiseCoRoutineLists() is called automatically when a
         * co-routine is created. */
        إذا( pxDelayedCoRoutineList != عدم )
        {
            /* See if any co-routines readied by events need moving to the ready lists. */
            prvCheckPendingReadyList();

            /* See if any delayed co-routines have timed out. */
            prvCheckDelayedList();

            /* Find the highest priority queue that contains ready co-routines. */
            طالما( list_LIST_IS_خالي_جايون( &( pxReadyCoRoutineLists[ ux_چوٽي_Co_Routine_Ready_ترجيح ] ) ) )
            {
                إذا( ux_چوٽي_Co_Routine_Ready_ترجيح == 0 )
                {
                    /* No more co-routines to check. */
                    أرجع;
                }

                --ux_چوٽي_Co_Routine_Ready_ترجيح;
            }

            /* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
             * of the same priority get an equal share of the processor time. */
            list_GET_OWNER_جو_ايندڙ_داخلا( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ ux_چوٽي_Co_Routine_Ready_ترجيح ] ) );

            /* Call the co-routine. */
            ( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->ux_اشاريو );
        }

        trace_RETURN_v_Co_Routine_وقت_جدول();
    }
/*-----------------------------------------------------------*/

    STATIC فراغ prvInitialiseCoRoutineLists( فراغ )
    {
        UBaseType_t ux_ترجيح;

        لكل( ux_ترجيح = 0; ux_ترجيح < configMAX_CO_ROUTINE_PRIORITIES; ux_ترجيح++ )
        {
            vListInitialise( ( List_t * ) &( pxReadyCoRoutineLists[ ux_ترجيح ] ) );
        }

        vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
        vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
        vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );

        /* Start with pxDelayedCoRoutineList using list1 and the
         * pxOverflowDelayedCoRoutineList using list2. */
        pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
        px_حد_کان_مٿي_Delayed_Co_Routine_List = &xDelayedCoRoutineList2;
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t xCoRoutineRemoveFromEventList( ثابت List_t * pxEventList )
    {
        CRCB_t * pxUnblockedCRCB;
        بنياد_Type_t xReturn;

        traceENTER_xCoRoutineRemoveFromEventList( pxEventList );

        /* This function is called from within an interrupt.  It can only access
         * event lists and the pending ready list.  This function assumes that a
         * check has already been made to ensure pxEventList is not empty. */
        pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_جو_سر_داخلا( pxEventList );
        ( فراغ ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_شي ) );
        v_List_وجهو_پڇاڙي( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->x_Event_List_شي ) );

        إذا( pxUnblockedCRCB->ux_ترجيح >= pxCurrentCoRoutine->ux_ترجيح )
        {
            xReturn = pdTRUE;
        }
        وإلا
        {
            xReturn = pdFALSE;
        }

        traceRETURN_xCoRoutineRemoveFromEventList( xReturn );

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

/*
 * Reset state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
    فراغ vCoRoutineResetState( فراغ )
    {
        /* Lists for ready and blocked co-routines. */
        pxDelayedCoRoutineList = عدم;
        px_حد_کان_مٿي_Delayed_Co_Routine_List = عدم;

        /* Other file private variables. */
        pxCurrentCoRoutine = عدم;
        ux_چوٽي_Co_Routine_Ready_ترجيح = ( UBaseType_t ) 0U;
        x_Co_Routine_Tick_ڳڻپ = ( TickType_t ) 0U;
        x_آخري_Tick_ڳڻپ = ( TickType_t ) 0U;
        xPassedTicks = ( TickType_t ) 0U;
    }
/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* configUSE_CO_ROUTINES != 0 */
