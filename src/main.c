/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:46:43 by atoof             #+#    #+#             */
/*   Updated: 2023/06/20 15:07:30 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char				*cmd;
	t_env				env;

	(void)ac;
	(void)av;
	initialize_environment(&env, environ);
	while (1)
	{
		disable_enable_ctl(0);
		init_signals();
		cmd = readline("Minishell>");
		add_history(cmd);
		if (cmd == NULL)
			ctrl_d_handler();
		signal(SIGINT, SIG_IGN);
		disable_enable_ctl(1);
		process_cmd(cmd, &env);
		free(cmd);
	}
	free_env(&env);
	return (0);
}
