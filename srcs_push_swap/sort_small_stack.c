/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:14:38 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/27 10:41:04 by lucaslefran      ###   ########.fr       */
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

void pushTwoLowestFromAToB(t_node* smallInstruct, t_allocMem* st)
{
	int* array;
	int size = 0;

	if (!(array = createArray(st->endA->next, st->endA, &size)))
		errorMsg(st);
	
    // Finding the value at rank 2 in a sorted serie
	copyIntoArray(st->endA->next, st->endA, array);
	sortArray(array, size);
    
	int med = array[1];
    int ra = 0;
    int rra = 0;

    // Pushing this value and the value inferior to it on B
    while (findNextNumberToMove(st->endA, med, &ra, &rra))
    {
        if (ra <= rra)
			while (ra--)
				execInstructPushSwap(smallInstruct, st, TRUE, RA);
		else
			while (rra--)
				execInstructPushSwap(smallInstruct, st, TRUE, RRA);
		execInstructPushSwap(smallInstruct, st, TRUE, PB);
    }
}

void sortSmallStack(t_node* smallInstruct, t_allocMem* st, int size)
{
	// If stack already sorted, the program would have exit before this function
	if (size == 2)
		execInstructPushSwap(smallInstruct, st, TRUE, SA);
		
	else if (size == 3)
		sortThreeElemsOnSmallA(smallInstruct, st);
		
    else if (size == 4 || size == 5)
    {
        // Pushing the two lowest values
        pushTwoLowestFromAToB(smallInstruct, st);
        
        // sorting A (2 or 3 values) and B (2 values)
        if (!isSorted(st->endB->next, st->endB, STACK_B))
            execInstructPushSwap(smallInstruct, st, TRUE, SB);
        if (!isSorted(st->endA->next, st->endA, STACK_A))
            size == 4 ? execInstructPushSwap(smallInstruct, st, TRUE, SA) :
                    sortThreeElemsOnSmallA(smallInstruct, st);
                    
        pushXTimeTo(STACK_A, smallInstruct, st, 2);
    }
}
