/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:38:31 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/27 17:00:42 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*ft_init_new_command(void)
{
	t_command	*new_command;

	new_command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!new_command)
	{
		perror("Error calloc new command");
		exit(EXIT_FAILURE);
	}
	return (new_command);
}

void	ft_add_command(t_command **commands, t_command *cmd)
{
	t_command	*temp;

	if (!*commands)
		*commands = cmd;
	else
	{
		temp = *commands;
		while (temp->next)
			temp = temp->next;
		temp->next = cmd;
	}
}

void	ft_parse_token(t_command **current, t_command **cmds, t_token **t_ptr)
{
	t_token	*token;

	token = *t_ptr;
	if (!*current)
		*current = ft_init_new_command();
	if (token->type == WORD || token->type == DQUOTE || token->type == QUOTE)
		ft_parse_word(*current, token->value);
	else if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT \
	|| token->type == APPEND)
	{
		ft_parse_redirection(*current, token);
		*t_ptr = token->next;
	}
	else if (token->type == HEREDOC)
	{
		ft_parse_heredoc(*current, t_ptr);
		*t_ptr = token->next;
	}
	else if (token->type == PIPE)
	{
		(*current)->is_piped = 1;
		ft_add_command(cmds, *current);
		*current = ft_init_new_command();
	}
}

void	ft_parser(t_minishell *shell)
{
	t_command	*current_cmd;
	t_command	*commands;
	t_token		*tokens;
	t_command	*cmd;

	current_cmd = NULL;
	commands = NULL;
	tokens = shell->tokens;
	while (tokens)
	{
		ft_parse_token(&current_cmd, &commands, &tokens);
		tokens = tokens->next;
	}
	if (current_cmd)
		ft_add_command(&commands, current_cmd);
	cmd = commands;
	while (cmd)
	{
		if (!cmd->args || !cmd->args[0])
			ft_parse_word(cmd, "\0");
		cmd = cmd->next;
	}
	shell->commands = commands;
}
