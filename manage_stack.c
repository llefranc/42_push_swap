/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:06:35 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/09 15:52:52 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

t_node* newEndNode()
{
	t_node* endList;
	
	endList = malloc(sizeof(t_node));
	endList->next = endList;
	endList->prev = endList;

	// Will store the list size
	endList->data = 0;

	return endList;
}

void deleteNode(t_node *toDelete)
{
	// Linking previous and next element together
	toDelete->prev->next = toDelete->next;
	toDelete->next->prev = toDelete->prev;

	free(toDelete);
}

t_node* createNode(const int val)
{
	t_node* newNode = malloc(sizeof(t_node));
	newNode->data = val;

	return newNode;
}

void swapNodesData(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void push_back(t_node* endList, const int val)
{
	t_node* tmp = createNode(val);

	tmp->prev = endList->prev;
	tmp->next = endList;
	endList->prev->next = tmp;
	endList->prev = tmp;
		
	++endList->data;
}

void printOpName(int opNumber)
{
	opNumber == SA ? ft_putstr_fd("Exec sa:\n\n", 1) : 0;
	opNumber == SB ? ft_putstr_fd("Exec sb:\n\n", 1) : 0;
	opNumber == SS ? ft_putstr_fd("Exec ss:\n\n", 1) : 0;
	opNumber == PA ? ft_putstr_fd("Exec pa:\n\n", 1) : 0;
	opNumber == PB ? ft_putstr_fd("Exec pb:\n\n", 1) : 0;
	opNumber == RA ? ft_putstr_fd("Exec ra:\n\n", 1) : 0;
	opNumber == RB ? ft_putstr_fd("Exec rb:\n\n", 1) : 0;
	opNumber == RR ? ft_putstr_fd("Exec rr:\n\n", 1) : 0;
	opNumber == RRA ? ft_putstr_fd("Exec rra:\n\n", 1) : 0;
	opNumber == RRB ? ft_putstr_fd("Exec rrb:\n\n", 1) : 0;
	opNumber == RRR ? ft_putstr_fd("Exec rrr:\n\n", 1) : 0;
}

void printStacks(t_node* endA, t_node* endB, int debug, int opNumber)
{
	if (!debug)
		return ;
	
	t_node* tmpA = endA->next;
	t_node* tmpB = endB->next;

	printOpName(opNumber);
	while (tmpA != endA || tmpB != endB)
	{
		if (tmpA != endA)
		{
			ft_printf("%d", tmpA->data);
			tmpA = tmpA->next;
		}
		ft_printf("\t");
		if (tmpB != endB)
		{
			ft_printf("%d", tmpB->data);
			tmpB = tmpB->next;
		}
		ft_putchar_fd('\n', 1);
	}
	ft_printf("\n-\t-\nA\tB\n----------------------------------------\n\n");
}