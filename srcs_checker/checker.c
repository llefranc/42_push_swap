/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:51:00 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/25 13:57:02 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void sortingResultMsg(int b, t_allocMem* st)
{
	b == TRUE ? ft_putstr_fd("OK\n", STDOUT_FILENO) : ft_putstr_fd("KO\n", STDOUT_FILENO);
	cleanExit(st, b);
}

void checkSort(t_allocMem* st)
{
	if (st->endB->data != 0)
		sortingResultMsg(FALSE, st);

	t_node* tmp = st->endA->next;
	while (tmp->next != st->endA)
	{
		if (tmp->data > tmp->next->data)
			sortingResultMsg(FALSE, st);
		
		tmp = tmp->next;
	}
	
	sortingResultMsg(TRUE, st);
}

int main(int ac, char **av)
{
	int debug = FALSE;

	// Checking if arguments are correct, setting debug to TRUE if -v option is present
	if (!checkArgs(ac, av, &debug))
		errorMsg(NULL);

	// Creating neutral nodes for stack A and B
	t_allocMem st;
	initStruct(&st);
	st.endA = newEndNode(&st);
	st.endB = newEndNode(&st);

	// Init stack A
	int i;
	i = (debug == TRUE) ? 1 : 0;
	while (++i < ac)
		push_back(&st, st.endA, ft_atoi(av[i]));
		
	// Printing stacks initialized if debug option is activated
	printStacks(INIT, &st, debug);

	// Reading and executing instructions
	char *instruct = NULL;
	int ret = 0;
	while ((ret = get_next_line(STDIN_FILENO, &instruct)) == TRUE)
	{
		if (!execInstructChecker(&st, debug, instruct))
			errorMsg(&st);
		free(instruct);
	}
	
	// If an error occured during get_next_line
	ret == -1 ? errorMsg(&st) : free(instruct);
	
	// Checking is stack A is sorted and stack B is empty, printing 
	// the result on STDOUT and freeing all memory allocated
	checkSort(&st);
	return 0;
}
