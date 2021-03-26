/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:04:39 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/26 13:17:55 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

// Transforming rr instructions into rrr instructions
void rr_rrr_Opti(t_node* endNode, t_node** node, int caseRrr)
{
	t_node* tmp = (*node)->next;

	while (tmp != endNode)
	{
		// Will alter order 
		if (tmp->data == PA || tmp->data == PB || tmp->data == SB || tmp->data == SA)
			break ;
		
		// RA + RRA = useless
		if (((*node)->data == RA + caseRrr && tmp->data == RRA - caseRrr) ||
				((*node)->data == RB + caseRrr && tmp->data == RRB - caseRrr))
		{
			deleteNode(tmp);
			tmp = *node;
			*node = (*node)->prev;
			deleteNode(tmp);
			return ;
		}

		tmp = tmp->next;
	}

	tmp = (*node)->next;
	while (tmp != endNode)
	{
		// Will alter order 
		if (tmp->data == PA || tmp->data == PB || tmp->data == SB || tmp->data == SA)
			break ;

		// Double instruction, we replace it with RR
		if (((*node)->data == RA + caseRrr && tmp->data == RB + caseRrr) ||
				((*node)->data == RB + caseRrr && tmp->data == RA + caseRrr))
		{
			(*node)->data = RR + caseRrr;
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
			rr_rrr_Opti(instruct, &tmp, 0);
		else if (tmp->data == RRA || tmp->data == RRB)
			rr_rrr_Opti(instruct, &tmp, 3);
		else if (tmp->data == PA || tmp->data == PB)
			papbOpti(instruct, &tmp);
		else if (tmp->data == SA || tmp->data == SB)
			ssOpti(instruct, &tmp);
		
		tmp = tmp->next;
	}
}