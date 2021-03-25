/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sizes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:37:08 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/19 15:37:56 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

// Checks if all elements between begin and end are sorted (neutral node shouldn't be included between begin and end)
int isSorted(t_node* begin, t_node* end, int whichStack)
{
	while (begin != end && begin->next != end) // case 0 elements or just one
	{
		if ((whichStack == STACK_A && begin->data > begin->next->data) ||
				(whichStack == STACK_B && begin->data < begin->next->data))
			return FALSE;
		begin = begin->next;
	}
	return TRUE;
}

// Returns number of elements between begin (included) and end (not included)
int sizeList(t_node* begin, t_node* end)
{
	int size = 0;

	while (begin != end)
	{
		begin = begin->next;
		++size;
	}
	return size;
}

// Returns the end of a serie of elements with a specific size and a specific beginning.
t_node* getEndNode(t_node* begin, int size)
{
	while (size--)
		begin = begin->next;
	return begin;
}

// Calculates inferior part size and superior part size of the serie to sort. If the serie to 
// sort is on stack A, median will be counted as in inferior part; otherwise if the serie is on 
// stack B the media will be counted as in superior part.
void calcSizeParts(t_sizeParts* sizeParts, t_node* begin, t_node* end, int med, int whichStack)
{
	sizeParts->infPartSize = 0;
	sizeParts->supPartSize = 0;
	
	while (begin != end)
	{
		if (begin->data < med)
			sizeParts->infPartSize++;
		else if (begin->data > med)
			sizeParts->supPartSize++;
		begin = begin->next;
	}
	whichStack == STACK_A ? sizeParts->infPartSize++ : sizeParts->supPartSize++;
}
