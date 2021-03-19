/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:30:11 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/19 16:21:36 by llefranc         ###   ########.fr       */
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
// ajouter truc qui genere la liste d'instruction

// sorts only on A, possible opti for B
void sortTwoOrThreeElemsOnA(t_node* instruct, t_twoStacks* st, int size)
{
	// Just a single swap for 2 non-sorted elements
	if (size == 2 && !isSorted(st->endA->next, st->endA->next->next->next, STACK_A))
		execInstructPushSwap(instruct, st, TRUE, "sa");

	else if (size == 3 && !isSorted(st->endA->next, st->endA->next->next->next->next, STACK_A)) // ex with numbers 1 / 2 / 3
	{
		if (st->endA->next->data < st->endA->next->next->data && 
				st->endA->next->data < st->endA->next->next->next->data) // case 1 / 3 / 2
		{
			execInstructPushSwap(instruct, st, TRUE, "ra"); // saving 1 cause sorted
			execInstructPushSwap(instruct, st, TRUE, "sa"); // swap 3 and 2
			--size;
		}
		
		else if (st->endA->next->data > st->endA->next->next->data && 
				st->endA->next->data > st->endA->next->next->next->data) // case 3 / 2 / 1 or 3 / 1 / 2
		{
			execInstructPushSwap(instruct, st, TRUE, "pb"); // pushing 3
			if (st->endA->next->data > st->endA->next->next->data) // swapping 1 and 2 if needed
				execInstructPushSwap(instruct, st, TRUE, "sa");
			
			do
				execInstructPushSwap(instruct, st, TRUE, "ra"); // saving 1 and 2 cause sorted
			while (--size > 1);

			execInstructPushSwap(instruct, st, TRUE, "pa"); // puting back 3 to top of A
		}
		
		else // case 2 / 1 / 3 or 2 / 3 / 1
		{
			if (st->endA->next->data > st->endA->next->next->data) // case 2 / 1 / 3, swapping 1 and 2
				execInstructPushSwap(instruct, st, TRUE, "sa");
			else								// case 2 / 3 / 1
			{
				execInstructPushSwap(instruct, st, TRUE, "pb"); // pushing 2
				execInstructPushSwap(instruct, st, TRUE, "sa"); // swapping 3 and 1
				execInstructPushSwap(instruct, st, TRUE, "ra"); // saving 1 cause sorted
				--size;
				execInstructPushSwap(instruct, st, TRUE, "pa"); // pushing back 2
			}
		}
	}

	// Saving at the end of the stack the sorted elements
	while (size--)
			execInstructPushSwap(instruct, st, TRUE, "ra");
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

void printInstruction(int instruct)
{
	if (instruct == SA)
		ft_putstr_fd("sa\n", 1);
	else if (instruct == SB)
		ft_putstr_fd("sb\n", 1);
	else if (instruct == SS)
		ft_putstr_fd("ss\n", 1);
	else if (instruct == PA)
		ft_putstr_fd("pa\n", 1);
	else if (instruct == PB)
		ft_putstr_fd("pb\n", 1);
	else if (instruct == RA)
		ft_putstr_fd("ra\n", 1);
	else if (instruct == RB)
		ft_putstr_fd("rb\n", 1);
	else if (instruct == RR)
		ft_putstr_fd("rr\n", 1);
	else if (instruct == RRA)
		ft_putstr_fd("rra\n", 1);
	else if (instruct == RRB)
		ft_putstr_fd("rrb\n", 1);
	else if (instruct == RRR)
		ft_putstr_fd("rrr\n", 1);
}

int main(int ac, char **av)
{
	// Checking if arguments are correct
	if (!checkArgs(ac, av))
		return FALSE;

	t_twoStacks st;
	t_node* instruct = newEndNode();

	st.endA = newEndNode();
	st.endB = newEndNode();
	
	// Creating stack A
	int i = 0;
	while (++i < ac)
		push_back(st.endA, ft_atoi(av[i]));

	printStacks(0, &st, TRUE);

	quicksort(instruct, &st, sizeList(st.endA->next, st.endA), STACK_A);
	
	printStacks(0, &st, TRUE);
	printf("nb instruc %d\n", compteur);

	t_node* tmp = instruct->next;
	while (tmp != instruct)
	{
		printInstruction(tmp->data);
		tmp = tmp->next;
	}

	return TRUE;
}