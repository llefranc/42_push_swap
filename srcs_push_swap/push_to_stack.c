/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:41:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/25 15:15:12 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void pushXTimeTo(int whichStack, t_node* instruct, t_allocMem* st, int x)
{
	while (whichStack == STACK_A && x--)
		execInstructPushSwap(instruct, st, TRUE, PA);
	while (whichStack == STACK_B && x--)
		execInstructPushSwap(instruct, st, TRUE, PB);
}

// Returns true if the median or a value superior to the median is present in 
// stack B, and sets the number of rb instruct to bring this value to top of 
// stack B in order to push it to A.
int findNumberInBToPushToA(t_node* endB, t_node* end, int med, int *rb)
{
	*rb = 0;
	t_node* tmp = endB->next;

	while (tmp != end)
	{
		// Pushing to B values superior to median and itself
		if (tmp->data >= med)
			return TRUE;
			
		// Counting number of rb moves needed to bring the median or an superior 
		// value to the top of B
		tmp = tmp->next;
		++(*rb);
	}

	return FALSE;
}

// Returns true if the median or a value inferior to the median is present in 
// stack A, and sets the number of ra instruct to bring this value to top of 
// stack A in order to push it to B.
int findNumberInAToPushToB(t_node* endA, t_node* end, int med, int *ra)
{
	*ra = 0;
	t_node* tmp = endA->next;

	while (tmp != end)
	{
		// Pushing to B values inferior to median and itself
		if (tmp->data <= med)
			return TRUE;

		// Counting number of ra moves needed to bring the median or an inferior 
		// value to the top of A
		++(*ra);
		tmp = tmp->next;
	}

	return FALSE;
}

// Pushes from stack B the median and all values superior to itself to stack A. 
// After this, the median will be in A and at its correct position in the serie,
// and so will be sorted.
void pushToA(t_node* instruct, t_allocMem* st, t_node* end, int med)
{
	int rb;
	int medianWasLast = FALSE;
	
	// As long as there are superior values to median or itself in B
	while (findNumberInBToPushToA(st->endB, end, med, &rb))
	{
		// Bringing the value to push to top of B and pushing it to A
		while (rb--)
			execInstructPushSwap(instruct, st, TRUE, RB);
		execInstructPushSwap(instruct, st, TRUE, PA);
		
		// If median value was the last value to be pushed, no need to put it at bottom and to bring 
		// it back at top : it's already at its correct position in the serie
		if (st->endA->next->data == med && !findNumberInBToPushToA(st->endB, end, med, &rb))
			medianWasLast = TRUE;
		
		// Otherwise saving the median at the bottom of A
		else if (st->endA->next->data == med)
			execInstructPushSwap(instruct, st, TRUE, RA);
	}

	// Puting median at its right position, at top of A (it was saved at the bottom of A).
	// The median is now at its corred position and is sorted.
	!medianWasLast ? execInstructPushSwap(instruct, st, TRUE, RRA) : 0;
}

// Pushes from stack A the median and all values inferior to itself to stack B. 
// After this, the median will be in B and at its correct position in the serie,
// and so will be sorted.
void pushToB(t_node* instruct, t_allocMem* st, t_node* end, int med)
{
	int ra;
	int medianWasLast = FALSE;
	int tmp = 0;
	
	// As long as there are inferior values to median or itself in A
	while (findNumberInAToPushToB(st->endA, end, med, &ra))
	{
		// Counting number of ra moves cause we need to bring back the superior part 
		// of the serie at the top of A after having pushed all values inferior to median, 
		// including itself
		tmp += ra;
		
		// Bringing the value to push to top of A and pushing it to B
        while (ra--)
			execInstructPushSwap(instruct, st, TRUE, RA);
		execInstructPushSwap(instruct, st, TRUE, PB);

		// If we just pushed the median on B, saving it at the bottom of B (except if B contains only 
		// median value, it's already at bottom)
		if (st->endB->next->data == med && findNumberInAToPushToB(st->endA, end, med, &ra))
			st->endB->data != 1 ? execInstructPushSwap(instruct, st, TRUE, RB) : 0;
			
		// If median value was the last value to be pushed, no need to put it at bottom and to bring 
		// it back at top : it's already at its correct position in the serie
		else if (st->endB->next->data == med && !findNumberInAToPushToB(st->endA, end, med, &ra)
				&& st->endB->data != 1)
			medianWasLast = TRUE;
	}

	// Bringing back to top of A the values superior to median
	while (tmp--)
		execInstructPushSwap(instruct, st, TRUE, RRA);

	// Puting median at its right position, at top of B (it was saved at the bottom of B).
	// The median is now at its corred position and is sorted.
	!medianWasLast ? execInstructPushSwap(instruct, st, TRUE, RRB) : 0;
}
