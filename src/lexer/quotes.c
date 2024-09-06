/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:03:57 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/01 12:17:08 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
t_token	*ft_concatenate_next_word(char **input, t_token *current_token)
{
	t_token	*next_token;
	char	*concatenated_value;

	if (**input && !ft_is_space(**input) && **input != '<' && **input != '>' \
	&& **input != '|')
	{
		next_token = ft_handle_word(input);
		if (next_token)
		{
			concatenated_value = ft_safe_calloc(ft_strlen(current_token->value) \
			+ ft_strlen(next_token->value) + 1, sizeof(char), \
			"concatenated value");
			ft_strcpy(concatenated_value, current_token->value);
			ft_strcat(concatenated_value, next_token->value);
			free(current_token->value);
			current_token->value = concatenated_value;
			free(next_token->value);
			free(next_token);
		}
	}
	return (current_token);
}

t_token	*ft_handle_quotes(char **input, char quote_type)
{
	char			*start;
	char			*end;
	char			*value;
	t_token			*token;
	t_token_type	token_type;

	start = *input;
	end = start + 1;
	while (*end && *end != quote_type)
		end++;
	if (*end != quote_type)
	{
		ft_error(1);
		return (NULL);
	}
	value = ft_strndup(start, end - start + 1);
	if (quote_type == '"')
		token_type = DQUOTE;
	else
		token_type = QUOTE;
	token = ft_create_token(value, token_type);
	free(value);
	*input = end + 1;
	token = ft_concatenate_next_word(input, token);
	return (token);
}
*/