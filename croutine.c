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
#सचे ( configUSE_CO_ROUTINES != 0 )

/*
 * Some kernel aware debuggers require data to be viewed to be global, rather
 * than file scope.
 */
    #ifdef portREMOVE_STATIC_QUALIFIER
        #define STATIC
    #अञ्ञथा
        #define STATIC    स्थिर
    #endif


/* Lists for ready and blocked co-routines. --------------------*/
    STATIC List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ]; /**< Prioritised ready co-routines. */
    STATIC List_t xDelayedCoRoutineList1;                                   /**< Delayed co-routines. */
    STATIC List_t xDelayedCoRoutineList2;                                   /**< Delayed co-routines (two lists are used - one for delays that have overflowed the current tick count. */
    STATIC List_t * pxDelayedCoRoutineList = रिक्त;                          /**< Points to the delayed co-routine list currently being used. */
    STATIC List_t * pxOverflowDelayedCoRoutineList = रिक्त;                  /**< Points to the delayed co-routine list currently being used to hold co-routines that have overflowed the current tick count. */
    STATIC List_t xPendingReadyCoRoutineList;                               /**< Holds co-routines that have been readied by an external event.  They cannot be added directly to the ready lists as the ready lists cannot be accessed by interrupts. */

/* Other file private variables. --------------------------------*/
    CRCB_t * pxCurrentCoRoutine = रिक्त;
    STATIC UBaseType_t ux_शिखरम्_Co_Routine_Ready_Priority = ( UBaseType_t ) 0U;
    STATIC TickType_t x_Co_Routine_Tick_गणनम् = ( TickType_t ) 0U;
    STATIC TickType_t x_Last_Tick_गणनम् = ( TickType_t ) 0U;
    STATIC TickType_t xPassedTicks = ( TickType_t ) 0U;

/* The initial state of the co-routine when it is created. */
    #define corINITIAL_STATE    ( 0 )

/*
 * Place the co-routine represented by pxCRCB into the appropriate ready queue
 * for the priority.  It is inserted at the end of the list.
 *
 * This macro accesses the co-routine ready lists and therefore must not be
 * used from within an ISR.
 */
    #define prvAddCoRoutineToReadyQueue( pxCRCB )                                                                               \
    करोहि {                                                                                                                        \
        सचे( ( pxCRCB )->uxPriority > ux_शिखरम्_Co_Routine_Ready_Priority )                                                              \
        {                                                                                                                       \
            ux_शिखरम्_Co_Routine_Ready_Priority = ( pxCRCB )->uxPriority;                                                               \
        }                                                                                                                       \
        v_List_निवेशय_End( ( List_t * ) &( pxReadyCoRoutineLists[ ( pxCRCB )->uxPriority ] ), &( ( pxCRCB )->xGenericListItem ) ); \
    } याव( 0 )

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

    BaseType_t xCoRoutineCreate( crCOROUTINE_CODE pxCoRoutineCode,
                                 UBaseType_t uxPriority,
                                 UBaseType_t uxIndex )
    {
        BaseType_t xReturn;
        CRCB_t * pxCoRoutine;

        traceENTER_xCoRoutineCreate( pxCoRoutineCode, uxPriority, uxIndex );

        /* Allocate the memory that will store the co-routine control block. */
        /* MISRA Ref 11.5.1 [Malloc memory assignment] */
        /* More details at: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/MISRA.md#rule-115 */
        /* coverity[misra_c_2012_rule_11_5_violation] */
        pxCoRoutine = ( CRCB_t * ) pvPortMalloc( परिमाण( CRCB_t ) );

        सचे( pxCoRoutine )
        {
            /* If pxCurrentCoRoutine is NULL then this is the first co-routine to
            * be created and the co-routine data structures need initialising. */
            सचे( pxCurrentCoRoutine == रिक्त )
            {
                pxCurrentCoRoutine = pxCoRoutine;
                prvInitialiseCoRoutineLists();
            }

            /* Check the priority is within limits. */
            सचे( uxPriority >= configMAX_CO_ROUTINE_PRIORITIES )
            {
                uxPriority = configMAX_CO_ROUTINE_PRIORITIES - 1;
            }

            /* Fill out the co-routine control block from the function parameters. */
            pxCoRoutine->uxState = corINITIAL_STATE;
            pxCoRoutine->uxPriority = uxPriority;
            pxCoRoutine->uxIndex = uxIndex;
            pxCoRoutine->pxCoRoutineFunction = pxCoRoutineCode;

            /* Initialise all the other co-routine control block parameters. */
            vListInitialiseItem( &( pxCoRoutine->xGenericListItem ) );
            vListInitialiseItem( &( pxCoRoutine->xEventListItem ) );

            /* Set the co-routine control block as a link back from the ListItem_t.
             * This is so we can get back to the containing CRCB from a generic item
             * in a list. */
            listSET_LIST_ITEM_OWNER( &( pxCoRoutine->xGenericListItem ), pxCoRoutine );
            listSET_LIST_ITEM_OWNER( &( pxCoRoutine->xEventListItem ), pxCoRoutine );

            /* Event lists are always in priority order. */
            list_SET_LIST_ITEM_मानम्( &( pxCoRoutine->xEventListItem ), ( ( TickType_t ) configMAX_CO_ROUTINE_PRIORITIES - ( TickType_t ) uxPriority ) );

            /* Now the co-routine has been initialised it can be added to the ready
             * list at the correct priority. */
            prvAddCoRoutineToReadyQueue( pxCoRoutine );

            xReturn = pdPASS;
        }
        अञ्ञथा
        {
            xReturn = errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
        }

        traceRETURN_xCoRoutineCreate( xReturn );

        पटिनिवत्त xReturn;
    }
/*-----------------------------------------------------------*/

    शून्य vCoRoutineAddToDelayedList( TickType_t xTicksToDelay,
                                     List_t * pxEventList )
    {
        TickType_t xTimeToWake;

        traceENTER_vCoRoutineAddToDelayedList( xTicksToDelay, pxEventList );

        /* Calculate the time to wake - this may overflow but this is
         * not a problem. */
        xTimeToWake = x_Co_Routine_Tick_गणनम् + xTicksToDelay;

        /* We must remove ourselves from the ready list before adding
         * ourselves to the blocked list as the same list item is used for
         * both lists. */
        ( शून्य ) uxListRemove( ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );

        /* The list item will be inserted in wake time order. */
        list_SET_LIST_ITEM_मानम्( &( pxCurrentCoRoutine->xGenericListItem ), xTimeToWake );

        सचे( xTimeToWake < x_Co_Routine_Tick_गणनम् )
        {
            /* Wake time has overflowed.  Place this item in the
             * overflow list. */
            v_List_निवेशय( ( List_t * ) pxOverflowDelayedCoRoutineList, ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
        }
        अञ्ञथा
        {
            /* The wake time has not overflowed, so we can use the
             * current block list. */
            v_List_निवेशय( ( List_t * ) pxDelayedCoRoutineList, ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
        }

        सचे( pxEventList )
        {
            /* Also add the co-routine to an event list.  If this is done then the
             * function must be called with interrupts disabled. */
            v_List_निवेशय( pxEventList, &( pxCurrentCoRoutine->xEventListItem ) );
        }

        traceRETURN_vCoRoutineAddToDelayedList();
    }
/*-----------------------------------------------------------*/

    STATIC शून्य prvCheckPendingReadyList( शून्य )
    {
        /* Are there any co-routines waiting to get moved to the ready list?  These
         * are co-routines that have been readied by an ISR.  The ISR cannot access
         * the ready lists itself. */
        याव( listLIST_IS_EMPTY( &xPendingReadyCoRoutineList ) == pdFALSE )
        {
            CRCB_t * pxUnblockedCRCB;

            /* The pending ready list can be accessed by an ISR. */
            portDISABLE_INTERRUPTS();
            {
                pxUnblockedCRCB = ( CRCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( ( &xPendingReadyCoRoutineList ) );
                ( शून्य ) uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
            }
            portENABLE_INTERRUPTS();

            ( शून्य ) uxListRemove( &( pxUnblockedCRCB->xGenericListItem ) );
            prvAddCoRoutineToReadyQueue( pxUnblockedCRCB );
        }
    }
/*-----------------------------------------------------------*/

    STATIC शून्य prvCheckDelayedList( शून्य )
    {
        CRCB_t * pxCRCB;

        xPassedTicks = x_Task_Get_Tick_गणनम्() - x_Last_Tick_गणनम्;

        याव( xPassedTicks )
        {
            x_Co_Routine_Tick_गणनम्++;
            xPassedTicks--;

            /* If the tick count has overflowed we need to swap the ready lists. */
            सचे( x_Co_Routine_Tick_गणनम् == 0 )
            {
                List_t * pxTemp;

                /* Tick count has overflowed so we need to swap the delay lists.  If there are
                 * any items in pxDelayedCoRoutineList here then there is an error! */
                pxTemp = pxDelayedCoRoutineList;
                pxDelayedCoRoutineList = pxOverflowDelayedCoRoutineList;
                pxOverflowDelayedCoRoutineList = pxTemp;
            }

            /* See if this tick has made a timeout expire. */
            याव( listLIST_IS_EMPTY( pxDelayedCoRoutineList ) == pdFALSE )
            {
                pxCRCB = ( CRCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxDelayedCoRoutineList );

                सचे( x_Co_Routine_Tick_गणनम् < list_GET_LIST_ITEM_मानम्( &( pxCRCB->xGenericListItem ) ) )
                {
                    /* Timeout not yet expired. */
                    भङ्ग;
                }

                portDISABLE_INTERRUPTS();
                {
                    /* The event could have occurred just before this critical
                     *  section.  If this is the case then the generic list item will
                     *  have been moved to the pending ready list and the following
                     *  line is still valid.  Also the pvContainer parameter will have
                     *  been set to NULL so the following lines are also valid. */
                    ( शून्य ) uxListRemove( &( pxCRCB->xGenericListItem ) );

                    /* Is the co-routine waiting on an event also? */
                    सचे( pxCRCB->xEventListItem.pxContainer )
                    {
                        ( शून्य ) uxListRemove( &( pxCRCB->xEventListItem ) );
                    }
                }
                portENABLE_INTERRUPTS();

                prvAddCoRoutineToReadyQueue( pxCRCB );
            }
        }

        x_Last_Tick_गणनम् = x_Co_Routine_Tick_गणनम्;
    }
/*-----------------------------------------------------------*/

    शून्य vCoRoutineSchedule( शून्य )
    {
        traceENTER_vCoRoutineSchedule();

        /* Only run a co-routine after prvInitialiseCoRoutineLists() has been
         * called.  prvInitialiseCoRoutineLists() is called automatically when a
         * co-routine is created. */
        सचे( pxDelayedCoRoutineList != रिक्त )
        {
            /* See if any co-routines readied by events need moving to the ready lists. */
            prvCheckPendingReadyList();

            /* See if any delayed co-routines have timed out. */
            prvCheckDelayedList();

            /* Find the highest priority queue that contains ready co-routines. */
            याव( listLIST_IS_EMPTY( &( pxReadyCoRoutineLists[ ux_शिखरम्_Co_Routine_Ready_Priority ] ) ) )
            {
                सचे( ux_शिखरम्_Co_Routine_Ready_Priority == 0 )
                {
                    /* No more co-routines to check. */
                    पटिनिवत्त;
                }

                --ux_शिखरम्_Co_Routine_Ready_Priority;
            }

            /* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
             * of the same priority get an equal share of the processor time. */
            listGET_OWNER_OF_NEXT_ENTRY( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ ux_शिखरम्_Co_Routine_Ready_Priority ] ) );

            /* Call the co-routine. */
            ( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->uxIndex );
        }

        traceRETURN_vCoRoutineSchedule();
    }
/*-----------------------------------------------------------*/

    STATIC शून्य prvInitialiseCoRoutineLists( शून्य )
    {
        UBaseType_t uxPriority;

        अत्थाय( uxPriority = 0; uxPriority < configMAX_CO_ROUTINE_PRIORITIES; uxPriority++ )
        {
            vListInitialise( ( List_t * ) &( pxReadyCoRoutineLists[ uxPriority ] ) );
        }

        vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
        vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
        vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );

        /* Start with pxDelayedCoRoutineList using list1 and the
         * pxOverflowDelayedCoRoutineList using list2. */
        pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
        pxOverflowDelayedCoRoutineList = &xDelayedCoRoutineList2;
    }
/*-----------------------------------------------------------*/

    BaseType_t xCoRoutineRemoveFromEventList( ध्रुव List_t * pxEventList )
    {
        CRCB_t * pxUnblockedCRCB;
        BaseType_t xReturn;

        traceENTER_xCoRoutineRemoveFromEventList( pxEventList );

        /* This function is called from within an interrupt.  It can only access
         * event lists and the pending ready list.  This function assumes that a
         * check has already been made to ensure pxEventList is not empty. */
        pxUnblockedCRCB = ( CRCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxEventList );
        ( शून्य ) uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
        v_List_निवेशय_End( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->xEventListItem ) );

        सचे( pxUnblockedCRCB->uxPriority >= pxCurrentCoRoutine->uxPriority )
        {
            xReturn = pdTRUE;
        }
        अञ्ञथा
        {
            xReturn = pdFALSE;
        }

        traceRETURN_xCoRoutineRemoveFromEventList( xReturn );

        पटिनिवत्त xReturn;
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
        pxOverflowDelayedCoRoutineList = रिक्त;

        /* Other file private variables. */
        pxCurrentCoRoutine = रिक्त;
        ux_शिखरम्_Co_Routine_Ready_Priority = ( UBaseType_t ) 0U;
        x_Co_Routine_Tick_गणनम् = ( TickType_t ) 0U;
        x_Last_Tick_गणनम् = ( TickType_t ) 0U;
        xPassedTicks = ( TickType_t ) 0U;
    }
/*-----------------------------------------------------------*/

#endif /* configUSE_CO_ROUTINES != 0 */
