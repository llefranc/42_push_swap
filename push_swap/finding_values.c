/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:55:14 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/16 11:38:27 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

// Allocates an array and copies into it all the values from the list
int* copyListIntoArray(t_node *endA)
{
	int* array;

	// Allocating an array of the size of args list
	if (!(array = malloc(sizeof(*array) * endA->data)))
		return NULL;
	
	t_node* tmp = endA->next;

	int i = -1;
	while (tmp != endA)
	{
		array[++i] = tmp->data;
		tmp = tmp->next;
	}

	return array;
}

// Find the median value in list of arguments. If a malloc failed, returns false
int findMedianInArgs(t_node* endA, int *med)
{
	int *array;

	if (!(array = copyListIntoArray(endA)))
		return FALSE;

	// Sorting the array
    int i = -1;
	while (++i < endA->data)
    {
		int j = i;
        
        while (++j < endA->data)
			if (array[i] > array[j])
				swapNodesData(&array[i], &array[j]);
    }

	// Finding median in sorted array (all values < to median 
	// will be moved to stack B, including itself).
	int medPosition = endA->data / 2;
	*med = endA->data > 1 ? array[medPosition - 1] : array[0];

	free(array);
	return TRUE;
}

// si nbInstruct est un nombre neg > rra ; si nombre pos > ra
// si la fonction return 0 pas de nombre inferieur au median a transferer
int findNextNumberToMove(t_node* endList, int med, int *raIns, int *rraIns)
{
	int fromTop = 0;
	int fromBot = -1; // Because we need one rra instruction minimum to put it at top of stack

	// Checking from the top for the first number <= to median number (ra instruct)
	t_node* tmp = endList->next;
	while (tmp != endList)
	{
		if (tmp->data <= med)
			break;
		tmp = tmp->next;
		++fromTop;
	}

	// Case there is no number <= to median number in the stack
	if (tmp == endList)
		return FALSE;

	// Checking from the bottom (rra instruct)
	tmp = endList->prev;
	while (tmp != endList)
	{
		if (tmp->data <= med)
			break;
		tmp = tmp->prev;
		--fromBot;
	}

	*raIns = fromTop;
	*rraIns = fromBot;

	return TRUE;
}

int prevNodeData(t_node* endList, t_node* node)
{
	if (node->prev == endList)
		return endList->prev->data;
	return node->prev->data;
}

int nextNodeData(t_node* endList, t_node* node)
{
	if (node->next == endList)
		return endList->next->data;
	return node->next->data;
}

int findCoupleToSwap(t_node* endList, t_node* startingNode, int *rIns, int *rrIns, int (*comp)(int, int))
{
	// starting node is min for A, max for B. comp is less for A, more for B
	if (checkIfSorted(endList, startingNode, comp))
		return FALSE;

	int fromTop = 0;
	
	// Checking from the top for the first couple to swap (r instruct)
	t_node* tmp = endList->next;
	while (tmp->next != endList)
	{
		if (!comp(prevNodeData(endList, tmp), tmp->data) && !comp(tmp->data, tmp->next->data)) // Need to swap, comp will be less func for A, more for B
			break;
		tmp = tmp->next;
		++fromTop;
	}

	// Case there is no number <= to median number in the stack
	if (tmp->next == endList)
		return FALSE;
	
	int fromBot = -1; // Case the couple to swap is first at top of stack, second at bot of stack,
					  // we need 1 rr instruction to bring the second member to the top of stack

	// Checking from the bottom (rr instruct)
	// if (comp(endList->prev->data, endList->next->data)) // if false, one rra move needed and fromBot was set above to -1
	// {
		tmp = endList->prev;
		while (tmp->prev != endList)
		{
			if (!comp(tmp->data, nextNodeData(endList, tmp)) && !comp(tmp->prev->data, tmp->data)) // Need to swap, comp will be less func for A, more for B
				break;
			tmp = tmp->prev;
			--fromBot;
		}
	// }

	*rIns = fromTop;
	*rrIns = fromBot;

	return TRUE;
}

// // Sets raIns (0 or positive number) and rraIns (negative number) to indicates how many moves 
// // need to occured in A to bring a couple to swap at top of A (sa instruct)
// int findCoupleToSwapInA(t_node* endA, int *raIns, int *rraIns)
// {
// 	// Stack is empty or contains only one elem or is already sorted
// 	if (checkIfSorted(endA, getMin(endA), &less))
// 		return FALSE;

// 	int fromTop = 0;
// 	int fromBot = -1; // Case the couple to swap is first at top of A, second at bot of A,
// 					  // we need 1 rra instruction to bring the second member to the top of A

// 	// Checking from the top for the first couple to swap (first > second) (ra instruct)
// 	t_node* tmp = endA->next;
// 	while (tmp->next != endA)
// 	{
// 		if (tmp->data > tmp->next->data) // Need to swap
// 			break;
// 		tmp = tmp->next;
// 		++fromTop;
// 	}

// 	// Case there is no number <= to median number in the stack
// 	if (tmp == endA)
// 		return FALSE;
	
// 	// Checking from the bottom (rra instruct)
// 	if (!(endA->next->data < endA->prev->data))
// 	{
// 		t_node* tmp = endA->prev;
// 		while (tmp->prev != endA)
// 		{
// 			if (tmp->data < tmp->prev->data) // Need to swap 
// 				break;
// 			tmp = tmp->prev;
// 			--fromBot;
// 		}
// 	}

// 	*raIns = fromTop;
// 	*rraIns = fromBot;

// 	return TRUE;
// }

// // Sets rbIns (0 or positive number) and rrbIns (negative number) to indicates how many moves 
// // need to occured in B to bring a couple to swap at top of B (sb instruct)
// int findCoupleToSwapInB(t_node* endB, int *rbIns, int *rrbIns)
// {
// 	// Stack is empty or contains only one elem or is already sorted
// 	if (checkIfSorted(endB, getMax(endB), &more))
// 		return FALSE;

// 	int fromTop = 0;
// 	int fromBot = -1; // Case the couple to swap is first at top of A, second at bot of A,
// 					  // we need 1 rra instruction to bring the second member to the top of A

// 	// Checking from the top for the first couple to swap (first > second) (ra instruct)
// 	t_node* tmp = endB->next;
// 	while (tmp->next != endB)
// 	{
// 		if (tmp->data < tmp->next->data) // Need to swap
// 			break;
// 		tmp = tmp->next;
// 		++fromTop;
// 	}

// 	// Case there is no number <= to median number in the stack
// 	if (tmp == endB)
// 		return FALSE;
	
// 	// Checking from the bottom (rra instruct)
// 	if (!(endB->next->data > endB->prev->data))
// 	{
// 		t_node* tmp = endB->prev;
// 		while (tmp->prev != endB)
// 		{
// 			if (tmp->data > tmp->prev->data) // Need to swap 
// 				break;
// 			tmp = tmp->prev;
// 			--fromBot;
// 		}
// 	}

// 	*rbIns = fromTop;
// 	*rrbIns = fromBot;

// 	return TRUE;
// }

void bringCoupleToSwapToTheTopOfA(t_twoStacks* st, int raIns, int rraIns)
{
	if (raIns <= -rraIns)
	{
		while (raIns--)
			execInstruct(st, TRUE, "ra");
	}
	else
	{
		while (rraIns++)
			execInstruct(st, TRUE, "rra");
	}
}

void bringCoupleToSwapToTheTopOfB(t_twoStacks* st, int rbIns, int rrbIns)
{
	if (rbIns <= -rrbIns)
	{
		while (rbIns--)
			execInstruct(st, TRUE, "rb");
	}
	else
	{
		while (rrbIns++)
			execInstruct(st, TRUE, "rrb");
	}
}

// calcule le meilleur a utiliser entre les rr et les rrr instructs
// Ensuite execute le nombre de rr / rrr instructions communes aux 2 couples, et 
// complete avec ra / rb /// rra / rrb pour finir d'aligner les 2 couples
void bringTwoCouplesToSwapToTheTop(t_twoStacks* st, int raIns, int rraIns, int rbIns, int rrbIns)
{
	int rrIns;
	int rrrIns;

	rrIns = raIns > rbIns ? raIns : rbIns;
	rrrIns = rraIns < rrbIns ? rraIns : rrbIns; // cause neg values
	
	ft_printf("rrins = %d, rrrIns = %d\n", rrIns, rrrIns);
	
	// RR instructions, putting rrr to absolute value for comparison
	if (rrIns <= -rrrIns)
	{
		// Minimum between number of ra and rb correspond to number of rr
		rrIns = raIns < rbIns ? raIns : rbIns;

		// Substrating number of rr instructions that will occured
		raIns -= rrIns;
		rbIns -= rrIns;

		while (rrIns--)
			execInstruct(st, TRUE, "rr");
		
		while (raIns--)
			execInstruct(st, TRUE, "ra");
		
		while (rbIns--)
			execInstruct(st, TRUE, "rb");
	}

	// RRR instructions
	else
	{
		// Minimum between number of rra and rrb correspond to number of rrr
		rrrIns = rraIns > rrbIns ? rraIns : rrbIns; // cause neg values

		// Substrating number of rr instructions that will occured
		rraIns -= rrrIns;
		rrbIns -= rrrIns;

		while (rrrIns++)
			execInstruct(st, TRUE, "rrr");
		
		while (rraIns++)
			execInstruct(st, TRUE, "rra");
		
		while (rrbIns++)
			execInstruct(st, TRUE, "rrb");
	}
	
}

// check if a sa need to occured (first in A > to second in A)
int checkSaInstruct(t_node* endA)
{
	if (endA->data < 2)
		return FALSE;

	return endA->next->data > endA->next->next->data;
}

// chheck if a sb need to occured (first in b < to second in B, because B is in reverse order)
int checkSbInstruct(t_node* endB)
{
	if (endB->data < 2)
		return FALSE;

	return endB->next->data < endB->next->next->data;
}

// Returns true if a SS instruction can occured (first / second of A and first / second of B
// both need to be swapped)
int checkSsInstruct(t_twoStacks* st, int med)
{
	// Both stacks need at least 2 elems
	if (st->endA->data < 2 || st->endB->data < 2)
		return FALSE;

	// If first and second element at top of A are in the same group (inf or sup to med)
	if (((st->endA->next->data >= med && st->endA->next->next->data >= med) ||
			(st->endA->next->data < med && st->endA->next->next->data < med)) &&
	
	// and if first and second element at top of B are in the same group (inf or sup to med)
			((st->endB->next->data >= med && st->endB->next->next->data >= med) ||
			(st->endB->next->data < med && st->endB->next->next->data < med)) &&

	// and if sa and sb can occured
			(checkSaInstruct(st->endA) &&checkSbInstruct(st->endB)))
		return TRUE;
	
	return FALSE;
}