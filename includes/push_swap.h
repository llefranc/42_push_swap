/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:56:44 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/12 15:14:30 by llefranc         ###   ########.fr       */
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

// Sets raIns and rraIns to the number of instruction needed to bring a couple 
// to swap at the top of A stack
int findCoupleToSwapInA(t_node* endA, int *raIns, int *rraIns);

// Sets rbIns and rrbIns to the number of instruction needed to bring a couple 
// to swap at the top of B stack
int findCoupleToSwapInB(t_node* endB, int *rbIns, int *rrbIns);

// Compares if it's better to use rr / ra / rb instructions or rrr / rra / rrb
// instructions to move two couples of datas that need to be swapped to the top 
// of both stacks (in order to use ss instruction)
void bringTwoCouplesToSwapToTheTop(t_twoStacks* st, int raIns, int rraIns, int rbIns, int rrbIns);

#endif