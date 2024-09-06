/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:35:28 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 06:42:05 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_heredoc_filename(void)
{
	static int	count = 0;
	char		*num;
	char		*temp;
	char		*filename;

	count = 0;
	count++;
	num = ft_itoa(count);
	if (!num)
		return (NULL);
	temp = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(temp, ".tmp");
	free(temp);
	if (!filename)
		return (NULL);
	return (filename);
}

void	ft_exec_heredoc(t_minishell *shell, t_command *cmd)
{
	t_heredoc	*current_heredoc;
	char		*heredoc_content;
	char		*temp_filename;
	int			fd;

	current_heredoc = cmd->heredocs;
	heredoc_content = NULL;
	while (current_heredoc)
	{
		temp_filename = ft_heredoc_filename();
		heredoc_content = ft_read_heredoc_content(shell, \
		current_heredoc->delimiter);
		ft_write_content_to_file(temp_filename, heredoc_content);
		free(heredoc_content);
		if (!current_heredoc->next)
		{
			fd = open(temp_filename, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		free(temp_filename);
		current_heredoc = current_heredoc->next;
	}
}

static int	ft_to_temp_file(t_minishell *shell, const char *delimiter)
{
	char	*temp_filename;
	char	*heredoc_content;
	int		fd;

	temp_filename = ft_heredoc_filename();
	if (!temp_filename)
		return (-1);
	heredoc_content = ft_read_heredoc_content(shell, delimiter);
	if (!heredoc_content)
	{
		free(temp_filename);
		return (-1);
	}
	ft_write_content_to_file(temp_filename, heredoc_content);
	free(heredoc_content);
	fd = open(temp_filename, O_RDONLY);
	if (fd < 0)
		perror("Opening heredoc temporary file failed");
	free(temp_filename);
	return (fd);
}

int	ft_exec_heredocs(t_minishell *shell, t_command *cmd)
{
	t_heredoc	*current_heredoc;
	int			last_fd;
	int			fd;

	last_fd = -1;
	current_heredoc = cmd->heredocs;
	while (current_heredoc)
	{
		fd = ft_to_temp_file(shell, current_heredoc->delimiter);
		if (fd != -1)
		{
			if (last_fd != -1)
				close(last_fd);
			last_fd = fd;
		}
		current_heredoc = current_heredoc->next;
	}
	return (last_fd);
}
