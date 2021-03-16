/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:02:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/16 16:46:09 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

// si nbInstruct est un nombre neg > rra ; si nombre pos > ra
// si la fonction return 0 pas de nombre inferieur au median a transferer
int findNextNumberToMove(t_node* endList, int med, int *raIns, int *rraIns)
{
	int fromTop = 0;
	int fromBot = -1; // Because we need one rra instruction minimum to put it at top of stack

	// Checking from the top for the first number <= to median number (ra instruct)
	t_node* tmp = endList->next;
	while (tmp != endList)
	{
		if (tmp->data <= med)
			break;
		tmp = tmp->next;
		++fromTop;
	}

	// Case there is no number <= to median number in the stack
	if (tmp == endList)
		return FALSE;

	// Checking from the bottom (rra instruct)
	tmp = endList->prev;
	while (tmp != endList)
	{
		if (tmp->data <= med)
			break;
		tmp = tmp->prev;
		--fromBot;
	}

	*raIns = fromTop;
	*rraIns = fromBot;

	return TRUE;
}

int findSpecificNumberToMove(t_node* endList, int numberToFind, int *raIns, int *rraIns)
{
	int fromTop = 0;
	int fromBot = -1; // Because we need one rra instruction minimum to put it at top of stack

	// Checking from the top for the first number <= to median number (ra instruct)
	t_node* tmp = endList->next;
	while (tmp != endList)
	{
		if (tmp->data == numberToFind)
			break;
		tmp = tmp->next;
		++fromTop;
	}

	// Case there is no number <= to median number in the stack
	if (tmp == endList)
		return FALSE;

	// Checking from the bottom (rra instruct)
	tmp = endList->prev;
	while (tmp != endList)
	{
		if (tmp->data == numberToFind)
			break;
		tmp = tmp->prev;
		--fromBot;
	}

	*raIns = fromTop;
	*rraIns = fromBot;

	return TRUE;
}