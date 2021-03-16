/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_v2.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:56:44 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/16 16:10:15 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_V2_H
#define PUSH_SWAP_V2_H

struct t_node;
struct t_twoStacks;

// Copies a stack into an array
int* copyStackIntoArray(t_node *endList, int* array);

// Sorts an array
void sortArray(int* array, int size);

// find a median value in an array of a certain size. Returns FALSE if malloc failed
int findMedianValue(t_node* begin, t_node* end, int* med);

// --------------------- FINDING VALUES ------------------------

// si nbInstruct est un nombre neg > rra ; si nombre pos > ra
// si la fonction return 0 pas de nombre inferieur au median a transferer
int findNextNumberToMove(t_node* endList, int med, int *raIns, int *rraIns);

// si nbInstruct est un nombre neg > rra ; si nombre pos > ra
// si la fonction return 0 pas le nombre n'existe pas dans la stack donnée
int findSpecificNumberToMove(t_node* endList, int numberToFind, int *raIns, int *rraIns);


#endif