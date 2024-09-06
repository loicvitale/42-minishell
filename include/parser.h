/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:50:12 by jhouyet           #+#    #+#             */
/*   Updated: 2024/02/23 10:38:59 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parser.c
void	ft_parser(t_minishell *shell);

// handle.c
void	ft_parse_word(t_command *current_cmd, char *value);
void	ft_parse_redirection(t_command *current_cmd, t_token *token);
void	ft_parse_heredoc(t_command *current_cmd, t_token **token_ptr);