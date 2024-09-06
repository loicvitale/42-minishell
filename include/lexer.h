/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:50:09 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/01 12:17:30 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lexer.c
t_token	*ft_lexer(char *input);

// handle.c
t_token	*ft_handle_input_redirection(char **input);
t_token	*ft_handle_output_redirection(char **input);
t_token	*ft_handle_pipe(char **input);
void	ft_handle_word_end(char **end, int *quote_count, char *quote_type);
t_token	*ft_handle_word(char **input);

// quotes.c
//t_token	*ft_concatenate_next_word(char **input, t_token *current_token);
//t_token	*ft_handle_quotes(char **input, char quote_type);

// tokens.c
t_token	*ft_create_token(char *value, t_token_type type);
void	ft_add_token(t_token **head, t_token *new_token);
//char	*ft_extract_token(char **input, char delimiter);

// utils.c
int		ft_is_space(char c);
void	ft_syntax_error(char next_char, char next_next_char);