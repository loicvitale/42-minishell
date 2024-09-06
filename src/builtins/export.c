/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:06:26 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/27 14:34:08 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	has_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

static int	is_valid_identifier(char *str, int i, int result)
{
	if (ft_isdigit(str[i]) || str[i] == '=')
		result = 0;
	while ((str[i] != '=' && str[i] != '+') && str[i])
	{
		if (is_env_char(str[i]) == 0)
			result = 0;
		i++;
	}
	if (str[i] == '+' && str[i + 1] != '='
		|| str[i] == '=' && str[i + 1] == '='
		|| i == 0)
		result = 0;
	if (!result)
		return (export_unset_error(0, str));
	return (result);
}

void	add_var(t_minishell *shell, char *str)
{
	t_env	*new_env;
	t_env	*env;

	new_env = ft_safe_calloc(1, sizeof(t_env), "new env add_var");
	if (has_plus(str))
		change_var(new_env->var, &new_env->var, str);
	else
		new_env->var = ft_delete_quote(ft_strdup(str));
	new_env->next = NULL;
	if (!shell->env)
		shell->env = new_env;
	else
	{
		env = shell->env;
		while (env)
		{
			if (!env->next)
			{
				env->next = new_env;
				return ;
			}
			env = env->next;
		}
	}
}

static char	*get_var_value(char *str, size_t pos)
{
	int		i;
	char	*new_words;

	i = pos;
	while (str[i])
		i++;
	new_words = ft_safe_calloc(i - pos, sizeof(char), \
	"new words get_var_value");
	if (!new_words)
		return (NULL);
	i = 0;
	while (str[i + pos])
	{
		new_words[i] = str[i + pos];
		i++;
	}
	return (new_words);
}

void	ft_export(t_minishell *shell, t_command *cmd, int i)
{
	char	*identifier;
	t_env	*var_exist;
	char	*new_var;
	int		size_idtf;

	if (cmd->args[1])
	{
		while (cmd->args[i])
		{
			if (!is_valid_identifier(cmd->args[i], 0, 1))
				return ;
			identifier = get_env_name(cmd->args[i]);
			var_exist = is_var_exist(shell->env, identifier);
			free(identifier);
			if (!var_exist)
				add_var(shell, cmd->args[i]);
			else
				change_var(new_var, &var_exist->var, cmd->args[i]);
			i++;
		}
	}
	else
		print_sort_env(shell->env);
}
