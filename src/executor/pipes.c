/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:46:50 by jhouyet           #+#    #+#             */
/*   Updated: 2024/02/26 16:23:48 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_pipe_fds(t_command *cmd, int *in_fd, int *out_fd, int fd[2])
{
	if (cmd->is_piped)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		*out_fd = fd[1];
	}
	else
		*out_fd = STDOUT_FILENO;
}

void	ft_cleanup_fds(int in_fd, int fd[2], t_command *cmd)
{
	if (cmd->is_piped)
		close(fd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
}

void	ft_handle_redirections_pipe(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}
