/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:03:34 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 09:56:22 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_search_exec_with_path(char *arg)
{
	if (access(arg, X_OK) == 0)
		return (ft_strdup(arg));
	else
		return (NULL);
}

char	*ft_check_command_path(const char *folder_path, const char *arg)
{
	char	*command_path;
	char	*full_command_path;

	command_path = ft_strjoin(folder_path, "/");
	full_command_path = ft_strjoin(command_path, arg);
	free(command_path);
	if (access(full_command_path, X_OK) == 0)
		return (full_command_path);
	else
	{
		free(full_command_path);
		return (NULL);
	}
}

char	*ft_search_exec(char *arg, char *path_env)
{
	char	**paths;
	char	*command_path_f;
	int		i;

	paths = ft_split(path_env, ':');
	command_path_f = NULL;
	i = 0;
	while (paths[i])
	{
		command_path_f = ft_check_command_path(paths[i], arg);
		if (command_path_f != NULL)
			break ;
		i++;
	}
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	paths = NULL;
	return (command_path_f);
}

char	*ft_check_cmd(t_minishell *shell, char *arg)
{
	char	*path;
	char	*path_env;
	t_env	*path_exist;

	path_env = NULL;
	path_exist = is_var_exist(shell->env, "PATH");
	if (arg[0] == '/' || arg[0] == '.')
		path = ft_search_exec_with_path(arg);
	else
	{
		if ((path_exist != NULL))
			path_env = get_env_value(path_exist->var);
		if (path_env == NULL)
			return (NULL);
		else
			path = ft_search_exec(arg, path_env);
		free(path_env);
	}
	if (path == NULL)
	{
		free(path);
		return (NULL);
	}
	else
		return (path);
}
