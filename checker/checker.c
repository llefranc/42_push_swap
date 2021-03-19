/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:51:00 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/19 16:23:34 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

int sortingResultMsg(int b, t_twoStacks* st, t_node* instruct)
{
	deallocateStacks(st, instruct);
	
	b == TRUE ? ft_putstr_fd("OK\n", STDOUT_FILENO) : ft_putstr_fd("KO\n", STDOUT_FILENO);
	return b;
}

int checkSort(t_twoStacks* st)
{
	if (st->endB->data != 0)
		return sortingResultMsg(FALSE, st, NULL);

	t_node* tmp = st->endA->next;
	while (tmp->next != st->endA)
	{
		if (tmp->data > tmp->next->data)
			return sortingResultMsg(FALSE, st, NULL);
		
		tmp = tmp->next;
	}
	
	return sortingResultMsg(TRUE, st, NULL);
}

int main(int ac, char **av)
{
	// A FAIRE LA CONFIG DEBUG
	int debug = TRUE;

	// Checking if arguments are correct
	if (!checkArgs(ac, av))
		return FALSE;

	// Creating neutral nodes for stack A and B
	t_twoStacks st;
	st.endA = newEndNode();
	st.endB = newEndNode();

	// Init stack A
	int i = 0;
	while (++i < ac)
		push_back(st.endA, ft_atoi(av[i]));
		
	// Printing stacks initialized if debug option is activated
	printStacks(INIT, &st, debug);

	// Reading and executing instructions
	char *instruct = NULL;
	while (get_next_line(STDIN_FILENO, &instruct))
		if (!execInstructChecker(&st, debug, instruct))
			return errorMsg(&st, NULL);
	
	// Checking is stack A is sorted and stack B is empty
	return checkSort(&st);
}
