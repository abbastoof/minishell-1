/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:39:59 by atoof             #+#    #+#             */
/*   Updated: 2023/05/25 11:29:25 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/syslimits.h>
# include <signal.h>

# define TRUE 1
# define FALSE 0

extern char	**environ;

typedef struct s_minishell
{
	pid_t	pid;
	int		end[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_arguments;
	char	*cmd;
	char	**args;
}			t_minishell;

typedef struct s_environment
{
	char	**env_var;
	int		counter;
}			t_environment;

void		pwd(char **env);
void		echo(char **args);
void		commands(char *cmd);
void		setup_signal_handlers(void);
void		free_env(t_environment *env);
char		*find_path(char **envp, char *str);
char		**ft_realloc(char **ptr, size_t size);
void		ft_cd(t_environment *env, char *args);
// void		initialize_minishell(t_minishell *line);
int			ft_strcmp(const char *s1, const char *s2);
void		handle_command(t_environment *env, const char *cmd);
void		initialize_environment(t_environment *env, char **environ);


# define TOKEN_CMD 1
# define TOKEN_ARG 2
# define TOKEN_PIPE 3
# define TOKEN_INPUT 4
# define TOKEN_OUTPUT 5
# define TOKEN_OUTPUT_APPEND 6
# define TOKEN_HEREDOC 7
# define TOKEN_VARIABLE 8
# define TOKEN_EXIT_STATUS 9
# define TOKEN_QUOTE 10
# define TOKEN_DQUOTE 11

# define TRUE 1
# define FALSE 0

#endif