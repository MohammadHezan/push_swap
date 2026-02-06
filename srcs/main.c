/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/02/06 12:33:29 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** =============================================================================
** MAIN.C - PROGRAM ENTRY POINT AND FLOW CONTROL
** =============================================================================
**
** This file contains the main function and the core logic for selecting
** the appropriate sorting algorithm based on the input size.
**
** Program Flow:
** 1. Parse and validate command-line arguments
** 2. Check if already sorted (exit early if yes)
** 3. Initialize stack B for sorting operations
** 4. Select and execute the optimal sorting algorithm
** 5. Clean up allocated memory
**
** =============================================================================
*/

#include "../push_swap.h"

/*
** sort_stack - Selects and executes the optimal sorting algorithm
**
** @param a: Pointer to stack A (the main stack to be sorted)
** @param b: Pointer to stack B (auxiliary stack for sorting operations)
**
** Algorithm Selection Strategy:
** - 2 elements : Single swap (sa) - simplest case
** - 3 elements : sort_three() - handles all 6 permutations optimally
** - 4-5 elements: sort_small() - push smallest to B, sort 3, push back
** - 6+ elements : radix_sort() - efficient binary radix sort algorithm
**
** Why Different Algorithms?
** - Small inputs benefit from hardcoded optimal solutions
** - Radix sort has overhead that makes it inefficient for tiny inputs
** - This approach minimizes the total number of operations
*/
static void	sort_stack(t_stack *a, t_stack *b)
{
	if (a->size == 2)
		sa(a, 1);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size <= 5)
		sort_small(a, b);
	else
		radix_sort(a, b);
}

/*
** init_vars - Initializes all variables to NULL/safe values
**
** @param a:     Pointer to stack A structure
** @param b:     Pointer to stack B structure
** @param split: Pointer to the split strings array pointer
**
** Why Initialize to NULL?
** - Prevents undefined behavior if error_exit is called before allocation
** - free() is safe to call on NULL pointers
** - Makes debugging easier by ensuring consistent initial state
**
** This follows the defensive programming principle of initializing
** all pointers before use.
*/
static void	init_vars(t_stack *a, t_stack *b, char ***split)
{
	a->arr = NULL;
	b->arr = NULL;
	*split = NULL;
}

/*
** main - Program entry point
**
** @param argc: Argument count (including program name)
** @param argv: Argument vector (array of argument strings)
** @return: 0 on success, 1 on error (via error_exit)
**
** Execution Flow:
** 1. Check for minimum arguments (exit silently if none provided)
** 2. Initialize variables to safe values
** 3. Parse arguments - validates and fills stack A
** 4. Early exit if already sorted (optimization)
** 5. Allocate stack B with same capacity as A
** 6. Execute sorting algorithm
** 7. Clean up and exit
**
** Error Handling:
** - Invalid arguments trigger error_exit() which prints "Error\n"
** - Memory allocation failures are handled gracefully
** - Already sorted input exits without output (as per subject)
*/
int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
	char	**split;

	/* No arguments provided - exit silently (not an error per subject) */
	if (argc < 2)
		return (0);
	/* Initialize all pointers to NULL for safe error handling */
	init_vars(&a, &b, &split);
	/* Parse and validate arguments; exit with error if invalid */
	if (!parse_args(argc, argv, &a, &split))
		error_exit(&a, &b, split);
	/* Optimization: if already sorted, no operations needed */
	if (is_sorted(&a))
	{
		free_split(split);
		free_stacks(&a, NULL);
		return (0);
	}
	/* Allocate stack B with same capacity as A for worst-case scenario */
	b.arr = malloc(sizeof(int) * a.size);
	b.size = 0;
	if (!b.arr)
		error_exit(&a, &b, split);
	/* Execute the appropriate sorting algorithm */
	sort_stack(&a, &b);
	/* Clean up all allocated memory before exit */
	free_split(split);
	free_stacks(&a, &b);
	return (0);
}
