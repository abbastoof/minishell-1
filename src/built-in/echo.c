/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/04 19:51:10 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *option)
{
	int	index;

	index = 1;
	if (!option || !option[0] || option[0] != '-')
		return (-1);
	while (option[index] == 'n')
		index++;
	if (index != (int)ft_strlen(option))
		return (-1);
	return (0);
}

void	ft_echo(char **args)
{
	int	index;
	int	flag;

	index = 1;
	flag = 0;
	if (args[1] != NULL && args[1][0] == '-')
	{
		if (check_flag(args[index]) == 0)
		{
			flag = 1;
			index++;
		}
	}
	while (args[index] != NULL)
	{
		ft_putstr(args[index]);
		if (args[index + 1] != NULL)
			ft_putchar(' ');
		index++;
	}
	if (flag == 0)
		ft_putchar('\n');
}
