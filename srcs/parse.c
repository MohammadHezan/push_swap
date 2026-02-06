/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/02/06 12:33:29 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** =============================================================================
** PARSE.C - ARGUMENT PARSING AND VALIDATION
** =============================================================================
**
** This file handles all input validation and parsing of command-line arguments.
** It converts string arguments into a validated array of integers in stack A.
**
** Validation Requirements:
** - All arguments must be valid integers (digits with optional sign)
** - Numbers must be within INT_MIN to INT_MAX range
** - No duplicate values allowed (each number must be unique)
**
** Input Formats Supported:
** - Multiple arguments: ./push_swap 1 2 3 4 5
** - Single quoted string: ./push_swap "1 2 3 4 5"
**
** =============================================================================
*/

#include "../push_swap.h"

/*
** is_valid_number - Validates if a string represents a valid integer
**
** @param str: The string to validate
** @return: 1 if valid integer format, 0 otherwise
**
** Valid Formats:
** - Positive numbers: "123", "+123"
** - Negative numbers: "-123"
** - Zero: "0", "+0", "-0"
**
** Invalid Formats:
** - Empty string: ""
** - Sign only: "+", "-"
** - Non-digits: "12a3", "abc"
** - Floating point: "1.5"
**
** This function only validates FORMAT, not RANGE (overflow checking is separate)
*/
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	/* Skip optional sign at the beginning */
	if (str[i] == '-' || str[i] == '+')
		i++;
	/* String cannot be empty or contain only a sign */
	if (str[i] == '\0')
		return (0);
	/* All remaining characters must be digits (0-9) */
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

/*
** ft_atol - Converts a string to a long integer
**
** @param str: The string to convert (must be pre-validated)
** @return: The converted long integer value
**
** Why Long Instead of Int?
** - Using long allows detection of integer overflow
** - We can safely compare the result against INT_MAX/INT_MIN
** - Prevents undefined behavior from integer overflow
**
** Algorithm:
** 1. Check for optional sign character
** 2. Process each digit: result = result * 10 + digit
** 3. Apply sign at the end
**
** Note: This function assumes the string is already validated by is_valid_number
*/
static long	ft_atol(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	/* Handle optional sign */
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	/* Convert each digit: multiply by 10 and add the digit */
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/*
** has_duplicate - Checks if a number already exists in the stack
**
** @param a:   Pointer to stack A
** @param num: The number to check for duplicates
** @param pos: Current position (only check elements before this position)
**
** @return: 1 if duplicate found, 0 if number is unique
**
** Why Check Only Before Current Position?
** - Elements are added sequentially from index 0
** - We only need to check against previously added elements
** - This avoids comparing an element with itself
** - Time complexity: O(n) per check, O(n²) total for all checks
*/
static int	has_duplicate(t_stack *a, int num, int pos)
{
	int	i;

	i = 0;
	/* Compare against all previously added elements */
	while (i < pos)
	{
		if (a->arr[i] == num)
			return (1);
		i++;
	}
	return (0);
}

/*
** fill_stack - Populates stack A with validated integers from arguments
**
** @param args:  Array of string arguments to convert
** @param count: Number of arguments to process
** @param a:     Pointer to stack A to fill
**
** @return: 1 on success, 0 on any validation failure
**
** Validation Steps for Each Argument:
** 1. Check if string is a valid number format
** 2. Convert to long and check for integer overflow
** 3. Check for duplicate values
**
** Memory Allocation:
** - Allocates exactly 'count' integers for the stack
** - On failure, the caller (error_exit) will free this memory
*/
static int	fill_stack(char **args, int count, t_stack *a)
{
	int		i;
	long	num;

	/* Allocate memory for the stack array */
	a->arr = malloc(sizeof(int) * count);
	if (!a->arr)
		return (0);
	a->size = count;
	i = 0;
	while (i < count)
	{
		/* Step 1: Validate number format */
		if (!is_valid_number(args[i]))
			return (0);
		/* Step 2: Convert and check for integer overflow */
		num = ft_atol(args[i]);
		if (num > INT_MAX || num < INT_MIN)
			return (0);
		a->arr[i] = (int)num;
		/* Step 3: Check for duplicates */
		if (has_duplicate(a, a->arr[i], i))
			return (0);
		i++;
	}
	return (1);
}

/*
** parse_args - Main parsing function that handles all input formats
**
** @param argc:  Argument count from main
** @param argv:  Argument vector from main
** @param a:     Pointer to stack A to populate
** @param split: Pointer to store split result (for later cleanup)
**
** @return: 1 on success, 0 on failure
**
** Input Format Handling:
**
** Case 1: Multiple arguments (argc > 2)
**   Example: ./push_swap 3 2 1
**   - Arguments are already separated in argv
**   - Pass argv + 1 (skip program name) directly to fill_stack
**
** Case 2: Single quoted string (argc == 2)
**   Example: ./push_swap "3 2 1"
**   - All numbers are in one string (argv[1])
**   - Use ft_split to separate numbers by spaces
**   - Store result in *split for later memory cleanup
**
** Why Store Split Result?
** - The split array needs to be freed after sorting is complete
** - Storing the pointer allows proper cleanup in any code path
*/
int	parse_args(int argc, char **argv, t_stack *a, char ***split)
{
	int	count;
	int	ret;

	*split = NULL;
	/* Single string input - need to split by spaces */
	if (argc == 2)
	{
		*split = ft_split(argv[1], &count);
		if (!*split || count == 0)
			return (0);
		ret = fill_stack(*split, count, a);
		return (ret);
	}
	/* Multiple arguments - already separated */
	ret = fill_stack(argv + 1, argc - 1, a);
	return (ret);
}
