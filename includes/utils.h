/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:34:50 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/25 14:12:06 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H


/* ------------------------------------------------------------- */
/* --------------------------- DEFINES ------------------------- */

#define FALSE 0
#define TRUE 1

#define STACK_A 1
#define STACK_B -1

enum e_instructions { INIT, SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR };

int compteur;


/* ------------------------------------------------------------- */
/* -------------------------- VARIABLES ------------------------ */

typedef struct		s_node
{
	int				data;	// Integer that need to be sorted, or list' size 
							// if this is the neutral node at the end.
	int				color;	// If true, data will be print with color.
	struct s_node*  prev;	// Pointer to previous node.
	struct s_node*  next;	// Pointer to next node.
}					t_node;

typedef struct	s_allocMem
{
	t_node*	endA;			// Neutral node of the first stack.
	t_node* endB;			// Neutral node of the second stack.
	t_node* smallIns;		// List of instructions for small stack algo.
	t_node* quickIns;		// List of instructions for quicksort algo.
	t_node* selecIns;		// List of instructions for selec algo.
}				t_allocMem;

typedef struct s_sizeParts
{
	int infPartSize;		// Size of the inferior part of a serie to sort (to begin to median included)
	int infPartStack;
	int supPartSize;		// Size of the superior part of a serie to sort (to median + 1 to end excluded)
	int supPartStack;
}				t_sizeParts;


/* ------------------------------------------------------------- */
/* --------------------- CHECK_AND_ERRORS.C -------------------- */

/**
*	Deallocates all lists previously allocated, including their neutral
*	nodes. Does nothing if an argument is  NULL;
*
*	@param st		Pointer to a structure containing 2 pointers to stack A and stack B.
*	@param instruct	Set of instructions implemented as a list, will be deallocated.
*/
void cleanExit(t_allocMem* st, int ret);


/**
*
*/
void errorMsg(t_allocMem* st);

int checkIfInt(char *str, int numOfDigits);

int checkArgs(int ac, char **av, int* debug);


/* ------------------------------------------------------------- */
/* ----------------------- MANAGE_STACK.C ---------------------- */

/**
*   Creates a new neutral node. For this node, data represents the size and 
*	is set to 0.
*
*	@return	The new neutral node allocated.
*/
t_node* newEndNode(t_allocMem* st);

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
t_node* createNode(t_allocMem* st, const int val);

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
*	@return			True if the element was correctly added, false if an error occured.
*/
int push_back(t_allocMem* st, t_node* endList, const int val);

/**
*   Adds a new element at the beginning of the list, before its current first element.
*   Size is increased. If list is empty, the new element becomes first list element.
*
*   @param endList	The neutral node of the list receiving the new element.
*   @param val		The new element will have his data sets to val.
*	@return			True if the element was correctly added, false if an error occured.
*/
int push_front(t_allocMem* st, t_node* endList, const int val);

/**
*   Prints the name of the operation on STDOUT.
*
*   @param opNumber	The operation number used to determinate which operation's name needs 
*					to be printed.
*/
void printOpName(int opNumber);

/**
*   Prints node's data on STDOUT with / without color (depend if data was affected by the 
*	last operation or not).
*
*   @param node	His data will be print.
*/
void printNode(t_node* node);

/**
*   Prints the operation's name and the two stacks on STDOUT if debug option is activated.
*
*   @param opNumber	The operation number used to determinate which operation's name needs 
*					to be printed.
*	@param st		Pointer to a structure containing 2 pointers to stack A and stack B.
*	@param debug	If TRUE, the function will print the stacks. Does nothing otherwise.
*/
void printStacks(int opNumber, t_allocMem* st, int debug);


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

/**
*	Calls the appropriate instruction, and adds it to the list of instructions.
*
*	@param instruct			The list of instruction that will be increased by the instruction to
*							execute.
*	@param st				Pointer to a structure containing 2 pointers to stack A and stack B.
*	@param debug			If true, the stacks will be printed on STDOUT after the 
*							instruction execution.
*	@param instructToExe	The instruction to execute (sa, sb, ss, pa, pb, ra, rb, 
*							rr, rra, rrb, rrr).
*	@return					True if instruct param was an existing instruction. False otherwise.
*/
int execInstructPushSwap(t_node* instruct, t_allocMem* st, int debug, int instructToExe);

/**
*	Calls the appropriate instruction.
*
*	@param st				Pointer to a structure containing 2 pointers to stack A and stack B.
*	@param debug			If true, the stacks will be printed on STDOUT after the 
*							instruction execution.
*	@param instructToExe	The instruction to execute (sa, sb, ss, pa, pb, ra, rb, 
*							rr, rra, rrb, rrr).
*	@return					True if instruct param was an existing instruction. False otherwise.
*/
int execInstructChecker(t_allocMem* st, int debug, char *instructToExe);


#endif