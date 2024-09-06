/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:05:40 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 06:59:23 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_safe_calloc(size_t count, size_t size, char *error_message)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		perror("Error allocating memory for : ");
		ft_printf("%s", error_message);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

int	ft_error(int error)
{
	if (error == 1)
	{
		ft_putstr_fd("minishell: syntax error: unable to locate closing ",
			STDERR_FILENO);
		ft_putstr_fd("quotation\n",
			STDERR_FILENO);
	}
	if (error == 6)
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
			STDERR_FILENO);
	if (error == 7)
		ft_putstr_fd("minishell: syntax error near unexpected token '||'\n",
			STDERR_FILENO);
	if (error == 8)
		ft_putstr_fd("minishell: syntax error near unexpected token \
		 `newline'\n",
			STDERR_FILENO);
	g_error_num = 2;
	return (EXIT_FAILURE);
}

int	ft_error_redir(int error)
{
	if (error == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token '<'\n",
			STDERR_FILENO);
	if (error == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token '<<'\n",
			STDERR_FILENO);
	if (error == 4)
		ft_putstr_fd("minishell: syntax error near unexpected token '>'\n",
			STDERR_FILENO);
	if (error == 5)
		ft_putstr_fd("minishell: syntax error near unexpected token '>>'\n",
			STDERR_FILENO);
	g_error_num = 2;
	return (EXIT_FAILURE);
}

int	ft_cmd_error(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

int	ft_redir_error(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	return (127);
}
