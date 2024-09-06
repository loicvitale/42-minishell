/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:49:59 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 06:41:27 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* cd.c */
void	ft_cd(t_minishell *shell, t_command *cmd);

/* echo.c */
void	ft_echo(t_minishell *shell, t_command *cmd);

/* env.c */
void	ft_env(t_minishell *shell, t_command *cmd);

/* exit.c */
void	ft_exit(t_minishell *shell, t_command *cmd);
void	ft_free_all(t_minishell *shell);

/* export.c */
void	add_var(t_minishell *shell, char *str);
void	ft_export(t_minishell *shell, t_command *cmd, int i);
size_t	has_equal(char *str);

/* pwd.c */
void	ft_pwd(t_minishell *shell, t_command *cmd);

/* unset.c */
void	ft_unset(t_minishell *shell, t_command *cmd);
void	free_node(t_minishell *shell, t_env *env);

/* builtins_utils.c */
void	print_sort_env(t_env *env);
void	change_var(char *new_var, char **var, char *arg);
size_t	has_plus(char *str);
int		export_unset_error(int option, char *str);