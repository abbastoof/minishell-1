/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:21:36 by atoof             #+#    #+#             */
/*   Updated: 2023/07/13 14:55:33 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_absolute_path(char *path)
{
	if ((access(path, F_OK) == 0) && (access(path, X_OK) == 0))
		return (TRUE);
	else
		return (FALSE);
}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*temp;
	char	*unix_cmd;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		unix_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (access(unix_cmd, X_OK) == 0)
			return (unix_cmd);
		free(unix_cmd);
		paths++;
	}
	return (NULL);
}

int	built_in(t_tree *tree, t_env *env)
{
	if (!(ft_strcmp(tree->cmd, "exit")))
		ft_exit(tree);
	else if (!(ft_strcmp(tree->cmd, "echo")))
		ft_echo(tree->args);
	// else if (!(ft_strcmp(tree->cmd, "cd")))
	// 	ft_cd(env->env_var, tree->cmd);
	else if (!(ft_strcmp(tree->cmd, "env")))
		ft_env(env);
	else if (!(ft_strcmp(tree->cmd, "export")))
		ft_export(env, tree->args);
	else if (!(ft_strcmp(tree->cmd, "pwd")))
		pwd();
	// else if (!(ft_strcmp(tree->cmd, "unset")))
	// 	ft_unset();
	else
		return (0);
	return (1);
}

void	run_cmd_token(t_tree *tree, t_env *env)
{
	tree->cmd_paths = NULL;
	tree->paths = find_path(env->env_var, "PATH=");
	if (tree->paths != NULL && tree->paths[0] != '\0')
		tree->cmd_paths = ft_split(tree->paths, ':');
	// free(tree->cmd);
	if (is_absolute_path(tree->args[0]))
		tree->cmd = ft_strdup(tree->args[0]);
	else
		tree->cmd = get_cmd(tree->cmd_paths, tree->args[0]);
	if (child_process() == 0)
	{
		if (execve(tree->cmd, tree->args, env->env_var) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tree->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	wait(&(g_exit_status));
	g_exit_status = g_exit_status % 255;
	exit_status_chk();
}

void	exec_cmd(t_tree *tree, t_env *env)
{
	if (tree->redir != NULL)
		exec_redir(tree->redir, tree, env);
	else
		run_cmd_token(tree, env);
}