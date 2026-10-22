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

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "croutine.h"

/* Remove the whole file if co-routines are not being used. */
#ಆದರೆ ( configUSE_CO_ROUTINES != 0 )

/*
 * Some kernel aware debuggers require data to be viewed to be global, rather
 * than file scope.
 */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ಪೋರ್ಟ್_REMOVE_STATIC_QUALIFIER
        #ವ್ಯಾಖ್ಯಾನಿಸು STATIC
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು STATIC    ಸ್ಥಿರ
    #ಆದರೆ_ಅಂತ್ಯ


/* Lists for ready and blocked co-routines. --------------------*/
    STATIC List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ]; /**< Prioritised ready co-routines. */
    STATIC List_t xDelayedCoRoutineList1;                                   /**< Delayed co-routines. */
    STATIC List_t xDelayedCoRoutineList2;                                   /**< Delayed co-routines (two lists are used - one for delays that have overflowed the current tick count. */
    STATIC List_t * pxDelayedCoRoutineList = ಖಾಲಿ;                          /**< Points to the delayed co-routine list currently being used. */
    STATIC List_t * px_ಅತಿಪ್ರವಾಹ_Delayed_Co_Routine_List = ಖಾಲಿ;                  /**< Points to the delayed co-routine list currently being used to hold co-routines that have overflowed the current tick count. */
    STATIC List_t xPendingReadyCoRoutineList;                               /**< Holds co-routines that have been readied by an external event.  They cannot be added directly to the ready lists as the ready lists cannot be accessed by interrupts. */

/* Other file private variables. --------------------------------*/
    CRCB_t * pxCurrentCoRoutine = ಖಾಲಿ;
    STATIC UBaseType_t ux_ತುದಿ_Co_Routine_Ready_ಆದ್ಯತೆ = ( UBaseType_t ) 0U;
    STATIC TickType_t x_Co_Routine_Tick_ಎಣಿಕೆ = ( TickType_t ) 0U;
    STATIC TickType_t x_ಕೊನೆಯ_Tick_ಎಣಿಕೆ = ( TickType_t ) 0U;
    STATIC TickType_t xPassedTicks = ( TickType_t ) 0U;

/* The initial state of the co-routine when it is created. */
    #ವ್ಯಾಖ್ಯಾನಿಸು corINITIAL_STATE    ( 0 )

/*
 * Place the co-routine represented by pxCRCB into the appropriate ready queue
 * for the priority.  It is inserted at the end of the list.
 *
 * This macro accesses the co-routine ready lists and therefore must not be
 * used from within an ISR.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು prv_ಕೂಡಿಸು_Co_Routine_ಗಮ್ಯ_Ready_ಸರತಿ( pxCRCB )                                                                               \
    ಮಾಡು {                                                                                                                        \
        ಆದರೆ( ( pxCRCB )->ux_ಆದ್ಯತೆ > ux_ತುದಿ_Co_Routine_Ready_ಆದ್ಯತೆ )                                                              \
        {                                                                                                                       \
            ux_ತುದಿ_Co_Routine_Ready_ಆದ್ಯತೆ = ( pxCRCB )->ux_ಆದ್ಯತೆ;                                                               \
        }                                                                                                                       \
        v_List_ಸೇರಿಸು_ಕೊನೆ( ( List_t * ) &( pxReadyCoRoutineLists[ ( pxCRCB )->ux_ಆದ್ಯತೆ ] ), &( ( pxCRCB )->x_Generic_List_ಅಂಶ ) ); \
    } ಆಗ( 0 )

/*
 * Utility to ready all the lists used by the scheduler.  This is called
 * automatically upon the creation of the first co-routine.
 */
    STATIC ಶೂನ್ಯ prvInitialiseCoRoutineLists( ಶೂನ್ಯ );

/*
 * Co-routines that are readied by an interrupt cannot be placed directly into
 * the ready lists (there is no mutual exclusion).  Instead they are placed in
 * in the pending ready list in order that they can later be moved to the ready
 * list by the co-routine scheduler.
 */
    STATIC ಶೂನ್ಯ prvCheckPendingReadyList( ಶೂನ್ಯ );

/*
 * Macro that looks at the list of co-routines that are currently delayed to
 * see if any require waking.
 *
 * Co-routines are stored in the queue in the order of their wake time -
 * meaning once one co-routine has been found whose timer has not expired
 * we need not look any further down the list.
 */
    STATIC ಶೂನ್ಯ prvCheckDelayedList( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

    ತಳ_Type_t xCoRoutineCreate( cr_COROUTINE_ಸಂಕೇತ px_Co_Routine_ಸಂಕೇತ,
                                 UBaseType_t ux_ಆದ್ಯತೆ,
                                 UBaseType_t ux_ಸೂಚ್ಯಂಕ )
    {
        ತಳ_Type_t xReturn;
        CRCB_t * pxCoRoutine;

        traceENTER_xCoRoutineCreate( px_Co_Routine_ಸಂಕೇತ, ux_ಆದ್ಯತೆ, ux_ಸೂಚ್ಯಂಕ );

        /* Allocate the memory that will store the co-routine control block. */
        /* MISRA Ref 11.5.1 [Malloc memory assignment] */
        /* More details at: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/MISRA.md#rule-115 */
        /* coverity[misra_c_2012_rule_11_5_violation] */
        pxCoRoutine = ( CRCB_t * ) pv_ಪೋರ್ಟ್_Malloc( ಗಾತ್ರ( CRCB_t ) );

        ಆದರೆ( pxCoRoutine )
        {
            /* If pxCurrentCoRoutine is NULL then this is the first co-routine to
            * be created and the co-routine data structures need initialising. */
            ಆದರೆ( pxCurrentCoRoutine == ಖಾಲಿ )
            {
                pxCurrentCoRoutine = pxCoRoutine;
                prvInitialiseCoRoutineLists();
            }

            /* Check the priority is within limits. */
            ಆದರೆ( ux_ಆದ್ಯತೆ >= configMAX_CO_ROUTINE_PRIORITIES )
            {
                ux_ಆದ್ಯತೆ = configMAX_CO_ROUTINE_PRIORITIES - 1;
            }

            /* Fill out the co-routine control block from the function parameters. */
            pxCoRoutine->uxState = corINITIAL_STATE;
            pxCoRoutine->ux_ಆದ್ಯತೆ = ux_ಆದ್ಯತೆ;
            pxCoRoutine->ux_ಸೂಚ್ಯಂಕ = ux_ಸೂಚ್ಯಂಕ;
            pxCoRoutine->pxCoRoutineFunction = px_Co_Routine_ಸಂಕೇತ;

            /* Initialise all the other co-routine control block parameters. */
            v_List_Initialise_ಅಂಶ( &( pxCoRoutine->x_Generic_List_ಅಂಶ ) );
            v_List_Initialise_ಅಂಶ( &( pxCoRoutine->x_Event_List_ಅಂಶ ) );

            /* Set the co-routine control block as a link back from the ListItem_t.
             * This is so we can get back to the containing CRCB from a generic item
             * in a list. */
            list_ಗಣ_LIST_ಅಂಶ_OWNER( &( pxCoRoutine->x_Generic_List_ಅಂಶ ), pxCoRoutine );
            list_ಗಣ_LIST_ಅಂಶ_OWNER( &( pxCoRoutine->x_Event_List_ಅಂಶ ), pxCoRoutine );

            /* Event lists are always in priority order. */
            list_ಗಣ_LIST_ಅಂಶ_ಮೌಲ್ಯ( &( pxCoRoutine->x_Event_List_ಅಂಶ ), ( ( TickType_t ) configMAX_CO_ROUTINE_PRIORITIES - ( TickType_t ) ux_ಆದ್ಯತೆ ) );

            /* Now the co-routine has been initialised it can be added to the ready
             * list at the correct priority. */
            prv_ಕೂಡಿಸು_Co_Routine_ಗಮ್ಯ_Ready_ಸರತಿ( pxCoRoutine );

            xReturn = pdPASS;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = err_COULD_NOT_ALLOCATE_REQUIRED_ಸ್ಮರಣೆ;
        }

        traceRETURN_xCoRoutineCreate( xReturn );

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ v_Co_Routine_ಕೂಡಿಸು_ಗಮ್ಯ_Delayed_List( TickType_t x_Ticks_ಗಮ್ಯ_Delay,
                                     List_t * pxEventList )
    {
        TickType_t x_ಸಮಯ_ಗಮ್ಯ_Wake;

        trace_ENTER_v_Co_Routine_ಕೂಡಿಸು_ಗಮ್ಯ_Delayed_List( x_Ticks_ಗಮ್ಯ_Delay, pxEventList );

        /* Calculate the time to wake - this may overflow but this is
         * not a problem. */
        x_ಸಮಯ_ಗಮ್ಯ_Wake = x_Co_Routine_Tick_ಎಣಿಕೆ + x_Ticks_ಗಮ್ಯ_Delay;

        /* We must remove ourselves from the ready list before adding
         * ourselves to the blocked list as the same list item is used for
         * both lists. */
        ( ಶೂನ್ಯ ) uxListRemove( ( List_ಅಂಶ_t * ) &( pxCurrentCoRoutine->x_Generic_List_ಅಂಶ ) );

        /* The list item will be inserted in wake time order. */
        list_ಗಣ_LIST_ಅಂಶ_ಮೌಲ್ಯ( &( pxCurrentCoRoutine->x_Generic_List_ಅಂಶ ), x_ಸಮಯ_ಗಮ್ಯ_Wake );

        ಆದರೆ( x_ಸಮಯ_ಗಮ್ಯ_Wake < x_Co_Routine_Tick_ಎಣಿಕೆ )
        {
            /* Wake time has overflowed.  Place this item in the
             * overflow list. */
            v_List_ಸೇರಿಸು( ( List_t * ) px_ಅತಿಪ್ರವಾಹ_Delayed_Co_Routine_List, ( List_ಅಂಶ_t * ) &( pxCurrentCoRoutine->x_Generic_List_ಅಂಶ ) );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* The wake time has not overflowed, so we can use the
             * current block list. */
            v_List_ಸೇರಿಸು( ( List_t * ) pxDelayedCoRoutineList, ( List_ಅಂಶ_t * ) &( pxCurrentCoRoutine->x_Generic_List_ಅಂಶ ) );
        }

        ಆದರೆ( pxEventList )
        {
            /* Also add the co-routine to an event list.  If this is done then the
             * function must be called with interrupts disabled. */
            v_List_ಸೇರಿಸು( pxEventList, &( pxCurrentCoRoutine->x_Event_List_ಅಂಶ ) );
        }

        trace_RETURN_v_Co_Routine_ಕೂಡಿಸು_ಗಮ್ಯ_Delayed_List();
    }
/*-----------------------------------------------------------*/

    STATIC ಶೂನ್ಯ prvCheckPendingReadyList( ಶೂನ್ಯ )
    {
        /* Are there any co-routines waiting to get moved to the ready list?  These
         * are co-routines that have been readied by an ISR.  The ISR cannot access
         * the ready lists itself. */
        ಆಗ( list_LIST_IS_ಖಾಲಿಗಳು( &xPendingReadyCoRoutineList ) == pdFALSE )
        {
            CRCB_t * pxUnblockedCRCB;

            /* The pending ready list can be accessed by an ISR. */
            ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
            {
                pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_ದ_ತಲೆ_ನಮೂದು( ( &xPendingReadyCoRoutineList ) );
                ( ಶೂನ್ಯ ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_ಅಂಶ ) );
            }
            ಪೋರ್ಟ್_ENABLE_INTERRUPTS();

            ( ಶೂನ್ಯ ) uxListRemove( &( pxUnblockedCRCB->x_Generic_List_ಅಂಶ ) );
            prv_ಕೂಡಿಸು_Co_Routine_ಗಮ್ಯ_Ready_ಸರತಿ( pxUnblockedCRCB );
        }
    }
/*-----------------------------------------------------------*/

    STATIC ಶೂನ್ಯ prvCheckDelayedList( ಶೂನ್ಯ )
    {
        CRCB_t * pxCRCB;

        xPassedTicks = x_Task_Get_Tick_ಎಣಿಕೆ() - x_ಕೊನೆಯ_Tick_ಎಣಿಕೆ;

        ಆಗ( xPassedTicks )
        {
            x_Co_Routine_Tick_ಎಣಿಕೆ++;
            xPassedTicks--;

            /* If the tick count has overflowed we need to swap the ready lists. */
            ಆದರೆ( x_Co_Routine_Tick_ಎಣಿಕೆ == 0 )
            {
                List_t * px_ತಾತ್ಕಾಲಿಕ;

                /* Tick count has overflowed so we need to swap the delay lists.  If there are
                 * any items in pxDelayedCoRoutineList here then there is an error! */
                px_ತಾತ್ಕಾಲಿಕ = pxDelayedCoRoutineList;
                pxDelayedCoRoutineList = px_ಅತಿಪ್ರವಾಹ_Delayed_Co_Routine_List;
                px_ಅತಿಪ್ರವಾಹ_Delayed_Co_Routine_List = px_ತಾತ್ಕಾಲಿಕ;
            }

            /* See if this tick has made a timeout expire. */
            ಆಗ( list_LIST_IS_ಖಾಲಿಗಳು( pxDelayedCoRoutineList ) == pdFALSE )
            {
                pxCRCB = ( CRCB_t * ) list_GET_OWNER_ದ_ತಲೆ_ನಮೂದು( pxDelayedCoRoutineList );

                ಆದರೆ( x_Co_Routine_Tick_ಎಣಿಕೆ < list_GET_LIST_ಅಂಶ_ಮೌಲ್ಯ( &( pxCRCB->x_Generic_List_ಅಂಶ ) ) )
                {
                    /* Timeout not yet expired. */
                    ನಿಲ್ಲಿಸು;
                }

                ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
                {
                    /* The event could have occurred just before this critical
                     *  section.  If this is the case then the generic list item will
                     *  have been moved to the pending ready list and the following
                     *  line is still valid.  Also the pvContainer parameter will have
                     *  been set to NULL so the following lines are also valid. */
                    ( ಶೂನ್ಯ ) uxListRemove( &( pxCRCB->x_Generic_List_ಅಂಶ ) );

                    /* Is the co-routine waiting on an event also? */
                    ಆದರೆ( pxCRCB->x_Event_List_ಅಂಶ.pxContainer )
                    {
                        ( ಶೂನ್ಯ ) uxListRemove( &( pxCRCB->x_Event_List_ಅಂಶ ) );
                    }
                }
                ಪೋರ್ಟ್_ENABLE_INTERRUPTS();

                prv_ಕೂಡಿಸು_Co_Routine_ಗಮ್ಯ_Ready_ಸರತಿ( pxCRCB );
            }
        }

        x_ಕೊನೆಯ_Tick_ಎಣಿಕೆ = x_Co_Routine_Tick_ಎಣಿಕೆ;
    }
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ v_Co_Routine_ವೇಳಾಪಟ್ಟಿ( ಶೂನ್ಯ )
    {
        trace_ENTER_v_Co_Routine_ವೇಳಾಪಟ್ಟಿ();

        /* Only run a co-routine after prvInitialiseCoRoutineLists() has been
         * called.  prvInitialiseCoRoutineLists() is called automatically when a
         * co-routine is created. */
        ಆದರೆ( pxDelayedCoRoutineList != ಖಾಲಿ )
        {
            /* See if any co-routines readied by events need moving to the ready lists. */
            prvCheckPendingReadyList();

            /* See if any delayed co-routines have timed out. */
            prvCheckDelayedList();

            /* Find the highest priority queue that contains ready co-routines. */
            ಆಗ( list_LIST_IS_ಖಾಲಿಗಳು( &( pxReadyCoRoutineLists[ ux_ತುದಿ_Co_Routine_Ready_ಆದ್ಯತೆ ] ) ) )
            {
                ಆದರೆ( ux_ತುದಿ_Co_Routine_Ready_ಆದ್ಯತೆ == 0 )
                {
                    /* No more co-routines to check. */
                    ಹಿಂತಿರುಗಿ;
                }

                --ux_ತುದಿ_Co_Routine_Ready_ಆದ್ಯತೆ;
            }

            /* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
             * of the same priority get an equal share of the processor time. */
            list_GET_OWNER_ದ_ಮುಂದಿನ_ನಮೂದು( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ ux_ತುದಿ_Co_Routine_Ready_ಆದ್ಯತೆ ] ) );

            /* Call the co-routine. */
            ( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->ux_ಸೂಚ್ಯಂಕ );
        }

        trace_RETURN_v_Co_Routine_ವೇಳಾಪಟ್ಟಿ();
    }
/*-----------------------------------------------------------*/

    STATIC ಶೂನ್ಯ prvInitialiseCoRoutineLists( ಶೂನ್ಯ )
    {
        UBaseType_t ux_ಆದ್ಯತೆ;

        ಗಾಗಿ( ux_ಆದ್ಯತೆ = 0; ux_ಆದ್ಯತೆ < configMAX_CO_ROUTINE_PRIORITIES; ux_ಆದ್ಯತೆ++ )
        {
            vListInitialise( ( List_t * ) &( pxReadyCoRoutineLists[ ux_ಆದ್ಯತೆ ] ) );
        }

        vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
        vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
        vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );

        /* Start with pxDelayedCoRoutineList using list1 and the
         * pxOverflowDelayedCoRoutineList using list2. */
        pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
        px_ಅತಿಪ್ರವಾಹ_Delayed_Co_Routine_List = &xDelayedCoRoutineList2;
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t xCoRoutineRemoveFromEventList( ಸ್ಥಿರಾಂಕ List_t * pxEventList )
    {
        CRCB_t * pxUnblockedCRCB;
        ತಳ_Type_t xReturn;

        traceENTER_xCoRoutineRemoveFromEventList( pxEventList );

        /* This function is called from within an interrupt.  It can only access
         * event lists and the pending ready list.  This function assumes that a
         * check has already been made to ensure pxEventList is not empty. */
        pxUnblockedCRCB = ( CRCB_t * ) list_GET_OWNER_ದ_ತಲೆ_ನಮೂದು( pxEventList );
        ( ಶೂನ್ಯ ) uxListRemove( &( pxUnblockedCRCB->x_Event_List_ಅಂಶ ) );
        v_List_ಸೇರಿಸು_ಕೊನೆ( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->x_Event_List_ಅಂಶ ) );

        ಆದರೆ( pxUnblockedCRCB->ux_ಆದ್ಯತೆ >= pxCurrentCoRoutine->ux_ಆದ್ಯತೆ )
        {
            xReturn = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = pdFALSE;
        }

        traceRETURN_xCoRoutineRemoveFromEventList( xReturn );

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

/*
 * Reset state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
    ಶೂನ್ಯ vCoRoutineResetState( ಶೂನ್ಯ )
    {
        /* Lists for ready and blocked co-routines. */
        pxDelayedCoRoutineList = ಖಾಲಿ;
        px_ಅತಿಪ್ರವಾಹ_Delayed_Co_Routine_List = ಖಾಲಿ;

        /* Other file private variables. */
        pxCurrentCoRoutine = ಖಾಲಿ;
        ux_ತುದಿ_Co_Routine_Ready_ಆದ್ಯತೆ = ( UBaseType_t ) 0U;
        x_Co_Routine_Tick_ಎಣಿಕೆ = ( TickType_t ) 0U;
        x_ಕೊನೆಯ_Tick_ಎಣಿಕೆ = ( TickType_t ) 0U;
        xPassedTicks = ( TickType_t ) 0U;
    }
/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_CO_ROUTINES != 0 */
