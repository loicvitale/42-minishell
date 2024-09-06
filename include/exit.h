/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:50:12 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 06:43:25 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// exit.c
void	ft_free_shell(t_minishell *shell);
void	ft_exit_failure(char *str, char **tab);

// errors.c
int		ft_error(int error);
int		ft_error_redir(int error);
void	*ft_safe_calloc(size_t count, size_t size, char *error_message);
int		ft_cmd_error(char *str);
int		ft_redir_error(char *filename);

// free.c
void	ft_free_env(t_minishell	*shell, t_env *env);
void	ft_free_tokens(t_token **tokens);
void	ft_free_commands(t_command **commands);
void	ft_free_redirections(t_redirection **redirection);
void	ft_free_heredocs(t_heredoc **heredoc);

// free_2.c
char	*str_join_free(char	*src, char *dst);
void	ft_free_tab(char **tab);