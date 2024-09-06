/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandeur_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:36:45 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/26 14:33:48 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	is_quote(char c)
{
	if (c == '\'')
		return ('\'');
	else if (c == '\"')
		return ('\"');
	else
		return ('\0');
}

t_env	*is_var_exist(t_env *env, char *arg)
{
	char	*var_name;

	while (env)
	{
		var_name = get_env_name(env->var);
		if (ft_strcmp(arg, var_name) == 0)
		{
			free(var_name);
			return (env);
		}
		free(var_name);
		env = env->next;
	}
	return (NULL);
}

int	is_env_char(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int	is_char_stop_var(char c)
{
	if (c && c != ' ' && c != '\'' && c != '\"' && is_env_char(c) == 1)
		return (1);
	return (0);
}

char	*find_stop_var(char *str, int k)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = ft_safe_calloc(1, sizeof(char), "new var_name find_stop");
	while (is_char_stop_var(str[k + i]) == 1)
	{
		var_name = str_join_free(var_name, ft_char_to_string(str[k + i]));
		i++;
	}
	return (var_name);
}
