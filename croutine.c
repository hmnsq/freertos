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

#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "croutine.h"

/* Remove the whole file if co-routines are not being used. */
#यदि ( configUSE_CO_ROUTINES != 0 )

/*
 * Some kernel aware debuggers require data to be viewed to be global, rather
 * than file scope.
 */
    #यदि_परिभाषितम् पत्तनम्_REMOVE_STATIC_QUALIFIER
        #परिभाषय STATIC
    #अन्यथा
        #परिभाषय STATIC    स्थिर
    #यदि_अन्तः


/* Lists for ready and blocked co-routines. --------------------*/
    STATIC List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ]; /**< Prioritised ready co-routines. */
    STATIC List_t xDelayedCoRoutineList1;                                   /**< Delayed co-routines. */
    STATIC List_t xDelayedCoRoutineList2;                                   /**< Delayed co-routines (two lists are used - one for delays that have overflowed the current tick count. */
    STATIC List_t * pxDelayedCoRoutineList = रिक्त;                          /**< Points to the delayed co-routine list currently being used. */
    STATIC List_t * px_अतिप्रवाहः_Delayed_Co_Routine_List = रिक्त;                  /**< Points to the delayed co-routine list currently being used to hold co-routines that have overflowed the current tick count. */
    STATIC List_t xPendingReadyCoRoutineList;                               /**< Holds co-routines that have been readied by an external event.  They cannot be added directly to the ready lists as the ready lists cannot be accessed by interrupts. */

/* Other file private variables. --------------------------------*/
    CRCB_t * pxCurrentCoRoutine = रिक्त;
    STATIC UBaseType_t ux_शिखरम्_Co_Routine_Ready_प्राथमिकता = ( UBaseType_t ) 0U;
    STATIC TickType_t x_Co_Routine_Tick_गणनम् = ( TickType_t ) 0U;
    STATIC TickType_t x_चरमः_Tick_गणनम् = ( TickType_t ) 0U;
    STATIC TickType_t xPassedTicks = ( TickType_t ) 0U;

/* The initial state of the co-routine when it is created. */
    #परिभाषय corINITIAL_STATE    ( 0 )

/*
 * Place the co-routine represented by pxCRCB into the appropriate ready queue
 * for the priority.  It is inserted at the end of the list.
 *
 * This macro accesses the co-routine ready lists and therefore must not be
 * used from within an ISR.
 */
    #परिभाषय prv_सङ्कलय_Co_Routine_गन्तव्यम्_Ready_Queue( pxCRCB )                                                                               \
    कुरु {                                                                                                                        \
        यदि( ( pxCRCB )->ux_प्राथमिकता > ux_शिखरम्_Co_Routine_Ready_प्राथमिकता )                                                              \
        {                                                                                                                       \
            ux_शिखरम्_Co_Routine_Ready_प्राथमिकता = ( pxCRCB )->ux_प्राथमिकता;                                                               \
        }                                                                                                                       \
        v_List_निवेशय_अन्तः( ( List_t * ) &( pxReadyCoRoutineLists[ ( pxCRCB )->ux_प्राथमिकता ] ), &( ( pxCRCB )->xGenericListItem ) ); \
    } यावत्( 0 )

/*
 * Utility to ready all the lists used by the scheduler.  This is called
 * automatically upon the creation of the first co-routine.
 */
    STATIC शून्य prvInitialiseCoRoutineLists( शून्य );

/*
 * Co-routines that are readied by an interrupt cannot be placed directly into
 * the ready lists (there is no mutual exclusion).  Instead they are placed in
 * in the pending ready list in order that they can later be moved to the ready
 * list by the co-routine scheduler.
 */
    STATIC शून्य prvCheckPendingReadyList( शून्य );

/*
 * Macro that looks at the list of co-routines that are currently delayed to
 * see if any require waking.
 *
 * Co-routines are stored in the queue in the order of their wake time -
 * meaning once one co-routine has been found whose timer has not expired
 * we need not look any further down the list.
 */
    STATIC शून्य prvCheckDelayedList( शून्य );

/*-----------------------------------------------------------*/

    आधारः_Type_t xCoRoutineCreate( cr_COROUTINE_संहिता px_Co_Routine_संहिता,
                                 UBaseType_t ux_प्राथमिकता,
                                 UBaseType_t ux_सूचकांक )
    {
        आधारः_Type_t xReturn;
        CRCB_t * pxCoRoutine;

        traceENTER_xCoRoutineCreate( px_Co_Routine_संहिता, ux_प्राथमिकता, ux_सूचकांक );

        /* Allocate the memory that will store the co-routine control block. */
        /* MISRA Ref 11.5.1 [Malloc memory assignment] */
        /* More details at: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/MISRA.md#rule-115 */
        /* coverity[misra_c_2012_rule_11_5_violation] */
        pxCoRoutine = ( CRCB_t * ) pv_पत्तनम्_Malloc( परिमाण( CRCB_t ) );

        यदि( pxCoRoutine )
        {
            /* If pxCurrentCoRoutine is NULL then this is the first co-routine to
            * be created and the co-routine data structures need initialising. */
            यदि( pxCurrentCoRoutine == रिक्त )
            {
                pxCurrentCoRoutine = pxCoRoutine;
                prvInitialiseCoRoutineLists();
            }

            /* Check the priority is within limits. */
            यदि( ux_प्राथमिकता >= configMAX_CO_ROUTINE_PRIORITIES )
            {
                ux_प्राथमिकता = configMAX_CO_ROUTINE_PRIORITIES - 1;
            }

            /* Fill out the co-routine control block from the function parameters. */
            pxCoRoutine->uxState = corINITIAL_STATE;
            pxCoRoutine->ux_प्राथमिकता = ux_प्राथमिकता;
            pxCoRoutine->ux_सूचकांक = ux_सूचकांक;
            pxCoRoutine->pxCoRoutineFunction = px_Co_Routine_संहिता;

            /* Initialise all the other co-routine control block parameters. */
            vListInitialiseItem( &( pxCoRoutine->xGenericListItem ) );
            vListInitialiseItem( &( pxCoRoutine->xEventListItem ) );

            /* Set the co-routine control block as a link back from the ListItem_t.
             * This is so we can get back to the containing CRCB from a generic item
             * in a list. */
            list_समुच्चयः_LIST_ITEM_OWNER( &( pxCoRoutine->xGenericListItem ), pxCoRoutine );
            list_समुच्चयः_LIST_ITEM_OWNER( &( pxCoRoutine->xEventListItem ), pxCoRoutine );

            /* Event lists are always in priority order. */
            list_समुच्चयः_LIST_ITEM_मानम्( &( pxCoRoutine->xEventListItem ), ( ( TickType_t ) configMAX_CO_ROUTINE_PRIORITIES - ( TickType_t ) ux_प्राथमिकता ) );

            /* Now the co-routine has been initialised it can be added to the ready
             * list at the correct priority. */
            prv_सङ्कलय_Co_Routine_गन्तव्यम्_Ready_Queue( pxCoRoutine );

            xReturn = pdPASS;
        }
        अन्यथा
        {
            xReturn = err_COULD_NOT_ALLOCATE_REQUIRED_स्मृतिः;
        }

        traceRETURN_xCoRoutineCreate( xReturn );

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    शून्य v_Co_Routine_सङ्कलय_गन्तव्यम्_Delayed_List( TickType_t x_Ticks_गन्तव्यम्_Delay,
                                     List_t * pxEventList )
    {
        TickType_t x_Time_गन्तव्यम्_Wake;

        trace_ENTER_v_Co_Routine_सङ्कलय_गन्तव्यम्_Delayed_List( x_Ticks_गन्तव्यम्_Delay, pxEventList );

        /* Calculate the time to wake - this may overflow but this is
         * not a problem. */
        x_Time_गन्तव्यम्_Wake = x_Co_Routine_Tick_गणनम् + x_Ticks_गन्तव्यम्_Delay;

        /* We must remove ourselves from the ready list before adding
         * ourselves to the blocked list as the same list item is used for
         * both lists. */
        ( शून्य ) uxListRemove( ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );

        /* The list item will be inserted in wake time order. */
        list_समुच्चयः_LIST_ITEM_मानम्( &( pxCurrentCoRoutine->xGenericListItem ), x_Time_गन्तव्यम्_Wake );

        यदि( x_Time_गन्तव्यम्_Wake < x_Co_Routine_Tick_गणनम् )
        {
            /* Wake time has overflowed.  Place this item in the
             * overflow list. */
            v_List_निवेशय( ( List_t * ) px_अतिप्रवाहः_Delayed_Co_Routine_List, ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
        }
        अन्यथा
        {
            /* The wake time has not overflowed, so we can use the
             * current block list. */
            v_List_निवेशय( ( List_t * ) pxDelayedCoRoutineList, ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
        }

        यदि( pxEventList )
        {
            /* Also add the co-routine to an event list.  If this is done then the
             * function must be called with interrupts disabled. */
            v_List_निवेशय( pxEventList, &( pxCurrentCoRoutine->xEventListItem ) );
        }

        trace_RETURN_v_Co_Routine_सङ्कलय_गन्तव्यम्_Delayed_List();
    }
/*-----------------------------------------------------------*/

    STATIC शून्य prvCheckPendingReadyList( शून्य )
    {
        /* Are there any co-routines waiting to get moved to the ready list?  These
         * are co-routines that have been readied by an ISR.  The ISR cannot access
         * the ready lists itself. */
        यावत्( list_LIST_IS_रिक्तानि( &xPendingReadyCoRoutineList ) == pdFALSE )
        {
            CRCB_t * pxUnblockedCRCB;

            /* The pending ready list can be accessed by an ISR. */
            पत्तनम्_DISABLE_INTERRUPTS();
            {
                pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_सम्बन्धि_शीर्ष_प्रविष्टिः( ( &xPendingReadyCoRoutineList ) );
                ( शून्य ) uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
            }
            पत्तनम्_ENABLE_INTERRUPTS();

            ( शून्य ) uxListRemove( &( pxUnblockedCRCB->xGenericListItem ) );
            prv_सङ्कलय_Co_Routine_गन्तव्यम्_Ready_Queue( pxUnblockedCRCB );
        }
    }
/*-----------------------------------------------------------*/

    STATIC शून्य prvCheckDelayedList( शून्य )
    {
        CRCB_t * pxCRCB;

        xPassedTicks = x_Task_Get_Tick_गणनम्() - x_चरमः_Tick_गणनम्;

        यावत्( xPassedTicks )
        {
            x_Co_Routine_Tick_गणनम्++;
            xPassedTicks--;

            /* If the tick count has overflowed we need to swap the ready lists. */
            यदि( x_Co_Routine_Tick_गणनम् == 0 )
            {
                List_t * px_अस्थायी;

                /* Tick count has overflowed so we need to swap the delay lists.  If there are
                 * any items in pxDelayedCoRoutineList here then there is an error! */
                px_अस्थायी = pxDelayedCoRoutineList;
                pxDelayedCoRoutineList = px_अतिप्रवाहः_Delayed_Co_Routine_List;
                px_अतिप्रवाहः_Delayed_Co_Routine_List = px_अस्थायी;
            }

            /* See if this tick has made a timeout expire. */
            यावत्( list_LIST_IS_रिक्तानि( pxDelayedCoRoutineList ) == pdFALSE )
            {
                pxCRCB = ( CRCB_t * ) list_GET_OWNER_सम्बन्धि_शीर्ष_प्रविष्टिः( pxDelayedCoRoutineList );

                यदि( x_Co_Routine_Tick_गणनम् < list_GET_LIST_ITEM_मानम्( &( pxCRCB->xGenericListItem ) ) )
                {
                    /* Timeout not yet expired. */
                    भङ्ग;
                }

                पत्तनम्_DISABLE_INTERRUPTS();
                {
                    /* The event could have occurred just before this critical
                     *  section.  If this is the case then the generic list item will
                     *  have been moved to the pending ready list and the following
                     *  line is still valid.  Also the pvContainer parameter will have
                     *  been set to NULL so the following lines are also valid. */
                    ( शून्य ) uxListRemove( &( pxCRCB->xGenericListItem ) );

                    /* Is the co-routine waiting on an event also? */
                    यदि( pxCRCB->xEventListItem.pxContainer )
                    {
                        ( शून्य ) uxListRemove( &( pxCRCB->xEventListItem ) );
                    }
                }
                पत्तनम्_ENABLE_INTERRUPTS();

                prv_सङ्कलय_Co_Routine_गन्तव्यम्_Ready_Queue( pxCRCB );
            }
        }

        x_चरमः_Tick_गणनम् = x_Co_Routine_Tick_गणनम्;
    }
/*-----------------------------------------------------------*/

    शून्य v_Co_Routine_कालसारणी( शून्य )
    {
        trace_ENTER_v_Co_Routine_कालसारणी();

        /* Only run a co-routine after prvInitialiseCoRoutineLists() has been
         * called.  prvInitialiseCoRoutineLists() is called automatically when a
         * co-routine is created. */
        यदि( pxDelayedCoRoutineList != रिक्त )
        {
            /* See if any co-routines readied by events need moving to the ready lists. */
            prvCheckPendingReadyList();

            /* See if any delayed co-routines have timed out. */
            prvCheckDelayedList();

            /* Find the highest priority queue that contains ready co-routines. */
            यावत्( list_LIST_IS_रिक्तानि( &( pxReadyCoRoutineLists[ ux_शिखरम्_Co_Routine_Ready_प्राथमिकता ] ) ) )
            {
                यदि( ux_शिखरम्_Co_Routine_Ready_प्राथमिकता == 0 )
                {
                    /* No more co-routines to check. */
                    प्रत्यागम;
                }

                --ux_शिखरम्_Co_Routine_Ready_प्राथमिकता;
            }

            /* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
             * of the same priority get an equal share of the processor time. */
            list_GET_OWNER_सम्बन्धि_अग्र_प्रविष्टिः( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ ux_शिखरम्_Co_Routine_Ready_प्राथमिकता ] ) );

            /* Call the co-routine. */
            ( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->ux_सूचकांक );
        }

        trace_RETURN_v_Co_Routine_कालसारणी();
    }
/*-----------------------------------------------------------*/

    STATIC शून्य prvInitialiseCoRoutineLists( शून्य )
    {
        UBaseType_t ux_प्राथमिकता;

        प्रति( ux_प्राथमिकता = 0; ux_प्राथमिकता < configMAX_CO_ROUTINE_PRIORITIES; ux_प्राथमिकता++ )
        {
            vListInitialise( ( List_t * ) &( pxReadyCoRoutineLists[ ux_प्राथमिकता ] ) );
        }

        vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
        vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
        vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );

        /* Start with pxDelayedCoRoutineList using list1 and the
         * pxOverflowDelayedCoRoutineList using list2. */
        pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
        px_अतिप्रवाहः_Delayed_Co_Routine_List = &xDelayedCoRoutineList2;
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t xCoRoutineRemoveFromEventList( ध्रुव List_t * pxEventList )
    {
        CRCB_t * pxUnblockedCRCB;
        आधारः_Type_t xReturn;

        traceENTER_xCoRoutineRemoveFromEventList( pxEventList );

        /* This function is called from within an interrupt.  It can only access
         * event lists and the pending ready list.  This function assumes that a
         * check has already been made to ensure pxEventList is not empty. */
        pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_सम्बन्धि_शीर्ष_प्रविष्टिः( pxEventList );
        ( शून्य ) uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
        v_List_निवेशय_अन्तः( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->xEventListItem ) );

        यदि( pxUnblockedCRCB->ux_प्राथमिकता >= pxCurrentCoRoutine->ux_प्राथमिकता )
        {
            xReturn = pdTRUE;
        }
        अन्यथा
        {
            xReturn = pdFALSE;
        }

        traceRETURN_xCoRoutineRemoveFromEventList( xReturn );

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

/*
 * Reset state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
    शून्य vCoRoutineResetState( शून्य )
    {
        /* Lists for ready and blocked co-routines. */
        pxDelayedCoRoutineList = रिक्त;
        px_अतिप्रवाहः_Delayed_Co_Routine_List = रिक्त;

        /* Other file private variables. */
        pxCurrentCoRoutine = रिक्त;
        ux_शिखरम्_Co_Routine_Ready_प्राथमिकता = ( UBaseType_t ) 0U;
        x_Co_Routine_Tick_गणनम् = ( TickType_t ) 0U;
        x_चरमः_Tick_गणनम् = ( TickType_t ) 0U;
        xPassedTicks = ( TickType_t ) 0U;
    }
/*-----------------------------------------------------------*/

#यदि_अन्तः /* configUSE_CO_ROUTINES != 0 */
