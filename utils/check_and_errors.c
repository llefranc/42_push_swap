/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:58:17 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/25 14:02:50 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void destroyList(t_node* endNode)
{
    t_node* tmp = endNode->next;
    
    while (tmp != endNode)
    {
        deleteNode(tmp);
        tmp = endNode->next;
    }
    free(endNode);
}

void cleanExit(t_allocMem* st, int ret)
{
	if (st)
    {
		st->endA ? destroyList(st->endA) : 0;
		st->endB ? destroyList(st->endB) : 0;
		st->smallIns ? destroyList(st->smallIns) : 0;
		st->quickIns ? destroyList(st->quickIns) : 0;
		st->selecIns ? destroyList(st->selecIns) : 0;
	}
    
    exit(ret);
}

void initStruct(t_allocMem* st)
{
	st->endA = NULL;
	st->endB = NULL;
	st->smallIns = NULL;
	st->quickIns = NULL;
	st->selecIns = NULL;
}

void errorMsg(t_allocMem* st)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	cleanExit(st, EXIT_FAILURE);
}

int checkIfInt(char *str, int numOfDigits)
{
	// INT_MAX / INT_MIN have a 10 numbers lenght
	if ((numOfDigits > 10 || !numOfDigits) ||
			(ft_atoi(str) > (long)INT_MAX || ft_atoi(str) < (long)INT_MIN))
		return FALSE;
		
	return TRUE;
}

int checkArgs(int ac, char** av, int* debug)
{
	// Case no args, checker displays nothing and quit (or if only -v and no args for checker, 
	// or if -v is present for push_swap (only checker handle this option))
	if (ac == 1 || (ac == 2 && ft_strcmp(av[1], "-v")) || 
			(ac >= 2 && !ft_strcmp(av[1], "-v") && !debug))
		return FALSE;

	// Case debug option is activated
	int i = 0;
	if (!ft_strcmp(av[1], "-v") && debug)
		*debug = ++i;

	while (++i < ac)
	{
		// tmp should be only made of digits
		char *tmp;
		tmp = av[i][0] == '+' || av[i][0] == '-' ? &av[i][1] : av[i];

		// Checking if it's a number between INT_MAX / INT_MIN
		if (!ft_strisdigit(tmp) || !checkIfInt(av[i], ft_strlen(tmp)))
			return FALSE;
		
		// Checking if there is no duplicates values
		int j = i;
		while (++j < ac)
			if (!ft_strcmp(av[i], av[j]))
				return FALSE;
	}
	
	return TRUE;
}
