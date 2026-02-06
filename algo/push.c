/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/02/06 12:33:23 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** =============================================================================
** PUSH.C - STACK OPERATIONS
** =============================================================================
**
** This file implements all the allowed stack operations for push_swap:
**
** SWAP OPERATIONS:
**   sa - Swap the first two elements of stack A
**
** PUSH OPERATIONS:
**   pa - Push the top element from stack B to stack A
**   pb - Push the top element from stack A to stack B
**
** ROTATE OPERATIONS:
**   ra  - Rotate stack A upward (first element becomes last)
**   rra - Reverse rotate stack A (last element becomes first)
**
** Stack Representation:
**   arr[0]        = TOP of stack (first element)
**   arr[size - 1] = BOTTOM of stack (last element)
**
** Each operation prints its name to stdout when executed, which is the
** required output format for the push_swap program.
**
** =============================================================================
*/

#include "../push_swap.h"

/*
** pa - Push A: Move top element from stack B to top of stack A
**
** @param a: Pointer to destination stack A
** @param b: Pointer to source stack B
**
** Operation Visualization:
**   Before:  A = [1, 2, 3]     B = [7, 8, 9]
**   After:   A = [7, 1, 2, 3]  B = [8, 9]
**
** Algorithm Steps:
** 1. Check if B is empty (nothing to push)
** 2. Shift all elements in A down by one position (make room at top)
** 3. Copy top element from B to top of A
** 4. Increment A's size
** 5. Shift all elements in B up by one position (remove top)
** 6. Decrement B's size
** 7. Print "pa\n" to stdout
**
** Time Complexity: O(n) where n = max(size_a, size_b)
** - Need to shift elements in both stacks
*/
void	pa(t_stack *a, t_stack *b)
{
	int	i;

	/* Guard clause: nothing to push if B is empty */
	if (b->size == 0)
		return ;
	/* Step 1: Shift all elements in A down to make room at index 0 */
	i = a->size;
	while (i > 0)
	{
		a->arr[i] = a->arr[i - 1];
		i--;
	}
	/* Step 2: Place B's top element at A's top position */
	a->arr[0] = b->arr[0];
	a->size++;
	/* Step 3: Remove top element from B by shifting all elements up */
	i = 0;
	while (i < b->size - 1)
	{
		b->arr[i] = b->arr[i + 1];
		i++;
	}
	b->size--;
	/* Print the operation name */
	ft_putstr("pa\n");
}

/*
** pb - Push B: Move top element from stack A to top of stack B
**
** @param a: Pointer to source stack A
** @param b: Pointer to destination stack B
**
** Operation Visualization:
**   Before:  A = [1, 2, 3]  B = [7, 8, 9]
**   After:   A = [2, 3]     B = [1, 7, 8, 9]
**
** This is the mirror operation of pa:
** - Takes from A (instead of B)
** - Puts on B (instead of A)
**
** Used heavily in radix sort to partition elements based on bit values.
*/
void	pb(t_stack *a, t_stack *b)
{
	int	i;

	/* Guard clause: nothing to push if A is empty */
	if (a->size == 0)
		return ;
	/* Step 1: Shift all elements in B down to make room at index 0 */
	i = b->size;
	while (i > 0)
	{
		b->arr[i] = b->arr[i - 1];
		i--;
	}
	/* Step 2: Place A's top element at B's top position */
	b->arr[0] = a->arr[0];
	b->size++;
	/* Step 3: Remove top element from A by shifting all elements up */
	i = 0;
	while (i < a->size - 1)
	{
		a->arr[i] = a->arr[i + 1];
		i++;
	}
	a->size--;
	/* Print the operation name */
	ft_putstr("pb\n");
}

/*
** ra - Rotate A: Shift all elements up, first element becomes last
**
** @param a:     Pointer to stack A
** @param print: Flag to control output (1 = print "ra\n", 0 = silent)
**
** Operation Visualization:
**   Before:  [1, 2, 3, 4, 5]
**   After:   [2, 3, 4, 5, 1]  (1 moved from top to bottom)
**
** Algorithm:
** 1. Save the first element (it will become last)
** 2. Shift all elements up by one position
** 3. Place saved element at the bottom
**
** Why the 'print' Parameter?
** - Some internal operations need rotation without output
** - sort_three uses ra internally but controls when to print
** - Allows code reuse while maintaining correct output
**
** Time Complexity: O(n) - need to shift all elements
*/
void	ra(t_stack *a, int print)
{
	int	tmp;
	int	i;

	/* Guard clause: rotation meaningless with < 2 elements */
	if (a->size < 2)
		return ;
	/* Save first element (will become last) */
	tmp = a->arr[0];
	/* Shift all elements up by one position */
	i = 0;
	while (i < a->size - 1)
	{
		a->arr[i] = a->arr[i + 1];
		i++;
	}
	/* Place saved element at the bottom */
	a->arr[a->size - 1] = tmp;
	/* Conditionally print based on flag */
	if (print)
		ft_putstr("ra\n");
}

/*
** sa - Swap A: Swap the first two elements of stack A
**
** @param a:     Pointer to stack A
** @param print: Flag to control output (1 = print "sa\n", 0 = silent)
**
** Operation Visualization:
**   Before:  [3, 1, 2]
**   After:   [1, 3, 2]
**
** Algorithm:
** - Classic swap using a temporary variable
** - Simply exchanges arr[0] and arr[1]
**
** Use Cases:
** - Sorting 2 elements
** - Part of sort_three combinations
** - Fine-tuning order after rotations
**
** Time Complexity: O(1) - constant time operation
*/
void	sa(t_stack *a, int print)
{
	int	tmp;

	/* Guard clause: can't swap with fewer than 2 elements */
	if (a->size < 2)
		return ;
	/* Classic three-step swap using temporary variable */
	tmp = a->arr[0];
	a->arr[0] = a->arr[1];
	a->arr[1] = tmp;
	/* Conditionally print based on flag */
	if (print)
		ft_putstr("sa\n");
}

/*
** rra - Reverse Rotate A: Shift all elements down, last becomes first
**
** @param a:     Pointer to stack A
** @param print: Flag to control output (1 = print "rra\n", 0 = silent)
**
** Operation Visualization:
**   Before:  [1, 2, 3, 4, 5]
**   After:   [5, 1, 2, 3, 4]  (5 moved from bottom to top)
**
** This is the reverse of ra:
** - ra:  first → last  (rotate upward)
** - rra: last → first  (rotate downward)
**
** Algorithm:
** 1. Save the last element (it will become first)
** 2. Shift all elements down by one position
** 3. Place saved element at the top
**
** When to Use rra vs ra?
** - Use rra when target element is closer to bottom of stack
** - Use ra when target element is closer to top of stack
** - Choosing the shorter path minimizes total operations
**
** Time Complexity: O(n) - need to shift all elements
*/
void	rra(t_stack *a, int print)
{
	int	tmp;
	int	i;

	/* Guard clause: rotation meaningless with < 2 elements */
	if (a->size < 2)
		return ;
	/* Save last element (will become first) */
	tmp = a->arr[a->size - 1];
	/* Shift all elements down by one position (from end to start) */
	i = a->size - 1;
	while (i > 0)
	{
		a->arr[i] = a->arr[i - 1];
		i--;
	}
	/* Place saved element at the top */
	a->arr[0] = tmp;
	/* Conditionally print based on flag */
	if (print)
		ft_putstr("rra\n");
}
