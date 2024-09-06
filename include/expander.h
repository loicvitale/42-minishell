/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:50:07 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 06:42:33 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* expandeur.c */
void	init_env(char **envp, t_minishell *shell);
void	ft_core_expander(t_minishell *shell);
void	ft_replace_var(t_env *env, char *str, int *k, char **temp);

/* expandeur_check.c */
char	is_quote(char c);
t_env	*is_var_exist(t_env *env, char *arg);
int		is_env_char(char c);
int		is_char_stop_var(char c);
char	*find_stop_var(char *str, int k);

/* expandeur_get.c */
char	*get_env_name(char *src);
char	*get_env_value(char *src);
int		get_size_env_name(char *src);
int		get_size_env_value(char *src);
char	**get_env_tab(t_env *env);

/* expandeur_utils.c */
char	*ft_join_quote(char *words, char c);
char	*ft_char_to_string(char c);
void	print_env(t_env *env);
char	*ft_delete_quote(char *str);
void	fill_env(char **envp, t_minishell *shell);
