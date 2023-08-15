/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:43:19 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/15 18:21:32 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_expand(char *word, int i)
{
	int		start;
	char	*exp_word;

	exp_word = ft_calloc(1, 1);
	if (!exp_word)
		return (NULL);
	while (word[++i])
	{
		start = i + 1;
		if (word[0] != '\'' && word[i] == '$')
		{
			if (word[i + 1] != '\0' && !ft_isspace(word[i + 1]))
			{
				if (expand(word, &i, start, &exp_word) == 2)
					return (ft_putstr_fd("Error: Bad syntax near '{'\n", 2), NULL);
			}
		}
		exp_word = ft_charjoin_mod(exp_word, word[i]);
		if (!exp_word)
			return (NULL);
		if (!word[i])
			break ;
	}
	exp_word = trim_word(exp_word);
	return (exp_word);
}

char	*trim_word(char *word)
{
	char	*trimmed_word;

	if (word[0] == '"')
		trimmed_word = ft_strtrim(word, "\"");
	else if (word[0] == '\'')
		trimmed_word = ft_strtrim(word, "'");
	else
		return (word);
	if (!trimmed_word)
		return (free(word), NULL);
	free(word);
	return (trimmed_word);
}

int	expand(char *word, int *i, int start, char **exp_word)
{
	char	*temp;
	char	*exp_var;
	int		offset;

	while (word[*i] && word[*i] != '"' && word[*i] != '\'' 
		&& word[*i] != '}' && word[*i] != ')' && !ft_isspace(word[*i]))
		(*i)++;
	offset = calc_offset(word, start, i);
	if (offset == -1)
		return (free(*exp_word), 2);
	temp = ft_substr(word, start + offset, *i - start - (2 * offset));
	if (!temp)
		return (free(*exp_word), 1);
	exp_var = determine_exp_var(temp);
	if (exp_var)
	{
		*exp_word = ft_strjoin_mod(*exp_word, exp_var);
		if (!(*exp_word))
			return (free(temp), 1);
	}
	if (exp_var)
		free(exp_var);
	free(temp);
	return (0);
}

int	calc_offset(char *word, int start, int *i)
{
	int	offset;

	offset = 0;
	if ((word[start] == '{' && word[*i] == '}')
		|| (word[start] == '(' && word[*i] == ')'))
	{
		offset++;
		(*i)++;
	}
	if (word[start + 1] == '{')
		offset = -1;
	return (offset);
}

char	*determine_exp_var(char *temp)
{
	char	*exp_var;
	char	*temp2;
	int		len;

	len = ft_strlen(temp);
	if (temp[0] == '(' && temp[1] == '('
		&& temp[len - 1] == ')' && temp[len - 2] == ')') // --> not completely working because word/temp stopped at space
	{
		exp_var = ft_strdup("You can calculate in your head"); // may implement do_op
	}
	if (temp[0] == '$' && temp[1] == '\0')
		exp_var = ft_strdup("67672");
	else if (temp[0] == '?' && temp[1] == '\0')
		exp_var = ft_strdup("<last exit code>"); //replace with static variable
	else
	{
		temp2 = getenv(temp);
		if (temp2)
			exp_var = strdup(temp2);
		else
			exp_var = NULL;
	}
	return (exp_var);
}

///// TESTING /////

// int main(void)
// {
// 	char *ret;
	
// 	ret = check_expand("\"Hello ${USER}T\"");
	
// //	temp = "Hello $SHLVL $XPC_FLAGS $TERMINAL_EMULATOR";
// 	printf("%s\n", ret);
// 	free(ret);
// }