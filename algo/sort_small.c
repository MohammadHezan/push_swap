/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/02/06 12:33:24 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** =============================================================================
** SORT_SMALL.C - OPTIMIZED SORTING FOR SMALL INPUTS
** =============================================================================
**
** This file contains specialized sorting algorithms for small inputs (≤5 elements).
** Using dedicated algorithms for small inputs reduces operation count significantly
** compared to using radix sort, which has overhead for small datasets.
**
** SIZE-BASED STRATEGIES:
** - 3 elements: sort_three() - handles all 6 permutations optimally
** - 4-5 elements: sort_small() - push smallest to B, sort 3, push back
**
** PERFORMANCE COMPARISON (3 elements):
** - Radix sort: up to 15+ operations
** - sort_three: maximum 2 operations
**
** =============================================================================
*/

#include "../push_swap.h"

/*
** attempt_simple_sort - Tries to sort stack with a single swap
**
** @param a: Pointer to stack A
** @return: 1 if single swap sorted the stack, 0 otherwise
**
** Purpose:
** Before running the full sorting algorithm, check if a single swap
** would completely sort the stack. This is an optimization that catches
** cases like [2, 1, 3, 4, 5] where only the first two elements are swapped.
**
** Algorithm:
** 1. Perform swap silently (print = 0)
** 2. Check if now sorted
** 3. If sorted: print "sa\n" and return success
** 4. If not sorted: undo the swap silently and return failure
**
** Why Silent Then Print?
** - We don't want to output "sa\n" if it doesn't actually help
** - Only output operations that are part of the final solution
** - This keeps the output minimal and correct
*/
static int	attempt_simple_sort(t_stack *a)
{
	/* Try a swap without printing */
	sa(a, 0);
	/* Check if the single swap solved everything */
	if (is_sorted(a))
	{
		ft_putstr("sa\n");
		return (1);
	}
	/* Didn't work - undo the swap (also silent) */
	sa(a, 0);
	return (0);
}

/*
** sort_three - Sorts exactly 3 elements with optimal operations
**
** @param a: Pointer to stack A (must have exactly 3 elements)
**
** There are 6 possible permutations of 3 elements. Each requires a
** specific sequence of operations (or none if already sorted):
**
** PERMUTATION ANALYSIS:
** Let the three values be represented by their relative order (1=smallest, 3=largest)
**
**   Initial   | Condition Check           | Operations | Result
**   -------------------------------------------------------
**   [1,2,3]   | already sorted            | (none)     | [1,2,3]
**   [2,1,3]   | first>second, second<third, first<third | sa      | [1,2,3]
**   [3,2,1]   | first>second, second>third | sa, rra    | [1,2,3]
**   [3,1,2]   | first>second, first>third  | ra         | [1,2,3]
**   [1,3,2]   | first<second, second>third, first<third | sa, ra  | [1,2,3]
**   [2,3,1]   | first<second, first>third  | rra        | [1,2,3]
**
** Why Hardcode Each Case?
** - Only 6 cases exist, making enumeration practical
** - Each case has a mathematically optimal solution
** - Faster than any general algorithm for 3 elements
** - Guarantees minimum operations (max 2 operations)
*/
void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	/* Store values for cleaner condition checking */
	first = a->arr[0];
	second = a->arr[1];
	third = a->arr[2];
	/* Case: [2,1,3] - only first two are swapped */
	if (first > second && second < third && first < third)
		sa(a, 1);
	/* Case: [3,2,1] - completely reversed */
	else if (first > second && second > third)
	{
		sa(a, 1);
		rra(a, 1);
	}
	/* Case: [3,1,2] - largest at top */
	else if (first > second && second < third && first > third)
		ra(a, 1);
	/* Case: [1,3,2] - only last two are swapped */
	else if (first < second && second > third && first < third)
	{
		sa(a, 1);
		ra(a, 1);
	}
	/* Case: [2,3,1] - smallest at bottom */
	else if (first < second && second > third && first > third)
		rra(a, 1);
	/* Case: [1,2,3] - already sorted, no operations needed */
}

/*
** get_min_pos - Finds the position of the minimum element in stack
**
** @param a: Pointer to stack A
** @return: Index (position) of the smallest element
**
** Algorithm:
** - Linear search tracking both minimum value and its position
** - Single pass through the stack: O(n) time complexity
**
** Example:
**   Stack: [5, 2, 8, 1, 4]
**   Returns: 3 (position of value 1)
**
** Use Case:
** This function is used by sort_small to find the smallest element,
** which is then rotated to the top and pushed to stack B.
*/
static int	get_min_pos(t_stack *a)
{
	int	min;
	int	pos;
	int	i;

	/* Initialize with first element */
	min = a->arr[0];
	pos = 0;
	i = 1;
	/* Search through remaining elements */
	while (i < a->size)
	{
		if (a->arr[i] < min)
		{
			min = a->arr[i];
			pos = i;
		}
		i++;
	}
	return (pos);
}

/*
** sort_small - Sorts 4 or 5 elements using an optimized selection approach
**
** @param a: Pointer to stack A (4 or 5 elements)
** @param b: Pointer to stack B (auxiliary stack)
**
** ALGORITHM OVERVIEW:
** 1. Try a simple swap first (might get lucky)
** 2. Repeatedly find and push the smallest element to B
**    - Continue until only 3 elements remain in A
** 3. Sort the remaining 3 elements using sort_three
** 4. Push all elements back from B to A
**
** ROTATION OPTIMIZATION:
** When moving the minimum element to the top:
** - If it's in the top half: use ra (rotate forward)
** - If it's in the bottom half: use rra (rotate backward)
** This minimizes the number of rotations needed.
**
** VISUAL EXAMPLE (5 elements):
**   Initial:     A = [3, 5, 1, 4, 2]
**
**   Step 1: Find min (1 at pos 2), rotate to top, push to B
**           ra, ra         → A = [1, 4, 2, 3, 5]
**           pb             → A = [4, 2, 3, 5], B = [1]
**
**   Step 2: Find min (2 at pos 1), rotate to top, push to B
**           ra             → A = [2, 3, 5, 4]
**           pb             → A = [3, 5, 4], B = [2, 1]
**
**   Step 3: Sort remaining 3 with sort_three
**           sort_three     → A = [3, 4, 5]
**
**   Step 4: Push back from B
**           pa, pa         → A = [1, 2, 3, 4, 5] ✓
**
** Why Push Smallest Elements?
** - Elements pushed to B will be in ascending order (smallest first)
** - When pushed back, they go to the top of A
** - This naturally builds the sorted order
*/
void	sort_small(t_stack *a, t_stack *b)
{
	int	pos;

	/* Optimization: check if single swap sorts everything */
	if (attempt_simple_sort(a))
		return ;
	/* Push smallest elements to B until only 3 remain */
	while (a->size > 3)
	{
		/* Find position of current minimum */
		pos = get_min_pos(a);
		/*
		** Rotate minimum to top using shortest path:
		** If in first half (pos <= size/2): rotate forward (ra)
		** If in second half (pos > size/2): rotate backward (rra)
		*/
		if (pos <= a->size / 2)
		{
			while (pos-- > 0)
				ra(a, 1);
		}
		else
		{
			while (pos++ < a->size)
				rra(a, 1);
		}
		/* Push minimum to B */
		pb(a, b);
	}
	/* Sort remaining 3 elements in A */
	sort_three(a);
	/* Push all elements back from B to A */
	while (b->size > 0)
		pa(a, b);
}
