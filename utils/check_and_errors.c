/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:58:17 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/11 12:59:08 by llefranc         ###   ########.fr       */
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
