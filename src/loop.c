/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:15:20 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 10:22:00 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_loop(t_minishell *shell, char **envp)
{
	char	*input;

	init_env(envp, shell);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_printf("exit\n");
			ft_free_all(shell);
			break ;
		}
		if (*input)
			add_history(input);
		shell->tokens = ft_lexer(input);
		shell->commands = NULL;
		if (shell->tokens)
		{
			ft_parser(shell);
			ft_core_expander(shell);
			ft_executor(shell);
			ft_free_shell(shell);
		}
		free(input);
	}
}
