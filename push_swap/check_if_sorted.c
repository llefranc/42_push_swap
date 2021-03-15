/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:18:21 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/15 16:47:49 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

int less(int a, int b)
{
	return a < b;
}

int more(int a, int b)
{
	return a > b;
}

t_node* getMin(t_node* endList)
{
	t_node* tmp = endList->next;
	t_node* min = endList->next;

	// Finding minimum value in stack
	while (tmp != endList)
	{
		if (min->data > tmp->data)
			min = tmp;
		tmp = tmp->next;
	}

	return min;
}

t_node* getMax(t_node* endList)
{
	t_node* tmp = endList->next;
	t_node* max = endList->next;

	// Finding minimum value in stack
	while (tmp != endList)
	{
		if (max->data < tmp->data)
			max = tmp;
		tmp = tmp->next;
	}

	return max;
}

int checkIfSorted(t_node* endList, t_node* startingNode, int (*comp)(int, int))
{
	// If stack is empty or contains only one elem
	if (endList->data < 2)
		return TRUE;

	t_node* nextNode;
	t_node* prevNode = startingNode;
	nextNode = (startingNode->next == endList) ? startingNode->next->next : startingNode->next;
	
	// Doing one loop in stack from the minimum / maximum value and checking if every
	// values are sorted
	while (nextNode != startingNode)
	{
		if (!comp(prevNode->data, nextNode->data))
			return FALSE;

		prevNode = nextNode;
		nextNode = (nextNode->next == endList) ? nextNode->next->next : nextNode->next;
	}

	return TRUE;	
}
