/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:04:32 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/27 09:29:32 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_parse_word(t_command *current_cmd, char *value)
{
	int		arg_count;
	char	**new_args;
	int		i;

	arg_count = 0;
	while (current_cmd->args && current_cmd->args[arg_count])
		arg_count++;
	new_args = ft_safe_calloc(arg_count + 2, sizeof(char *), "new args");
	i = 0;
	while (i < arg_count)
	{
		new_args[i] = current_cmd->args[i];
		i++;
	}
	new_args[arg_count] = ft_strdup(value);
	free(current_cmd->args);
	current_cmd->args = new_args;
}

void	ft_parse_redirection(t_command *current_cmd, t_token *token)
{
	t_redirection	*new_redirection;
	t_redirection	*last;

	new_redirection = ft_safe_calloc(1, sizeof(t_redirection), "new redir");
	if (token->type == REDIRECT_IN)
		new_redirection->type = REDIR_INPUT;
	else if (token->type == APPEND)
		new_redirection->type = REDIR_APPEND;
	else
		new_redirection->type = REDIR_OUTPUT;
	new_redirection->filename = ft_strdup(token->next->value);
	new_redirection->next = NULL;
	if (!current_cmd->redirections)
		current_cmd->redirections = new_redirection;
	else
	{
		last = current_cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new_redirection;
	}
}

void	ft_add_heredoc_to_command(t_command *current, t_heredoc *new_heredoc)
{
	t_heredoc	*last;

	if (!current->heredocs)
		current->heredocs = new_heredoc;
	else
	{
		last = current->heredocs;
		while (last->next)
			last = last->next;
		last->next = new_heredoc;
	}
}

void	ft_parse_heredoc(t_command *current_cmd, t_token **token_ptr)
{
	t_heredoc	*new_heredoc;
	t_token		*token;
	t_token		*next_token;

	token = *token_ptr;
	next_token = token->next;
	if (next_token && (next_token->type == WORD || next_token->type == DQUOTE \
	|| next_token->type == QUOTE))
	{
		new_heredoc = ft_safe_calloc(1, sizeof(t_heredoc), "new heredoc");
		new_heredoc->delimiter = ft_strdup(next_token->value);
		new_heredoc->next = NULL;
		ft_add_heredoc_to_command(current_cmd, new_heredoc);
		*token_ptr = next_token->next;
	}
}
