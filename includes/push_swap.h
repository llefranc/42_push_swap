/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:56:44 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/15 17:28:31 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

struct t_node;
struct t_twoStacks;

// Allocates an array and copies into it all the values from the list
int* copyListIntoArray(t_node *endA);

// Find the median value in list of arguments. If a malloc failed, returns false
int findMedianInArgs(t_node* endA, int *med);

// sets raIns and rraIns to the number of instruction needed to bring the number to 
// transfer to the top of the stack
// si la fonction return 0 pas de nombre inferieur au median a transferer
int findNextNumberToMove(t_node* endList, int med, int *raIns, int *rraIns);

// Sets raIns/rbIns and rraIns/rrbIns to the number of instruction needed to bring a couple 
// to swap at the top of stack A/B
int findCoupleToSwap(t_node* endList, t_node* startingNode, int *rIns, int *rrIns, int (*comp)(int, int));


// // Sets raIns and rraIns to the number of instruction needed to bring a couple 
// // to swap at the top of A stack
// int findCoupleToSwapInA(t_node* endA, int *raIns, int *rraIns);

// // Sets rbIns and rrbIns to the number of instruction needed to bring a couple 
// // to swap at the top of B stack
// int findCoupleToSwapInB(t_node* endB, int *rbIns, int *rrbIns);

// A FUSIONNER
void bringCoupleToSwapToTheTopOfA(t_twoStacks* st, int raIns, int rraIns);

// A FUSIONNER
void bringCoupleToSwapToTheTopOfB(t_twoStacks* st, int rbIns, int rrbIns);

// Compares if it's better to use rr / ra / rb instructions or rrr / rra / rrb
// instructions to move two couples of datas that need to be swapped to the top 
// of both stacks (in order to use ss instruction)
void bringTwoCouplesToSwapToTheTop(t_twoStacks* st, int raIns, int rraIns, int rbIns, int rrbIns);

// check if a sa need to occured (first in A > to second in A)
int checkSaInstruct(t_node* endA);

// chheck if a sb need to occured (first in b < to second in B, because B is in reverse order)
int checkSbInstruct(t_node* endB);

// Returns true if a SS instruction can occured (first / second of A and first / second of B
// both need to be swapped)
int checkSsInstruct(t_twoStacks* st, int med);


// ------------ CHECK IF SORTED -------------------
int less(int a, int b);

int more(int a, int b);

t_node* getMin(t_node* endList);

t_node* getMax(t_node* endList);

// Starts form min / value and use comp function to check if stack is sorted
int checkIfSorted(t_node* endList, t_node* startingNode, int (*comp)(int, int));

#endif