/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:35:28 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 07:09:26 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	ft_write_content_to_file(const char *filename, const char *content)
// {
// 	FILE	*file;

// 	file = fopen(filename, "w");
// 	if (!file)
// 	{
// 		perror("Unable to open file for writing");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (content)
// 	{
// 		fputs(content, file);
// 		fputc('\n', file);
// 	}
// 	fclose(file);
// }

void	ft_add_newline_to_file(const char *filename)
{
	int		fd;
	char	newline;

	newline = '\n';
	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		perror("Unable to open file for writing");
		exit(EXIT_FAILURE);
	}
	if (write(fd, &newline, 1) == -1)
	{
		perror("Error while writing newline character to file");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	ft_write_content_to_file(const char *filename, const char *content)
{
	int	fd;
	int	content_length;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("Unable to open file for writing");
		exit(EXIT_FAILURE);
	}
	if (content)
	{
		content_length = 0;
		while (content[content_length] != '\0')
			content_length++;
		if (write(fd, content, content_length) == -1)
		{
			perror("Error while writing content to file");
			close(fd);
			exit(EXIT_FAILURE);
		}
		ft_add_newline_to_file(filename);
	}
	close(fd);
}

static void	ft_expandeur_heredoc(t_minishell *shell, char **str, int i)
{
	char	*temp;

	temp = ft_safe_calloc(1, sizeof(char), "temp replace var");
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (is_char_stop_var((*str)[i + 1]) == 1)
			|| ((*str)[i + 1] == '?'))
			ft_replace_var(shell->env, (*str), &i, &temp);
		else
			temp = ft_join_quote(temp, (*str)[i]);
		i++;
	}
	free((*str));
	(*str) = ft_strdup(temp);
	free(temp);
}

// char	*ft_read_heredoc_content(const char *delimiter)
// {
// 	char	*line;
// 	char	*content;
// 	char	*temp;

// 	content = NULL;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break;
// 		if (strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		temp = content;
// 		asprintf(&content, "%s\n%s", temp ? temp : "", line);
// 		free(temp);
// 		free(line);
// 	}
// 	return (content);
// }

void	ft_heredoc_join(char **temp, char **content, char **line)
{
	*content = ft_strjoin(*temp, "\n");
	free(*temp);
	*temp = ft_strjoin(*content, *line);
	free(*content);
	*content = *temp;
}

char	*ft_read_heredoc_content(t_minishell *shell, const char *delimiter)
{
	char	*line;
	char	*content;
	char	*temp;

	content = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		temp = content;
		ft_expandeur_heredoc(shell, &line, 0);
		if (temp)
			ft_heredoc_join(&temp, &content, &line);
		else
			content = ft_strjoin("", line);
		free(line);
	}
	return (content);
}
