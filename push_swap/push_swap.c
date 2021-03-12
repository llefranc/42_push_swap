/* ************************************************************************** */
/*    */
/*        :::      ::::::::   */
/*   push_swap.c    :+:      :+:    :+:   */
/*    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*+#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:54:30 by llefranc          #+#    #+# */
/*   Updated: 2021/03/11 15:07:09 by llefranc         ###   ########.fr       */
/*    */
/* ************************************************************************** */

#include "../includes/headers.h"

// Penser a mettre des optis sortir resultat rapide si peu d'operation

// ope qui permettent de trier > SA, SB, SS, PA, PB
// ope qui permettent de changer l'ordre > RA, RB, RR, RRA, RRB, RRR

// essayer d'utiliser le plus possible les doubles instru

/*
// B est triee à l'envers de A !!!!!!!


// au debut on divise en 2 piles egales
// > trouver le median qui sera lui aussi inclu dans b
// > mettre ceux en dessous du median sur B >> choisir RA ou RRA en fonction du nombre de chiffre
//												en fonction du plus proche d'une extremite + favoriser celui deja
//												sur le top de la pile (celui en bas prend une instruction en plus)
// > qunad j'en balance un sur B, SS si 2 +/- median sur A et 2 +/- median sur B
// > Si pas possible SS, regarder si on peut faire un SA. Quand on va push sur B, regarder si on peut faire un SB avant
// > Si possible SB en face, sur dernier move de RA faire un SS

// Ensuite on trie les 2 piles
// > on cherche les 2 couples que l'on peut amener le plus rapidement sur le haut de la pile pour faire un ss
// a la fin in equilibre les 2 en regardant dans quelle moitie de la pile se situe le minimum pour A et B
// en regardant quelle combinaison d'instruction permet de les ramener en faisant le moins d'instruction possible

*/


int checkSaInstruct(t_node* endA)
{
	if (endA->data < 2)
		return FALSE;

	return endA->next->data > endA->next->next->data;
}

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


int main(int ac, char **av)
{
	// Checking if arguments are correct
	if (!checkArgs(ac, av))
		return FALSE;

	t_twoStacks st;
	t_node* instruct = newEndNode();

	st.endA = newEndNode();
	st.endB = newEndNode();
	
	// Creating stack A
	int i = 0;
	while (++i < ac)
		push_back(st.endA, ft_atoi(av[i]));

	// Finding the median value in the arguments list
	int med = 0;
	if (!(findMedianInArgs(st.endA, &med))) // implement if malloc failed
		return errorMsg(&st, instruct);

	// ----------------- PUSH_SWAP PART -------------------------
	printStacks(INIT, &st, TRUE);
	
	while (1)
	{
		int raIns;
		int rraIns;

		if (findNextNumberToMove(st.endA, med, &raIns, &rraIns))
		{
			ft_printf("------------------\n");	
			ft_printf("med = %d, ra = %d, rra = %d\n", med, raIns, rraIns);	
			ft_printf("------------------\n");	

			// moving number < to med with RA (if they're closer to the top)
			if (raIns <= -rraIns)
			{
				while (raIns > 1) // doing ra until 1 because we can in some case optimize last ra instruction with ss instruction
				{
					// if ss can occured, we do it. Do not change our target number's position because he's not first and second number at top of A
					checkSsInstruct(&st, med) ? execInstruct(&st, TRUE, "ss") : 0;
					// if ss can't occured, doing sa before changing the numbers at top. SA will occured on the right subgroup because the first number of opposite subgroup isnt first or second numbers at top of A
					checkSaInstruct(st.endA) ? execInstruct(&st, TRUE, "sa") : 0;
		
					execInstruct(&st, TRUE, "ra");
					--raIns;
				}

				if (raIns && checkSbInstruct(st.endB)) // case a swap need to occured in B. Optimizing one ra move and one sb with ss
					execInstruct(&st, TRUE, "ss");
				else if (raIns)
					execInstruct(&st, TRUE, "ra"); // case ss can't occured
			}

			// moving number < to med with RRA (if they're closer to the bot)
			else
			{
				while (rraIns++) // doing all rra
				{
					// if ss can occured, we do it. Do not change our target number's position because he's not first and second number at top of A
					checkSsInstruct(&st, med) ? execInstruct(&st, TRUE, "ss") : 0;
					// if ss can't occured, doing sa before changing the numbers at top. SA will occured on the right subgroup because the first number of opposite subgroup isnt first or second numbers at top of A
					checkSaInstruct(st.endA) ? execInstruct(&st, TRUE, "sa") : 0;
					
					execInstruct(&st, TRUE, "rra");
				}
			}

			execInstruct(&st, TRUE, "pb");
		}
		else // si plus de nombre en dessous du median
			break;
	}

	ft_printf("----------- END ----------\n");
	printStacks(INIT, &st, TRUE);

	
	// ----------------- CHECKER PART -------------------------
	// Printing stacks initialized if debug option is activated
	// printStacks(INIT, endA, endB, TRUE);

	// // Reading and executing instructions
	// char *line = NULL;
	// while (get_next_line(STDIN_FILENO, &line))
	// {
	// 	ft_printf("------------------\n", med);	
	// 	ft_printf("med = %d\n", med);	
	// 	ft_printf("------------------\n", med);	

		
	// 	if (!execInstruct(&endA, &endB, TRUE, line))
	// 		return errorMsg(endA, endB, NULL);
	
	// }		

	return TRUE;
}
