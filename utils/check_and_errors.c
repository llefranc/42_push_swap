/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:58:17 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/23 14:17:43 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void deallocateStacks(t_allocMem* st, t_node* instruct)
{
	while (st && st->endA && st->endA->next != st->endA)
		deleteNode(st->endA->next);
	st ? free(st->endA) : 0;

	while (st && st->endB && st->endB->next != st->endB)
		deleteNode(st->endB->next);
	st ? free(st->endB) : 0;

	while (instruct && instruct->next != instruct)
		deleteNode(instruct->next);
	free(instruct);
}

int errorMsg(t_allocMem* st, t_node* instruct)
{
	deallocateStacks(st, instruct);
	
	ft_putstr_fd("Error\n", STDERR_FILENO);
	return FALSE;
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
