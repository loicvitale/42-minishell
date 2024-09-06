/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:35:43 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/27 07:39:03 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_apply_input_redirection(t_redirection *redirection)
{
	int	fd;

	if (redirection->type == REDIR_INPUT)
	{
		fd = open(redirection->filename, O_RDONLY);
		if (fd < 0)
		{
			perror(redirection->filename);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	ft_apply_output_redirection(t_redirection *redirection)
{
	int	fd;
	int	flags;

	flags = 0;
	if (redirection->type == REDIR_OUTPUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redirection->type == REDIR_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redirection->filename, flags, 0644);
	if (fd == -1)
	{
		perror("open redirection");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_exec_redirections(t_command *cmd)
{
	t_redirection	*current;

	current = cmd->redirections;
	while (current != NULL)
	{
		if (current->type == REDIR_INPUT)
			ft_apply_input_redirection(current);
		else
			ft_apply_output_redirection(current);
		current = current->next;
	}
}
