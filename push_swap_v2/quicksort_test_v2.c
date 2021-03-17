/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_test_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:44:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/17 15:33:57 by llefranc         ###   ########.fr       */
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

// whichStack = 1 > A, -1 > B
t_node* parti(t_twoStacks* st, t_node* list, t_node* begin, t_node* end, int whichStack)
{
	global++;
	
	t_node* med;
	if (!(med = findMed(begin, end)))
		return NULL;

	// si size de 2 on swap A VOIR SI JE LAISSE
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

	printf("med = %d\n", med->data);

	t_node* tmp = begin;
	while (tmp != end)
	{
		if (tmp->data < med->data)
			push_fro
	}
	swapNodesData(&j->data, &med->data);
	setIndex(list);

	// printf("parti = ");
	// printList(list);
	// printf("\n");
	
	return j;
}

// void quicksort_test(t_twoStacks* st, t_node* begin, t_node* end)
// {	
// 	if (begin->color < end->color)
// 	{
// 		t_node* med = parti(list, begin, end);

// 		if (!(begin->next->next == end))
// 		{
// 			quicksort_test(list, begin, med);
// 			quicksort_test(list, med->next, end);
// 		}
// 	}
// }

// quicksort avec 2 stacks
// >> on push sur B les inf et median, et on remonte le med au dessus
// >> on push sur A les sup et median, et on remonte le median au dess
// >> si serie de 2 ou 3 sur le haut de la stack A, on swap et on les push en dessous >> ra
// >> si serie de 2 ou 3 sur B >> on repush sur A

int main(int ac, char **av)
{
	t_twoStacks st;
	st.endA = newEndNode();
	st.endB = newEndNode();

	// Creating stack A
	int i = 0;
	while (++i < ac)
		push_back(st.endA, ft_atoi(av[i]));

	setIndex(st.endA);
	printStacks(INIT, &st, TRUE);

	// parti(endA, endA->next, endA);
	// quicksort_test(st.endA, st.endA->next, st.endA);

	printf("en %d reccursion\n", global);
}