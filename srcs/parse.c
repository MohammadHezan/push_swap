/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/01/25 15:55:27 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	has_duplicate(t_stack *a, int num, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (a->arr[i] == num)
			return (1);
		i++;
	}
	return (0);
}

static int	fill_stack(char **args, int count, t_stack *a)
{
	int		i;
	long	num;

	a->arr = malloc(sizeof(int) * count);
	if (!a->arr)
		return (0);
	a->size = count;
	i = 0;
	while (i < count)
	{
		if (!is_valid_number(args[i]))
			return (0);
		num = ft_atol(args[i]);
		if (num > INT_MAX || num < INT_MIN)
			return (0);
		a->arr[i] = (int)num;
		if (has_duplicate(a, a->arr[i], i))
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_stack *a, char ***split)
{
	int	count;
	int	ret;

	*split = NULL;
	if (argc == 2)
	{
		*split = ft_split(argv[1], &count);
		if (!*split || count == 0)
			return (0);
		ret = fill_stack(*split, count, a);
		return (ret);
	}
	ret = fill_stack(argv + 1, argc - 1, a);
	return (ret);
}
