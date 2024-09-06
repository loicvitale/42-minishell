/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:32:11 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/27 17:01:23 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_process_char_as_token(char **input, t_token **tokens)
{
	t_token	*new_token ;

	new_token = NULL;
	if (**input == '<')
		new_token = ft_handle_input_redirection(input);
	else if (**input == '>')
		new_token = ft_handle_output_redirection(input);
	else if (**input == '|')
		new_token = ft_handle_pipe(input);
	else
		new_token = ft_handle_word(input);
	if (!new_token)
	{
		ft_free_tokens(tokens);
		*tokens = NULL;
		return (NULL);
	}
	ft_add_token(tokens, new_token);
	return (new_token);
}

t_token	*ft_lexer(char *input)
{
	t_token	*tokens;
	int		first_char;

	first_char = 0;
	tokens = NULL;
	while (*input)
	{
		if (ft_is_space(*input))
		{
			input++;
			continue ;
		}
		else if (!first_char && *input == '|')
			return (ft_syntax_error(*(input), *(input + 1)), NULL);
		first_char = 1;
		if (!ft_process_char_as_token(&input, &tokens))
			return (NULL);
	}
	return (tokens);
}
