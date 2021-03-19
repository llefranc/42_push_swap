/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:39:33 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/19 16:17:24 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

t_sizeParts* partitionning(t_node* instruct, t_twoStacks* st, int totalSize, int whichStack)
{
	// If the serie to sort is 3 elements or less, we don't need quicksort to sort it
	if (totalSize <= 3)
	{
		// Pushing on A first if we are treating elements on B
		int i = 0;
		if (whichStack == STACK_B) // FAIRE UNE FOCNTION QUI SORT POUR B, ET UNE POUR A
			while (i++ < totalSize)
				execInstructPushSwap(instruct, st, TRUE, "pa");
		
		// On stack A, will put the 2 or 3 elements on in the right order and ra 2/3 times to 
		// save them at the end of stack A
		sortTwoOrThreeElemsOnA(instruct, st, totalSize);
		
		// Sorted, no need to return median value, this recursivity loop will stop
		return NULL;
	}

	// Finding begin and end of the serie to sort
	t_node* begin = (whichStack == STACK_A) ? st->endA->next : st->endB->next;
	t_node* end = getEndNode(begin, totalSize);
	
	// Finding median
	t_node* med;
	if (!(med = findMed(begin, end))) // proteger
		return NULL;

	// Finding the size of the two parts of the serie for the next recursive loop
	t_sizeParts* sizeParts;
	sizeParts = malloc(sizeof(*sizeParts)); //proteger
	calcSizeParts(sizeParts, begin, end, med->data, whichStack);

	whichStack == STACK_A ? pushToB(instruct, st, end, med->data) : pushToA(instruct, st, end, med->data);

	return sizeParts;
}

void quicksort(t_node* instruct, t_twoStacks* st, int totalSize, int whichStack)
{
	t_sizeParts* sizeParts = partitionning(instruct, st, totalSize, whichStack);

	if (sizeParts)
	{
		quicksort(instruct, st, sizeParts->infPartSize, STACK_B); // Inferior part will always be pushed to B
		quicksort(instruct, st, sizeParts->supPartSize, STACK_A); // Superior part will always be pushed to A
		free(sizeParts);
	}
}
