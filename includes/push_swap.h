/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:32:46 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/19 12:11:19 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

struct t_node;

// Sorts an array
void sortArray(int* array, int size);

// Copies all elements between begin and end (not included) into an array
void copyIntoArray(t_node *begin, t_node* end, int* array);

// Creates an array of same size than elemtns between begin and end (not included)
int* createArray(t_node* begin, t_node* end, int* size);

// return median value
t_node* findMed(t_node* begin, t_node* end);


#endif