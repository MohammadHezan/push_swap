/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/01/22 22:17:29 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	free_stacks(t_stack *a, t_stack *b)
{
	if (a && a->arr)
	{
		free(a->arr);
		a->arr = NULL;
	}
	if (b && b->arr)
	{
		free(b->arr);
		b->arr = NULL;
	}
}

void	error_exit(t_stack *a, t_stack *b, char **split)
{
	free_split(split);
	free_stacks(a, b);
	write(2, "Error\n", 6);
	exit(1);
}

int	is_sorted(t_stack *a)
{
	int	i;

	i = 0;
	while (i < a->size - 1)
	{
		if (a->arr[i] > a->arr[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	get_max_bits(t_stack *a)
{
	int	max;
	int	bits;

	max = a->size - 1;
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}
