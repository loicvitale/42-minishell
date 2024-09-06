/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 07:34:22 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/27 16:56:54 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exe_child(t_minishell *shell, t_command *cmd, char *path)
{
	pid_t	pid;
	char	**env;

	if (!path)
	{
		ft_cmd_error(cmd->args[0]);
		g_error_num = 127;
		return ;
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			env = get_env_tab(shell->env);
			execve(path, cmd->args, env);
			ft_exit_failure("minishell", env);
		}
		else if (pid < 0)
			perror("minishell");
		else
			waitpid(pid, NULL, 0);
		free(path);
	}
}

void	ft_exec_command(t_minishell *shell, t_command *cmd)
{
	char	*path;
	pid_t	pid;

	ft_exec_heredoc(shell, cmd);
	if (ft_execute_builtin(shell, cmd, STDIN_FILENO, STDOUT_FILENO) == 0)
	{
		path = ft_check_cmd(shell, cmd->args[0]);
		if (cmd->args[0][0] != '\0')
			ft_exe_child(shell, cmd, path);
	}
}

void	ft_restore_std(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	ft_simple_cmd(t_minishell *shell, t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	if (cmd && cmd->next == NULL)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		ft_exec_redirections(cmd);
		ft_exec_command(shell, cmd);
		ft_restore_std(saved_stdin, saved_stdout);
	}
}
