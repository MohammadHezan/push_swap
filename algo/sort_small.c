/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/01/22 22:17:25 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/push_swap.h"

static int	attempt_simple_sort(t_stack *a)
{
	sa(a, 0);
	if (is_sorted(a))
	{
		ft_putstr("sa\n");
		return (1);
	}
	sa(a, 0);
	return (0);
}

void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	first = a->arr[0];
	second = a->arr[1];
	third = a->arr[2];
	if (first > second && second < third && first < third)
		sa(a, 1);
	else if (first > second && second > third)
	{
		sa(a, 1);
		rra(a, 1);
	}
	else if (first > second && second < third && first > third)
		ra(a, 1);
	else if (first < second && second > third && first < third)
	{
		sa(a, 1);
		ra(a, 1);
	}
	else if (first < second && second > third && first > third)
		rra(a, 1);
}

static int	get_min_pos(t_stack *a)
{
	int	min;
	int	pos;
	int	i;

	min = a->arr[0];
	pos = 0;
	i = 1;
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

void	sort_small(t_stack *a, t_stack *b)
{
	int	pos;

	if (attempt_simple_sort(a))
		return ;
	while (a->size > 3)
	{
		pos = get_min_pos(a);
		if (pos <= a->size / 2)
			while (pos-- > 0)
				ra(a, 1);
		else
			while (pos++ < a->size)
				rra(a, 1);
		pb(a, b);
	}
	sort_three(a);
	while (b->size > 0)
		pa(a, b);
}
