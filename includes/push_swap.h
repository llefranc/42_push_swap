/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:32:46 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/22 18:01:26 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

struct t_node;

// ---------- FINDING_MEDIAN.C ----------

// Sorts an array
void sortArray(int* array, int size);

// Copies all elements between begin and end (not included) into an array
void copyIntoArray(t_node *begin, t_node* end, int* array);

// Creates an array of same size than elemtns between begin and end (not included)
int* createArray(t_node* begin, t_node* end, int* size);

// return median value
t_node* findMed(t_node* begin, t_node* end);


// ---------- STACK_SIZES.C ----------

// Checks if all elements between begin and end are sorted (neutral node shouldn't be included between begin and end)
int isSorted(t_node* begin, t_node* end, int whichStack);

// Returns number of elements between begin (included) and end (not included)
int sizeList(t_node* begin, t_node* end);

// Returns the end of a serie of elements with a specific size and a specific beginning.
t_node* getEndNode(t_node* begin, int size);

// Calculates inferior part size and superior part size of the serie to sort. If the serie to 
// sort is on stack A, median will be counted as in inferior part; otherwise if the serie is on 
// stack B the media will be counted as in superior part.
void calcSizeParts(t_sizeParts* sizeParts, t_node* begin, t_node* end, int med, int whichStack);


// ---------- PUSH_TO_STACK.C ----------

// Returns true if the median or a value superior to the median is present in 
// stack B, and sets the number of rb instruct to bring this value to top of 
// stack B in order to push it to A.
int findNumberInBToPushToA(t_node* endB, t_node* end, int med, int *rb);

// Pushes from stack B the median and all values superior to itself to stack A. 
// After this, the median will be in A and at its correct position in the serie,
// and so will be sorted.
void pushToA(t_node* instruct, t_twoStacks* st, t_node* end, int med);

// Returns true if the median or a value inferior to the median is present in 
// stack A, and sets the number of ra instruct to bring this value to top of 
// stack A in order to push it to B.
int findNumberInAToPushToB(t_node* endA, t_node* end, int med, int *ra);

// Pushes from stack A the median and all values inferior to itself to stack B. 
// After this, the median will be in B and at its correct position in the serie,
// and so will be sorted.
void pushToB(t_node* instruct, t_twoStacks* st, t_node* end, int med);


void pushToAOpti(t_node* instruct, t_twoStacks* st, t_node* end, int med);


// ---------- QUICKSORT.C ----------

t_sizeParts* partitionning(t_node* instruct, t_twoStacks* st, int totalSize, int whichStack);

void quicksort(t_node* instruct, t_twoStacks* st, int totalSize, int whichStack);


// ---------- PUSH_SWAP.C ----------

// si nbInstruct est un nombre neg > rra ; si nombre pos > ra
// si la fonction return 0 pas de nombre inferieur au median a transferer
int findNextNumberToMove(t_node* endList, int med, int *raIns, int *rraIns);

// sorts only on A, possible opti for B
void sortTwoOrThreeElemsOnA(t_node* instruct, t_twoStacks* st, int size);

t_sizeParts* initPartitionning(t_node* instruct, t_twoStacks* st);


// ---------- OPTI.C ----------

void ssOpti(t_node* endNode, t_node** node);

void papbOpti(t_node* endNode, t_node** node);

void rrrOpti(t_node* endNode, t_node** node);

void rrOpti(t_node* endNode, t_node** node);

void removeUselessInstructions(t_node* instruct);

#endif