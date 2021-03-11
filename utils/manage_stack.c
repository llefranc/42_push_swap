/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:06:35 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/11 12:49:49 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

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
	if (opNumber == INIT)
		ft_putstr_fd("Init stacks:\n\n", 1);
	else if (opNumber == SA)
		ft_putstr_fd("Exec sa:\n\n", 1);
	else if (opNumber == SB)
		ft_putstr_fd("Exec sb:\n\n", 1);
	else if (opNumber == SS)
		ft_putstr_fd("Exec ss:\n\n", 1);
	else if (opNumber == PA)
		ft_putstr_fd("Exec pa:\n\n", 1);
	else if (opNumber == PB)
		ft_putstr_fd("Exec pb:\n\n", 1);
	else if (opNumber == RA)
		ft_putstr_fd("Exec ra:\n\n", 1);
	else if (opNumber == RB)
		ft_putstr_fd("Exec rb:\n\n", 1);
	else if (opNumber == RR)
		ft_putstr_fd("Exec rr:\n\n", 1);
	else if (opNumber == RR)
		 ft_putstr_fd("Exec rra:\n\n", 1);
	else if (opNumber == RR)
		 ft_putstr_fd("Exec rrb:\n\n", 1);
	else if (opNumber == RR)
		 ft_putstr_fd("Exec rrr:\n\n", 1);
}

void printStacks(int opNumber, t_node* endA, t_node* endB, int debug)
{
	if (!debug)
		return ;
	
	int i = 0;
	t_node* tmpA = endA->next;
	t_node* tmpB = endB->next;

	printOpName(opNumber);
	while (tmpA != endA || tmpB != endB)
	{		
		if (tmpA != endA && (endA->data >= endB->data
				|| (endB->data - i == endA->data)))
				// || (endA->data < endB->data && endA->data + i == endB->data)))
		{
			ft_printf("%d", tmpA->data);
			tmpA = tmpA->next;
		}
		ft_printf("\t");

		if (tmpB != endB && (endB->data >= endA->data
				|| (endA->data - i == endB->data)))
				// || (endB->data < endA->data && endB->data + i == endA->data)))
		{
			ft_printf("%d", tmpB->data);
			tmpB = tmpB->next;
		}
		ft_putchar_fd('\n', 1);

		if (endA->data +i != endB->data && endA->data != endB->data + i)
			++i;
	}
	ft_printf("\n-\t-\nA\tB\n----------------------------------------\n\n");
}