/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:27:20 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/28 10:21:21 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_all(t_minishell *shell)
{
	ft_free_shell(shell);
	if (shell->env)
		ft_free_env(shell, shell->env);
	free(shell->name);
	free(shell);
	shell = NULL;
}

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_code(char *str)
{
	int	code;

	if (!str)
		code = 0;
	else if (is_digit(str))
		code = ft_atoi(str);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		code = 156;
	}
	if (str)
		free(str);
	exit(code);
}

void	ft_exit(t_minishell *shell, t_command *cmd)
{
	char	*str;

	ft_printf("exit\n");
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	}
	else
	{
		str = NULL;
		if (cmd->args[1])
			str = ft_strdup(cmd->args[1]);
		ft_free_all(shell);
		exit_code(str);
	}
}
