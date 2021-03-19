/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:30:11 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/19 15:12:01 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

// quicksort avec 2 stacks
// >> on push sur B les inf et median, et on remonte le med au dessus
// >> on push sur A les sup et median, et on remonte le median au dess
// >> si serie de 2 ou 3 sur le haut de la stack A, on swap et on les push en dessous >> ra
// >> si serie de 2 ou 3 sur B >> on repush sur A
// ajouter opti si cession deja triee
// ajouter option si median transfere en dernier

// Checks if all elements between begin and end are sorted (neutral node shouldn't be included between begin and end)
int isSorted(t_node* begin, t_node* end, int whichStack)
{
	while (begin != end && begin->next != end) // case 0 elements or just one
	{
		if ((whichStack == STACK_A && begin->data > begin->next->data) ||
				(whichStack == STACK_B && begin->data < begin->next->data))
			return FALSE;
		begin = begin->next;
	}
	return TRUE;
}

// Returns number of elements between begin (included) and end (not included)
int sizeList(t_node* begin, t_node* end)
{
	int size = 0;

	while (begin != end)
	{
		begin = begin->next;
		++size;
	}
	return size;
}

// sorts only on A, possible opti for B
void sortTwoOrThreeElemsOnA(t_twoStacks* st, int size)
{
	// Just a single swap for 2 non-sorted elements
	if (size == 2 && !isSorted(st->endA->next, st->endA->next->next->next, STACK_A))
		execInstruct(st, FALSE, "sa");

	else if (size == 3 && !isSorted(st->endA->next, st->endA->next->next->next->next, STACK_A)) // ex with numbers 1 / 2 / 3
	{
		if (st->endA->next->data < st->endA->next->next->data && 
				st->endA->next->data < st->endA->next->next->next->data) // case 1 / 3 / 2
		{
			execInstruct(st, FALSE, "ra"); // saving 1 cause sorted
			execInstruct(st, FALSE, "sa"); // swap 3 and 2
			--size;
		}
		
		else if (st->endA->next->data > st->endA->next->next->data && 
				st->endA->next->data > st->endA->next->next->next->data) // case 3 / 2 / 1 or 3 / 1 / 2
		{
			execInstruct(st, FALSE, "pb"); // pushing 3
			if (st->endA->next->data > st->endA->next->next->data) // swapping 1 and 2 if needed
				execInstruct(st, FALSE, "sa");
			
			do
				execInstruct(st, FALSE, "ra"); // saving 1 and 2 cause sorted
			while (--size > 1);

			execInstruct(st, FALSE, "pa"); // puting back 3 to top of A
		}
		
		else // case 2 / 1 / 3 or 2 / 3 / 1
		{
			if (st->endA->next->data > st->endA->next->next->data) // case 2 / 1 / 3, swapping 1 and 2
				execInstruct(st, FALSE, "sa");
			else								// case 2 / 3 / 1
			{
				execInstruct(st, FALSE, "pb"); // pushing 2
				execInstruct(st, FALSE, "sa"); // swapping 3 and 1
				execInstruct(st, FALSE, "ra"); // saving 1 cause sorted
				--size;
				execInstruct(st, FALSE, "pa"); // pushing back 2
			}
		}
	}

	// Saving at the end of the stack the sorted elements
	while (size--)
			execInstruct(st, FALSE, "ra");
}

// si nbInstruct est un nombre neg > rra ; si nombre pos > ra
// si la fonction return 0 pas de nombre inferieur au median a transferer
int findNextNumberToMove(t_node* endList, int med, int *raIns, int *rraIns)
{
	int fromTop = 0;
	int fromBot = -1; // Because we need one rra instruction minimum to put it at top of stack

	// Checking from the top for the first number <= to median number (ra instruct)
	t_node* tmp = endList->next;
	while (tmp != endList)
	{
		if (tmp->data <= med)
			break;
		tmp = tmp->next;
		++fromTop;
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
		--fromBot;
	}

	*raIns = fromTop;
	*rraIns = fromBot;

	return TRUE;
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

// Pushes from stack B the median and all values superior to itself to stack A. 
// After this, the median will be in A and at its correct position in the serie,
// and so will be sorted.
void pushToA(t_twoStacks* st, t_node* end, int med)
{
	int rb;
	
	// As long as there are superior values to median or itself in B
	while (findNumberInBToPushToA(st->endB, end, med, &rb))
	{
		// Bringing the value to push to top of B and pushing it to A
		while (rb--)
			execInstruct(st, FALSE, "rb");
		execInstruct(st, FALSE, "pa");
		
		// If we just pushed the median on A, saving it at the bottom of A
		if (st->endA->next->data == med)
			execInstruct(st, FALSE, "ra");
	}

	// Puting median at its right position, at top of B (it was saved at the bottom of B).
	// The median is now at its corred position and is sorted.
	execInstruct(st, FALSE, "rra");
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

// Pushes from stack A the median and all values inferior to itself to stack B. 
// After this, the median will be in B and at its correct position in the serie,
// and so will be sorted.
void pushToB(t_twoStacks* st, t_node* end, int med)
{
	int ra;
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
			execInstruct(st, FALSE, "ra");
		execInstruct(st, FALSE, "pb");

		// If we just pushed the median on B, saving it at the bottom of B
		if (st->endB->next->data == med)
			execInstruct(st, FALSE, "rb");
	}

	// Bringing back to top of A the values superior to median
	while (tmp--)
		execInstruct(st, FALSE, "rra");

	// Puting median at its right position, at top of B (it was saved at the bottom of B).
	// The median is now at its corred position and is sorted.
	execInstruct(st, FALSE, "rrb");
}

// Returns the end of a serie of elements with a specific size and a specific beginning.
t_node* getEndNode(t_node* begin, int size)
{
	while (size--)
		begin = begin->next;
	return begin;
}

// Calculates inferior part size and superior part size of the serie to sort. If the serie to 
// sort is on stack A, median will be counted as in inferior part; otherwise if the serie is on 
// stack B the media will be counted as in superior part.
void calcSizeParts(t_sizeParts* sizeParts, t_node* begin, t_node* end, int med, int whichStack)
{
	sizeParts->infPartSize = 0;
	sizeParts->supPartSize = 0;
	
	while (begin != end)
	{
		if (begin->data < med)
			sizeParts->infPartSize++;
		else if (begin->data > med)
			sizeParts->supPartSize++;
		begin = begin->next;
	}
	whichStack == STACK_A ? sizeParts->infPartSize++ : sizeParts->supPartSize++;
}

t_sizeParts* partitionning(t_twoStacks* st, int totalSize, int whichStack)
{
	// If the serie to sort is 3 elements or less, we don't need quicksort to sort it
	if (totalSize <= 3)
	{
		// Pushing on A first if we are treating elements on B
		int i = 0;
		if (whichStack == STACK_B) // FAIRE UNE FOCNTION QUI SORT POUR B, ET UNE POUR A
			while (i++ < totalSize)
				execInstruct(st, FALSE, "pa");
		
		// On stack A, will put the 2 or 3 elements on in the right order and ra 2/3 times to 
		// save them at the end of stack A
		sortTwoOrThreeElemsOnA(st, totalSize);
		
		// Sorted, no need to return median value, this recursivity loop will stop
		return NULL;
	}

	// Finding begin and end of the serie to sort
	t_node* begin = (whichStack == STACK_A) ? st->endA->next : st->endB->next;
	t_node* end = getEndNode(begin, totalSize);
	
	// Finding median
	t_node* med;
	if (!(med = findMed(begin, end))) // proteger
		return NULL;

	// Finding the size of the two parts of the serie for the next recursive loop
	t_sizeParts* sizeParts;
	sizeParts = malloc(sizeof(*sizeParts)); //proteger
	calcSizeParts(sizeParts, begin, end, med->data, whichStack);

	whichStack == STACK_A ? pushToB(st, end, med->data) : pushToA(st, end, med->data);

	return sizeParts;
}

void quicksort(t_twoStacks* st, int totalSize, int whichStack)
{
	t_sizeParts* sizeParts = partitionning(st, totalSize, whichStack);

	if (sizeParts)
	{
		quicksort(st, sizeParts->infPartSize, STACK_B); // Inferior part will always be pushed to B
		quicksort(st, sizeParts->supPartSize, STACK_A); // Superior part will always be pushed to A
		free(sizeParts);
	}
}

int main(int ac, char **av)
{
	// Checking if arguments are correct
	if (!checkArgs(ac, av))
		return FALSE;

	t_twoStacks st;
	// t_node* instruct = newEndNode();

	st.endA = newEndNode();
	st.endB = newEndNode();
	
	// Creating stack A
	int i = 0;
	while (++i < ac)
		push_back(st.endA, ft_atoi(av[i]));

	printStacks(0, &st, TRUE);

	quicksort(&st, sizeList(st.endA->next, st.endA), STACK_A);
	
	printStacks(0, &st, TRUE);
	printf("nb instruc %d\n", compteur);

	return TRUE;
}