/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:30:11 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/26 10:54:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.h"

void printOneInstruction(int instruct)
{
	if (instruct == SA)
		ft_putstr_fd("sa\n", 1);
	else if (instruct == SB)
		ft_putstr_fd("sb\n", 1);
	else if (instruct == SS)
		ft_putstr_fd("ss\n", 1);
	else if (instruct == PA)
		ft_putstr_fd("pa\n", 1);
	else if (instruct == PB)
		ft_putstr_fd("pb\n", 1);
	else if (instruct == RA)
		ft_putstr_fd("ra\n", 1);
	else if (instruct == RB)
		ft_putstr_fd("rb\n", 1);
	else if (instruct == RR)
		ft_putstr_fd("rr\n", 1);
	else if (instruct == RRA)
		ft_putstr_fd("rra\n", 1);
	else if (instruct == RRB)
		ft_putstr_fd("rrb\n", 1);
	else if (instruct == RRR)
		ft_putstr_fd("rrr\n", 1);
}

void printAllInstructions(t_node* instruct)
{
    t_node* tmp = instruct->next;
	while (tmp != instruct)
	{
		printOneInstruction(tmp->data);
		tmp = tmp->next;
	}
}

int main(int ac, char **av)
{
	// Checking if arguments are correct
	if (!checkArgs(ac, av, NULL))
		errorMsg(NULL);

	t_allocMem st;
	initStruct(&st);
	st.endA = newEndNode(&st);
	st.endB = newEndNode(&st);
	st.smallIns = newEndNode(&st);
	st.quickIns = newEndNode(&st);
	st.selecIns = newEndNode(&st);
    
	// Creating stack A
	int size = 0;
	while (++size < ac)
		push_back(&st, st.endA, ft_atoi(av[size]));

    // Case stack is already sorted, no instructions needed
    if (isSorted(st.endA->next, st.endA, STACK_A))
        cleanExit(&st, EXIT_SUCCESS);

	// Calling the proper algo to sort the stack
    if (--size <= 5)
		sortSmallStack(st.smallIns, &st, sizeList(st.endA->next, st.endA));
    else
		quicksort(st.quickIns, &st, sizeList(st.endA->next, st.endA), INIT);

		// printf("jhsd\n");
		// printAllInstructions(st.smallIns);
		
	
	removeUselessInstructions(st.quickIns);
	removeUselessInstructions(st.smallIns);

		// printAllInstructions(st.smallIns);

    if (size <= 5)
		printAllInstructions(st.smallIns);
	else
		printAllInstructions(st.quickIns);

	cleanExit(&st, TRUE);
	return TRUE;
}


// pour 100 : 67 88 20 7 94 58 28 42 48 83 2 14 17 6 100 26 21 16 98 97 22 44 39 53 60 35 84 63 87 69 80 38 32 19 78 75 54 52 70 15 59 92 61 13 93 29 1 27 50 72 30 96 86 46 66 55 73 77 34 49 36 64 56 71 8 95 99 79 85 45 51 9 57 47 5 33 62 76 31 68 3 25 11 23 74 65 37 41 82 18 91 10 12 4 90 89 40 24 81 43
// pour 500 : 295 497 341 116 213 218 300 405 270 44 182 406 188 233 34 311 60 277 109 26 484 30 320 231 374 293 124 204 71 271 29 408 80 449 240 199 223 115 381 155 377 171 358 181 403 355 32 236 99 318 224 107 459 382 64 370 351 453 437 289 328 50 65 91 49 259 335 209 41 334 100 347 103 419 88 389 164 161 292 249 254 125 286 73 220 74 118 75 317 426 394 379 342 154 222 383 139 329 42 40 110 191 479 441 151 434 172 397 4 350 166 208 45 411 489 36 296 421 62 407 353 452 392 170 364 38 415 473 144 412 243 214 193 92 206 376 47 440 319 359 393 13 331 499 477 487 63 276 86 14 455 448 260 162 375 344 126 442 451 362 84 140 475 305 15 9 145 281 402 16 472 433 269 147 31 330 192 219 401 169 308 387 345 185 253 290 458 463 460 205 2 310 229 258 327 241 450 388 312 482 146 427 68 257 466 67 58 55 422 247 189 1 52 298 478 444 314 61 306 414 339 266 97 446 150 474 390 3 81 255 197 135 360 432 227 443 237 132 184 123 282 251 19 356 303 215 72 104 156 202 90 495 275 274 22 366 69 436 480 346 101 129 11 6 51 336 410 385 168 429 82 343 469 280 160 470 108 96 384 435 398 368 157 93 416 117 89 367 120 438 232 494 348 165 268 57 481 153 250 409 242 234 365 476 313 252 21 369 307 456 380 468 498 278 106 267 272 18 121 496 137 179 301 315 238 294 483 225 136 142 201 404 363 178 226 399 66 130 324 333 235 273 10 491 340 113 95 285 112 152 245 283 418 131 430 198 465 357 114 371 23 180 159 338 326 35 485 48 431 174 211 27 265 56 461 167 54 396 291 119 122 420 76 175 464 279 177 127 299 400 439 302 39 337 195 447 102 373 148 149 194 264 492 196 428 111 322 361 176 417 186 183 59 216 352 228 98 94 413 263 133 349 297 454 43 207 83 20 354 378 445 221 309 304 7 105 325 143 70 190 53 391 262 128 163 423 288 79 372 287 134 230 462 8 37 323 471 261 316 486 332 17 200 425 217 386 212 244 33 46 24 28 490 138 210 87 239 77 78 493 500 25 158 203 12 5 488 321 141 246 467 284 256 173 187 248 395 424 457 85