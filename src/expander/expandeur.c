/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandeur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:49:20 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/27 16:14:30 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_replace_var(t_env *env, char *str, int *k, char **temp)
{
	char	*var;
	char	*var_env;
	t_env	*var_exist;

	if (str[*k + 1] && str[*k + 1] == '?')
	{
		*temp = str_join_free((*temp), ft_itoa(g_error_num));
		*k += 1;
	}
	else
	{
		var = find_stop_var(str, *k + 1);
		var_env = NULL;
		var_exist = is_var_exist(env, var);
		if (var_exist)
			var_env = ft_strdup(var_exist->var);
		if (var_env)
			*temp = str_join_free((*temp), get_env_value(var_env));
		*k += ft_strlen(var);
		free(var);
		free(var_env);
	}
}

static void	ft_replace_tab(char **str, char **temp, int *i)
{
	free((*str));
	if (!*temp)
		return ;
	*temp = ft_delete_quote(*temp);
	*str = ft_strdup(*temp);
	*i += 1;
	free(*temp);
}

void	init_env(char **envp, t_minishell *shell)
{
	t_env	*new_env;
	t_env	*prev;
	int		i;

	prev = NULL;
	i = 0;
	if (!envp[i])
		fill_env(envp, shell);
	while (envp[i] != NULL)
	{
		new_env = ft_safe_calloc(1, sizeof(t_env), "new node env");
		new_env->var = ft_strdup(envp[i]);
		new_env->next = NULL;
		if (prev)
			prev->next = new_env;
		else
			shell->env = new_env;
		prev = new_env;
		i++;
	}
}

static void	ft_replace(t_minishell *shell, char ***tab, int i, int k)
{
	char	*temp;
	char	current_quote;

	while ((*tab)[i])
	{
		k = 0;
		temp = ft_safe_calloc(1, sizeof(char), "temp replace var");
		while ((*tab)[i][k])
		{
			if (!current_quote)
				current_quote = is_quote((*tab)[i][k]);
			if ((*tab)[i][k] == '$' && (is_char_stop_var((*tab)[i][k + 1]) == 1
				|| (*tab)[i][k + 1] == '?') && current_quote != '\'')
				ft_replace_var(shell->env, (*tab)[i], &k, &temp);
			else
				temp = ft_join_quote(temp, (*tab)[i][k]);
			if ((*tab)[i][k + 1] == current_quote)
				current_quote = '\0';
			k++;
		}
		ft_replace_tab(&(*tab)[i], &temp, &i);
	}
}

void	ft_core_expander(t_minishell *shell)
{
	t_command	*cmd;
	char		**tmp;

	cmd = shell->commands;
	while (cmd)
	{
		if (cmd->redirections && cmd->redirections->filename)
		{
			tmp = ft_safe_calloc(2, sizeof(char *), "tab redirection");
			tmp[0] = ft_strdup(cmd->redirections->filename);
			tmp[1] = NULL;
			ft_replace(shell, &tmp, 0, 0);
			if (tmp[0][0])
			{
				free(cmd->redirections->filename);
				cmd->redirections->filename = ft_strdup(tmp[0]);
			}
			ft_free_tab(tmp);
		}
		if (cmd->args)
			ft_replace(shell, &cmd->args, 0, 0);
		cmd = cmd->next;
	}
}
