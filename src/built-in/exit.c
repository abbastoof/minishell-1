/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/10 11:22:54 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_digits(t_tree *tree, int indx)
{
	int	c;

	c = 0;
	while (tree->args[indx][c])
	{
		if (tree->args[indx][c] == '-' || tree->args[indx][c] == '+')
			c++;
		if (!ft_isdigit(tree->args[indx][c]))
		{
			ft_putstr_fd("exit\nMinishell: exit: ", 2);
			ft_putstr_fd(tree->args[indx], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_tree(tree);
			exit(255);
		}
		c++;
	}
}

void	ft_exit(t_tree *tree)
{
	int		indx;
	int		exit_num;

	indx = 1;
	exit_num = 0;
	if (tree->args[indx] != NULL)
	{
		check_digits(tree, indx);
		indx++;
		if (tree->args[indx] != NULL)
		{
			ft_putstr_fd("exit\nMinishell: exit: too many arguments\n", 2);
			g_exit_status = 1;
			return ;
		}
		ft_putstr_fd("exit\n", 2);
		exit_num = ft_atoi(tree->args[1]);
		free_tree(tree);
		exit(exit_num);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
}
