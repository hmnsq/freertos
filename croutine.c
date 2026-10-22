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

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "croutine.h"

/* Remove the whole file if co-routines are not being used. */
#ఒకవేళ ( configUSE_CO_ROUTINES != 0 )

/*
 * Some kernel aware debuggers require data to be viewed to be global, rather
 * than file scope.
 */
    #నిర్వచితమైతే పోర్టు_REMOVE_STATIC_QUALIFIER
        #నిర్వచించు STATIC
    #లేకపోతే
        #నిర్వచించు STATIC    స్థిర
    #అయితే_ముగింపు


/* Lists for ready and blocked co-routines. --------------------*/
    STATIC List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ]; /**< Prioritised ready co-routines. */
    STATIC List_t xDelayedCoRoutineList1;                                   /**< Delayed co-routines. */
    STATIC List_t xDelayedCoRoutineList2;                                   /**< Delayed co-routines (two lists are used - one for delays that have overflowed the current tick count. */
    STATIC List_t * pxDelayedCoRoutineList = ఖాళీ;                          /**< Points to the delayed co-routine list currently being used. */
    STATIC List_t * px_అధికప్రవాహం_Delayed_Co_Routine_List = ఖాళీ;                  /**< Points to the delayed co-routine list currently being used to hold co-routines that have overflowed the current tick count. */
    STATIC List_t xPendingReadyCoRoutineList;                               /**< Holds co-routines that have been readied by an external event.  They cannot be added directly to the ready lists as the ready lists cannot be accessed by interrupts. */

/* Other file private variables. --------------------------------*/
    CRCB_t * pxCurrentCoRoutine = ఖాళీ;
    STATIC UBaseType_t ux_శిఖరం_Co_Routine_Ready_ప్రాధాన్యత = ( UBaseType_t ) 0U;
    STATIC TickType_t x_Co_Routine_Tick_లెక్క = ( TickType_t ) 0U;
    STATIC TickType_t x_చివరి_Tick_లెక్క = ( TickType_t ) 0U;
    STATIC TickType_t xPassedTicks = ( TickType_t ) 0U;

/* The initial state of the co-routine when it is created. */
    #నిర్వచించు corINITIAL_STATE    ( 0 )

/*
 * Place the co-routine represented by pxCRCB into the appropriate ready queue
 * for the priority.  It is inserted at the end of the list.
 *
 * This macro accesses the co-routine ready lists and therefore must not be
 * used from within an ISR.
 */
    #నిర్వచించు prv_కూడు_Co_Routine_గమ్యం_Ready_వరుస( pxCRCB )                                                                               \
    చేయి {                                                                                                                        \
        ఒకవేళ( ( pxCRCB )->ux_ప్రాధాన్యత > ux_శిఖరం_Co_Routine_Ready_ప్రాధాన్యత )                                                              \
        {                                                                                                                       \
            ux_శిఖరం_Co_Routine_Ready_ప్రాధాన్యత = ( pxCRCB )->ux_ప్రాధాన్యత;                                                               \
        }                                                                                                                       \
        v_List_చొప్పించు_చివర( ( List_t * ) &( pxReadyCoRoutineLists[ ( pxCRCB )->ux_ప్రాధాన్యత ] ), &( ( pxCRCB )->x_Generic_List_అంశం ) ); \
    } అయితే( 0 )

/*
 * Utility to ready all the lists used by the scheduler.  This is called
 * automatically upon the creation of the first co-routine.
 */
    STATIC శూన్య prvInitialiseCoRoutineLists( శూన్య );

/*
 * Co-routines that are readied by an interrupt cannot be placed directly into
 * the ready lists (there is no mutual exclusion).  Instead they are placed in
 * in the pending ready list in order that they can later be moved to the ready
 * list by the co-routine scheduler.
 */
    STATIC శూన్య prvCheckPendingReadyList( శూన్య );

/*
 * Macro that looks at the list of co-routines that are currently delayed to
 * see if any require waking.
 *
 * Co-routines are stored in the queue in the order of their wake time -
 * meaning once one co-routine has been found whose timer has not expired
 * we need not look any further down the list.
 */
    STATIC శూన్య prvCheckDelayedList( శూన్య );

/*-----------------------------------------------------------*/

    పునాది_Type_t xCoRoutineCreate( cr_COROUTINE_సంకేతం px_Co_Routine_సంకేతం,
                                 UBaseType_t ux_ప్రాధాన్యత,
                                 UBaseType_t ux_సూచీ )
    {
        పునాది_Type_t xReturn;
        CRCB_t * pxCoRoutine;

        traceENTER_xCoRoutineCreate( px_Co_Routine_సంకేతం, ux_ప్రాధాన్యత, ux_సూచీ );

        /* Allocate the memory that will store the co-routine control block. */
        /* MISRA Ref 11.5.1 [Malloc memory assignment] */
        /* More details at: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/MISRA.md#rule-115 */
        /* coverity[misra_c_2012_rule_11_5_violation] */
        pxCoRoutine = ( CRCB_t * ) pv_పోర్టు_Malloc( పరిమాణం( CRCB_t ) );

        ఒకవేళ( pxCoRoutine )
        {
            /* If pxCurrentCoRoutine is NULL then this is the first co-routine to
            * be created and the co-routine data structures need initialising. */
            ఒకవేళ( pxCurrentCoRoutine == ఖాళీ )
            {
                pxCurrentCoRoutine = pxCoRoutine;
                prvInitialiseCoRoutineLists();
            }

            /* Check the priority is within limits. */
            ఒకవేళ( ux_ప్రాధాన్యత >= configMAX_CO_ROUTINE_PRIORITIES )
            {
                ux_ప్రాధాన్యత = configMAX_CO_ROUTINE_PRIORITIES - 1;
            }

            /* Fill out the co-routine control block from the function parameters. */
            pxCoRoutine->uxState = corINITIAL_STATE;
            pxCoRoutine->ux_ప్రాధాన్యత = ux_ప్రాధాన్యత;
            pxCoRoutine->ux_సూచీ = ux_సూచీ;
            pxCoRoutine->pxCoRoutineFunction = px_Co_Routine_సంకేతం;

            /* Initialise all the other co-routine control block parameters. */
            v_List_Initialise_అంశం( &( pxCoRoutine->x_Generic_List_అంశం ) );
            v_List_Initialise_అంశం( &( pxCoRoutine->x_Event_List_అంశం ) );

            /* Set the co-routine control block as a link back from the ListItem_t.
             * This is so we can get back to the containing CRCB from a generic item
             * in a list. */
            list_సమితి_LIST_అంశం_OWNER( &( pxCoRoutine->x_Generic_List_అంశం ), pxCoRoutine );
            list_సమితి_LIST_అంశం_OWNER( &( pxCoRoutine->x_Event_List_అంశం ), pxCoRoutine );

            /* Event lists are always in priority order. */
            list_సమితి_LIST_అంశం_విలువ( &( pxCoRoutine->x_Event_List_అంశం ), ( ( TickType_t ) configMAX_CO_ROUTINE_PRIORITIES - ( TickType_t ) ux_ప్రాధాన్యత ) );

            /* Now the co-routine has been initialised it can be added to the ready
             * list at the correct priority. */
            prv_కూడు_Co_Routine_గమ్యం_Ready_వరుస( pxCoRoutine );

            xReturn = pdPASS;
        }
        లేకపోతే
        {
            xReturn = err_COULD_NOT_ALLOCATE_REQUIRED_జ్ఞాపకం;
        }

        traceRETURN_xCoRoutineCreate( xReturn );

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    శూన్య v_Co_Routine_కూడు_గమ్యం_Delayed_List( TickType_t x_Ticks_గమ్యం_Delay,
                                     List_t * pxEventList )
    {
        TickType_t x_సమయం_గమ్యం_Wake;

        trace_ENTER_v_Co_Routine_కూడు_గమ్యం_Delayed_List( x_Ticks_గమ్యం_Delay, pxEventList );

        /* Calculate the time to wake - this may overflow but this is
         * not a problem. */
        x_సమయం_గమ్యం_Wake = x_Co_Routine_Tick_లెక్క + x_Ticks_గమ్యం_Delay;

        /* We must remove ourselves from the ready list before adding
         * ourselves to the blocked list as the same list item is used for
         * both lists. */
        ( శూన్య ) uxListRemove( ( List_అంశం_t * ) &( pxCurrentCoRoutine->x_Generic_List_అంశం ) );

        /* The list item will be inserted in wake time order. */
        list_సమితి_LIST_అంశం_విలువ( &( pxCurrentCoRoutine->x_Generic_List_అంశం ), x_సమయం_గమ్యం_Wake );

        ఒకవేళ( x_సమయం_గమ్యం_Wake < x_Co_Routine_Tick_లెక్క )
        {
            /* Wake time has overflowed.  Place this item in the
             * overflow list. */
            v_List_చొప్పించు( ( List_t * ) px_అధికప్రవాహం_Delayed_Co_Routine_List, ( List_అంశం_t * ) &( pxCurrentCoRoutine->x_Generic_List_అంశం ) );
        }
        లేకపోతే
        {
            /* The wake time has not overflowed, so we can use the
             * current block list. */
            v_List_చొప్పించు( ( List_t * ) pxDelayedCoRoutineList, ( List_అంశం_t * ) &( pxCurrentCoRoutine->x_Generic_List_అంశం ) );
        }

        ఒకవేళ( pxEventList )
        {
            /* Also add the co-routine to an event list.  If this is done then the
             * function must be called with interrupts disabled. */
            v_List_చొప్పించు( pxEventList, &( pxCurrentCoRoutine->x_Event_List_అంశం ) );
        }

        trace_RETURN_v_Co_Routine_కూడు_గమ్యం_Delayed_List();
    }
/*-----------------------------------------------------------*/

    STATIC శూన్య prvCheckPendingReadyList( శూన్య )
    {
        /* Are there any co-routines waiting to get moved to the ready list?  These
         * are co-routines that have been readied by an ISR.  The ISR cannot access
         * the ready lists itself. */
        అయితే( list_LIST_IS_ఖాళీలు( &xPendingReadyCoRoutineList ) == pdFALSE )
        {
            CRCB_t * pxUnblockedCRCB;

            /* The pending ready list can be accessed by an ISR. */
            పోర్టు_DISABLE_INTERRUPTS();
            {
                pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_యొక్క_తల_నమోదు( ( &xPendingReadyCoRoutineList ) );
                ( శూన్య ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_అంశం ) );
            }
            పోర్టు_ENABLE_INTERRUPTS();

            ( శూన్య ) uxListRemove( &( pxUnblockedCRCB->x_Generic_List_అంశం ) );
            prv_కూడు_Co_Routine_గమ్యం_Ready_వరుస( pxUnblockedCRCB );
        }
    }
/*-----------------------------------------------------------*/

    STATIC శూన్య prvCheckDelayedList( శూన్య )
    {
        CRCB_t * pxCRCB;

        xPassedTicks = x_Task_Get_Tick_లెక్క() - x_చివరి_Tick_లెక్క;

        అయితే( xPassedTicks )
        {
            x_Co_Routine_Tick_లెక్క++;
            xPassedTicks--;

            /* If the tick count has overflowed we need to swap the ready lists. */
            ఒకవేళ( x_Co_Routine_Tick_లెక్క == 0 )
            {
                List_t * px_తాత్కాలిక;

                /* Tick count has overflowed so we need to swap the delay lists.  If there are
                 * any items in pxDelayedCoRoutineList here then there is an error! */
                px_తాత్కాలిక = pxDelayedCoRoutineList;
                pxDelayedCoRoutineList = px_అధికప్రవాహం_Delayed_Co_Routine_List;
                px_అధికప్రవాహం_Delayed_Co_Routine_List = px_తాత్కాలిక;
            }

            /* See if this tick has made a timeout expire. */
            అయితే( list_LIST_IS_ఖాళీలు( pxDelayedCoRoutineList ) == pdFALSE )
            {
                pxCRCB = ( CRCB_t * ) list_GET_OWNER_యొక్క_తల_నమోదు( pxDelayedCoRoutineList );

                ఒకవేళ( x_Co_Routine_Tick_లెక్క < list_GET_LIST_అంశం_విలువ( &( pxCRCB->x_Generic_List_అంశం ) ) )
                {
                    /* Timeout not yet expired. */
                    ఆపు;
                }

                పోర్టు_DISABLE_INTERRUPTS();
                {
                    /* The event could have occurred just before this critical
                     *  section.  If this is the case then the generic list item will
                     *  have been moved to the pending ready list and the following
                     *  line is still valid.  Also the pvContainer parameter will have
                     *  been set to NULL so the following lines are also valid. */
                    ( శూన్య ) uxListRemove( &( pxCRCB->x_Generic_List_అంశం ) );

                    /* Is the co-routine waiting on an event also? */
                    ఒకవేళ( pxCRCB->x_Event_List_అంశం.pxContainer )
                    {
                        ( శూన్య ) uxListRemove( &( pxCRCB->x_Event_List_అంశం ) );
                    }
                }
                పోర్టు_ENABLE_INTERRUPTS();

                prv_కూడు_Co_Routine_గమ్యం_Ready_వరుస( pxCRCB );
            }
        }

        x_చివరి_Tick_లెక్క = x_Co_Routine_Tick_లెక్క;
    }
/*-----------------------------------------------------------*/

    శూన్య v_Co_Routine_కాలపట్టిక( శూన్య )
    {
        trace_ENTER_v_Co_Routine_కాలపట్టిక();

        /* Only run a co-routine after prvInitialiseCoRoutineLists() has been
         * called.  prvInitialiseCoRoutineLists() is called automatically when a
         * co-routine is created. */
        ఒకవేళ( pxDelayedCoRoutineList != ఖాళీ )
        {
            /* See if any co-routines readied by events need moving to the ready lists. */
            prvCheckPendingReadyList();

            /* See if any delayed co-routines have timed out. */
            prvCheckDelayedList();

            /* Find the highest priority queue that contains ready co-routines. */
            అయితే( list_LIST_IS_ఖాళీలు( &( pxReadyCoRoutineLists[ ux_శిఖరం_Co_Routine_Ready_ప్రాధాన్యత ] ) ) )
            {
                ఒకవేళ( ux_శిఖరం_Co_Routine_Ready_ప్రాధాన్యత == 0 )
                {
                    /* No more co-routines to check. */
                    తిరిగి;
                }

                --ux_శిఖరం_Co_Routine_Ready_ప్రాధాన్యత;
            }

            /* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
             * of the same priority get an equal share of the processor time. */
            list_GET_OWNER_యొక్క_తదుపరి_నమోదు( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ ux_శిఖరం_Co_Routine_Ready_ప్రాధాన్యత ] ) );

            /* Call the co-routine. */
            ( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->ux_సూచీ );
        }

        trace_RETURN_v_Co_Routine_కాలపట్టిక();
    }
/*-----------------------------------------------------------*/

    STATIC శూన్య prvInitialiseCoRoutineLists( శూన్య )
    {
        UBaseType_t ux_ప్రాధాన్యత;

        కొరకు( ux_ప్రాధాన్యత = 0; ux_ప్రాధాన్యత < configMAX_CO_ROUTINE_PRIORITIES; ux_ప్రాధాన్యత++ )
        {
            vListInitialise( ( List_t * ) &( pxReadyCoRoutineLists[ ux_ప్రాధాన్యత ] ) );
        }

        vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
        vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
        vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );

        /* Start with pxDelayedCoRoutineList using list1 and the
         * pxOverflowDelayedCoRoutineList using list2. */
        pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
        px_అధికప్రవాహం_Delayed_Co_Routine_List = &xDelayedCoRoutineList2;
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t xCoRoutineRemoveFromEventList( స్థిరరాశి List_t * pxEventList )
    {
        CRCB_t * pxUnblockedCRCB;
        పునాది_Type_t xReturn;

        traceENTER_xCoRoutineRemoveFromEventList( pxEventList );

        /* This function is called from within an interrupt.  It can only access
         * event lists and the pending ready list.  This function assumes that a
         * check has already been made to ensure pxEventList is not empty. */
        pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_యొక్క_తల_నమోదు( pxEventList );
        ( శూన్య ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_అంశం ) );
        v_List_చొప్పించు_చివర( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->x_Event_List_అంశం ) );

        ఒకవేళ( pxUnblockedCRCB->ux_ప్రాధాన్యత >= pxCurrentCoRoutine->ux_ప్రాధాన్యత )
        {
            xReturn = pdTRUE;
        }
        లేకపోతే
        {
            xReturn = pdFALSE;
        }

        traceRETURN_xCoRoutineRemoveFromEventList( xReturn );

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

/*
 * Reset state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
    శూన్య vCoRoutineResetState( శూన్య )
    {
        /* Lists for ready and blocked co-routines. */
        pxDelayedCoRoutineList = ఖాళీ;
        px_అధికప్రవాహం_Delayed_Co_Routine_List = ఖాళీ;

        /* Other file private variables. */
        pxCurrentCoRoutine = ఖాళీ;
        ux_శిఖరం_Co_Routine_Ready_ప్రాధాన్యత = ( UBaseType_t ) 0U;
        x_Co_Routine_Tick_లెక్క = ( TickType_t ) 0U;
        x_చివరి_Tick_లెక్క = ( TickType_t ) 0U;
        xPassedTicks = ( TickType_t ) 0U;
    }
/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* configUSE_CO_ROUTINES != 0 */
