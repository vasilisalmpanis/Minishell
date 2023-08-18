/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:43:19 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 12:35:02 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_expand(char *word, int i, int exit_code, int trim_flag)
{
	char	*exp_word;

	exp_word = ft_calloc(1, 1);
	if (!exp_word)
		return (NULL);
	while (word[++i])
	{
		if (word[0] != '\'' && word[i] == '$')
		{
			if (check_expand_helper(word, &i, &exp_word, exit_code))
				return (NULL);
		}
		else
		{
			exp_word = ft_charjoin_mod(exp_word, word[i]);
			if (!exp_word)
				return (NULL);
		}
		if (!word[i])
			break ;
	}
	if (trim_flag)
		exp_word = trim_word(exp_word);
	return (exp_word);
}

int	check_expand_helper(char *word, int *i, char **exp_word, int exit_code)
{
	if (word[*i + 1] != '\0' && !ft_isspace(word[*i + 1]) // what else needs to be added? e.g. '+'
		&& word[*i + 1] != '"' && word[*i + 1] != '\'' 
		&& word[*i + 1] != '}' && word[*i + 1] != ')')
	{
		(*i)++;
		if (expand(word, i, exp_word, exit_code) == 2)
			return (1);
		(*i)--;
	}
	else 
	{
		*exp_word = ft_charjoin_mod(*exp_word, word[*i]);
		if (!(*exp_word))
			return (1);
	}
	return (0);
}

int	expand(char *word, int *i, char **exp_word, int exit_code)
{
	char	*exp_var;

	if (word[*i] && word[*i] == '$')
		exp_var = find_pid(i);
	else
		exp_var = create_exp_var(word, i, exp_word, exit_code);
	if (exp_var)
	{
		*exp_word = ft_strjoin_mod(*exp_word, exp_var);
		if (!(*exp_word))
			return (1);
	}
	free(exp_var);
	return (0);
}
