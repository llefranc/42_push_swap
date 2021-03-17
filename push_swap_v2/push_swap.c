/* ************************************************************************** */
/*    */
/*        :::      ::::::::   */
/*   push_swap.c    :+:      :+:    :+:   */
/*    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*+#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:54:30 by llefranc          #+#    #+# */
/*   Updated: 2021/03/11 15:07:09 by llefranc         ###   ########.fr       */
/*    */
/* ************************************************************************** */

#include "../includes/headers.h"

// 1: quicksort est plus efficace si l'element pris est le median
// 2: penser a faire une fonction qui check si la une certaine zone est deja triee
// 3: possible opti quand plus que 2/3 elements à trier ?
// 4: faire une fonction qui replace bien le precedent median

int checkSort(t_twoStacks* st)
{
	if (st->endB->data != 0)
		return FALSE;

	t_node* tmp = st->endA->next;
	while (tmp->next != st->endA)
	{
		if (tmp->data > tmp->next->data)
			return FALSE;
		
		tmp = tmp->next;
	}
	
	return TRUE;
}

// peut etre mettre le median dans B
t_node* partitionning(t_node* begin, t_node* end, t_twoStacks* st)//, t_node* prevMed)
{
	int med;

	if (!(findMedianValue(begin, end, &med)))
		return NULL;
	
	int ra;
	int rra;
	
	// pushing all values < to med to stack b (AND MEDIAN)
	while (findNextNumberToMove(st->endA, med, &ra, &rra))
	{
		printf("ra = %d, rra = %d, med = %d\n", ra, rra, med);

		if (ra <= -rra)
			while (ra--)
				execInstruct(st, TRUE, "ra");

		else
			while (rra++)
				execInstruct(st, TRUE, "rra");
		
		execInstruct(st, TRUE, "pb");
	}

	// CHECKER CE PROBLEME ICI DU MEDIAN QUI NE PEUT PAS REVENIR A SA PLACE
	// int prevMedData = prevMed->data;
	// while (1)
	// {
	// 	t_node* tmp = prevMed;
	// 	while (tmp != st->endA)
	// 	{
	// 		if (tmp->data < prevMedData)
	// 		{
	// 			execInstruct(st, TRUE, "rra");
	// 			break;
	// 		}
	// 		tmp = tmp->next;
	// 	}
	// }

	// bringing median to the top of B
	if (findSpecificNumberToMove(st->endB, med, &ra, &rra))
	{
		if (ra <= -rra)
		while (ra--)
			execInstruct(st, TRUE, "rb");

	else
		while (rra++)
			execInstruct(st, TRUE, "rrb");
	}
	execInstruct(st, TRUE, "pa");

	// saving median position for recursivity
	t_node* medPos = st->endA->next;
	
	// Bringing back to stack A 
	while (st->endB->data)
		execInstruct(st, TRUE, "pa");

	return medPos;
}

int quicksort(t_node* begin, t_node* end, t_twoStacks* st)//, t_node* prevMed)
{
	if (!checkSort(st))
	{
		t_node *med = partitionning(begin, end, st);//, med); // checker le retour ici pour malloc
		quicksort(begin, med, st);// med);
		quicksort(med->next, end, st);// med);
	}
	return TRUE;
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

	// Copying stack A into an array for finding median value
	// int* array;
	// if (!(array = malloc(sizeof(*array) * st.endA->data)))
	// 	return errorMsg(&st, instruct);
	// copyStackIntoArray(st.endA, array);
	
	// if (!partitionning(st.endA->next, st.endA, &st))
	// 	return errorMsg(&st, instruct);

	quicksort(st.endA->next, st.endA, &st);
	// int med;
	// if (!(findMedianValue(st.endA->next, st.endA->prev->prev, &med)))
	// 	return FALSE;

	// ----------------- PUSH_SWAP PART -------------------------
	printStacks(INIT, &st, TRUE);

	// if (!quicksort(array, med, st.endA->next, st.endA, &st))
	// 	return FALSE;

	return TRUE;
}