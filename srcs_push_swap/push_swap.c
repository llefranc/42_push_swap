/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:30:11 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/27 10:48:02 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void printOneInstruction(int instruct)
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

void printAllInstructions(t_node* instruct)
{
    t_node* tmp = instruct->next;
	while (tmp != instruct)
	{
		printOneInstruction(tmp->data);
		tmp = tmp->next;
	}
}

int main(int ac, char **av)
{
	// Checking if arguments are correct
	if (!checkArgs(ac, av, NULL))
		errorMsg(NULL);

	t_allocMem st;
	initStruct(&st);
	st.endA = newEndNode(&st);
	st.endB = newEndNode(&st);
	st.smallIns = newEndNode(&st);
	st.quickIns = newEndNode(&st);
	st.selecIns = newEndNode(&st);
    
	// Creating stack A
	int size = 0;
	while (++size < ac)
		push_back(&st, st.endA, ft_atoi(av[size]));

    // Case stack is already sorted, no instructions needed
    if (isSorted(st.endA->next, st.endA, STACK_A))
        cleanExit(&st, EXIT_SUCCESS);

	// Calling the proper algo to sort the stack
    if (--size <= 5)
		sortSmallStack(st.smallIns, &st, sizeList(st.endA->next, st.endA));
    else
		quicksort(st.quickIns, &st, sizeList(st.endA->next, st.endA), INIT);
	
	removeUselessInstructions(st.quickIns);
	removeUselessInstructions(st.smallIns);
    
    if (size <= 5)
		printAllInstructions(st.smallIns);
	else
		printAllInstructions(st.quickIns);

	cleanExit(&st, TRUE);
	return TRUE;
}
