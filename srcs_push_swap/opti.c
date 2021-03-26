/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:04:39 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/26 13:06:21 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void rrOpti(t_node* endNode, t_node** node)
{
	t_node* tmp = (*node)->next;

	while (tmp != endNode)
	{
		// Will alter order 
		if (tmp->data == PA || tmp->data == PB || tmp->data == SB || tmp->data == SA)
			break ;
		
		// Double instruction, we replace it with RR
		if (((*node)->data == RA && tmp->data == RB) || ((*node)->data == RB && tmp->data == RA))
		{
			(*node)->data = RR;
			deleteNode(tmp);
			return ;
		}

		// RA + RRA = useless
		if (((*node)->data == RA && tmp->data == RRA) || ((*node)->data == RB && tmp->data == RRB))
		{
			deleteNode(tmp);
			tmp = *node;
			*node = (*node)->prev;
			deleteNode(tmp);
			return ;
		}

		tmp = tmp->next;
	}
}

void rrrOpti(t_node* endNode, t_node** node)
{
	t_node* tmp = (*node)->next;

	while (tmp != endNode)
	{
		// Will alter order 
		if (tmp->data == PA || tmp->data == PB || tmp->data == SB || tmp->data == SA)
			break ;
		
		// Double instruction, we replace it with RRR
		if (((*node)->data == RRA && tmp->data == RRB) || ((*node)->data == RRB && tmp->data == RRA))
		{
			(*node)->data = RRR;
			deleteNode(tmp);
			return ;
		}

		// RRA + RA = useless
		if (((*node)->data == RRA && tmp->data == RA) || ((*node)->data == RRB && tmp->data == RB))
		{
			deleteNode(tmp);
			tmp = *node;
			*node = (*node)->prev;
			deleteNode(tmp);
			return ;
		}

		tmp = tmp->next;
	}
}

void papbOpti(t_node* endNode, t_node** node)
{
	t_node* tmp = (*node)->next;

	// Skipping all consecutives PA
	while ((*node)->data == PA && tmp != endNode && tmp->data == PA)
		tmp = tmp->next;
	
	while ((*node)->data == PB && tmp != endNode && tmp->data == PB)
		tmp = tmp->next;

	// PA + PB = useless
	if (tmp != endNode && (((*node)->data == PA && tmp->data == PB) || 
			((*node)->data == PB && tmp->data == PA)))
	{
		deleteNode(tmp);
		tmp = *node;
		*node = (*node)->prev;
		deleteNode(tmp);
	}
}

void ssOpti(t_node* endNode, t_node** node)
{
	t_node* tmp = (*node)->next;

	// Skipping instructions that will not alter a swap on B
	while ((*node)->data == SA && tmp != endNode && (tmp->data == RA || tmp->data == RRA))
		tmp = tmp->next;
	
	// Skipping instructions that will not alter a swap on A
	while ((*node)->data == SB && tmp != endNode && (tmp->data == RB || tmp->data == RRB))
		tmp = tmp->next;
	
	if (tmp != endNode && (((*node)->data == SA && tmp->data == SB) || 
		((*node)->data == SB && tmp->data == SA)))
	{
		(*node)->data = SS;
		deleteNode(tmp);
	}	
}

void removeUselessInstructions(t_node* instruct)
{
	t_node* tmp = instruct->next;

	while (tmp != instruct && tmp->next != instruct)
	{
		if (tmp->data == RA || tmp->data == RB)
			rrOpti(instruct, &tmp);
		else if (tmp->data == RRA || tmp->data == RRB)
			rrrOpti(instruct, &tmp);
		else if (tmp->data == PA || tmp->data == PB)
			papbOpti(instruct, &tmp);
		else if (tmp->data == SA || tmp->data == SB)
			ssOpti(instruct, &tmp);
		
		tmp = tmp->next;
	}
}