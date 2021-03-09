/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:51:00 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/09 15:53:33 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

int main(int ac, char **av)
{
	int i;
	int debug;
	t_node* endA;
	t_node* endB;

	i = 0;
	debug = TRUE;
	// FAIRE CHECK DES ERREURS

	// If no arguments
	// if (ac == 1 || (ac == 2 && !ft_strcmp("-v", av[1])))
	// 	return 0;
	// // if option -v
	// else if (!ft_strcmp("-v", av[1]))
	// {
	// 	debug = TRUE;
	// 	++i;
	// }
	
	endA = newEndNode();
	endB = newEndNode();

	while(++i < ac)
		push_back(endA, ft_atoi(av[i]));

	printStacks(endA, endB, debug, sa_sb(endA, SA));

	printStacks(endA, endB, debug, pa_pb(endB, endA, PB));
	printStacks(endA, endB, debug, pa_pb(endB, endA, PB));
	printStacks(endA, endB, debug, pa_pb(endB, endA, PB));

	printStacks(endA, endB, debug, ra_rb(&endA, RA));
	printStacks(endA, endB, debug, ra_rb(&endB, RB));

	printStacks(endA, endB, debug, rra_rrb(&endA, RRA));
	printStacks(endA, endB, debug, rra_rrb(&endB, RRB));

	printStacks(endA, endB, debug, sa_sb(endA, SA));

	printStacks(endA, endB, debug, pa_pb(endA, endB, PA));
	printStacks(endA, endB, debug, pa_pb(endA, endB, PA));
	printStacks(endA, endB, debug, pa_pb(endA, endB, PA));

	return 0;
}