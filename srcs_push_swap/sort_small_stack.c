/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:14:38 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/25 14:12:56 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void sortThreeElemsOnSmallA(t_node* instruct, t_allocMem* st)
{
    if (st->endA->next->data < st->endA->next->next->data && 
			st->endA->next->data < st->endA->next->next->next->data &&
            st->endA->next->next->data > st->endA->next->next->next->data) // case 1 / 3 / 2
    {
        execInstructPushSwap(instruct, st, TRUE, SA);
        execInstructPushSwap(instruct, st, TRUE, RA);
    }
        
    else if (st->endA->next->data > st->endA->next->next->data && 
	    	st->endA->next->data > st->endA->next->next->next->data &&
            st->endA->next->next->data < st->endA->next->next->next->data) // case 3 / 1 / 2
        execInstructPushSwap(instruct, st, TRUE, RA);

    else if (st->endA->next->data > st->endA->next->next->data && 
	    	st->endA->next->data > st->endA->next->next->next->data) // case 3 / 2 / 1
    {
        execInstructPushSwap(instruct, st, TRUE, RA);
        execInstructPushSwap(instruct, st, TRUE, SA);
    }

    else if (st->endA->next->data > st->endA->next->next->data && 
	    	st->endA->next->data < st->endA->next->next->next->data) // case 2 / 1 / 3
        execInstructPushSwap(instruct, st, TRUE, SA);
            
    else // case 2 / 3 / 1
        execInstructPushSwap(instruct, st, TRUE, RRA);
}

void sortThreeElemsOnSmallB(t_node* instruct, t_allocMem* st)
{
    if (st->endB->next->data < st->endB->next->next->data && 
			st->endB->next->data < st->endB->next->next->next->data &&
            st->endB->next->next->data > st->endB->next->next->next->data) // case 1 / 3 / 2
        execInstructPushSwap(instruct, st, TRUE, RB);
        
    else if (st->endB->next->data < st->endB->next->next->data && 
			st->endB->next->data < st->endB->next->next->next->data) // case 1 / 2 / 3
    {
        execInstructPushSwap(instruct, st, TRUE, RB);
        execInstructPushSwap(instruct, st, TRUE, SB);
    }
    
    else if (st->endB->next->data > st->endB->next->next->data && 
	    	st->endB->next->data > st->endB->next->next->next->data) // case 3 / 1 / 2
    {
        execInstructPushSwap(instruct, st, TRUE, SB);
        execInstructPushSwap(instruct, st, TRUE, RB);
    }

    else if (st->endB->next->data > st->endB->next->next->data && 
	    	st->endB->next->data < st->endB->next->next->next->data) // case 2 / 1 / 3
        execInstructPushSwap(instruct, st, TRUE, RRB);
            
    else // case 2 / 3 / 1
        execInstructPushSwap(instruct, st, TRUE, SB);
}

void sortSmallStack(t_node* smallInstruct, t_allocMem* st, int size)
{
	// If stack already sorted, the program would have exit before this function
	if (size == 2)
		execInstructPushSwap(smallInstruct, st, TRUE, SA);
		
	else if (size == 3)
		sortThreeElemsOnSmallA(smallInstruct, st);
		
	else if (size == 4)
	{
		// Splitting the serie in two couples
		initPartitionning(smallInstruct, st);
		
		// Swapping the two couples if needed
		if (!isSorted(st->endA->next, st->endA, STACK_A))
			execInstructPushSwap(smallInstruct, st, TRUE, SA);
		if (!isSorted(st->endB->next, st->endB, STACK_B))
			execInstructPushSwap(smallInstruct, st, TRUE, SB);

		pushXTimeTo(STACK_A, smallInstruct, st, 2);
	}

	else if (size == 5)
	{
		// Spliting the serie in 2 elems on A, 3 on B
		initPartitionning(smallInstruct, st);

		sortThreeElemsOnSmallB(smallInstruct, st);
		if (!isSorted(st->endA->next, st->endA, STACK_A))
			execInstructPushSwap(smallInstruct, st, TRUE, SA);

		pushXTimeTo(STACK_A, smallInstruct, st, 3);
	}
}
