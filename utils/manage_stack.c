/* ************************************************************************** */
/*    */
/*        :::      ::::::::   */
/*   manage_stack.c :+:      :+:    :+:   */
/*    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*+#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:06:35 by llefranc          #+#    #+# */
/*   Updated: 2021/03/17 12:10:40 by llefranc         ###   ########.fr       */
/*    */
/* ************************************************************************** */

#include "../includes/headers.h"

int compteur = 0;

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
	newNode->color = FALSE;

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

void push_front (t_node* endList, const int val)
{
    t_node* tmp = createNode(val);

    tmp->prev = endList;
    tmp->next = endList->next;
    endList->next->prev = tmp;
    endList->next = tmp;
    
    ++endList->data;
}


void printOpName(int opNumber)
{
	// if (opNumber == INIT)
	// 	ft_putstr_fd("Init stacks:\n\n", 1);
	// else if (opNumber == SA)
	// 	ft_putstr_fd("Exec sa:\n\n", 1);
	// else if (opNumber == SB)
	// 	ft_putstr_fd("Exec sb:\n\n", 1);
	// else if (opNumber == SS)
	// 	ft_putstr_fd("Exec ss:\n\n", 1);
	// else if (opNumber == PA)
	// 	ft_putstr_fd("Exec pa:\n\n", 1);
	// else if (opNumber == PB)
	// 	ft_putstr_fd("Exec pb:\n\n", 1);
	// else if (opNumber == RA)
	// 	ft_putstr_fd("Exec ra:\n\n", 1);
	// else if (opNumber == RB)
	// 	ft_putstr_fd("Exec rb:\n\n", 1);
	// else if (opNumber == RR)
	// 	ft_putstr_fd("Exec rr:\n\n", 1);
	// else if (opNumber == RRA)
	// 	 ft_putstr_fd("Exec rra:\n\n", 1);
	// else if (opNumber == RRB)
	// 	 ft_putstr_fd("Exec rrb:\n\n", 1);
	// else if (opNumber == RRR)
	// 	 ft_putstr_fd("Exec rrr:\n\n", 1);
	if (opNumber == INIT)
		ft_printf("Init stacks:\n\n");
	else if (opNumber == SA)
		ft_printf("ins %d: Exec sa:\n\n", compteur);
	else if (opNumber == SB)
		ft_printf("ins %d: Exec sb:\n\n", compteur);
	else if (opNumber == SS)
		ft_printf("ins %d: Exec ss:\n\n", compteur);
	else if (opNumber == PA)
		ft_printf("ins %d: Exec pa:\n\n", compteur);
	else if (opNumber == PB)
		ft_printf("ins %d: Exec pb:\n\n", compteur);
	else if (opNumber == RA)
		ft_printf("ins %d: Exec ra:\n\n", compteur);
	else if (opNumber == RB)
		ft_printf("ins %d: Exec rb:\n\n", compteur);
	else if (opNumber == RR)
		ft_printf("ins %d: Exec rr:\n\n", compteur);
	else if (opNumber == RRA)
		 ft_printf("ins %d: Exec rra:\n\n",compteur);
	else if (opNumber == RRB)
		 ft_printf("ins %d: Exec rrb:\n\n",compteur);
	else if (opNumber == RRR)
		 ft_printf("ins %d: Exec rrr:\n\n",compteur);
}

void printNode(t_node* node)
{
	if (node->color)
	{
		node->color = FALSE;
		ft_printf("\033[31m%-12d\033[0m", node->data);
	}
	else
	{
		ft_printf("%-12d", node->data);
	}
}

void printStacks(int opNumber, t_twoStacks* st, int debug)
{
	if (!debug)
		return ;
	
	int i = 0;
	t_node* tmpA = st->endA->next;
	t_node* tmpB = st->endB->next;

	printOpName(opNumber);

	while (tmpA != st->endA || tmpB != st->endB)
	{		
		// Printing stack A
		if (tmpA != st->endA && (st->endA->data >= st->endB->data
				|| (st->endB->data - i == st->endA->data)))
		{
			printNode(tmpA);
			tmpA = tmpA->next;
		}

		// If B is taller than A, printing spaces to correctly print B numbers
		else
			ft_printf("%12c", ' ');

		if (tmpB != st->endB && (st->endB->data >= st->endA->data
				|| (st->endA->data - i == st->endB->data)))
		{
			printNode(tmpB);
			tmpB = tmpB->next;
		}
		ft_putchar_fd('\n', 1);

		if (st->endA->data + i != st->endB->data && st->endA->data != st->endB->data + i)
			++i;
	}
	
	ft_printf("\n-%11c-\nA%11cB\n----------------------------------------\n\n", ' ', ' ');
}