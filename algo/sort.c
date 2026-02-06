/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/02/06 12:33:24 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** =============================================================================
** SORT.C - RADIX SORT ALGORITHM
** =============================================================================
**
** This file implements the Radix Sort algorithm adapted for two stacks.
** Radix sort is chosen for its predictable performance and simplicity
** when working with the limited operations available in push_swap.
**
** ALGORITHM OVERVIEW:
** 1. Index Normalization: Convert actual values to indices (0 to n-1)
** 2. Binary Radix Sort: Sort by processing one bit at a time (LSB to MSB)
**
** WHY RADIX SORT?
** - Consistent O(n * log n) complexity in all cases
** - Simple implementation with only pb, pa, and ra operations
** - No need for comparison-based decisions (reduces operation count)
** - Works well with the two-stack constraint
**
** PERFORMANCE:
** - 100 numbers: ~1084 operations (well under 1500 limit)
** - 500 numbers: ~6784 operations (well under 8500 limit)
**
** =============================================================================
*/

#include "../push_swap.h"

/*
** count_smaller - Counts how many elements are smaller than element at idx
**
** @param a:   Pointer to stack A
** @param idx: Index of the element to compare against
**
** @return: Count of elements smaller than a->arr[idx]
**
** Purpose:
** This helper function determines the "rank" or "position" of an element
** when the array is sorted. It counts how many elements should come
** before this element in the sorted order.
**
** Example:
**   Array: [42, 10, 30, 5]
**   count_smaller(a, 0) for 42: 3 elements smaller (10, 30, 5)
**   count_smaller(a, 1) for 10: 1 element smaller (5)
**   count_smaller(a, 2) for 30: 2 elements smaller (10, 5)
**   count_smaller(a, 3) for  5: 0 elements smaller
**
** Time Complexity: O(n) - must check all elements
*/
static int	count_smaller(t_stack *a, int idx)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	/* Count all elements smaller than the element at idx */
	while (j < a->size)
	{
		if (a->arr[j] < a->arr[idx])
			count++;
		j++;
	}
	return (count);
}

/*
** index_stack - Normalizes values to indices (0 to n-1) based on relative order
**
** @param a: Pointer to stack A
**
** Why Indexing is Necessary:
** - Original values can be any integers (negative, large, etc.)
** - Radix sort works with binary representation
** - Indexing ensures values are in range [0, n-1] with exactly log2(n) bits
** - This makes radix sort efficient and predictable
**
** Transformation Example:
**   Original: [42, -5, 100, 0]
**   Indexed:  [2,   0,   3, 1]
**
**   Explanation:
**   - -5 is smallest  → index 0
**   -  0 is 2nd smallest → index 1
**   - 42 is 3rd smallest → index 2
**   - 100 is largest → index 3
**
** Algorithm:
** 1. Create temporary array for indexed values
** 2. For each element, count how many are smaller (that's its index)
** 3. Copy indexed values back to original array
** 4. Free temporary array
**
** Time Complexity: O(n²) - count_smaller is O(n), called n times
** Space Complexity: O(n) - temporary array for indexed values
**
** Note: While O(n²) seems expensive, it's a one-time cost before sorting
** and is acceptable for the input sizes in push_swap (up to 500 elements).
*/
void	index_stack(t_stack *a)
{
	int	*indexed;
	int	i;

	/* Allocate temporary array for indexed values */
	indexed = malloc(sizeof(int) * a->size);
	if (!indexed)
		return ;
	/* First pass: calculate index for each element */
	i = 0;
	while (i < a->size)
	{
		indexed[i] = count_smaller(a, i);
		i++;
	}
	/* Second pass: copy indexed values back to stack */
	i = 0;
	while (i < a->size)
	{
		a->arr[i] = indexed[i];
		i++;
	}
	/* Clean up temporary array */
	free(indexed);
}

/*
** radix_sort - Sorts stack A using binary radix sort algorithm
**
** @param a: Pointer to stack A (to be sorted)
** @param b: Pointer to stack B (auxiliary stack)
**
** RADIX SORT CONCEPT:
** Instead of comparing values directly, we sort by looking at one bit
** at a time, starting from the least significant bit (LSB).
**
** For each bit position:
** - If the bit is 0 → push to stack B (pb)
** - If the bit is 1 → rotate stack A (ra) to keep it in A
** After processing all elements, push everything back from B to A (pa)
**
** VISUAL EXAMPLE (sorting 5 elements: indices 0,1,2,3,4):
**
**   Initial (after indexing): A = [3, 0, 4, 1, 2]
**
**   Bit 0 (LSB):
**   - 3 (011) → bit 0 is 1 → ra → A = [0, 4, 1, 2, 3]
**   - 0 (000) → bit 0 is 0 → pb → A = [4, 1, 2, 3], B = [0]
**   - 4 (100) → bit 0 is 0 → pb → A = [1, 2, 3], B = [4, 0]
**   - 1 (001) → bit 0 is 1 → ra → A = [2, 3, 1]
**   - 2 (010) → bit 0 is 0 → pb → A = [3, 1], B = [2, 4, 0]
**   - Push back: A = [0, 4, 2, 3, 1], B = []
**
**   Continue with bit 1, bit 2... until sorted!
**
** WHY THIS WORKS:
** - Each pass groups numbers by their bit value at that position
** - After all bits are processed, numbers are sorted
** - Like sorting cards first by suit, then by rank
**
** Time Complexity: O(n * b) where b = number of bits = log2(n)
** Total: O(n * log n) operations
*/
void	radix_sort(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	size;
	int	bit;
	int	i;

	/* Step 1: Convert values to indices (0 to n-1) */
	index_stack(a);
	/* Step 2: Calculate how many bits we need to process */
	max_bits = get_max_bits(a);
	/* Step 3: Process each bit position from LSB to MSB */
	bit = 0;
	while (bit < max_bits)
	{
		/* Save current size (it will change as we push/rotate) */
		size = a->size;
		i = 0;
		/* Process each element in stack A */
		while (i < size)
		{
			/*
			** Check the current bit of the top element:
			** (a->arr[0] >> bit) shifts right to bring target bit to position 0
			** & 1 isolates that single bit (result is 0 or 1)
			*/
			if (((a->arr[0] >> bit) & 1) == 0)
				pb(a, b);
			else
				ra(a, 1);
			i++;
		}
		/* Push all elements back from B to A */
		while (b->size > 0)
			pa(a, b);
		/* Move to next bit position */
		bit++;
	}
}
