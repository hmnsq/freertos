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

#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "croutine.h"

/* Remove the whole file if co-routines are not being used. */
#अगर ( configUSE_CO_ROUTINES != 0 )

/*
 * Some kernel aware debuggers require data to be viewed to be global, rather
 * than file scope.
 */
    #अगर_घोषित portREMOVE_STATIC_QUALIFIER
        #घोषणा STATIC
    #अन्यथा
        #घोषणा STATIC    अटल
    #पूर्ण_अगर


/* Lists for ready and blocked co-routines. --------------------*/
    STATIC List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ]; /**< Prioritised ready co-routines. */
    STATIC List_t xDelayedCoRoutineList1;                                   /**< Delayed co-routines. */
    STATIC List_t xDelayedCoRoutineList2;                                   /**< Delayed co-routines (two lists are used - one for delays that have overflowed the current tick count. */
    STATIC List_t * pxDelayedCoRoutineList = शून्य;                          /**< Points to the delayed co-routine list currently being used. */
    STATIC List_t * pxOverflowDelayedCoRoutineList = शून्य;                  /**< Points to the delayed co-routine list currently being used to hold co-routines that have overflowed the current tick count. */
    STATIC List_t xPendingReadyCoRoutineList;                               /**< Holds co-routines that have been readied by an external event.  They cannot be added directly to the ready lists as the ready lists cannot be accessed by interrupts. */

/* Other file private variables. --------------------------------*/
    CRCB_t * pxCurrentCoRoutine = शून्य;
    STATIC UBaseType_t ux_शीर्ष_Co_Routine_Ready_Priority = ( UBaseType_t ) 0U;
    STATIC TickType_t x_Co_Routine_Tick_गिनती = ( TickType_t ) 0U;
    STATIC TickType_t x_Last_Tick_गिनती = ( TickType_t ) 0U;
    STATIC TickType_t xPassedTicks = ( TickType_t ) 0U;

/* The initial state of the co-routine when it is created. */
    #घोषणा corINITIAL_STATE    ( 0 )

/*
 * Place the co-routine represented by pxCRCB into the appropriate ready queue
 * for the priority.  It is inserted at the end of the list.
 *
 * This macro accesses the co-routine ready lists and therefore must not be
 * used from within an ISR.
 */
    #घोषणा prvAddCoRoutineToReadyQueue( pxCRCB )                                                                               \
    करो {                                                                                                                        \
        अगर( ( pxCRCB )->uxPriority > ux_शीर्ष_Co_Routine_Ready_Priority )                                                              \
        {                                                                                                                       \
            ux_शीर्ष_Co_Routine_Ready_Priority = ( pxCRCB )->uxPriority;                                                               \
        }                                                                                                                       \
        v_List_जोड़ो_End( ( List_t * ) &( pxReadyCoRoutineLists[ ( pxCRCB )->uxPriority ] ), &( ( pxCRCB )->xGenericListItem ) ); \
    } जबतक( 0 )

/*
 * Utility to ready all the lists used by the scheduler.  This is called
 * automatically upon the creation of the first co-routine.
 */
    STATIC व्योम prvInitialiseCoRoutineLists( व्योम );

/*
 * Co-routines that are readied by an interrupt cannot be placed directly into
 * the ready lists (there is no mutual exclusion).  Instead they are placed in
 * in the pending ready list in order that they can later be moved to the ready
 * list by the co-routine scheduler.
 */
    STATIC व्योम prvCheckPendingReadyList( व्योम );

/*
 * Macro that looks at the list of co-routines that are currently delayed to
 * see if any require waking.
 *
 * Co-routines are stored in the queue in the order of their wake time -
 * meaning once one co-routine has been found whose timer has not expired
 * we need not look any further down the list.
 */
    STATIC व्योम prvCheckDelayedList( व्योम );

/*-----------------------------------------------------------*/

    BaseType_t xCoRoutineCreate( crCOROUTINE_CODE pxCoRoutineCode,
                                 UBaseType_t uxPriority,
                                 UBaseType_t ux_सूचकांक )
    {
        BaseType_t xReturn;
        CRCB_t * pxCoRoutine;

        traceENTER_xCoRoutineCreate( pxCoRoutineCode, uxPriority, ux_सूचकांक );

        /* Allocate the memory that will store the co-routine control block. */
        /* MISRA Ref 11.5.1 [Malloc memory assignment] */
        /* More details at: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/MISRA.md#rule-115 */
        /* coverity[misra_c_2012_rule_11_5_violation] */
        pxCoRoutine = ( CRCB_t * ) pvPortMalloc( माप( CRCB_t ) );

        अगर( pxCoRoutine )
        {
            /* If pxCurrentCoRoutine is NULL then this is the first co-routine to
            * be created and the co-routine data structures need initialising. */
            अगर( pxCurrentCoRoutine == शून्य )
            {
                pxCurrentCoRoutine = pxCoRoutine;
                prvInitialiseCoRoutineLists();
            }

            /* Check the priority is within limits. */
            अगर( uxPriority >= configMAX_CO_ROUTINE_PRIORITIES )
            {
                uxPriority = configMAX_CO_ROUTINE_PRIORITIES - 1;
            }

            /* Fill out the co-routine control block from the function parameters. */
            pxCoRoutine->uxState = corINITIAL_STATE;
            pxCoRoutine->uxPriority = uxPriority;
            pxCoRoutine->ux_सूचकांक = ux_सूचकांक;
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
            list_SET_LIST_ITEM_मूल्य( &( pxCoRoutine->xEventListItem ), ( ( TickType_t ) configMAX_CO_ROUTINE_PRIORITIES - ( TickType_t ) uxPriority ) );

            /* Now the co-routine has been initialised it can be added to the ready
             * list at the correct priority. */
            prvAddCoRoutineToReadyQueue( pxCoRoutine );

            xReturn = pdPASS;
        }
        अन्यथा
        {
            xReturn = errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
        }

        traceRETURN_xCoRoutineCreate( xReturn );

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    व्योम vCoRoutineAddToDelayedList( TickType_t xTicksToDelay,
                                     List_t * pxEventList )
    {
        TickType_t xTimeToWake;

        traceENTER_vCoRoutineAddToDelayedList( xTicksToDelay, pxEventList );

        /* Calculate the time to wake - this may overflow but this is
         * not a problem. */
        xTimeToWake = x_Co_Routine_Tick_गिनती + xTicksToDelay;

        /* We must remove ourselves from the ready list before adding
         * ourselves to the blocked list as the same list item is used for
         * both lists. */
        ( व्योम ) uxListRemove( ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );

        /* The list item will be inserted in wake time order. */
        list_SET_LIST_ITEM_मूल्य( &( pxCurrentCoRoutine->xGenericListItem ), xTimeToWake );

        अगर( xTimeToWake < x_Co_Routine_Tick_गिनती )
        {
            /* Wake time has overflowed.  Place this item in the
             * overflow list. */
            v_List_जोड़ो( ( List_t * ) pxOverflowDelayedCoRoutineList, ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
        }
        अन्यथा
        {
            /* The wake time has not overflowed, so we can use the
             * current block list. */
            v_List_जोड़ो( ( List_t * ) pxDelayedCoRoutineList, ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
        }

        अगर( pxEventList )
        {
            /* Also add the co-routine to an event list.  If this is done then the
             * function must be called with interrupts disabled. */
            v_List_जोड़ो( pxEventList, &( pxCurrentCoRoutine->xEventListItem ) );
        }

        traceRETURN_vCoRoutineAddToDelayedList();
    }
/*-----------------------------------------------------------*/

    STATIC व्योम prvCheckPendingReadyList( व्योम )
    {
        /* Are there any co-routines waiting to get moved to the ready list?  These
         * are co-routines that have been readied by an ISR.  The ISR cannot access
         * the ready lists itself. */
        जबतक( listLIST_IS_EMPTY( &xPendingReadyCoRoutineList ) == pdFALSE )
        {
            CRCB_t * pxUnblockedCRCB;

            /* The pending ready list can be accessed by an ISR. */
            portDISABLE_INTERRUPTS();
            {
                pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_OF_शीर्ष_ENTRY( ( &xPendingReadyCoRoutineList ) );
                ( व्योम ) uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
            }
            portENABLE_INTERRUPTS();

            ( व्योम ) uxListRemove( &( pxUnblockedCRCB->xGenericListItem ) );
            prvAddCoRoutineToReadyQueue( pxUnblockedCRCB );
        }
    }
/*-----------------------------------------------------------*/

    STATIC व्योम prvCheckDelayedList( व्योम )
    {
        CRCB_t * pxCRCB;

        xPassedTicks = x_Task_Get_Tick_गिनती() - x_Last_Tick_गिनती;

        जबतक( xPassedTicks )
        {
            x_Co_Routine_Tick_गिनती++;
            xPassedTicks--;

            /* If the tick count has overflowed we need to swap the ready lists. */
            अगर( x_Co_Routine_Tick_गिनती == 0 )
            {
                List_t * px_अस्थायी;

                /* Tick count has overflowed so we need to swap the delay lists.  If there are
                 * any items in pxDelayedCoRoutineList here then there is an error! */
                px_अस्थायी = pxDelayedCoRoutineList;
                pxDelayedCoRoutineList = pxOverflowDelayedCoRoutineList;
                pxOverflowDelayedCoRoutineList = px_अस्थायी;
            }

            /* See if this tick has made a timeout expire. */
            जबतक( listLIST_IS_EMPTY( pxDelayedCoRoutineList ) == pdFALSE )
            {
                pxCRCB = ( CRCB_t * ) list_GET_OWNER_OF_शीर्ष_ENTRY( pxDelayedCoRoutineList );

                अगर( x_Co_Routine_Tick_गिनती < list_GET_LIST_ITEM_मूल्य( &( pxCRCB->xGenericListItem ) ) )
                {
                    /* Timeout not yet expired. */
                    अवरोध;
                }

                portDISABLE_INTERRUPTS();
                {
                    /* The event could have occurred just before this critical
                     *  section.  If this is the case then the generic list item will
                     *  have been moved to the pending ready list and the following
                     *  line is still valid.  Also the pvContainer parameter will have
                     *  been set to NULL so the following lines are also valid. */
                    ( व्योम ) uxListRemove( &( pxCRCB->xGenericListItem ) );

                    /* Is the co-routine waiting on an event also? */
                    अगर( pxCRCB->xEventListItem.pxContainer )
                    {
                        ( व्योम ) uxListRemove( &( pxCRCB->xEventListItem ) );
                    }
                }
                portENABLE_INTERRUPTS();

                prvAddCoRoutineToReadyQueue( pxCRCB );
            }
        }

        x_Last_Tick_गिनती = x_Co_Routine_Tick_गिनती;
    }
/*-----------------------------------------------------------*/

    व्योम vCoRoutineSchedule( व्योम )
    {
        traceENTER_vCoRoutineSchedule();

        /* Only run a co-routine after prvInitialiseCoRoutineLists() has been
         * called.  prvInitialiseCoRoutineLists() is called automatically when a
         * co-routine is created. */
        अगर( pxDelayedCoRoutineList != शून्य )
        {
            /* See if any co-routines readied by events need moving to the ready lists. */
            prvCheckPendingReadyList();

            /* See if any delayed co-routines have timed out. */
            prvCheckDelayedList();

            /* Find the highest priority queue that contains ready co-routines. */
            जबतक( listLIST_IS_EMPTY( &( pxReadyCoRoutineLists[ ux_शीर्ष_Co_Routine_Ready_Priority ] ) ) )
            {
                अगर( ux_शीर्ष_Co_Routine_Ready_Priority == 0 )
                {
                    /* No more co-routines to check. */
                    वापस;
                }

                --ux_शीर्ष_Co_Routine_Ready_Priority;
            }

            /* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
             * of the same priority get an equal share of the processor time. */
            list_GET_OWNER_OF_अग्र_ENTRY( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ ux_शीर्ष_Co_Routine_Ready_Priority ] ) );

            /* Call the co-routine. */
            ( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->ux_सूचकांक );
        }

        traceRETURN_vCoRoutineSchedule();
    }
/*-----------------------------------------------------------*/

    STATIC व्योम prvInitialiseCoRoutineLists( व्योम )
    {
        UBaseType_t uxPriority;

        क्रम( uxPriority = 0; uxPriority < configMAX_CO_ROUTINE_PRIORITIES; uxPriority++ )
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

    BaseType_t xCoRoutineRemoveFromEventList( स्थिर List_t * pxEventList )
    {
        CRCB_t * pxUnblockedCRCB;
        BaseType_t xReturn;

        traceENTER_xCoRoutineRemoveFromEventList( pxEventList );

        /* This function is called from within an interrupt.  It can only access
         * event lists and the pending ready list.  This function assumes that a
         * check has already been made to ensure pxEventList is not empty. */
        pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_OF_शीर्ष_ENTRY( pxEventList );
        ( व्योम ) uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
        v_List_जोड़ो_End( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->xEventListItem ) );

        अगर( pxUnblockedCRCB->uxPriority >= pxCurrentCoRoutine->uxPriority )
        {
            xReturn = pdTRUE;
        }
        अन्यथा
        {
            xReturn = pdFALSE;
        }

        traceRETURN_xCoRoutineRemoveFromEventList( xReturn );

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

/*
 * Reset state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
    व्योम vCoRoutineResetState( व्योम )
    {
        /* Lists for ready and blocked co-routines. */
        pxDelayedCoRoutineList = शून्य;
        pxOverflowDelayedCoRoutineList = शून्य;

        /* Other file private variables. */
        pxCurrentCoRoutine = शून्य;
        ux_शीर्ष_Co_Routine_Ready_Priority = ( UBaseType_t ) 0U;
        x_Co_Routine_Tick_गिनती = ( TickType_t ) 0U;
        x_Last_Tick_गिनती = ( TickType_t ) 0U;
        xPassedTicks = ( TickType_t ) 0U;
    }
/*-----------------------------------------------------------*/

#पूर्ण_अगर /* configUSE_CO_ROUTINES != 0 */
