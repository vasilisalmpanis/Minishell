/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:52:47 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/06 16:42:42 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_args(char *input)
{
	int		j;
	char	buf;
	char	**split;

	j = -1;
	while (input[++j])
	{
		if (input[j] == ' ')
			input[j] = 26;
		if (input[j] == 39 || input[j] == 34)
		{
			buf = input[j];
			++j;
			while (input[j] != buf && input[j])
				j++;
			++j;
		}
	}
	split = ft_split(input, 26);
	return (split);
}

// int	main(void)
// {
// 	char	**ret;
// 	char	*str;
// 	int	i = 0;
	
// 	str = 
// 	ret = split_args(str);
// 	while (ret[i])
// 	{
// 		printf("%s\n", ret[i++]);
// 	}
	
// }