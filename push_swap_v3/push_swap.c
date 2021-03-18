/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:30:11 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/18 16:34:33 by llefranc         ###   ########.fr       */
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
		execInstruct(st, TRUE, "sa");

	else if (size == 3 && !isSorted(st->endA->next, st->endA->next->next->next->next, STACK_A)) // ex with numbers 1 / 2 / 3
	{
		if (st->endA->next->data < st->endA->next->next->data && 
				st->endA->next->data < st->endA->next->next->next->data) // case 1 / 3 / 2
		{
			execInstruct(st, TRUE, "ra"); // saving 1 cause sorted
			execInstruct(st, TRUE, "sa"); // swap 3 and 2
			--size;
		}
		
		else if (st->endA->next->data > st->endA->next->next->data && 
				st->endA->next->data > st->endA->next->next->next->data) // case 3 / 2 / 1 or 3 / 1 / 2
		{
			execInstruct(st, TRUE, "pb"); // pushing 3
			if (st->endA->next->data > st->endA->next->next->data) // swapping 1 and 2 if needed
				execInstruct(st, TRUE, "sa");
			
			do
				execInstruct(st, TRUE, "ra"); // saving 1 and 2 cause sorted
			while (--size > 1);

			execInstruct(st, TRUE, "pa"); // puting back 3 to top of A
		}
		
		else // case 2 / 1 / 3 or 2 / 3 / 1
		{
			if (st->endA->next->data > st->endA->next->next->data) // case 2 / 1 / 3, swapping 1 and 2
				execInstruct(st, TRUE, "sa");
			else								// case 2 / 3 / 1
			{
				execInstruct(st, TRUE, "pb"); // pushing 2
				execInstruct(st, TRUE, "sa"); // swapping 3 and 1
				execInstruct(st, TRUE, "ra"); // saving 1 cause sorted
				--size;
				execInstruct(st, TRUE, "pa"); // pushing back 2
			}
		}
	}

	// Saving at the end of the stack the sorted elements
	while (size--)
			execInstruct(st, TRUE, "ra");
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

int findNumberInBToPushToA(t_node* endB, t_node* end, int med, int *ra)
{
	*ra = 0;
	t_node* tmp = endB->next;

	while (tmp != end)
	{
		if (tmp->data >= med) // Pushing to A values superior to median and itself
			return TRUE;
		tmp = tmp->next;
		++(*ra);
	}

	return FALSE;
}

// void pushToA(t_twoStacks* st, t_node* begin, t_node* end, t_node* med)
void pushToA(t_twoStacks* st, t_node* end, int med)
{
	int rb;
	
	while (findNumberInBToPushToA(st->endB, end, med, &rb))
	{
		while (rb--)
			execInstruct(st, TRUE, "rb");
		execInstruct(st, TRUE, "pa");
		if (st->endA->next->data == med) // saving median at the end
			execInstruct(st, TRUE, "ra");
	}

	execInstruct(st, TRUE, "rra"); // puting median at right position
}

int findNumberInAToPushToB(t_node* endA, t_node* end, int med, int *ra)
{
	*ra = 0;
	t_node* tmp = endA->next;

	while (tmp != end)
	{
		if (tmp->data <= med) // Pushing to B values inferior to median and itself
			return TRUE;
		tmp = tmp->next;
		++(*ra);
	}

	return FALSE;
}

// void pushToB(t_twoStacks* st, t_node* begin, t_node* end, int med)
void pushToB(t_twoStacks* st, t_node* end, int med)
{
	int ra;
	int tmp = 0;
	
	while (findNumberInAToPushToB(st->endA, end, med, &ra))
	{
		tmp += ra;
		while (ra--)
			execInstruct(st, TRUE, "ra");
		execInstruct(st, TRUE, "pb");
		if (st->endB->next->data == med) // saving median at the end
			execInstruct(st, TRUE, "rb");
	}

	while (tmp--)
		execInstruct(st, TRUE, "rra");

	execInstruct(st, TRUE, "rrb"); // puting median at right position
}

t_node* getEndNode(t_node* begin, int size)
{
	while (size--)
		begin = begin->next;
	return begin;
}

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
	char stack;
	stack = whichStack == STACK_A ? 'A' : 'B';
	
	if (totalSize <= 3)
	{
		printf("saving : stack %c, size %d\n", stack, totalSize);
		// Pushing on A first
		int i = 0;
		if (whichStack == STACK_B) // FAIRE UNE FOCNTION QUI SORT POUR B, ET UNE POUR A
			while (i++ < totalSize)
				execInstruct(st, TRUE, "pa");
		
		sortTwoOrThreeElemsOnA(st, totalSize);
		
		// Sorted, no need to return median value, this recursivity loop will stop
		return NULL;
	}

	// Finding begin and end of the serie to sort
	t_node* begin;
	t_node* end;

	begin = (whichStack == STACK_A) ? st->endA->next : st->endB->next;
	end = getEndNode(begin, totalSize);
	
	
	printf("stack %c, size %d, begin %d, end->prev %d\n",
			stack, totalSize, begin->data, end->prev->data);

	// Finding median
	t_node* med = findMed(begin, end); // proteger
	// if (!(med = findMed(begin, end))) // proteger
	// 	return NULL;


	// Finding the size of the two parts of the serie for the next recursive loop
	t_sizeParts* sizeParts;
	sizeParts = malloc(sizeof(*sizeParts)); //proteger
	calcSizeParts(sizeParts, begin, end, med->data, whichStack);

	// sizeParts->infPartStack = (whichStack == STACK_A) ? STACK_B
	// sizeParts->infPartSize = sizeList(begin, med->next);
	// sizeParts->supPartSize = sizeList(med->next, end);
	
	
	printf("stack %c, size %d, infSize %d, supSize %d, med %d, begin %d, end->prev %d\n",
			stack, totalSize, sizeParts->infPartSize, sizeParts->supPartSize, med->data, begin->data, end->prev->data);
	
	// ADD HERE CASE 2 OR 3 ELEMS BETWEEN BEGIN AND END // possible optimization si elements sur B, a voir
	// int size = 0;
	// if ((size = sizeList(begin, end)) <= 3)

	whichStack == STACK_A ? pushToB(st, end, med->data) : pushToA(st, end, med->data);

	return sizeParts;
}

void quicksort_v3(t_twoStacks* st, int totalSize, int whichStack) // gerer whichstack
{
	t_sizeParts* sizeParts = partitionning(st, totalSize, whichStack);

	if (sizeParts)
	{
		quicksort_v3(st, sizeParts->infPartSize, STACK_B);
		quicksort_v3(st, sizeParts->supPartSize, STACK_A);
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

	// sortTwoOrThreeElemsOnA(&st, 3);
	// partitionning(&st, sizeList(st.endA->next, st.endA), STACK_A);
	quicksort_v3(&st, sizeList(st.endA->next, st.endA), STACK_A);
	
	printStacks(0, &st, TRUE);
	printf("nb instruc %d\n", compteur);

	return TRUE;
}