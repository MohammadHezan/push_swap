/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/02/06 12:33:29 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** =============================================================================
** UTILS.C - UTILITY FUNCTIONS
** =============================================================================
**
** This file contains helper functions used throughout the program:
** - Output utilities for printing operation names
** - Memory management for cleanup and error handling
** - Stack analysis functions for sorting decisions
**
** =============================================================================
*/

#include "../push_swap.h"

/*
** ft_putstr - Outputs a string to standard output
**
** @param str: The null-terminated string to print
**
** Implementation Details:
** - Uses write() system call instead of printf (no external library dependency)
** - Writes one character at a time
** - The str++ advances the pointer after each write
**
** Why Not Use printf?
** - 42 School projects typically forbid standard library I/O functions
** - write() is a lower-level system call that's always allowed
** - Reduces dependencies and executable size
**
** Usage in push_swap:
** - Prints operation names: "sa\n", "pb\n", "ra\n", etc.
*/
void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

/*
** free_stacks - Deallocates memory for both stack arrays
**
** @param a: Pointer to stack A (can be NULL)
** @param b: Pointer to stack B (can be NULL)
**
** Safety Features:
** - Checks if stack pointer is not NULL before accessing
** - Checks if arr is not NULL before freeing
** - Sets arr to NULL after freeing (prevents double-free)
**
** Why Set to NULL After Free?
** - Prevents "use after free" bugs
** - Makes debugging easier (NULL access vs garbage access)
** - Allows safe repeated calls to this function
**
** Memory Cleanup Strategy:
** - Called at program exit (normal or error)
** - Called after successful sorting completion
*/
void	free_stacks(t_stack *a, t_stack *b)
{
	/* Free stack A if it exists and has allocated memory */
	if (a && a->arr)
	{
		free(a->arr);
		a->arr = NULL;
	}
	/* Free stack B if it exists and has allocated memory */
	if (b && b->arr)
	{
		free(b->arr);
		b->arr = NULL;
	}
}

/*
** error_exit - Centralized error handling function
**
** @param a:     Pointer to stack A (for cleanup)
** @param b:     Pointer to stack B (for cleanup)
** @param split: Split array to free (from ft_split, can be NULL)
**
** Error Handling Protocol:
** 1. Free all allocated memory (prevent leaks even on error)
** 2. Print "Error\n" to stderr (file descriptor 2)
** 3. Exit with status code 1 (indicates error to shell)
**
** Why Write to stderr (fd 2)?
** - Standard convention: errors go to stderr, output goes to stdout
** - Allows error messages to be separated from normal output
** - Example: ./push_swap 2 1 > output.txt 2> errors.txt
**
** When Called:
** - Invalid input (non-numbers, duplicates, overflow)
** - Memory allocation failure
*/
void	error_exit(t_stack *a, t_stack *b, char **split)
{
	free_split(split);
	free_stacks(a, b);
	write(2, "Error\n", 6);
	exit(1);
}

/*
** is_sorted - Checks if stack A is sorted in ascending order
**
** @param a: Pointer to stack A
** @return: 1 if sorted (or empty/single element), 0 if not sorted
**
** Definition of "Sorted":
** - Elements are in non-decreasing order: arr[0] <= arr[1] <= ... <= arr[n-1]
** - Since duplicates are not allowed, this means strictly ascending
**
** Algorithm:
** - Compare each adjacent pair of elements
** - If any pair is out of order (left > right), return 0
** - If we check all pairs without finding disorder, return 1
**
** Edge Cases:
** - Empty stack (size 0): considered sorted
** - Single element (size 1): considered sorted
** - Both handled by the while loop condition (i < size - 1)
**
** Use Cases:
** - Early exit optimization: if already sorted, no operations needed
** - Verification during development/testing
*/
int	is_sorted(t_stack *a)
{
	int	i;

	i = 0;
	/* Check each adjacent pair */
	while (i < a->size - 1)
	{
		/* If current element is greater than next, not sorted */
		if (a->arr[i] > a->arr[i + 1])
			return (0);
		i++;
	}
	return (1);
}

/*
** get_max_bits - Calculates bits needed to represent the maximum index
**
** @param a: Pointer to stack A (after indexing, values are 0 to size-1)
** @return: Number of bits needed to represent the largest index
**
** Why This Function Exists:
** - Radix sort processes numbers bit by bit
** - We need to know how many bits to process
** - After indexing, the maximum value is (size - 1)
**
** Algorithm:
** - Start with max = size - 1 (largest possible index)
** - Right-shift until we reach 0, counting shifts
** - Number of shifts = number of bits needed
**
** Example Calculations:
**   size = 5  -> max = 4  -> binary: 100   -> 3 bits
**   size = 10 -> max = 9  -> binary: 1001  -> 4 bits
**   size = 100 -> max = 99 -> binary: 1100011 -> 7 bits
**
** Mathematical Relation:
**   bits = floor(log2(max)) + 1  (for max > 0)
**
** Why Not Calculate log2 Directly?
** - Bit shifting is faster than floating-point math
** - No need for math.h library
** - Works perfectly for our integer-based radix sort
*/
int	get_max_bits(t_stack *a)
{
	int	max;
	int	bits;

	max = a->size - 1;
	bits = 0;
	/* Count how many right-shifts needed to reduce max to 0 */
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}
