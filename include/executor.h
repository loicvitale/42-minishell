/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:50:05 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 06:42:52 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// executor.c
void	ft_run_child(t_minishell *shell, t_command *cmd, int in_fd, int out_fd);
int		ft_execute_builtin(t_minishell *shell, t_command *cmd, int in, int out);
void	ft_execute_command(t_minishell *shell, t_command *cmd, int in, int ou);
void	ft_executor(t_minishell *shell);

// commands.c
char	*ft_check_command_path(const char *folder_path, const char *arg);
char	*ft_search_exec_with_path(char *arg);
char	*ft_search_exec(char *arg, char *path_env);
char	*ft_check_cmd(t_minishell *shell, char *arg);

// heredocs.c
void	ft_write_content_to_file(const char *filename, const char *content);
char	*ft_read_heredoc_content(t_minishell *shell, const char *delimiter);
char	*ft_heredoc_filename(void);
void	ft_exec_heredoc(t_minishell *shell, t_command *cmd);
int		ft_exec_heredocs(t_minishell *shell, t_command *cmd);

// pipes.c
void	ft_init_pipe_fds(t_command *cmd, int *in_fd, int *out_fd, int fd[2]);
void	ft_cleanup_fds(int in_fd, int fd[2], t_command *cmd);
void	ft_handle_redirections_pipe(int in_fd, int out_fd);

// redirections.c
void	ft_exec_redirections(t_command *cmd);

// simple.c
void	ft_simple_cmd(t_minishell *shell, t_command *cmd);