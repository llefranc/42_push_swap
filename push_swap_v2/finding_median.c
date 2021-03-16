/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_median.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:30:59 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/16 16:41:36 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

// Copy a stack into an array for finding median value
int* copyStackIntoArray(t_node *endList, int* array)
{
	t_node* tmp = endList->next;

	int i = -1;
	while (tmp != endList)
	{
		array[++i] = tmp->data;
		tmp = tmp->next;
	}

	return array;
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

// find a median value in an array of a certain size. Returns FALSE if malloc failed
int findMedianValue(t_node* begin, t_node* end, int* med)
{
	int *array;
	int size = 0;
	t_node* tmp = begin;

	while (tmp != end)
	{
		tmp = tmp->next;
		++size;
	}
	
	if (!(array = malloc(sizeof(*array) * size)))
		return FALSE;

	int i = -1;
	tmp = begin;
	while (tmp != end)
	{
		array[++i] = tmp->data;
		tmp = tmp->next;
	}

	sortArray(array, size);

	// Finding median in sorted array (all values < to median 
	// will be moved to stack B, including itself).
	int medPosition = size / 2 + size % 2;
	ft_printf("medPos = %d, size = %d\n", medPosition, size);
	ft_printf("begin = %d, end = %d\n", begin->data, end->data);
	ft_printf("begin = %p, end = %p\n", begin, end);
	*med = size > 1 ? array[medPosition - 1] : array[0];
	
	i = -1;
	while (++i < size)
		ft_printf("%d ", array[i]);
	ft_printf("\nmed = %d\n", *med);


	free(array);
	return TRUE;
}
