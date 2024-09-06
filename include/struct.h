/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:41:39 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 06:40:51 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND,
	QUOTE,
	DQUOTE,
}			t_token_type;

typedef enum e_redirection_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND
}				t_redirection_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_redirection
{
	t_redirection_type		type;
	char					*filename;
	struct s_redirection	*next;
}				t_redirection;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*filename;
	struct s_heredoc	*next;
}				t_heredoc;

typedef struct s_command
{
	char				**args;
	t_redirection		*redirections;
	t_heredoc			*heredocs;
	int					is_piped;
	struct s_command	*next;
}				t_command;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char		*name;
	t_env		*env;
	t_token		*tokens;
	t_command	*commands;
}				t_minishell;