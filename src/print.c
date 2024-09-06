/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:34:59 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 06:40:13 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	print_token_type(t_token_type type)
{
	if (type == WORD)
		printf("WORD");
	else if (type == PIPE)
		printf("PIPE");
	else if (type == REDIRECT_IN)
		printf("REDIRECT_IN");
	else if (type == REDIRECT_OUT)
		printf("REDIRECT_OUT");
	else if (type == HEREDOC)
		printf("HEREDOC");
	else if (type == APPEND)
		printf("APPEND");
	else if (type == QUOTE)
		printf("QUOTE");
	else if (type == DQUOTE)
		printf("DQUOTE");
	else
		printf("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	while (tokens != NULL)
	{
		print_token_type(tokens->type);
		printf("\t\t%s\n", tokens->value);
		tokens = tokens->next;
	}
}

void	print_commands(t_command *commands)
{
	int	cmd_count;

	cmd_count = 1;
	while (commands)
	{
		ft_printf("Command %d:\n", cmd_count++);
		if (commands->args)
		{
			ft_printf("  Args: ");
			for (int i = 0; commands->args[i]; ++i)
			{
				ft_printf("'%s' ", commands->args[i]);
			}
			ft_printf("\n");
		}
		t_redirection *redir = commands->redirections;
		while (redir) {
			ft_printf("  Redirection: ");
			switch (redir->type) {
				case REDIR_INPUT:
				ft_printf("Input from '%s'", redir->filename);
                    break;
                case REDIR_OUTPUT:
                    printf("Output to '%s'", redir->filename);
                    break;
                case REDIR_APPEND:
                    printf("Append to '%s'", redir->filename);
                    break;
            }
            printf("\n");
            redir = redir->next;
        }

        t_heredoc *heredoc = commands->heredocs;
        while (heredoc) {
            printf("  Heredoc with delimiter '%s'\n", heredoc->delimiter);
            heredoc = heredoc->next;
        }

        printf("  Is piped: %s\n", commands->is_piped ? "Yes" : "No");
        printf("\n");

        commands = commands->next;
    }
}*/
