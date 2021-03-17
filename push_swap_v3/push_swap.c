/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:30:11 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/17 17:04:32 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

// quicksort avec 2 stacks
// >> on push sur B les inf et median, et on remonte le med au dessus
// >> on push sur A les sup et median, et on remonte le median au dess
// >> si serie de 2 ou 3 sur le haut de la stack A, on swap et on les push en dessous >> ra
// >> si serie de 2 ou 3 sur B >> on repush sur A

// Checks if all elements between begin and end are sorted (neutral node shouldn't be included between begin and end)
int isSorted(t_node* begin, t_node* end)
{
	while (begin != end && begin->next != end) // case 0 elements or just one
	{
		if (begin->data > begin->next->data)
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

void sortTwoOrThreeElems(t_twoStacks* st, t_node* endA, int size)
{
	// Just a single swap for 2 non-sorted elements
	if (size == 2 && !isSorted(endA->next, endA->next->next))
		execInstruct(st, TRUE, "sa");

	else if (size == 3 !isSorted(endA->next, endA->next->next->next))
	{
		REPRENDRE ICI TROUVER UN MOYEN DE TRIER UNE SUITE DE 3 FACILEMENT
	}

	// Saving at the end of the stack the sorted elements
	while (size--)
		execInstruct(st, TRUE, "ra");
}

void partitionning(t_twoStacks* st, t_node* begin, t_node* end, int whichStack)
{
	// Finding median
	t_node* med;
	if (!(med = findMed(begin, end)))
		return NULL;
	
	// ADD HERE CASE 2 OR 3 ELEMS BETWEEN BEGIN AND END
	int size = 0;
	if ((size = sizeList(begin, end)) <= 3)
	{
		// Pushing on A first
		int i = 0;
		if (whichStack == STACK_B)
			while (i++ < size)
				execInstruct(st, TRUE, "pa");
		
		sortTwoOrThreeElems(st->endA, size);
		
		// Sorted, no need to return median value, this recursivity loop will stop
		return NULL;
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

	

	return TRUE;
}