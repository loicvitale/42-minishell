/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:42:45 by jhouyet           #+#    #+#             */
/*   Updated: 2024/03/28 07:10:25 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "struct.h"
# include "builtins.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "signals.h"
# include "exit.h"

extern int	g_error_num;

void	ft_loop(t_minishell *shell, char **envp);
void	print_tokens(t_token *tokens);
void	print_commands(t_command *commands);

#endif