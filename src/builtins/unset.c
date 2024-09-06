/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:42:32 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/27 14:34:26 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	free_node(t_minishell *shell, t_env *env)
{
	if (shell->env == env && env->next == NULL)
	{
		ft_memdel(shell->env->var);
		shell->env->var = NULL;
		shell->env->next = NULL;
		return ;
	}
	ft_memdel(env->var);
	ft_memdel(env);
}

static void	delete_var(t_minishell *shell, t_env *env, char *str)
{
	t_env	*tmp;
	t_env	*new_env;
	char	*var_name;

	while (env && env->next)
	{
		var_name = get_env_name(env->next->var);
		if (ft_strcmp(str, var_name) == 0)
		{
			tmp = env->next->next;
			free_node(shell, env->next);
			env->next = tmp;
			free(var_name);
			return ;
		}
		free(var_name);
		env = env->next;
	}
}

static int	valid_identifier(char *str)
{
	int	i;
	int	result;

	result = 1;
	i = 0;
	if (ft_isdigit(str[i]))
		return (export_unset_error(1, str));
	while (str[i])
	{
		if (is_env_char(str[i]) == 0 || str[i] == '=')
			return (export_unset_error(1, str));
		i++;
	}
	return (1);
}

void	ft_unset(t_minishell *shell, t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1])
	{
		while (cmd->args[i])
		{
			if (valid_identifier(cmd->args[i]))
			{
				if (is_var_exist(shell->env, cmd->args[i]))
					delete_var(shell, shell->env, cmd->args[i]);
			}
			i++;
		}
	}
}
