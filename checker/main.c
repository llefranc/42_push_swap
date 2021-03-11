/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:51:00 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/11 12:52:32 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void deallocateStacks(t_node* endA, t_node* endB)
{
	while (endA->next != endA)
		deleteNode(endA->next);
	free(endA);

	while (endB->next != endB)
		deleteNode(endB->next);
	free(endB);
}

int errorMsg(t_node* endA, t_node* endB)
{
	if (endA && endB)
		deallocateStacks(endA, endB);
	
	ft_putstr_fd("Error\n", STDERR_FILENO);
	return FALSE;
}

int sortingResultMsg(int b, t_node* endA, t_node *endB)
{
	deallocateStacks(endA, endB);
	
	b == TRUE ? ft_putstr_fd("OK\n", STDOUT_FILENO) : ft_putstr_fd("KO\n", STDOUT_FILENO);
	return b;
}

int checkIfInt(char *str, int numOfDigits)
{
	// INT_MAX / INT_MIN have a 10 numbers lenght
	if ((numOfDigits > 10 || !numOfDigits) ||
			(ft_atoi(str) > (long)INT_MAX || ft_atoi(str) < (long)INT_MIN))
		return FALSE;
		
	return TRUE;
}

int checkArgs(int ac, char **av)
{
	// Case no args, checker displays nothing and quit
	if (ac == 1)
		return FALSE;

	int i = 0;
	while (++i < ac)
	{
		// tmp should be only made of digits
		char *tmp;
		tmp = av[i][0] == '+' || av[i][0] == '-' ? &av[i][1] : av[i];

		// Checking if it's a number between INT_MAX / INT_MIN
		if (!ft_strisdigit(tmp) || !checkIfInt(av[i], ft_strlen(tmp)))
			return errorMsg(NULL, NULL);
		
		// Checking if there is no duplicates values
		int j = i;
		while (++j < ac)
			if (!ft_strcmp(av[i], av[j]))
				return errorMsg(NULL, NULL);
	}
	
	return TRUE;
}

int checkSort(t_node* endA, t_node* endB)
{
	if (endB->data != 0)
		return sortingResultMsg(FALSE, endA, endB);

	t_node* tmp = endA->next;
	while (tmp->next != endA)
	{
		if (tmp->data > tmp->next->data)
			return sortingResultMsg(FALSE, endA, endB);
		
		tmp = tmp->next;
	}
	
	return sortingResultMsg(TRUE, endA, endB);
}

int execInstruct(t_node** endA, t_node** endB, int debug, char *instruct)
{
	if (!ft_strcmp(instruct, "sa"))
		printStacks(sa_sb(*endA, SA), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "sb"))
		printStacks(sa_sb(*endB, SB), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "ss"))
		printStacks(ss(*endA, *endB), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "pa"))
		printStacks(pa_pb(*endA, *endB, PA), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "pb"))
		printStacks(pa_pb(*endB, *endA, PB), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "ra"))
		printStacks(ra_rb(endA, RA), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "rb"))
		printStacks(ra_rb(endB, RB), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "rr"))
		printStacks(rr(endA, endB), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "rra"))
		printStacks(rra_rrb(endA, RRA), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "rrb"))
		printStacks(rra_rrb(endB, RRB), *endA, *endB, debug);
	else if (!ft_strcmp(instruct, "rrr"))
		printStacks(rrr(endA, endB), *endA, *endB, debug);
	else
		return FALSE;
	return TRUE;
}

int main(int ac, char **av)
{
	// A FAIRE LA CONFIG DEBUG
	int debug = TRUE;

	// Checking if arguments are correct
	if (!checkArgs(ac, av))
		return FALSE;

	// Creating neutral nodes for stack A and B
	t_node* endA = newEndNode();
	t_node* endB = newEndNode();

	// Init stack A
	int i = 0;
	while (++i < ac)
		push_back(endA, ft_atoi(av[i]));
		
	// Printing stacks initialized if debug option is activated
	printStacks(INIT, endA, endB, debug);

	// Reading and executing instructions
	char *instruct = NULL;
	while (get_next_line(STDIN_FILENO, &instruct))
		if (!execInstruct(&endA, &endB, debug, instruct))
			return errorMsg(endA, endB);
	
	// Checking is stack A is sorted and stack B is empty
	return checkSort(endA, endB);
}
