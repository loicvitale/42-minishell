/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandeur_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:45:16 by lvitale           #+#    #+#             */
/*   Updated: 2024/03/28 10:01:50 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_char_to_string(char c)
{
	char	*str;

	str = ft_safe_calloc(2, sizeof(char), "new str char_to_string");
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_join_quote(char *words, char c)
{
	char	*new_words;

	if (!words)
		words = ft_safe_calloc(1, sizeof(char), "new join quote");
	new_words = ft_char_to_string(c);
	words = str_join_free(words, new_words);
	return (words);
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (has_equal(env->var))
			ft_printf("%s\n", env->var);
		env = env->next;
	}
}

char	*ft_delete_quote(char *str)
{
	int		i;
	char	*new_word;
	char	current_quote;

	i = 0;
	new_word = ft_safe_calloc(1, sizeof(char), "new word delete quote");
	while (str[i])
	{
		if (!current_quote)
			current_quote = is_quote(str[i]);
		if (!(is_quote(str[i]))
			|| (is_quote(str[i]) && is_quote(str[i]) != current_quote))
			new_word = ft_join_quote(new_word, str[i]);
		i++;
	}
	return (new_word);
}

void	fill_env(char **envp, t_minishell *shell)
{
	char	*var;

	var = ft_strjoin("_=", getcwd(NULL, sizeof(NULL)));
	var = ft_strjoin(var, "/");
	envp[0] = ft_strdup("OLDPWD");
	envp[1] = ft_strjoin("PWD=", getcwd(NULL, sizeof(NULL)));
	envp[2] = ft_strdup("SHLVL=1");
	envp[3] = ft_strjoin(var, shell->name);
	envp[4] = NULL;
}
