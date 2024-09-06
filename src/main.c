/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:41:50 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 10:22:08 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error_num = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;

	shell = ft_safe_calloc(1, sizeof(*shell), "shell");
	shell->name = ft_strdup(argv[0]);
	ft_signals();
	ft_loop(shell, envp);
}
