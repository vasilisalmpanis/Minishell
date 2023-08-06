/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:52:47 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/06 15:52:51 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_args(t_data object, int i)
{
	int		j;
	char	buf;
	char	**split;

	j = -1;
	while (object.argv[i][++j])
	{
		if (object.argv[i][j] == ' ')
			object.argv[i][j] = 26;
		if (object.argv[i][j] == 39 || object.argv[i][j] == 34)
		{
			buf = object.argv[i][j];
			object.argv[i][j] = 26;
			while (object.argv[i][j] != buf && object.argv[i][j])
				j++;
			object.argv[i][j] = 26;
		}
	}
	split = ft_split(object.argv[i], 26);
	return (split);
}