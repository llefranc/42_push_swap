/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:08:12 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/19 16:14:42 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

int sa_sb(t_node* endList, int opNumber)
{
	if (endList->data <= 1)
		return opNumber;

	endList->next->color = TRUE;
	endList->next->next->color = TRUE;

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
	tmp->color = TRUE;
		
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
	
	(*endList)->color = TRUE;
	
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
	
	(*endList)->color = TRUE;
	
	swapNodesData(&(*endList)->prev->data, &(*endList)->data);
	*endList = (*endList)->prev;
	
	return opNumber;
}

int rrr(t_node** endA, t_node** endB)
{
	rra_rrb(endA, RRA);
	rra_rrb(endB, RRB);
	return RRR;
}

int execInstructChecker(t_twoStacks* st, int debug, char *instructToExe)
{
	compteur++;// a enlever

	if (!ft_strcmp(instructToExe, "sa"))
		printStacks(sa_sb(st->endA, SA), st, debug);
	else if (!ft_strcmp(instructToExe, "sb"))
		printStacks(sa_sb(st->endB, SB), st, debug);
	else if (!ft_strcmp(instructToExe, "ss"))
		printStacks(ss(st->endA, st->endB), st, debug);
	else if (!ft_strcmp(instructToExe, "pa"))
		printStacks(pa_pb(st->endA, st->endB, PA), st, debug);
	else if (!ft_strcmp(instructToExe, "pb"))
		printStacks(pa_pb(st->endB, st->endA, PB), st, debug);
	else if (!ft_strcmp(instructToExe, "ra"))
		printStacks(ra_rb(&st->endA, RA), st, debug);
	else if (!ft_strcmp(instructToExe, "rb"))
		printStacks(ra_rb(&st->endB, RB), st, debug);
	else if (!ft_strcmp(instructToExe, "rr"))
		printStacks(rr(&st->endA, &st->endB), st, debug);
	else if (!ft_strcmp(instructToExe, "rra"))
		printStacks(rra_rrb(&st->endA, RRA), st, debug);
	else if (!ft_strcmp(instructToExe, "rrb"))
		printStacks(rra_rrb(&st->endB, RRB), st, debug);
	else if (!ft_strcmp(instructToExe, "rrr"))
		printStacks(rrr(&st->endA, &st->endB), st, debug);
	else
		return FALSE;

	return TRUE;
}

int execInstructPushSwap(t_node* instruct, t_twoStacks* st, int debug, char *instructToExe)
{
	compteur++;// a enlever

	if (!ft_strcmp(instructToExe, "sa") && push_back(instruct, SA))
		printStacks(sa_sb(st->endA, SA), st, debug);
	else if (!ft_strcmp(instructToExe, "sb") && push_back(instruct, SB))
		printStacks(sa_sb(st->endB, SB), st, debug);
	else if (!ft_strcmp(instructToExe, "ss") && push_back(instruct, SS))
		printStacks(ss(st->endA, st->endB), st, debug);
	else if (!ft_strcmp(instructToExe, "pa") && push_back(instruct, PA))
		printStacks(pa_pb(st->endA, st->endB, PA), st, debug);
	else if (!ft_strcmp(instructToExe, "pb") && push_back(instruct, PB))
		printStacks(pa_pb(st->endB, st->endA, PB), st, debug);
	else if (!ft_strcmp(instructToExe, "ra") && push_back(instruct, RA))
		printStacks(ra_rb(&st->endA, RA), st, debug);
	else if (!ft_strcmp(instructToExe, "rb") && push_back(instruct, RB))
		printStacks(ra_rb(&st->endB, RB), st, debug);
	else if (!ft_strcmp(instructToExe, "rr") && push_back(instruct, RR))
		printStacks(rr(&st->endA, &st->endB), st, debug);
	else if (!ft_strcmp(instructToExe, "rra") && push_back(instruct, RRA))
		printStacks(rra_rrb(&st->endA, RRA), st, debug);
	else if (!ft_strcmp(instructToExe, "rrb") && push_back(instruct, RRB))
		printStacks(rra_rrb(&st->endB, RRB), st, debug);
	else if (!ft_strcmp(instructToExe, "rrr") && push_back(instruct, RRR))
		printStacks(rrr(&st->endA, &st->endB), st, debug);
	else
		return FALSE;

	return TRUE;
}