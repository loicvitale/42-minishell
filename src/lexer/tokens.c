/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:37:12 by jhouyet           #+#    #+#             */
/*   Updated: 2024/02/29 10:45:59 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_safe_calloc(1, sizeof(t_token), "new_token");
	if (!new_token)
		return (NULL);
	if (value)
		new_token->value = value;
	else
		new_token->value = NULL;
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	ft_add_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
		new_token->prev = temp;
	}
}

/*
char	*ft_extract_token(char **input, char delimiter)
{
	char	*start;

	start = *input;
	while (**input && **input != delimiter)
		(*input)++;
	if (**input == delimiter)
		(*input)++;
	return (ft_strndup(start, *input - start));
}
*/
