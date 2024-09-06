/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:41:07 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/23 07:50:14 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || \
	c == '\v')
		return (1);
	else
		return (0);
}

void	ft_syntax_error(char next_char, char next_next_char)
{
	if (next_char == '|')
	{
		if (next_next_char == '|')
			ft_error(7);
		else
			ft_error(6);
	}
	else if (next_char == '<')
	{
		if (next_next_char == '<')
			ft_error_redir(3);
		else
			ft_error_redir(2);
	}
	else if (next_char == '>')
	{
		if (next_next_char == '>')
			ft_error_redir(5);
		else
			ft_error_redir(4);
	}
	else
		ft_error(8);
}
