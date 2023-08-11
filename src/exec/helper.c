/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:50:02 by atoof             #+#    #+#             */
/*   Updated: 2023/08/11 13:52:21 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_last(t_redir *redir)
{
	t_redir	*last_input;
	t_redir	*last_outfile;

	last_input = NULL;
	last_outfile = NULL;
	while (redir != NULL)
	{
		if (redir->type == TOKEN_HEREDOC || redir->type == TOKEN_INPUT)
			last_input = redir;
		if (redir->type == TOKEN_OUTPUT || redir->type == TOKEN_OUTPUT_APPEND)
			last_outfile = redir;
		redir = redir->next;
	}
	if (last_input != NULL)
		last_input->last = 1;
	if (last_outfile != NULL)
		last_outfile->last = 1;
}

int	contains_heredoc(t_redir *redir_list)
{
	t_redir	*current;

	current = redir_list;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
			return (1);
		current = current->next;
	}
	return (0);
}

void	handle_only_heredoc_logic(t_redir *redir_list, t_tree *cmd_node)
{
	t_redir	*current_redir;

	current_redir = redir_list;
	while (current_redir)
	{
		if (current_redir->type == TOKEN_HEREDOC)
		{
			run_heredoc(current_redir, cmd_node);
			if (g_tree.exit_status == 1)
			{
				unlink(current_redir->file_name);
				return ;
			}
			if (redir_list->last == 0)
				unlink(redir_list->file_name);
		}
		current_redir = current_redir->next;
	}
}
