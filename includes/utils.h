/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:34:50 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/11 12:30:00 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H


/* ------------------------------------------------------------- */
/* --------------------------- DEFINES ------------------------- */

#define FALSE 0
#define TRUE 1

#define INIT 0
#define SA 1
#define SB 2
#define SS 3
#define PA 4
#define PB 5
#define RA 6
#define RB 7
#define RR 8
#define RRA 9
#define RRB 10
#define RRR 11


/* ------------------------------------------------------------- */
/* -------------------------- VARIABLES ------------------------ */

typedef struct		s_node
{
	int				data;	// Integer that need to be sorted, or list' size 
							// if this is the neutral node at the end
	struct s_node*  prev;	// Pointer to previous node
	struct s_node*  next;	// Pointer to next node
}					t_node;


/* ------------------------------------------------------------- */
/* ----------------------- MANAGE_STACK.C ---------------------- */

/**
*   Creates a new neutral node. For this node, data represents the size and 
*	is set to 0.
*
*	@return	The new neutral node allocated.
*/
t_node* newEndNode();

/**
*   Removes from the list a node deallocates it.
*
*   @param toDelete The node to remove and deallocate.
*/
void deleteNode(t_node *toDelete);

/**
*   Allocates a new node and sets his data .
*
*   @param val  The new node's data.
*   @return		The new node allocated.
*/
t_node* createNode(const int val);

/**
*   Swaps two nodes' data.
*
*   @param a	Will be swap with b.
*   @param b	Will be swap with a.
*/
void swapNodesData(int* a, int* b);

/**
*   Adds a new element at the end of the list, after its current last element.
*   Size is increased. If list is empty, the new element becomes first list element.
*
*   @param endList	The neutral node of the list receiving the new element.
*   @param val		The new element will have his data sets to val.
*/
void push_back(t_node* endList, const int val);

/**
*   Prints the name of the operation on STDOUT.
*
*   @param opNumber	The operation number used to determinate which operation's name needs 
*					to be printed.
*/
void printOpName(int opNumber);

/**
*   Prints the operation's name and the two stacks on STDOUT if debug option is activated.
*
*   @param opNumber	The operation number used to determinate which operation's name needs 
*					to be printed.
*	@param endA		The first stack to print.
*	@param endB		The second stack to print.
*	@param debug	If TRUE, the function will print the stacks. Does nothing otherwise.
*/
void printStacks(int opNumber, t_node* endA, t_node* endB, int debug);


/* ------------------------------------------------------------- */
/* ---------------------- STACK_METHODS.C ---------------------- */

/**
*	sa: swap a - swap the first 2 elements at the top of stack a. Do nothing if there 
*	is only one or no elements).
*	sb: swap b - swap the first 2 elements at the top of stack b. Do nothing if there 
*	is only one or no elements).
*
*	@param endlist	The neutral node of the list to modify.
*	@param opNumber	The method's code number.
*	@return			The method's code number.
*/
int sa_sb(t_node* endList, int opNumber);

/**
*	ss: sa and sb at the same time.
*
*	@param endA	The neutral node of the first list to modify.
*	@param endB	The neutral node of the second list to modify.
*	@return		The method's code number.
*/
int ss(t_node* endA, t_node* endB);

/**
*	pa: push a - take the first element at the top of b and put it at the top of a. Do 
*	nothing if b is empty.
*	pb:	push b - take the first element at the top of a and put it at the top of b. Do 
*	nothing if a is empty.
*
*	@param stackReceiving	The neutral node of the list that's gonna receive the new element.
*	@param stackGiving		The neutral node of the list that's gonna give an element.
*	@param opNumber			The method's code number.
*	@return					The method's code number.
*/
int pa_pb(t_node* stackReceiving, t_node* stackGiving, int opNumber);

/**
*	ra: rotate a - shift up all elements of stack a by 1. The first element becomes 
*	the last one.
*	rb: rotate b - shift up all elements of stack b by 1. The first element becomes 
*	the last one.
*
*	@param endlist	The neutral node of the list to modify.
*	@param opNumber	The method's code number.
*	@return			The method's code number.
*/
int ra_rb(t_node** endList, int opNumber);

/**
*	rr: ra and rb at the same time.
*
*	@param endA	The neutral node of the first list to modify.
*	@param endB	The neutral node of the second list to modify.
*	@return		The method's code number.
*/
int rr(t_node** endA, t_node** endB);

/**
*	rra: reverse rotate a - shift down all elements of stack a by 1. The last element 
*	becomes the first one.
*	rrb: reverse rotate b - shift down all elements of stack b by 1. The last element 
*	becomes the first one.
*
*	@param endlist	The neutral node of the list to modify.
*	@param opNumber	The method's code number.
*	@return			The method's code number.
*/
int rra_rrb(t_node** endList, int opNumber);

/**
*	rrr: rra and rrb at the same time.
*
*	@param endA	The neutral node of the first list to modify.
*	@param endB	The neutral node of the second list to modify.
*	@return		The method's code number.
*/
int rrr(t_node** endA, t_node** endB);

#endif