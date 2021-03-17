/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_test_v1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:44:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/17 15:14:42 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void setIndex(t_node* list)
{
	t_node* tmp = list->next;

	int index = 0;
	while (tmp != list)
	{
		tmp->color = index++;
		tmp = tmp->next;
	}
	tmp->color = index;
}

void printList(t_node* list)
{
	t_node *tmp = list->next;

	// // printing index
	// while (tmp != list)
	// {
	// 	printf("%d ", tmp->color);
	// 	tmp = tmp->next;
	// }
	// printf("\n");
	
	tmp = list->next;
	while (tmp != list)
	{
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

// Sorts an array
void sortArray(int* array, int size)
{
	int i = -1;
        
	while (++i < size)
	{
		int j = i;

		while (++j < size)
			if (array[i] > array[j])
				swapNodesData(&array[i], &array[j]);
	}
}

void copyIntoArray(t_node *begin, t_node* end, int* array)
{
	t_node* tmp = begin;

	int i = -1;
	while (tmp != end)
	{
		array[++i] = tmp->data;
		tmp = tmp->next;
	}
}

int* createArray(t_node* begin, t_node* end, int* size)
{
	while (begin != end)
	{
		++(*size);
		begin = begin->next;
	}

	int* array;

	if (!(array = malloc(sizeof(*array) * *size)))
		return NULL;
	
	return array;
}

t_node* findMed(t_node* begin, t_node* end)
{
	int med = 0;
	int* array;
	int size = 0;

	if (!(array = createArray(begin, end, &size)))
		return NULL;
	
	copyIntoArray(begin, end, array);
	sortArray(array, size);

	int medPosition = size / 2 + size % 2;
	med = size > 1 ? array[medPosition - 1] : array[0];

	t_node *tmp = begin;

	while (tmp->data != med)
		tmp = tmp->next;

	return tmp;
}

int global;

t_node* parti(t_node* list, t_node* begin, t_node* end)
{
	global++;
	
	t_node* med;
	if (!(med = findMed(begin, end)))
		return NULL;

	// si size de 2
	if (begin->next->next == end)
	{
		if (begin->data > begin->next->data)
		{
			swapNodesData(&begin->data, &begin->next->data);
			med = (med == begin) ? begin->next : begin;
		}
		setIndex(list);
		return med;
	}

	swapNodesData(&begin->data, &med->data);
	med = begin;

	printf("med = %d\n", med->data);

	t_node* i = begin->next;
	t_node* j = end->prev;

	printf("i = %d, j = %d\n", i->data, j->data);

	while (i->color < j->color)
	{
		while (i->data < med->data && i != end)
			i = i->next;
		
		while (j->data > med->data && j != begin)
			j = j->prev;
		
		printf("i->data = %d, j->data = %d\n", i->data, j->data);

		if (i->color < j->color)	
			swapNodesData(&i->data, &j->data);

		printf("loop = ");
		printList(list);
		printf("\n");
	}

	swapNodesData(&j->data, &med->data);
	setIndex(list);

	printf("parti = ");
	printList(list);
	printf("\n");
	
	return j;
}

void quicksort_test(t_node* list, t_node* begin, t_node* end)
{	
	if (begin->color < end->color)
	{
		t_node* med = parti(list, begin, end);

		// evite le quicksort sur 1
		if (!(begin->next->next == end))
		{
			quicksort_test(list, begin, med);
			quicksort_test(list, med->next, end);
		}
	}
}

// quicksort sur une liste OK

int main(int ac, char **av)
{
	t_node* list = newEndNode();

	// Creating stack A
	int i = 0;
	while (++i < ac)
		push_back(list, ft_atoi(av[i]));

	setIndex(list);

	// printf("med = %d\n", findMed(list->next, list)->data);
	quicksort_test(list, list->next, list);

	printList(list);
	printf("en %d reccursion\n", global);
}