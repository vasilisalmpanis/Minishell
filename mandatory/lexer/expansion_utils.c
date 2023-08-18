/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:34:18 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 12:34:49 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	{
		offset = -1;
		ft_putstr_fd("Error: Bad syntax near '{'\n", 2);
	}
	return (offset);
}
