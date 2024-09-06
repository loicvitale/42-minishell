/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:47:35 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/27 16:59:07 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_env(t_minishell	*shell, t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = NULL;
		if (env->next)
			tmp = env->next;
		free_node(shell, env);
		env = tmp;
	}
}

void	ft_free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	ft_free_commands(t_command **commands)
{
	t_command	*current;
	t_command	*next;
	int			i;

	if (!commands || !*commands)
		return ;
	current = *commands;
	while (current)
	{
		next = current->next;
		i = 0;
		while (current->args && current->args[i])
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
		ft_free_redirections(&current->redirections);
		ft_free_heredocs(&current->heredocs);
		free(current);
		current = next;
	}
	*commands = NULL;
}

void	ft_free_redirections(t_redirection **redirection)
{
	t_redirection	*current;
	t_redirection	*next;

	if (!redirection || !*redirection)
		return ;
	current = *redirection;
	while (current)
	{
		next = current->next;
		free(current->filename);
		free(current);
		current = next;
	}
	*redirection = NULL;
}

void	ft_free_heredocs(t_heredoc **heredoc)
{
	t_heredoc	*current;
	t_heredoc	*next;

	if (!heredoc || !*heredoc)
		return ;
	current = *heredoc;
	while (current)
	{
		next = current->next;
		free(current->delimiter);
		free(current);
		current = next;
	}
	*heredoc = NULL;
}
