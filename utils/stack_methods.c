/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:08:12 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/11 12:28:19 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

int sa_sb(t_node* endList, int opNumber)
{
	if (endList->data <= 1)
		return opNumber;

	swapNodesData(&endList->next->data, &endList->next->next->data);
	return opNumber;
}

int ss(t_node* endA, t_node* endB)
{
	sa_sb(endA, SA);
	sa_sb(endB, SB);
	return SS;
}

int pa_pb(t_node* stackReceiving, t_node* stackGiving, int opNumber)
{
	// If the stack is empty and has no element to give, do nothing
	if (!stackGiving->data)
		return opNumber;
		
	t_node* tmp = stackGiving->next;
		
	// removing node from the giving stack
	tmp->next->prev = stackGiving;
	stackGiving->next = tmp->next;

	// Inserting node into the receiving stack
	tmp->prev = stackReceiving;
	tmp->next = stackReceiving->next;
	stackReceiving->next->prev = tmp;
	stackReceiving->next = tmp;

	++(stackReceiving->data);
	--(stackGiving->data);

	return opNumber;
}

int ra_rb(t_node** endList, int opNumber)
{
	if ((*endList)->data <= 1)
		return opNumber;
	
	swapNodesData(&(*endList)->next->data, &(*endList)->data);
	*endList = (*endList)->next;

	return opNumber;
}

int rr(t_node** endA, t_node** endB)
{
	ra_rb(endA, RA);
	ra_rb(endB, RB);
	return RR;
}

int rra_rrb(t_node** endList, int opNumber)
{
	if ((*endList)->data <= 1)
		return opNumber;
	
	swapNodesData(&(*endList)->prev->data, &(*endList)->data);
	*endList = (*endList)->prev;
	return opNumber;
}

// rrr : rra and rrb at the same time
int rrr(t_node** endA, t_node** endB)
{
	rra_rrb(endA, RRA);
	rra_rrb(endB, RRB);
	return RRR;
}
