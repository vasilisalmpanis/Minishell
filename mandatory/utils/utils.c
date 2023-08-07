/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:52:47 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/07 11:58:33 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	**split_args(char *input)
{
	int		j;
	char	buf;
	char	**split;

	j = -1;
	while (input[++j])
	{
		if (ft_isspace(input[j]))
			input[j] = 26;
		if (input[j] == '"' || input[j] == '\'')
		{
			buf = input[j];
			++j;
			while (input[j] != buf && input[j])
				j++;
		}
	}
	split = ft_split(input, 26);
	return (split);
}
