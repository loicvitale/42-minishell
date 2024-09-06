/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:28:00 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/27 16:55:58 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_run_child(t_minishell *shell, t_command *cmd, int in, int out)
{
	char	*path;
	char	**env;

	ft_handle_redirections_pipe(in, out);
	ft_exec_redirections(cmd);
	path = ft_check_cmd(shell, cmd->args[0]);
	if (!path)
	{
		ft_cmd_error(cmd->args[0]);
		exit(127);
	}
	env = get_env_tab(shell->env);
	execve(path, cmd->args, env);
	ft_exit_failure("execve", env);
	free(path);
}

int	ft_execute_builtin(t_minishell *shell, t_command *cmd, int in, int out)
{
	ft_handle_redirections_pipe(in, out);
	ft_exec_redirections(cmd);
	if (cmd->args && cmd->args[0])
	{
		if (ft_strcmp(cmd->args[0], "cd") == 0)
			return (ft_cd(shell, cmd), 1);
		else if (ft_strcmp(cmd->args[0], "echo") == 0)
			return (ft_echo(shell, cmd), 1);
		else if (ft_strcmp(cmd->args[0], "env") == 0)
			return (ft_env(shell, cmd), 1);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			return (ft_exit(shell, cmd), 1);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
			return (ft_export(shell, cmd, 1), 1);
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			return (ft_pwd(shell, cmd), 1);
		else if (ft_strcmp(cmd->args[0], "unset") == 0)
			return (ft_unset(shell, cmd), 1);
	}
	return (0);
}

void	ft_execute_command(t_minishell *shell, t_command *cmd, int in, int out)
{
	int		heredoc_fd;
	pid_t	pid;

	heredoc_fd = ft_exec_heredocs(shell, cmd);
	pid = fork();
	if (pid == 0)
	{
		if (heredoc_fd != -1)
			in = heredoc_fd;
		if (ft_execute_builtin(shell, cmd, in, out) == 0)
			ft_run_child(shell, cmd, in, out);
		exit(EXIT_SUCCESS);
	}
	if (pid < 0)
		perror("fork");
	else
		waitpid(pid, NULL, 0);
	if (heredoc_fd != -1)
		close(heredoc_fd);
}

void	ft_executor(t_minishell *shell)
{
	int			in_fd;
	int			fd[2];
	int			out_fd;
	t_command	*current_cmd;
	int			status;

	in_fd = STDIN_FILENO;
	current_cmd = shell->commands;
	if (current_cmd && current_cmd->next == NULL)
		return (ft_simple_cmd(shell, current_cmd));
	while (current_cmd)
	{
		ft_init_pipe_fds(current_cmd, &in_fd, &out_fd, fd);
		ft_execute_command(shell, current_cmd, in_fd, out_fd);
		ft_cleanup_fds(in_fd, fd, current_cmd);
		in_fd = fd[0];
		current_cmd = current_cmd->next;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_error_num = WEXITSTATUS(status);
	}
}
