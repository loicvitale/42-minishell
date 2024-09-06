/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:37:18 by jhouyet           #+#    #+#             */
/*   Updated: 2024/02/29 10:45:33 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_handle_input_redirection(char **input)
{
	t_token_type	type;
	char			*token_value;

	type = REDIRECT_IN;
	token_value = "<";
	if (*(*input + 1) == '<')
	{
		type = HEREDOC;
		token_value = "<<";
		(*input)++;
		if (*(*input + 1) == '<')
			return (ft_syntax_error(*(*input + 1), *(*input + 2)), NULL);
	}
	(*input)++;
	while (ft_is_space(**input))
		(*input)++;
	if (**input == '\0' || ft_strchr("<>|", **input))
		return (ft_syntax_error(*(*input), *(*input + 1)), NULL);
	return (ft_create_token(ft_strdup(token_value), type));
}

t_token	*ft_handle_output_redirection(char **input)
{
	t_token_type	type;
	char			*token_value;

	type = REDIRECT_OUT;
	token_value = ">";
	if (*(*input + 1) == '>')
	{
		type = APPEND;
		token_value = ">>";
		(*input)++;
		if (*(*input + 1) == '>')
			return (ft_syntax_error(*(*input + 1), *(*input + 2)), NULL);
	}
	(*input)++;
	while (ft_is_space(**input))
		(*input)++;
	if (**input == '\0' || ft_strchr("<>|", **input))
		return (ft_syntax_error(*(*input), *(*input + 1)), NULL);
	return (ft_create_token(ft_strdup(token_value), type));
}

t_token	*ft_handle_pipe(char **input)
{
	if (*(*input + 1) == '|')
		return (ft_syntax_error(*(*input + 1), *(*input + 2)), NULL);
	(*input)++;
	while (ft_is_space(**input))
		(*input)++;
	if (**input == '\0' || ft_strchr("|", **input))
		return (ft_syntax_error(*(*input + 1), *(*input + 2)), NULL);
	return (ft_create_token(ft_strdup("|"), PIPE));
}

void	ft_handle_word_end(char **end, int *quote_count, char *quote_type)
{
	while (**end)
	{
		if (**end == '\'' || **end == '"')
		{
			if (*quote_count == 0 || *quote_type == **end)
			{
				(*quote_count)++;
				*quote_type = **end;
			}
		}
		else if (ft_is_space(**end) && *quote_count % 2 == 0)
			break ;
		else if (ft_strchr("<>|", **end) && *quote_count % 2 == 0)
			break ;
		(*end)++;
	}
}

t_token	*ft_handle_word(char **input)
{
	char	*start;
	char	*end;
	int		quote_count;
	char	quote_type ;

	start = *input;
	end = *input;
	quote_count = 0;
	quote_type = '\0';
	ft_handle_word_end(&end, &quote_count, &quote_type);
	if (quote_count % 2 != 0)
	{
		ft_error(1);
		return (NULL);
	}
	*input = end;
	return (ft_create_token(ft_strndup(start, end - start), WORD));
}

/*
t_token	*ft_handle_word(char **input)
{
	char	*start;

	start = *input;
	while (**input && !ft_is_space(**input) && !ft_strchr("\"'<>|", **input))
		(*input)++;
	return (ft_create_token(ft_strndup(start, *input - start), WORD));
}
*/
