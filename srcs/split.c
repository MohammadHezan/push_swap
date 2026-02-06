/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:08:00 by mhaizan           #+#    #+#             */
/*   Updated: 2026/02/06 12:33:29 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** =============================================================================
** SPLIT.C - STRING SPLITTING UTILITY
** =============================================================================
**
** This file implements a string splitting function that separates a string
** into words based on space delimiters. It's used when arguments are passed
** as a single quoted string: ./push_swap "3 2 1"
**
** Memory Management:
** - Each word is allocated separately
** - The result array is NULL-terminated
** - free_split() must be called to prevent memory leaks
**
** Example:
**   Input:  "  42  -5   100  "
**   Output: ["42", "-5", "100", NULL]
**
** =============================================================================
*/

#include "../push_swap.h"

/*
** count_words - Counts the number of space-separated words in a string
**
** @param str: The input string to analyze
** @return: The number of words found
**
** Algorithm (State Machine):
** - Uses 'in_word' flag to track if we're currently inside a word
** - Transitions:
**   - Not in word → found non-space → enter word, increment count
**   - In word → found space → exit word
**
** Visual Example:
**   String: "  hello world  "
**   State:  00111110111110 00
**   Words counted: 2 (hello, world)
**
** Why State Machine?
** - Handles multiple consecutive spaces correctly
** - Handles leading/trailing spaces correctly
** - Single pass through the string (O(n) time complexity)
*/
static int	count_words(char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		/* Found a non-space while not in a word - new word starts */
		if (*str != ' ' && !in_word)
		{
			in_word = 1;
			count++;
		}
		/* Found a space - no longer in a word */
		else if (*str == ' ')
			in_word = 0;
		str++;
	}
	return (count);
}

/*
** get_word - Extracts the next word from the string
**
** @param str: Pointer to string pointer (modified to point after extracted word)
** @return: Newly allocated string containing the word, or NULL on failure
**
** How It Works:
** 1. Skip leading spaces
** 2. Find word boundaries (start and length)
** 3. Allocate memory for the word (+1 for null terminator)
** 4. Copy characters from original string
** 5. Update *str to point past the extracted word
**
** Why Double Pointer (char **str)?
** - Allows modification of the caller's string pointer
** - Next call to get_word continues from where we left off
** - Enables sequential extraction of all words
**
** Memory: Caller is responsible for freeing the returned string
*/
static char	*get_word(char **str)
{
	char	*start;
	char	*word;
	int		len;
	int		i;

	/* Skip leading spaces to find word start */
	while (**str == ' ')
		(*str)++;
	start = *str;
	len = 0;
	/* Count word length (until space or end of string) */
	while (**str && **str != ' ')
	{
		len++;
		(*str)++;
	}
	/* Allocate memory for word plus null terminator */
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	/* Copy characters from original string to new word */
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/*
** ft_split - Splits a string into an array of words separated by spaces
**
** @param str:   The string to split
** @param count: Output parameter - stores the number of words found
**
** @return: NULL-terminated array of strings, or NULL on failure
**
** Memory Layout of Result:
**   result[0] -> "word1"
**   result[1] -> "word2"
**   ...
**   result[n] -> NULL (terminator)
**
** Error Handling:
** - If any word allocation fails, all previously allocated words are freed
** - The result array itself is also freed on error
** - Returns NULL to indicate failure
**
** Why NULL-Terminate the Array?
** - Standard C convention for string arrays
** - Allows iteration without knowing count: while(result[i])
** - Makes freeing easier: iterate until NULL
*/
char	**ft_split(char *str, int *count)
{
	char	**result;
	int		words;
	int		i;

	/* First pass: count how many words we have */
	words = count_words(str);
	*count = words;
	/* Allocate array for pointers (+1 for NULL terminator) */
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	/* Second pass: extract each word */
	while (i < words)
	{
		result[i] = get_word(&str);
		/* Handle allocation failure: clean up and return NULL */
		if (!result[i])
		{
			while (--i >= 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

/*
** free_split - Frees all memory allocated by ft_split
**
** @param split: The array returned by ft_split (can be NULL)
**
** Memory Cleanup Order:
** 1. Free each individual word string
** 2. Free the array of pointers itself
**
** Safety Features:
** - NULL check prevents segmentation fault if called with NULL
** - Safe to call multiple times (should set pointer to NULL after calling)
**
** Usage Pattern:
**   char **words = ft_split(str, &count);
**   // ... use words ...
**   free_split(words);
**   words = NULL;  // Prevent use-after-free
*/
void	free_split(char **split)
{
	int	i;

	/* Safety check: do nothing if NULL pointer */
	if (!split)
		return ;
	i = 0;
	/* Free each word string */
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	/* Free the array of pointers */
	free(split);
}
