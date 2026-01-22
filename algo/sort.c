/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/01/22 22:15:30 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/push_swap.h"

static int	count_smaller(t_stack *a, int idx)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	while (j < a->size)
	{
		if (a->arr[j] < a->arr[idx])
			count++;
		j++;
	}
	return (count);
}

void	index_stack(t_stack *a)
{
	int	*indexed;
	int	i;

	indexed = malloc(sizeof(int) * a->size);
	if (!indexed)
		return ;
	i = 0;
	while (i < a->size)
	{
		indexed[i] = count_smaller(a, i);
		i++;
	}
	i = 0;
	while (i < a->size)
	{
		a->arr[i] = indexed[i];
		i++;
	}
	free(indexed);
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	size;
	int	bit;
	int	i;

	index_stack(a);
	max_bits = get_max_bits(a);
	bit = 0;
	while (bit < max_bits)
	{
		size = a->size;
		i = 0;
		while (i < size)
		{
			if (((a->arr[0] >> bit) & 1) == 0)
				pb(a, b);
			else
				ra(a, 1);
			i++;
		}
		while (b->size > 0)
			pa(a, b);
		bit++;
	}
}
