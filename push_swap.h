/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/02/06 12:34:26 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** =============================================================================
** PUSH_SWAP - HEADER FILE
** =============================================================================
**
** This header defines the data structures, constants, and function prototypes
** for the push_swap program - a sorting algorithm implementation that sorts
** integers using two stacks and a limited set of operations.
**
** Algorithm Overview:
** - For small inputs (2-5 elements): Uses optimized sorting strategies
** - For large inputs (>5 elements): Uses Radix Sort with binary representation
**
** The program outputs the sequence of operations needed to sort the stack,
** optimizing for the minimum number of moves.
** =============================================================================
*/

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* ========================== STANDARD LIBRARIES ========================== */
/*
** stdlib.h - Memory allocation (malloc, free) and program termination (exit)
** unistd.h - System calls for I/O operations (write)
*/
# include <stdlib.h>
# include <unistd.h>

/* ========================== CONSTANT DEFINITIONS ======================== */
/*
** Integer limits used for overflow validation during parsing.
** These ensure that input numbers fit within the 32-bit signed integer range.
*/
# define INT_MAX 2147483647
# define INT_MIN -2147483648

/* ========================== DATA STRUCTURES ============================= */
/*
** t_stack - Represents a stack data structure
**
** Members:
**   arr  - Dynamic array holding the stack elements (arr[0] = top of stack)
**   size - Current number of elements in the stack
**
** Stack Visualization:
**   arr[0]     -> Top of stack (first element)
**   arr[1]     -> Second element
**   ...
**   arr[size-1] -> Bottom of stack (last element)
**
** Memory Layout:
**   The array is dynamically allocated to match the number of input elements.
**   Stack B is allocated with the same capacity as stack A to handle
**   all elements during sorting operations.
*/
typedef struct s_stack
{
	int	*arr;
	int	size;
}	t_stack;

/* ========================== STACK OPERATIONS ============================ */
/*
** These are the fundamental operations allowed by the push_swap rules.
** Each operation prints its name to stdout when executed (if print flag set).
**
** sa  - Swap A: Swaps the first two elements at the top of stack A
**       The 'print' parameter controls whether to output "sa\n"
**
** pa  - Push A: Takes the top element from B and pushes it onto A
**       Moves element from B to A (B -> A)
**
** pb  - Push B: Takes the top element from A and pushes it onto B
**       Moves element from A to B (A -> B)
**
** ra  - Rotate A: Shifts all elements of A up by 1 (first becomes last)
**       Circular rotation upward
**
** rra - Reverse Rotate A: Shifts all elements of A down by 1 (last becomes first)
**       Circular rotation downward
*/
void	sa(t_stack *a, int print);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a, int print);
void	rra(t_stack *a, int print);

/* ========================== SORTING ALGORITHMS ========================== */
/*
** radix_sort  - Main sorting algorithm for large datasets (>5 elements)
**               Uses binary radix sort, processing one bit at a time
**               Time Complexity: O(n * log(n)) where log is base 2
**
** sort_small  - Optimized sorting for 4-5 elements
**               Pushes smallest elements to B, sorts remaining 3, pushes back
**
** sort_three  - Hardcoded optimal sorting for exactly 3 elements
**               Handles all 6 possible permutations with minimal operations
*/
void	radix_sort(t_stack *a, t_stack *b);
void	sort_small(t_stack *a, t_stack *b);
void	sort_three(t_stack *a);

/* ========================== INPUT PARSING =============================== */
/*
** parse_args - Validates and parses command-line arguments into stack A
**              Handles both formats: "./push_swap 1 2 3" and "./push_swap '1 2 3'"
**              Returns: 1 on success, 0 on failure (invalid input)
**
** ft_split   - Splits a string by spaces into an array of words
**              Used when all numbers are passed as a single quoted string
**              count: output parameter for the number of words found
**
** free_split - Frees memory allocated by ft_split
**              Safely handles NULL pointer input
*/
int		parse_args(int argc, char **argv, t_stack *a, char ***split);
char	**ft_split(char *str, int *count);
void	free_split(char **split);

/* ========================== UTILITY FUNCTIONS =========================== */
/*
** is_sorted   - Checks if stack A is already sorted in ascending order
**               Returns: 1 if sorted, 0 if not sorted
**               Used to avoid unnecessary operations on sorted input
**
** ft_putstr   - Outputs a string to stdout, character by character
**               Used for printing operation names (sa, pb, ra, etc.)
**
** free_stacks - Deallocates memory for both stacks
**               Safely handles NULL pointers
**
** error_exit  - Error handling: frees all memory, prints "Error\n" to stderr
**               Terminates program with exit code 1
**
** get_max_bits - Calculates the number of bits needed to represent
**                the maximum index value (used in radix sort)
**                Example: 5 elements need indices 0-4, max=4, bits=3
**
** index_stack  - Converts actual values to their sorted indices (0 to n-1)
**                Essential for radix sort to work with any integer range
**                Example: [42, -5, 100] becomes [1, 0, 2]
*/
int		is_sorted(t_stack *a);
void	ft_putstr(char *str);
void	free_stacks(t_stack *a, t_stack *b);
void	error_exit(t_stack *a, t_stack *b, char **split);
int		get_max_bits(t_stack *a);
void	index_stack(t_stack *a);

#endif
