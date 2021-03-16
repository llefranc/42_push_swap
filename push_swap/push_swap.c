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
// OK > trouver le median qui sera lui aussi inclu dans b
// OK > mettre ceux en dessous du median sur B >> choisir RA ou RRA en fonction du nombre de chiffre
//												en fonction du plus proche d'une extremite + favoriser celui deja
//												sur le top de la pile (celui en bas prend une instruction en plus)
// OK > qunad j'en balance un sur B, SS si 2 +/- median sur A et 2 +/- median sur B
// OK > Si pas possible SS, regarder si on peut faire un SA. Quand on va push sur B, regarder si on peut faire un SB avant
// OK > Si possible SB en face, sur dernier move de RA faire un SS

// Ensuite on trie les 2 piles
// > on cherche les 2 couples que l'on peut amener le plus rapidement sur le haut de la pile pour faire un ss
// a la fin in equilibre les 2 en regardant dans quelle moitie de la pile se situe le minimum pour A et B
// en regardant quelle combinaison d'instruction permet de les ramener en faisant le moins d'instruction possible

// Ensuite une fois que tout est trié, on parcourt le set d'instruction pour eliminer certaines et les remplacer
// par les instructions double (ex : ra sa rb >> rr sa)

// 1 2 9  3 7 10 6 18 -5 29 -6 33 >>>>> serie pour tester

*/


int splitStackAInTwo(t_twoStacks *st, int med)
{
	int raIns;
	int rraIns;
	
	while (findNextNumberToMove(st->endA, med, &raIns, &rraIns))
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
				checkSsInstruct(st, med) ? execInstruct(st, TRUE, "ss") : 0;
				// if ss can't occured, doing sa before changing the numbers at top. SA will occured on the right subgroup because the first number of opposite subgroup isnt first or second numbers at top of A
				checkSaInstruct(st->endA) ? execInstruct(st, TRUE, "sa") : 0;
	
				execInstruct(st, TRUE, "ra");
				--raIns;
			}

			if (raIns && checkSbInstruct(st->endB)) // case a swap need to occured in B. Optimizing one ra move and one sb with ss
				execInstruct(st, TRUE, "ss");
			else if (raIns)
				execInstruct(st, TRUE, "ra"); // case ss can't occured
			else if (checkSbInstruct(st->endB))
				execInstruct(st, TRUE, "sb"); // case element already at top of A and a sb need to occured
		}

		// moving number < to med with RRA (if they're closer to the bot)
		else
		{
			while (rraIns++) // doing all rra
			{
				// if ss can occured, we do it. Do not change our target number's position because he's not first and second number at top of A
				checkSsInstruct(st, med) ? execInstruct(st, TRUE, "ss") : 0;
				// if ss can't occured, doing sa before changing the numbers at top. SA will occured on the right subgroup because the first number of opposite subgroup isnt first or second numbers at top of A
				checkSaInstruct(st->endA) ? execInstruct(st, TRUE, "sa") : 0;
				
				execInstruct(st, TRUE, "rra");
			}

			if (checkSbInstruct(st->endB))
				execInstruct(st, TRUE, "sb"); // case element already at top of A and a sb need to occured
		}

		execInstruct(st, TRUE, "pb");
	}

	return TRUE; // A ENLVER PEUT ETRE METTRE EN VOID A VOIR
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
	
	splitStackAInTwo(&st, med);

	ft_printf("----------- END SPLIT PART ----------\n");

	
	// 2EME PARTIE DU PROGRAMME COMMENCE ICI, ON FAIT D'ABORD LES DOUBLES SWAP
	// int raIns = 0;
	int rbIns = 0;
	// int rraIns = 0;
	int rrbIns = 0;

	// Still at least one couple to swap in stack A and B. If both raIns/rraIns or rbIns/rrbIns = 0, means
	// findCouple function returned false and this stack is sorted

	// ft_printf("coule in A: %d\n", findCoupleToSwapInA(st.endA, &raIns, &rraIns));
	// ft_printf("coule in B: %d\n", findCoupleToSwapInB(st.endB, &rbIns, &rrbIns));

	// ft_printf("stackA sorted %d, stack B sorted %d\n", checkIfSorted(st.endA, getMin(st.endA), &less), 
	// 		checkIfSorted(st.endB, getMax(st.endB), &more));
	
	// while (findCoupleToSwap(st.endA, getMin(st.endA), &raIns, &rraIns, &less) 
	// 		&& findCoupleToSwap(st.endB, getMax(st.endB), &rbIns, &rrbIns, &more))
	// {
		// ft_printf("ra %d, rb %d, rra %d, rrb %d\n", raIns, rbIns, rraIns, rrbIns);
	// 	bringTwoCouplesToSwapToTheTop(&st, raIns, rraIns, rbIns, rrbIns);
	// 	execInstruct(&st, TRUE, "ss");
	// }


	// A CE STADE, AU MOINS UNE DES 2 STACKS EST TRIEE (PLUS BESOIN DE SWAP, PEUT ETRE BESOIN BOUGER
	// LA STACK POUR METTRE LA MINI/MAXI VALUE EN HAUT)
	
	// Swapping values in A until it's sorted (and B is already sorted)
	// int j = 20;
	// while (findCoupleToSwap(st.endA, getMin(st.endA), &raIns, &rraIns, &less))
	// {
		// ft_printf("ra %d, rra %d\n", raIns, rraIns);
	// 	bringCoupleToSwapToTheTopOfA(&st, raIns, rraIns);
	// 	execInstruct(&st, TRUE, "sa");
	// }

	// // Swapping values in B until it's sorted (and A is already sorted)
	// int j = 10;
	while (findCoupleToSwap(st.endB, getMax(st.endB), &rbIns, &rrbIns, &more))
	{
		ft_printf("rb %d, rrb %d\n", rbIns, rrbIns);
		bringCoupleToSwapToTheTopOfB(&st, rbIns, rrbIns);
		execInstruct(&st, TRUE, "sb");
	}


	ft_printf("----------- END ----------\n");
	printStacks(INIT, &st, TRUE);

	
	// ----------------- CHECKER PART -------------------------

	return TRUE;
}