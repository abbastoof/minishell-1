/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:00:56 by atoof             #+#    #+#             */
/*   Updated: 2023/06/08 18:55:25 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_token_type(char *str, t_token *token, t_lexer *state)
{
	if (ft_strcmp(str, "|") == 0)
		token[state->token_indx].type = TOKEN_PIPE;
	else if (ft_strcmp(str, "<") == 0)
		token[state->token_indx].type = TOKEN_INPUT;
	else if (ft_strcmp(str, ">") == 0)
		token[state->token_indx].type = TOKEN_OUTPUT;
	else if (ft_strcmp(str, ">>") == 0)
		token[state->token_indx].type = TOKEN_OUTPUT_APPEND;
	else if (ft_strcmp(str, "<<") == 0)
		token[state->token_indx].type = TOKEN_HEREDOC;
	else
		token[state->token_indx].type = TOKEN_CMD;
	token[state->token_indx].value = ft_strdup(str);
	state->token_indx++;
}

static void	init_info(t_lexer *state, char *line)
{
	state->inquote = 0;
	state->indquote = 0;
	state->indx = 0;
	state->path = NULL;
	state->var = NULL;
	state->tmp = NULL;
	state->res = NULL;
	state->des = NULL;
	state->token_indx = 0;
	state->start = line;
	state->crnt_str = line;
	state->token = malloc(sizeof(t_token) * 1024);
}

t_token	*lexer(char *line, t_env *env)
{
	t_lexer	state;

	init_info(&state, line);
	while (state.crnt_str[state.indx])
	{
		if (state.crnt_str[state.indx] == '\'' && !state.indquote)
			is_word(state.crnt_str + state.indx, &state, env, 0);
		else if (state.crnt_str[state.indx] == '\"' && !state.inquote)
			is_word(state.crnt_str + state.indx, &state, env, 1);
		else if (((state.crnt_str[state.indx] == ' ')
				|| (state.crnt_str[state.indx] == '\t')) && (!state.inquote)
			&& (!state.indquote))
		{
			assign_token_type(state.start, state.token, &state);
			state.start = &state.crnt_str[state.indx + 1];
		}
		state.indx++;
	}
	assign_token_type(state.start, &(state.token[state.token_indx]), &state);
	return (state.token);
}

void	process_cmd(char *line, t_env *env)
{
	// t_cmdsplit	cmd;
	t_token	*tokens;
	int			i;

	// t_token	*tokens;
	// tokens = lexer(line, env);
	// handle_command(tokens);
	(void)env;
	if (line[0] == '\0')
		return ;
	tokens = ft_cmdtrim(line);
	//error handling
	// if (check_line(result) == -1)
		// ft_putstr_fd("Quotes are open\n", 2);
	//free the prompt if there is an open quote
	
	// test display tokens of words
	i = -1;
	while (tokens[++i].value)
	{
		printf("%s\n", tokens[i].value);
	}
	// test free tokens of words
	// while (result[i--])
		// free(result[i]);
	// free(result);
	// result = NULL;
}
