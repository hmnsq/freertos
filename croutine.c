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
    #که_تعریف_شوی پورټ_REMOVE_STATIC_QUALIFIER
        #تعریف_کړه STATIC
    #وإلا
        #تعریف_کړه STATIC    ساكن
    #د_که_پای


/* Lists for ready and blocked co-routines. --------------------*/
    STATIC List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ]; /**< Prioritised ready co-routines. */
    STATIC List_t xDelayedCoRoutineList1;                                   /**< Delayed co-routines. */
    STATIC List_t xDelayedCoRoutineList2;                                   /**< Delayed co-routines (two lists are used - one for delays that have overflowed the current tick count. */
    STATIC List_t * pxDelayedCoRoutineList = عدم;                          /**< Points to the delayed co-routine list currently being used. */
    STATIC List_t * px_ډکېدنه_Delayed_Co_Routine_List = عدم;                  /**< Points to the delayed co-routine list currently being used to hold co-routines that have overflowed the current tick count. */
    STATIC List_t xPendingReadyCoRoutineList;                               /**< Holds co-routines that have been readied by an external event.  They cannot be added directly to the ready lists as the ready lists cannot be accessed by interrupts. */

/* Other file private variables. --------------------------------*/
    CRCB_t * pxCurrentCoRoutine = عدم;
    STATIC UBaseType_t ux_سر_Co_Routine_Ready_لومړیتوب = ( UBaseType_t ) 0U;
    STATIC TickType_t x_Co_Routine_Tick_شمېر = ( TickType_t ) 0U;
    STATIC TickType_t x_وروستی_Tick_شمېر = ( TickType_t ) 0U;
    STATIC TickType_t xPassedTicks = ( TickType_t ) 0U;

/* The initial state of the co-routine when it is created. */
    #تعریف_کړه corINITIAL_STATE    ( 0 )

/*
 * Place the co-routine represented by pxCRCB into the appropriate ready queue
 * for the priority.  It is inserted at the end of the list.
 *
 * This macro accesses the co-routine ready lists and therefore must not be
 * used from within an ISR.
 */
    #تعریف_کړه prv_جمع_کړه_Co_Routine_منزل_Ready_کتار( pxCRCB )                                                                               \
    افعل {                                                                                                                        \
        إذا( ( pxCRCB )->ux_لومړیتوب > ux_سر_Co_Routine_Ready_لومړیتوب )                                                              \
        {                                                                                                                       \
            ux_سر_Co_Routine_Ready_لومړیتوب = ( pxCRCB )->ux_لومړیتوب;                                                               \
        }                                                                                                                       \
        v_List_ورننباسه_پای_ټکی( ( List_t * ) &( pxReadyCoRoutineLists[ ( pxCRCB )->ux_لومړیتوب ] ), &( ( pxCRCB )->x_Generic_List_توکی ) ); \
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

    بنسټ_Type_t xCoRoutineCreate( cr_COROUTINE_کوډ px_Co_Routine_کوډ,
                                 UBaseType_t ux_لومړیتوب,
                                 UBaseType_t ux_شاخص )
    {
        بنسټ_Type_t xReturn;
        CRCB_t * pxCoRoutine;

        traceENTER_xCoRoutineCreate( px_Co_Routine_کوډ, ux_لومړیتوب, ux_شاخص );

        /* Allocate the memory that will store the co-routine control block. */
        /* MISRA Ref 11.5.1 [Malloc memory assignment] */
        /* More details at: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/MISRA.md#rule-115 */
        /* coverity[misra_c_2012_rule_11_5_violation] */
        pxCoRoutine = ( CRCB_t * ) pv_پورټ_Malloc( حجم( CRCB_t ) );

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
            إذا( ux_لومړیتوب >= configMAX_CO_ROUTINE_PRIORITIES )
            {
                ux_لومړیتوب = configMAX_CO_ROUTINE_PRIORITIES - 1;
            }

            /* Fill out the co-routine control block from the function parameters. */
            pxCoRoutine->uxState = corINITIAL_STATE;
            pxCoRoutine->ux_لومړیتوب = ux_لومړیتوب;
            pxCoRoutine->ux_شاخص = ux_شاخص;
            pxCoRoutine->pxCoRoutineFunction = px_Co_Routine_کوډ;

            /* Initialise all the other co-routine control block parameters. */
            v_List_Initialise_توکی( &( pxCoRoutine->x_Generic_List_توکی ) );
            v_List_Initialise_توکی( &( pxCoRoutine->x_Event_List_توکی ) );

            /* Set the co-routine control block as a link back from the ListItem_t.
             * This is so we can get back to the containing CRCB from a generic item
             * in a list. */
            list_سېټ_LIST_توکی_OWNER( &( pxCoRoutine->x_Generic_List_توکی ), pxCoRoutine );
            list_سېټ_LIST_توکی_OWNER( &( pxCoRoutine->x_Event_List_توکی ), pxCoRoutine );

            /* Event lists are always in priority order. */
            list_سېټ_LIST_توکی_ارزښت( &( pxCoRoutine->x_Event_List_توکی ), ( ( TickType_t ) configMAX_CO_ROUTINE_PRIORITIES - ( TickType_t ) ux_لومړیتوب ) );

            /* Now the co-routine has been initialised it can be added to the ready
             * list at the correct priority. */
            prv_جمع_کړه_Co_Routine_منزل_Ready_کتار( pxCoRoutine );

            xReturn = pdPASS;
        }
        وإلا
        {
            xReturn = err_COULD_NOT_ALLOCATE_REQUIRED_حافظه;
        }

        traceRETURN_xCoRoutineCreate( xReturn );

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    فراغ v_Co_Routine_جمع_کړه_منزل_Delayed_List( TickType_t x_Ticks_منزل_Delay,
                                     List_t * pxEventList )
    {
        TickType_t x_وخت_منزل_Wake;

        trace_ENTER_v_Co_Routine_جمع_کړه_منزل_Delayed_List( x_Ticks_منزل_Delay, pxEventList );

        /* Calculate the time to wake - this may overflow but this is
         * not a problem. */
        x_وخت_منزل_Wake = x_Co_Routine_Tick_شمېر + x_Ticks_منزل_Delay;

        /* We must remove ourselves from the ready list before adding
         * ourselves to the blocked list as the same list item is used for
         * both lists. */
        ( فراغ ) uxListRemove( ( List_توکی_t * ) &( pxCurrentCoRoutine->x_Generic_List_توکی ) );

        /* The list item will be inserted in wake time order. */
        list_سېټ_LIST_توکی_ارزښت( &( pxCurrentCoRoutine->x_Generic_List_توکی ), x_وخت_منزل_Wake );

        إذا( x_وخت_منزل_Wake < x_Co_Routine_Tick_شمېر )
        {
            /* Wake time has overflowed.  Place this item in the
             * overflow list. */
            v_List_ورننباسه( ( List_t * ) px_ډکېدنه_Delayed_Co_Routine_List, ( List_توکی_t * ) &( pxCurrentCoRoutine->x_Generic_List_توکی ) );
        }
        وإلا
        {
            /* The wake time has not overflowed, so we can use the
             * current block list. */
            v_List_ورننباسه( ( List_t * ) pxDelayedCoRoutineList, ( List_توکی_t * ) &( pxCurrentCoRoutine->x_Generic_List_توکی ) );
        }

        إذا( pxEventList )
        {
            /* Also add the co-routine to an event list.  If this is done then the
             * function must be called with interrupts disabled. */
            v_List_ورننباسه( pxEventList, &( pxCurrentCoRoutine->x_Event_List_توکی ) );
        }

        trace_RETURN_v_Co_Routine_جمع_کړه_منزل_Delayed_List();
    }
/*-----------------------------------------------------------*/

    STATIC فراغ prvCheckPendingReadyList( فراغ )
    {
        /* Are there any co-routines waiting to get moved to the ready list?  These
         * are co-routines that have been readied by an ISR.  The ISR cannot access
         * the ready lists itself. */
        طالما( list_LIST_IS_تشه( &xPendingReadyCoRoutineList ) == pdFALSE )
        {
            CRCB_t * pxUnblockedCRCB;

            /* The pending ready list can be accessed by an ISR. */
            پورټ_DISABLE_INTERRUPTS();
            {
                pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_د_سر_ثبت( ( &xPendingReadyCoRoutineList ) );
                ( فراغ ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_توکی ) );
            }
            پورټ_ENABLE_INTERRUPTS();

            ( فراغ ) uxListRemove( &( pxUnblockedCRCB->x_Generic_List_توکی ) );
            prv_جمع_کړه_Co_Routine_منزل_Ready_کتار( pxUnblockedCRCB );
        }
    }
/*-----------------------------------------------------------*/

    STATIC فراغ prvCheckDelayedList( فراغ )
    {
        CRCB_t * pxCRCB;

        xPassedTicks = x_Task_Get_Tick_شمېر() - x_وروستی_Tick_شمېر;

        طالما( xPassedTicks )
        {
            x_Co_Routine_Tick_شمېر++;
            xPassedTicks--;

            /* If the tick count has overflowed we need to swap the ready lists. */
            إذا( x_Co_Routine_Tick_شمېر == 0 )
            {
                List_t * px_لنډمهاله;

                /* Tick count has overflowed so we need to swap the delay lists.  If there are
                 * any items in pxDelayedCoRoutineList here then there is an error! */
                px_لنډمهاله = pxDelayedCoRoutineList;
                pxDelayedCoRoutineList = px_ډکېدنه_Delayed_Co_Routine_List;
                px_ډکېدنه_Delayed_Co_Routine_List = px_لنډمهاله;
            }

            /* See if this tick has made a timeout expire. */
            طالما( list_LIST_IS_تشه( pxDelayedCoRoutineList ) == pdFALSE )
            {
                pxCRCB = ( CRCB_t * ) list_GET_OWNER_د_سر_ثبت( pxDelayedCoRoutineList );

                إذا( x_Co_Routine_Tick_شمېر < list_GET_LIST_توکی_ارزښت( &( pxCRCB->x_Generic_List_توکی ) ) )
                {
                    /* Timeout not yet expired. */
                    اكسر;
                }

                پورټ_DISABLE_INTERRUPTS();
                {
                    /* The event could have occurred just before this critical
                     *  section.  If this is the case then the generic list item will
                     *  have been moved to the pending ready list and the following
                     *  line is still valid.  Also the pvContainer parameter will have
                     *  been set to NULL so the following lines are also valid. */
                    ( فراغ ) uxListRemove( &( pxCRCB->x_Generic_List_توکی ) );

                    /* Is the co-routine waiting on an event also? */
                    إذا( pxCRCB->x_Event_List_توکی.pxContainer )
                    {
                        ( فراغ ) uxListRemove( &( pxCRCB->x_Event_List_توکی ) );
                    }
                }
                پورټ_ENABLE_INTERRUPTS();

                prv_جمع_کړه_Co_Routine_منزل_Ready_کتار( pxCRCB );
            }
        }

        x_وروستی_Tick_شمېر = x_Co_Routine_Tick_شمېر;
    }
/*-----------------------------------------------------------*/

    فراغ v_Co_Routine_مهالوېش( فراغ )
    {
        trace_ENTER_v_Co_Routine_مهالوېش();

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
            طالما( list_LIST_IS_تشه( &( pxReadyCoRoutineLists[ ux_سر_Co_Routine_Ready_لومړیتوب ] ) ) )
            {
                إذا( ux_سر_Co_Routine_Ready_لومړیتوب == 0 )
                {
                    /* No more co-routines to check. */
                    أرجع;
                }

                --ux_سر_Co_Routine_Ready_لومړیتوب;
            }

            /* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
             * of the same priority get an equal share of the processor time. */
            list_GET_OWNER_د_بل_ثبت( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ ux_سر_Co_Routine_Ready_لومړیتوب ] ) );

            /* Call the co-routine. */
            ( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->ux_شاخص );
        }

        trace_RETURN_v_Co_Routine_مهالوېش();
    }
/*-----------------------------------------------------------*/

    STATIC فراغ prvInitialiseCoRoutineLists( فراغ )
    {
        UBaseType_t ux_لومړیتوب;

        لكل( ux_لومړیتوب = 0; ux_لومړیتوب < configMAX_CO_ROUTINE_PRIORITIES; ux_لومړیتوب++ )
        {
            vListInitialise( ( List_t * ) &( pxReadyCoRoutineLists[ ux_لومړیتوب ] ) );
        }

        vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
        vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
        vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );

        /* Start with pxDelayedCoRoutineList using list1 and the
         * pxOverflowDelayedCoRoutineList using list2. */
        pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
        px_ډکېدنه_Delayed_Co_Routine_List = &xDelayedCoRoutineList2;
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t xCoRoutineRemoveFromEventList( ثابت List_t * pxEventList )
    {
        CRCB_t * pxUnblockedCRCB;
        بنسټ_Type_t xReturn;

        traceENTER_xCoRoutineRemoveFromEventList( pxEventList );

        /* This function is called from within an interrupt.  It can only access
         * event lists and the pending ready list.  This function assumes that a
         * check has already been made to ensure pxEventList is not empty. */
        pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_د_سر_ثبت( pxEventList );
        ( فراغ ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_توکی ) );
        v_List_ورننباسه_پای_ټکی( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->x_Event_List_توکی ) );

        إذا( pxUnblockedCRCB->ux_لومړیتوب >= pxCurrentCoRoutine->ux_لومړیتوب )
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
        px_ډکېدنه_Delayed_Co_Routine_List = عدم;

        /* Other file private variables. */
        pxCurrentCoRoutine = عدم;
        ux_سر_Co_Routine_Ready_لومړیتوب = ( UBaseType_t ) 0U;
        x_Co_Routine_Tick_شمېر = ( TickType_t ) 0U;
        x_وروستی_Tick_شمېر = ( TickType_t ) 0U;
        xPassedTicks = ( TickType_t ) 0U;
    }
/*-----------------------------------------------------------*/

#د_که_پای /* configUSE_CO_ROUTINES != 0 */
