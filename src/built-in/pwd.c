/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:43:35 by mtoof             #+#    #+#             */
/*   Updated: 2023/05/25 10:51:41 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **env)
{
	char	cwd[1024];

	(void)env;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
}
