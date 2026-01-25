/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/01/23 20:45:47 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	pa(t_stack *a, t_stack *b)
{
	int	i;

	if (b->size == 0)
		return ;
	i = a->size;
	while (i > 0)
	{
		a->arr[i] = a->arr[i - 1];
		i--;
	}
	a->arr[0] = b->arr[0];
	a->size++;
	i = 0;
	while (i < b->size - 1)
	{
		b->arr[i] = b->arr[i + 1];
		i++;
	}
	b->size--;
	ft_putstr("pa\n");
}

void	pb(t_stack *a, t_stack *b)
{
	int	i;

	if (a->size == 0)
		return ;
	i = b->size;
	while (i > 0)
	{
		b->arr[i] = b->arr[i - 1];
		i--;
	}
	b->arr[0] = a->arr[0];
	b->size++;
	i = 0;
	while (i < a->size - 1)
	{
		a->arr[i] = a->arr[i + 1];
		i++;
	}
	a->size--;
	ft_putstr("pb\n");
}

void	ra(t_stack *a, int print)
{
	int	tmp;
	int	i;

	if (a->size < 2)
		return ;
	tmp = a->arr[0];
	i = 0;
	while (i < a->size - 1)
	{
		a->arr[i] = a->arr[i + 1];
		i++;
	}
	a->arr[a->size - 1] = tmp;
	if (print)
		ft_putstr("ra\n");
}

void	sa(t_stack *a, int print)
{
	int	tmp;

	if (a->size < 2)
		return ;
	tmp = a->arr[0];
	a->arr[0] = a->arr[1];
	a->arr[1] = tmp;
	if (print)
		ft_putstr("sa\n");
}

void	rra(t_stack *a, int print)
{
	int	tmp;
	int	i;

	if (a->size < 2)
		return ;
	tmp = a->arr[a->size - 1];
	i = a->size - 1;
	while (i > 0)
	{
		a->arr[i] = a->arr[i - 1];
		i--;
	}
	a->arr[0] = tmp;
	if (print)
		ft_putstr("rra\n");
}
