/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#             */
/*   Updated: 2026/01/22 22:17:27 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int	*arr;
	int	size;
}	t_stack;

/* Stack Operations */
void	sa(t_stack *a, int print);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a, int print);
void	rra(t_stack *a, int print);

/* Sorting */
void	radix_sort(t_stack *a, t_stack *b);
void	sort_small(t_stack *a, t_stack *b);
void	sort_three(t_stack *a);

/* Parsing */
int		parse_args(int argc, char **argv, t_stack *a, char ***split);
int		is_sorted(t_stack *a);
char	**ft_split(char *str, int *count);
void	free_split(char **split);

/* Utils */
void	ft_putstr(char *str);
void	free_stacks(t_stack *a, t_stack *b);
void	error_exit(t_stack *a, t_stack *b, char **split);
int		get_max_bits(t_stack *a);
void	index_stack(t_stack *a);

#endif
