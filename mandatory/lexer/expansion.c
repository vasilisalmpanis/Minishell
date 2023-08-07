/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:43:19 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/07 15:48:27 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_expand(char *word)
{
	int		i;
	int		start;
	char 	*exp_word;

	i = -1;
	exp_word = ft_calloc(1, 1);
	if (!exp_word)
		return (NULL);
	while (word[++i])
	{
		start = i;
		if (word[i] == '$')
		{
			if (!ft_isspace(word[i + 1]) && word[i + 1] != '\0')
				expand(word, &i, start, &exp_word);
		}
		exp_word = ft_charjoin_mod(exp_word, word[i]);
		if (!exp_word)
			return (NULL);
	}
	return (exp_word);
}

void	expand(char *word, int *i, int start, char **exp_word)
{
	char	*temp;
	char	*exp_var;
	
	while (word[*i] && !ft_isspace(word[*i]))
		(*i)++;
	temp = ft_substr(word, start + 1, *i - start - 1);
	if (!temp)
	{
		free(*exp_word);
		return ;
	}
	exp_var = getenv(temp);
	if (exp_var)
	{
		*exp_word = ft_strjoin_mod(*exp_word, exp_var);
		if (!(*exp_word))
		{
			free(temp);
			return ;
		}
	}
	free(temp);
}


// int main(void)
// {
// 	char *ret;
// 	char temp[] = "Hello $\0";

// 	ret = check_expand(temp);
// //	temp = "Hello $SHLVL $XPC_FLAGS $TERMINAL_EMULATOR";
// 	printf("%s", ret);
// 	free(ret);
// }
