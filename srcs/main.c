/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/01/22 22:18:19 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_stack(t_stack *a, t_stack *b)
{
	if (a->size == 2)
		sa(a, 1);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size <= 5)
		sort_small(a, b);
	else
		radix_sort(a, b);
}

static void	init_vars(t_stack *a, t_stack *b, char ***split)
{
	a->arr = NULL;
	b->arr = NULL;
	*split = NULL;
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
	char	**split;

	if (argc < 2)
		return (0);
	init_vars(&a, &b, &split);
	if (!parse_args(argc, argv, &a, &split))
		error_exit(&a, &b, split);
	if (is_sorted(&a))
	{
		free_split(split);
		free_stacks(&a, NULL);
		return (0);
	}
	b.arr = malloc(sizeof(int) * a.size);
	b.size = 0;
	if (!b.arr)
		error_exit(&a, &b, split);
	sort_stack(&a, &b);
	free_split(split);
	free_stacks(&a, &b);
	return (0);
}
