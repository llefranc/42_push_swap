/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_median.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:31:46 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/26 10:50:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

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

t_node* findMed(t_allocMem* st, t_node* begin, t_node* end)
{
	int med = 0;
	int* array;
	int size = 0;

	if (!(array = createArray(begin, end, &size)))
		errorMsg(st);
	
	copyIntoArray(begin, end, array);
	sortArray(array, size);

	int medPosition = size / 2 + size % 2;
	med = size > 1 ? array[medPosition - 1] : array[0];

	t_node *tmp = begin;

	while (tmp->data != med)
		tmp = tmp->next;
	
	free(array);

	return tmp;
}
