/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:27:20 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/28 10:09:10 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	cd_error(int option, char *str)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (option == 1)
		ft_putstr_fd(": not set\n", STDERR_FILENO);
	else if (option == 2)
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	else
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

static void	change_path(t_minishell *shell)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*var;

	pwd = is_var_exist(shell->env, "PWD");
	oldpwd = is_var_exist(shell->env, "OLDPWD");
	var = get_env_value(pwd->var);
	if (!oldpwd)
		add_var(shell, ft_strjoin("OLDPWD=", var));
	else
	{
		free(oldpwd->var);
		oldpwd->var = ft_strjoin("OLDPWD=", var);
	}
	free(var);
	free(pwd->var);
	pwd->var = ft_strjoin("PWD=", getcwd(NULL, sizeof(NULL)));
}

static int	search_path(t_minishell *shell, char *str)
{
	t_env	*env;
	char	*var;
	int		result;

	result = 1;
	env = is_var_exist(shell->env, str);
	if (env)
	{
		var = get_env_value(env->var);
		if (!var[0])
		{
			result = -1;
			cd_error(1, str);
		}
		else
		{
			result = chdir(var);
			if (result == -1)
				cd_error(1, var);
		}
		free(var);
	}
	else
		cd_error(1, str);
	return (result);
}

void	ft_cd(t_minishell *shell, t_command *cmd)
{
	int	result;

	result = -1;
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		result = search_path(shell, "HOME");
	else if (ft_strncmp(cmd->args[1], "-", 1) == 0)
	{
		if (cmd->args[1][1] != '\0')
			cd_error(2, cmd->args[1]);
		else
		{
			result = search_path(shell, "OLDPWD");
			if (result == 0)
				ft_printf("%s\n", getcwd(NULL, sizeof(NULL)));
		}
	}
	else
	{
		result = chdir(cmd->args[1]);
		if (result == -1)
			cd_error(0, cmd->args[1]);
	}
	if (result == 0)
		change_path(shell);
}
