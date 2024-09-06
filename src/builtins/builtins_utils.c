/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:33:25 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/27 15:04:21 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_sort_string_tab(char **tab)
{
	int		i;
	int		j;
	char	*temp;
	int		size;

	i = 0;
	size = 0;
	while (tab[size])
		size++;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[j];
				tab[j] = tab[i];
				tab[i] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_sort_env(t_env *env)
{
	char	**tab;
	int		i;

	tab = get_env_tab(env);
	ft_sort_string_tab(tab);
	i = 0;
	while (tab[i])
	{
		if (ft_strlen(get_env_value(tab[i])) > 0)
			ft_printf("declare -x %s=\"%s\"\n", get_env_name(tab[i]), \
			get_env_value(tab[i]));
		else
			ft_printf("declare -x %s\n", get_env_name(tab[i]));
		i++;
	}
	ft_free_tab(tab);
}

size_t	has_plus(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (i + 1);
		i++;
	}
	return (0);
}

void	change_var(char *new_var, char **var, char *arg)
{
	if (*var)
		new_var = ft_join_quote(get_env_name(*var), '=');
	else
		new_var = ft_join_quote(get_env_name(arg), '=');
	if (has_plus(arg))
	{
		if (*var)
			new_var = str_join_free(new_var, get_env_value(*var));
		new_var = str_join_free(new_var, get_env_value(arg));
	}
	else
		new_var = str_join_free(new_var, get_env_value(arg));
	new_var = ft_delete_quote(new_var);
	*var = new_var;
}

int	export_unset_error(int option, char *str)
{
	if (option == 1)
		ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
	else
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (0);
}
