/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandeur_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:33:54 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/27 13:01:27 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_name(char *src)
{
	int		i;
	char	*dest;

	dest = ft_safe_calloc(get_size_env_name(src) + 1, sizeof(char), \
	"new env_name");
	i = 0;
	while (src[i] && src[i] != '=' && src[i] != '+')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_env_value(char *src)
{
	char	*var_value;
	int		i;
	int		k;

	var_value = ft_safe_calloc(get_size_env_value(src) + 1, sizeof(char), \
	"new env_value");
	i = get_size_env_name(src) + 1;
	if (has_plus(src))
		i++;
	if (!has_equal(src))
		i--;
	k = 0;
	while (src[i + k])
	{
		var_value[k] = src[i + k];
		k++;
	}
	var_value[k] = '\0';
	return (var_value);
}

int	get_size_env_name(char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && src[i] != '+')
		i++;
	return (i);
}

int	get_size_env_value(char *src)
{
	int	i;
	int	k;

	i = get_size_env_name(src) + 1;
	if (has_plus(src))
		i++;
	if (!has_equal(src))
		i--;
	k = 0;
	while (src[i + k])
		k++;
	return (k);
}

char	**get_env_tab(t_env *env)
{
	char	**tab;
	int		i;
	t_env	*start;

	i = 0;
	start = env;
	while (env)
	{
		i++;
		env = env->next;
	}
	tab = ft_safe_calloc(i, sizeof(char *) + 1, "transform env");
	i = 0;
	while (start)
	{
		tab[i] = ft_safe_calloc(ft_strlen(start->var), sizeof(char), \
		"transform env 2");
		tab[i++] = ft_strdup(start->var);
		start = start->next;
	}
	tab[i] = NULL;
	return (tab);
}
