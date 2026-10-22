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

#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "croutine.h"

/* Remove the whole file if co-routines are not being used. */
#اگر ( configUSE_CO_ROUTINES != 0 )

/*
 * Some kernel aware debuggers require data to be viewed to be global, rather
 * than file scope.
 */
    #اگر_تعریف_شدہ پورٹ_REMOVE_STATIC_QUALIFIER
        #تعریف_کرو STATIC
    #ورنہ
        #تعریف_کرو STATIC    ساکن
    #اگر_ختم


/* Lists for ready and blocked co-routines. --------------------*/
    STATIC List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ]; /**< Prioritised ready co-routines. */
    STATIC List_t xDelayedCoRoutineList1;                                   /**< Delayed co-routines. */
    STATIC List_t xDelayedCoRoutineList2;                                   /**< Delayed co-routines (two lists are used - one for delays that have overflowed the current tick count. */
    STATIC List_t * pxDelayedCoRoutineList = تہی;                          /**< Points to the delayed co-routine list currently being used. */
    STATIC List_t * px_حد_سے_تجاوز_Delayed_Co_Routine_List = تہی;                  /**< Points to the delayed co-routine list currently being used to hold co-routines that have overflowed the current tick count. */
    STATIC List_t xPendingReadyCoRoutineList;                               /**< Holds co-routines that have been readied by an external event.  They cannot be added directly to the ready lists as the ready lists cannot be accessed by interrupts. */

/* Other file private variables. --------------------------------*/
    CRCB_t * pxCurrentCoRoutine = تہی;
    STATIC UBaseType_t ux_چوٹی_Co_Routine_Ready_ترجیح = ( UBaseType_t ) 0U;
    STATIC TickType_t x_Co_Routine_Tick_گنتی = ( TickType_t ) 0U;
    STATIC TickType_t x_آخری_Tick_گنتی = ( TickType_t ) 0U;
    STATIC TickType_t xPassedTicks = ( TickType_t ) 0U;

/* The initial state of the co-routine when it is created. */
    #تعریف_کرو corINITIAL_STATE    ( 0 )

/*
 * Place the co-routine represented by pxCRCB into the appropriate ready queue
 * for the priority.  It is inserted at the end of the list.
 *
 * This macro accesses the co-routine ready lists and therefore must not be
 * used from within an ISR.
 */
    #تعریف_کرو prv_جوڑو_Co_Routine_مقصد_Ready_قطار( pxCRCB )                                                                               \
    کرو {                                                                                                                        \
        اگر( ( pxCRCB )->ux_ترجیح > ux_چوٹی_Co_Routine_Ready_ترجیح )                                                              \
        {                                                                                                                       \
            ux_چوٹی_Co_Routine_Ready_ترجیح = ( pxCRCB )->ux_ترجیح;                                                               \
        }                                                                                                                       \
        v_List_داخل_کرو_انتہا( ( List_t * ) &( pxReadyCoRoutineLists[ ( pxCRCB )->ux_ترجیح ] ), &( ( pxCRCB )->x_Generic_List_شے ) ); \
    } جب( 0 )

/*
 * Utility to ready all the lists used by the scheduler.  This is called
 * automatically upon the creation of the first co-routine.
 */
    STATIC خالی prvInitialiseCoRoutineLists( خالی );

/*
 * Co-routines that are readied by an interrupt cannot be placed directly into
 * the ready lists (there is no mutual exclusion).  Instead they are placed in
 * in the pending ready list in order that they can later be moved to the ready
 * list by the co-routine scheduler.
 */
    STATIC خالی prvCheckPendingReadyList( خالی );

/*
 * Macro that looks at the list of co-routines that are currently delayed to
 * see if any require waking.
 *
 * Co-routines are stored in the queue in the order of their wake time -
 * meaning once one co-routine has been found whose timer has not expired
 * we need not look any further down the list.
 */
    STATIC خالی prvCheckDelayedList( خالی );

/*-----------------------------------------------------------*/

    بنیاد_Type_t xCoRoutineCreate( cr_COROUTINE_رمز px_Co_Routine_رمز,
                                 UBaseType_t ux_ترجیح,
                                 UBaseType_t ux_اشاریہ )
    {
        بنیاد_Type_t xReturn;
        CRCB_t * pxCoRoutine;

        traceENTER_xCoRoutineCreate( px_Co_Routine_رمز, ux_ترجیح, ux_اشاریہ );

        /* Allocate the memory that will store the co-routine control block. */
        /* MISRA Ref 11.5.1 [Malloc memory assignment] */
        /* More details at: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/MISRA.md#rule-115 */
        /* coverity[misra_c_2012_rule_11_5_violation] */
        pxCoRoutine = ( CRCB_t * ) pv_پورٹ_Malloc( حجم( CRCB_t ) );

        اگر( pxCoRoutine )
        {
            /* If pxCurrentCoRoutine is NULL then this is the first co-routine to
            * be created and the co-routine data structures need initialising. */
            اگر( pxCurrentCoRoutine == تہی )
            {
                pxCurrentCoRoutine = pxCoRoutine;
                prvInitialiseCoRoutineLists();
            }

            /* Check the priority is within limits. */
            اگر( ux_ترجیح >= configMAX_CO_ROUTINE_PRIORITIES )
            {
                ux_ترجیح = configMAX_CO_ROUTINE_PRIORITIES - 1;
            }

            /* Fill out the co-routine control block from the function parameters. */
            pxCoRoutine->uxState = corINITIAL_STATE;
            pxCoRoutine->ux_ترجیح = ux_ترجیح;
            pxCoRoutine->ux_اشاریہ = ux_اشاریہ;
            pxCoRoutine->pxCoRoutineFunction = px_Co_Routine_رمز;

            /* Initialise all the other co-routine control block parameters. */
            v_List_Initialise_شے( &( pxCoRoutine->x_Generic_List_شے ) );
            v_List_Initialise_شے( &( pxCoRoutine->x_Event_List_شے ) );

            /* Set the co-routine control block as a link back from the ListItem_t.
             * This is so we can get back to the containing CRCB from a generic item
             * in a list. */
            list_سیٹ_LIST_شے_OWNER( &( pxCoRoutine->x_Generic_List_شے ), pxCoRoutine );
            list_سیٹ_LIST_شے_OWNER( &( pxCoRoutine->x_Event_List_شے ), pxCoRoutine );

            /* Event lists are always in priority order. */
            list_سیٹ_LIST_شے_قدر( &( pxCoRoutine->x_Event_List_شے ), ( ( TickType_t ) configMAX_CO_ROUTINE_PRIORITIES - ( TickType_t ) ux_ترجیح ) );

            /* Now the co-routine has been initialised it can be added to the ready
             * list at the correct priority. */
            prv_جوڑو_Co_Routine_مقصد_Ready_قطار( pxCoRoutine );

            xReturn = pdPASS;
        }
        ورنہ
        {
            xReturn = err_COULD_NOT_ALLOCATE_REQUIRED_حافظہ;
        }

        traceRETURN_xCoRoutineCreate( xReturn );

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    خالی v_Co_Routine_جوڑو_مقصد_Delayed_List( TickType_t x_Ticks_مقصد_Delay,
                                     List_t * pxEventList )
    {
        TickType_t x_وقت_مقصد_Wake;

        trace_ENTER_v_Co_Routine_جوڑو_مقصد_Delayed_List( x_Ticks_مقصد_Delay, pxEventList );

        /* Calculate the time to wake - this may overflow but this is
         * not a problem. */
        x_وقت_مقصد_Wake = x_Co_Routine_Tick_گنتی + x_Ticks_مقصد_Delay;

        /* We must remove ourselves from the ready list before adding
         * ourselves to the blocked list as the same list item is used for
         * both lists. */
        ( خالی ) uxListRemove( ( List_شے_t * ) &( pxCurrentCoRoutine->x_Generic_List_شے ) );

        /* The list item will be inserted in wake time order. */
        list_سیٹ_LIST_شے_قدر( &( pxCurrentCoRoutine->x_Generic_List_شے ), x_وقت_مقصد_Wake );

        اگر( x_وقت_مقصد_Wake < x_Co_Routine_Tick_گنتی )
        {
            /* Wake time has overflowed.  Place this item in the
             * overflow list. */
            v_List_داخل_کرو( ( List_t * ) px_حد_سے_تجاوز_Delayed_Co_Routine_List, ( List_شے_t * ) &( pxCurrentCoRoutine->x_Generic_List_شے ) );
        }
        ورنہ
        {
            /* The wake time has not overflowed, so we can use the
             * current block list. */
            v_List_داخل_کرو( ( List_t * ) pxDelayedCoRoutineList, ( List_شے_t * ) &( pxCurrentCoRoutine->x_Generic_List_شے ) );
        }

        اگر( pxEventList )
        {
            /* Also add the co-routine to an event list.  If this is done then the
             * function must be called with interrupts disabled. */
            v_List_داخل_کرو( pxEventList, &( pxCurrentCoRoutine->x_Event_List_شے ) );
        }

        trace_RETURN_v_Co_Routine_جوڑو_مقصد_Delayed_List();
    }
/*-----------------------------------------------------------*/

    STATIC خالی prvCheckPendingReadyList( خالی )
    {
        /* Are there any co-routines waiting to get moved to the ready list?  These
         * are co-routines that have been readied by an ISR.  The ISR cannot access
         * the ready lists itself. */
        جب( list_LIST_IS_خالی_خانے( &xPendingReadyCoRoutineList ) == pdFALSE )
        {
            CRCB_t * pxUnblockedCRCB;

            /* The pending ready list can be accessed by an ISR. */
            پورٹ_DISABLE_INTERRUPTS();
            {
                pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_کا_سر_اندراج( ( &xPendingReadyCoRoutineList ) );
                ( خالی ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_شے ) );
            }
            پورٹ_ENABLE_INTERRUPTS();

            ( خالی ) uxListRemove( &( pxUnblockedCRCB->x_Generic_List_شے ) );
            prv_جوڑو_Co_Routine_مقصد_Ready_قطار( pxUnblockedCRCB );
        }
    }
/*-----------------------------------------------------------*/

    STATIC خالی prvCheckDelayedList( خالی )
    {
        CRCB_t * pxCRCB;

        xPassedTicks = x_Task_Get_Tick_گنتی() - x_آخری_Tick_گنتی;

        جب( xPassedTicks )
        {
            x_Co_Routine_Tick_گنتی++;
            xPassedTicks--;

            /* If the tick count has overflowed we need to swap the ready lists. */
            اگر( x_Co_Routine_Tick_گنتی == 0 )
            {
                List_t * px_عارضی;

                /* Tick count has overflowed so we need to swap the delay lists.  If there are
                 * any items in pxDelayedCoRoutineList here then there is an error! */
                px_عارضی = pxDelayedCoRoutineList;
                pxDelayedCoRoutineList = px_حد_سے_تجاوز_Delayed_Co_Routine_List;
                px_حد_سے_تجاوز_Delayed_Co_Routine_List = px_عارضی;
            }

            /* See if this tick has made a timeout expire. */
            جب( list_LIST_IS_خالی_خانے( pxDelayedCoRoutineList ) == pdFALSE )
            {
                pxCRCB = ( CRCB_t * ) list_GET_OWNER_کا_سر_اندراج( pxDelayedCoRoutineList );

                اگر( x_Co_Routine_Tick_گنتی < list_GET_LIST_شے_قدر( &( pxCRCB->x_Generic_List_شے ) ) )
                {
                    /* Timeout not yet expired. */
                    توڑو;
                }

                پورٹ_DISABLE_INTERRUPTS();
                {
                    /* The event could have occurred just before this critical
                     *  section.  If this is the case then the generic list item will
                     *  have been moved to the pending ready list and the following
                     *  line is still valid.  Also the pvContainer parameter will have
                     *  been set to NULL so the following lines are also valid. */
                    ( خالی ) uxListRemove( &( pxCRCB->x_Generic_List_شے ) );

                    /* Is the co-routine waiting on an event also? */
                    اگر( pxCRCB->x_Event_List_شے.pxContainer )
                    {
                        ( خالی ) uxListRemove( &( pxCRCB->x_Event_List_شے ) );
                    }
                }
                پورٹ_ENABLE_INTERRUPTS();

                prv_جوڑو_Co_Routine_مقصد_Ready_قطار( pxCRCB );
            }
        }

        x_آخری_Tick_گنتی = x_Co_Routine_Tick_گنتی;
    }
/*-----------------------------------------------------------*/

    خالی v_Co_Routine_جدول_وقت( خالی )
    {
        trace_ENTER_v_Co_Routine_جدول_وقت();

        /* Only run a co-routine after prvInitialiseCoRoutineLists() has been
         * called.  prvInitialiseCoRoutineLists() is called automatically when a
         * co-routine is created. */
        اگر( pxDelayedCoRoutineList != تہی )
        {
            /* See if any co-routines readied by events need moving to the ready lists. */
            prvCheckPendingReadyList();

            /* See if any delayed co-routines have timed out. */
            prvCheckDelayedList();

            /* Find the highest priority queue that contains ready co-routines. */
            جب( list_LIST_IS_خالی_خانے( &( pxReadyCoRoutineLists[ ux_چوٹی_Co_Routine_Ready_ترجیح ] ) ) )
            {
                اگر( ux_چوٹی_Co_Routine_Ready_ترجیح == 0 )
                {
                    /* No more co-routines to check. */
                    واپس;
                }

                --ux_چوٹی_Co_Routine_Ready_ترجیح;
            }

            /* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
             * of the same priority get an equal share of the processor time. */
            list_GET_OWNER_کا_اگلا_اندراج( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ ux_چوٹی_Co_Routine_Ready_ترجیح ] ) );

            /* Call the co-routine. */
            ( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->ux_اشاریہ );
        }

        trace_RETURN_v_Co_Routine_جدول_وقت();
    }
/*-----------------------------------------------------------*/

    STATIC خالی prvInitialiseCoRoutineLists( خالی )
    {
        UBaseType_t ux_ترجیح;

        برائے( ux_ترجیح = 0; ux_ترجیح < configMAX_CO_ROUTINE_PRIORITIES; ux_ترجیح++ )
        {
            vListInitialise( ( List_t * ) &( pxReadyCoRoutineLists[ ux_ترجیح ] ) );
        }

        vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
        vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
        vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );

        /* Start with pxDelayedCoRoutineList using list1 and the
         * pxOverflowDelayedCoRoutineList using list2. */
        pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
        px_حد_سے_تجاوز_Delayed_Co_Routine_List = &xDelayedCoRoutineList2;
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t xCoRoutineRemoveFromEventList( ثابت List_t * pxEventList )
    {
        CRCB_t * pxUnblockedCRCB;
        بنیاد_Type_t xReturn;

        traceENTER_xCoRoutineRemoveFromEventList( pxEventList );

        /* This function is called from within an interrupt.  It can only access
         * event lists and the pending ready list.  This function assumes that a
         * check has already been made to ensure pxEventList is not empty. */
        pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_کا_سر_اندراج( pxEventList );
        ( خالی ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_شے ) );
        v_List_داخل_کرو_انتہا( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->x_Event_List_شے ) );

        اگر( pxUnblockedCRCB->ux_ترجیح >= pxCurrentCoRoutine->ux_ترجیح )
        {
            xReturn = pdTRUE;
        }
        ورنہ
        {
            xReturn = pdFALSE;
        }

        traceRETURN_xCoRoutineRemoveFromEventList( xReturn );

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

/*
 * Reset state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
    خالی vCoRoutineResetState( خالی )
    {
        /* Lists for ready and blocked co-routines. */
        pxDelayedCoRoutineList = تہی;
        px_حد_سے_تجاوز_Delayed_Co_Routine_List = تہی;

        /* Other file private variables. */
        pxCurrentCoRoutine = تہی;
        ux_چوٹی_Co_Routine_Ready_ترجیح = ( UBaseType_t ) 0U;
        x_Co_Routine_Tick_گنتی = ( TickType_t ) 0U;
        x_آخری_Tick_گنتی = ( TickType_t ) 0U;
        xPassedTicks = ( TickType_t ) 0U;
    }
/*-----------------------------------------------------------*/

#اگر_ختم /* configUSE_CO_ROUTINES != 0 */
