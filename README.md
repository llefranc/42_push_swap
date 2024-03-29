# push_swap (@42Paris)

> This project was code for MACOS. Here is the [subject][8].
>
*"Because swap_push isn't as natural"*

![Alt text](https://github.com/llefranc/42_push_swap/blob/master/push_swap_example.png)

## About

Push_swap is a project of the mandatory part of the cursus.
</br>It's only made in C and was about creating two programs : one sorting two "special" stacks, and another one checking if the stacks are sorted or not. 
</br>We were only allowed to modify the two "stacks", called **stack a** and **stack b**, using a set of instruction : 
- `sa` *(swap a)* -- swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements).
- `sb` *(swap b)* -- swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements).
- `ss` sa and sb at the same time.
- `pa` *(push a)* -- take the first element at the top of b and put it at the top of a. Do nothing if b is empty.
- `pb` *(push b)* -- take the first element at the top of a and put it at the top of b. Do nothing if a is empty.
- `ra` *(rotate a)* -- shift up all elements of stack a by 1. The first element becomes the last one.
- `rb` *(rotate b)* -- shift up all elements of stack b by 1. The first element becomes the last one.
- `rr` -- ra and rb at the same time.
- `rra` *(reverse rotate a)* -- shift down all elements of stack a by 1. The flast element becomes the first one.
- `rrb` *(reverse rotate b)* -- shift down all elements of stack b by 1. The flast element becomes the first one.
- `rrr` -- rra and rrb at the same time.

In order to succeed, a good comprehension of what is **complexity**, and how the best **sorting algorithms** work was necessary. 

## How I solved the problem

For small list of integers (< 5 numbers) I used custom sortings to optimize the number of instructions. 
</br>For bigger list, I implemented a variant of quicksort algorithm with several optimizations.
</br></br>Average nb of insctructions for 100 tests :
- :white_check_mark: : 3 numbers in `1` instruction *(grade 5/5)*
- :white_check_mark: : 5 numbers in `9` instructions *(grade 5/5)*
- :white_check_mark: : 100 numbers in `772` instructions *(grade 4/5)*
- :white_check_mark: : 500 numbers in `5357` instructions *(grade 5/5)*

## Building and running the project

1. Download/Clone this repo

        git clone https://github.com/llefranc/42_push_swap.git

2. `cd` into the root directory and run `make`

        cd 42_push_swap
        make

3.  Run `push_swap` with a list of integers in order to print the list of instructions on stdout.
	
		./push_swap 2 1 5 4

4.	Run `checker` with a list of integers to solve manually the stack. It will wait for instruction on stdin. Ctrl+D to stop typing instructions
	
		./checker 2 1 5 4


5.	Pipe `push_swap` into `checker` with the same list of integers as argument to see if the output of `push_swap` correctly solved the problem
	
		./push_swap 2 1 5 4 | ./checker 2 1 5 4

6. Use `checker` with `-v` option to visualize how push_swap solved the problem
	
		./push_swap 2 1 5 4 | ./checker -v 2 1 5 4
   

## Sources

- [Quicksort algorithm explained step by step][7]
- [Understanding sorting algorithms and complexity][6]
- [Comprendre la notion de complexité (FR)][4]
- [Visualization of 15 sorting algorithms][3]
- [Explication de quelques algos de tri (FR)][5]
- [Interesting to understang the basics of the project and the algos for stack of 3 / 5 numbers][1]
- [Allows to visualize push_swap in action][2]

[1]: https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a
[2]: https://github.com/o-reo/push_swap_visualizer
[3]: https://www.youtube.com/watch?v=kPRA0W1kECg
[4]: https://zestedesavoir.com/tutoriels/621/algorithmique-pour-lapprenti-programmeur/399_presentation-de-la-notion-de-complexite-algorithmique/2020_la-notion-de-complexite/
[5]: https://zestedesavoir.com/tutoriels/621/algorithmique-pour-lapprenti-programmeur/400_premiers-exemples-de-structures-de-donnees-et-dalgorithmes-courants/2024_introduction-au-probleme-du-tri/
[6]: https://medium.com/jl-codes/understanding-sorting-algorithms-af6222995c8
[7]: https://www.youtube.com/watch?v=7h1s2SojIRw
[8]: https://github.com/llefranc/42_push_swap/blob/master/push_swap.en.pdf