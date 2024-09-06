/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:42:32 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/26 09:44:50 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_minishell *shell, t_command *cmd)
{
	int	i;
	int	k;
	int	n;

	i = 1;
	n = 0;
	if (cmd->args[i] && cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
	{
		k = 1;
		while (cmd->args[i][k] == 'n')
			k++;
		if (!cmd->args[i][k])
		{
			n = 1;
			i++;
		}
	}
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i++]);
		if (cmd->args[i])
			ft_printf(" ");
	}
	if (n == 0)
		ft_printf("\n");
}
