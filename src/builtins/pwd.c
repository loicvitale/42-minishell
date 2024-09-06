/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:27:20 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/27 14:26:30 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_minishell *shell, t_command *cmd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		ft_printf("%s\n", cwd);
}
