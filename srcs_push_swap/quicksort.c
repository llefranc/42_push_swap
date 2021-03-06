/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:39:33 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/25 15:15:07 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void sortTwoOrThreeElemsOnA(t_node* instruct, t_allocMem* st, int size)
{
	// Just a single swap for 2 non-sorted elements
	if (size == 2 && !isSorted(st->endA->next, st->endA->next->next->next, STACK_A))
		execInstructPushSwap(instruct, st, TRUE, SA);

	else if (size == 3 && !isSorted(st->endA->next, st->endA->next->next->next->next, STACK_A)) // ex with numbers 1 / 2 / 3
	{
		if (st->endA->next->data < st->endA->next->next->data && 
				st->endA->next->data < st->endA->next->next->next->data) // case 1 / 3 / 2
		{
			execInstructPushSwap(instruct, st, TRUE, RA); // saving 1 cause sorted
			execInstructPushSwap(instruct, st, TRUE, SA); // swap 3 and 2
			--size;
		}
		
		else if (st->endA->next->data > st->endA->next->next->data && 
				st->endA->next->data > st->endA->next->next->next->data) // case 3 / 2 / 1 or 3 / 1 / 2
		{
			execInstructPushSwap(instruct, st, TRUE, PB); // pushing 3
			if (st->endA->next->data > st->endA->next->next->data) // swapping 1 and 2 if needed
				execInstructPushSwap(instruct, st, TRUE, SA);
			
			do
				execInstructPushSwap(instruct, st, TRUE, RA); // saving 1 and 2 cause sorted
			while (--size > 1);

			execInstructPushSwap(instruct, st, TRUE, PA); // puting back 3 to top of A
		}
		
		else // case 2 / 1 / 3 or 2 / 3 / 1
		{
			if (st->endA->next->data > st->endA->next->next->data) // case 2 / 1 / 3, swapping 1 and 2
				execInstructPushSwap(instruct, st, TRUE, SA);
			else								// case 2 / 3 / 1
			{
				execInstructPushSwap(instruct, st, TRUE, PB); // pushing 2
				execInstructPushSwap(instruct, st, TRUE, SA); // swapping 3 and 1
				execInstructPushSwap(instruct, st, TRUE, RA); // saving 1 cause sorted
				--size;
				execInstructPushSwap(instruct, st, TRUE, PA); // pushing back 2
			}
		}
	}

	// Saving at the end of the stack the sorted elements
	while (size--)
			execInstructPushSwap(instruct, st, TRUE, RA);
}

// si nbInstruct est un nombre neg > rra ; si nombre pos > ra
// si la fonction return 0 pas de nombre inferieur au median a transferer
int findNextNumberToMove(t_node* endList, int med, int *ra, int *rra)
{
	*ra = 0;
	*rra = 1;// Because we need one rra instruction minimum to put it at top of stack
	
	// Checking from the top for the first number <= to median number (ra instruct)
	t_node* tmp = endList->next;
	while (tmp != endList)
	{
		if (tmp->data <= med)
			break;
		tmp = tmp->next;
		++(*ra);
	}

	// Case there is no number <= to median number in the stack
	if (tmp == endList)
		return FALSE;

	// Checking from the bottom (rra instruct)
	tmp = endList->prev;
	while (tmp != endList)
	{
		if (tmp->data <= med)
			break;
		tmp = tmp->prev;
		++(*rra);
	}

	return TRUE;
}

t_sizeParts* initPartitionning(t_node* instruct, t_allocMem* st)
{
	// Finding begin and end of the serie to sort
	t_node* begin = st->endA->next;
	t_node* end = st->endA;
	
	// Finding median
	t_node* med = findMed(st, begin, end);
		
	// Finding the size of the two parts of the serie for the next recursive loop
	t_sizeParts* sizeParts;
	if (!(sizeParts = malloc(sizeof(*sizeParts))))
		errorMsg(st);
	calcSizeParts(sizeParts, begin, end, med->data, STACK_A);

	int ra = 0;
	int rra = 0;
	int median = med->data;
	int medianWasLast;

	while (findNextNumberToMove(st->endA, median, &ra, &rra))
	{
		// Bringing median or inf value in the less possibles moves on top 
		// of A, and then pushing it to B
		if (ra <= rra)
			while (ra--)
				execInstructPushSwap(instruct, st, TRUE, RA);
		else
			while (rra--)
				execInstructPushSwap(instruct, st, TRUE, RRA);
		execInstructPushSwap(instruct, st, TRUE, PB);

		// If we just pushed the median on B, saving it at the bottom of B (except if B contains only 
		// median value, it's already at bottom)
		if (st->endB->next->data == med->data && findNumberInAToPushToB(st->endA, st->endA, med->data, &ra))
			st->endB->data != 1 ? execInstructPushSwap(instruct, st, TRUE, RB) : 0;

		// If median value was the last value to be pushed, no need to put it at bottom and to bring 
		// it back at top : it's already at its correct position in the serie
		else if (st->endB->next->data == med->data && !findNumberInAToPushToB(st->endA, st->endA, med->data, &ra)
				&& st->endB->data != 1)
			medianWasLast = TRUE;
	}

	// Puting median at its right position, at top of B (it was saved at the bottom of B).
	// The median is now at its corred position and is sorted.
	!medianWasLast ? execInstructPushSwap(instruct, st, TRUE, RRB) : 0;

	return sizeParts;
}


t_sizeParts* partitionning(t_node* instruct, t_allocMem* st, int totalSize, int whichStack)
{
	// If the serie to sort is 3 elements or less, we don't need quicksort to sort it
	if (totalSize <= 3)
	{
		// Pushing on A first if we are treating elements on B
		int i = 0;
		if (whichStack == STACK_B) // FAIRE UNE FOCNTION QUI SORT POUR B, ET UNE POUR A
			while (i++ < totalSize)
				execInstructPushSwap(instruct, st, TRUE, PA);
		
		// On stack A, will put the 2 or 3 elements on in the right order and ra 2/3 times to 
		// save them at the end of stack A
		sortTwoOrThreeElemsOnA(instruct, st, totalSize);
		
		// Sorted, no need to return median value, this recursivity loop will stop
		return NULL;
	}
	
	// Finding begin and end of the serie to sort
	t_node* begin = (whichStack == STACK_A) ? st->endA->next : st->endB->next;
	t_node* end = getEndNode(begin, totalSize);
    
	// Finding median
	t_node* med = findMed(st, begin, end);

	// Finding the size of the two parts of the serie for the next recursive loop
	t_sizeParts* sizeParts;
	if (!(sizeParts = malloc(sizeof(*sizeParts))))
		errorMsg(st);
	calcSizeParts(sizeParts, begin, end, med->data, whichStack);

    whichStack == STACK_A ? pushToB(instruct, st, end, med->data) : pushToA(instruct, st, end, med->data);

	return sizeParts;
}

void quicksort(t_node* instruct, t_allocMem* st, int totalSize, int whichStack)
{
	t_sizeParts* sizeParts;
	
	if (whichStack == INIT)
		sizeParts = initPartitionning(instruct, st);
	else
		sizeParts = partitionning(instruct, st, totalSize, whichStack);

	if (sizeParts)
	{
		quicksort(instruct, st, sizeParts->infPartSize, STACK_B); // Inferior part will always be pushed to B
		quicksort(instruct, st, sizeParts->supPartSize, STACK_A); // Superior part will always be pushed to A
		free(sizeParts);
	}
}
