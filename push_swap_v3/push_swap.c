/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:30:11 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/18 12:34:44 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

// quicksort avec 2 stacks
// >> on push sur B les inf et median, et on remonte le med au dessus
// >> on push sur A les sup et median, et on remonte le median au dess
// >> si serie de 2 ou 3 sur le haut de la stack A, on swap et on les push en dessous >> ra
// >> si serie de 2 ou 3 sur B >> on repush sur A

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

t_node* partitionning(t_twoStacks* st, t_node* begin, t_node* end, int whichStack)
{
	// Finding median
	t_node* med;
	if (!(med = findMed(begin, end)))
		return NULL;
	
	// ADD HERE CASE 2 OR 3 ELEMS BETWEEN BEGIN AND END // possible optimization si elements sur B, a voir
	int size = 0;
	if ((size = sizeList(begin, end)) <= 3)
	{
		// Pushing on A first
		int i = 0;
		if (whichStack == STACK_B) // FAIRE UNE FOCNTION QUI SORT POUR B, ET UNE POUR A
			while (i++ < size)
				execInstruct(st, TRUE, "pa");
		
		sortTwoOrThreeElems(st, st->endA, size);
		
		// Sorted, no need to return median value, this recursivity loop will stop
		return NULL;
	}

	return NULL;
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
	execInstruct(&st, TRUE, "pb");
	execInstruct(&st, TRUE, "pb");
	execInstruct(&st, TRUE, "pb");

	partitionning(&st, st.endB->next, st.endB, STACK_B);
	
	printStacks(0, &st, TRUE);

	return TRUE;
}