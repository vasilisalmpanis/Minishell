/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:34:18 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 15:50:05 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*trim_word(char *exp_word)
{
	char	*trimmed_word;

	if (exp_word[0] == '"')
		trimmed_word = ft_strtrim(exp_word, "\"");
	else if (exp_word[0] == '\'')
		trimmed_word = ft_strtrim(exp_word, "'");
	else
		return (exp_word);
	if (!trimmed_word)
		return (free(exp_word), NULL);
	free(exp_word);
	return (trimmed_word);
}

int	calc_offset(char *split, int start, int *i)
{
	int	offset;

	offset = 0;
	if ((split[start] == '{' && split[*i] == '}')
		|| (split[start] == '(' && split[*i] == ')'))
	{
		offset++;
		(*i)++;
	}
	if (split[start + 1] == '{')
	{
		offset = -1;
		ft_putstr_fd("Error: Bad syntax near '{'\n", 2);
	}
	return (offset);
}

char	*remove_quotes(char *split)
{
	int		i;
	int		count;
	char	*word;

	if (split[0] == '\'' || split[0] == '\"')
		return (split);
	i = -1;
	count = 0;
	while (split[++i])
	{
		if (split[i] != '\'' && split[i] != '\"')
			++count;
	}
	word = ft_calloc(count + 1, sizeof(char));
	if (!word)
		return (split);
	i = -1;
	count = 0;
	while (split[++i])
	{
		if (split[i] != '\'' && split[i] != '\"')
			word[count++] = split[i];
	}
	return (word);
}
