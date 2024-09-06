/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:06:03 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/26 13:22:13 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_shell(t_minishell *shell)
{
	if (shell)
	{
		if (shell->tokens)
			ft_free_tokens(&shell->tokens);
		if (shell->commands)
			ft_free_commands(&shell->commands);
	}
}

void	ft_exit_failure(char *str, char **tab)
{
	if (tab)
		ft_free_tab(tab);
	perror(str);
	exit(EXIT_FAILURE);
}
