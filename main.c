/* ************************************************************************** */
/*	*/
/*		:::	  ::::::::   */
/*   main.c		 :+:	  :+:	:+:   */
/*	+:+ +:+		 +:+	 */
/*   By: llefranc <llefranc@student.42.fr>		  +#+  +:+	   +#+		*/
/*+#+#+#+#+#+   +#+		   */
/*   Created: 2021/03/08 15:48:06 by llefranc		  #+#	#+# */
/*   Updated: 2021/03/08 16:35:30 by llefranc		 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#include "push_swap.h"

typedef struct s_node
{
	int		data;	// Integer that need to be sorted, or list' size 
					// if this is the neutral node at the end
	struct s_node*   prev;	// Pointer to previous node
	struct s_node*   next;	// Pointer to next node
} t_node;

// /**
// *   Create a new endNode. Data isn't constructed.
// */
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

// /**
// *   Destroy Node's content and then deallocate the Node.
// *
// *   @param toDelete The Node to destroy and deallocate.
// */
void deleteNode(t_node *toDelete)
{
	// Linking previous and next element together
	toDelete->prev->next = toDelete->next;
	toDelete->next->prev = toDelete->prev;

	free(toDelete);
}

// /**
// *   Allocate a new Node and copy construct his content from val.
// *
// *   @param val  The content to copy construct.
// *   @return The Node newly created.
// */
t_node* createNode(const int val)
{
	t_node* newNode = malloc(sizeof(t_node));
	newNode->data = val;

	return newNode;
}

// /**
// *   Swaps two variables using references.
// *
// *   @param a		Will be swap with b.
// *   @param b		Will be swap with a.
// */
void swapNodesData(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// sa : swap a - swap the first 2 elements at the top of stack a. Do nothing if there
// is only one or no elements).
void sa(t_node* endListA)
{
	if (endListA->data <= 1)
		return ;
	swapNodesData(&endListA->next->data, &endListA->next->next->data);
}

//  swap b - swap the first 2 elements at the top of stack b. Do nothing if there
// is only one or no elements).
void sb(t_node* endListB)
{
	if (endListB->data <= 1)
		return ;
	swapNodesData(&endListB->next->data, &endListB->next->next->data);
}

// : sa and sb at the same time.
void ss(t_node* endListA, t_node* endListB)
{
	sa(endListA);
	sb(endListB);
}

// : push a - take the first element at the top of b and put it at the top of a. Do
// nothing if b is empty.
void pa(t_node* endListA, t_node* endListB)
{
	// If B is empty, do nothing
	if (!endListB->data)
		return ;
		
	t_node* tmp = endListB->next;
		
	// removing node from B
	tmp->next->prev = endListB;
	endListB->next = tmp->next;

	// Inserting node into A
	tmp->prev = endListA;
	tmp->next = endListA->next;
	endListA->next->prev = tmp;
	endListA->next = tmp;

	++(endListA->data);
	--(endListB->data);
}

//  push b - take the first element at the top of a and put it at the top of b. Do
// nothing if a is empty.
void pb(t_node* endListA, t_node* endListB)
{
	// If B is empty, do nothing
	if (!endListA->data)
		return ;
	
	t_node* tmp = endListA->next;
		
	// removing node from A
	tmp->next->prev = endListA;
	endListA->next = tmp->next;

	// Inserting element into B
	tmp->prev = endListB;
	tmp->next = endListB->next;
	endListB->next->prev = tmp;
	endListB->next = tmp;
		
	++(endListB->data);
	--(endListA->data);
}

// rotate a - shift up all elements of stack a by 1. The first element becomes
// the last one.
void ra(t_node** endListA)
{
	if ((*endListA)->data <= 1)
		return ;
	
	swapNodesData(&(*endListA)->next->data, &(*endListA)->data);
	*endListA = (*endListA)->next;
}

// rotate b - shift up all elements of stack b by 1. The first element becomes
// the last one.
void rb(t_node** endListB)
{
	if ((*endListB)->data <= 1)
		return ;
	
	swapNodesData(&(*endListB)->next->data, &(*endListB)->data);
	*endListB = (*endListB)->next;
}

// r : ra and rb at the same time
void rr(t_node** endListA, t_node** endListB)
{
	ra(endListA);
	rb(endListB);
}

//  reverse rotate a - shift down all elements of stack a by 1. The last element
// becomes the first one.
void rra(t_node** endListA)
{
	if ((*endListA)->data <= 1)
		return ;
	
	swapNodesData(&(*endListA)->prev->data, &(*endListA)->data);
	*endListA = (*endListA)->prev;
}

// rrb : reverse rotate b - shift down all elements of stack b by 1. The last element
// becomes the first one.
void rrb(t_node** endListB)
{
	if ((*endListB)->data <= 1)
		return ;
	
	swapNodesData(&(*endListB)->prev->data, &(*endListB)->data);
	*endListB = (*endListB)->prev;
}

// rrr : rra and rrb at the same time
void rrr(t_node** endListA, t_node** endListB)
{
	rra(endListA);
	rra(endListB);
}

void printStacks(t_node* endListA, t_node* endListB)
{
	t_node* tmpA = endListA->next;
	t_node* tmpB = endListB->next;

	while (tmpA != endListA || tmpB != endListB)
	{
		A FAIRE
	}

}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	return 0;
}