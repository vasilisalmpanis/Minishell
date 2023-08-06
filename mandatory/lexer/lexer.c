/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:15:37 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/06 19:05:06 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *input)
{
	int		i;
	int		flag;
	char	buf;

	i = -1;
	flag = 0;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			flag = 1;
			buf = input[i];
			i++;
		}
		while (input[i] != buf && input[i] && buf != 0)
			i++;
		if (input[i] == buf)
		{
			flag = 0;
			buf = 0;
		}
	}
	ft_putnbr_fd(flag, 1);
	return (flag);
}

// pre_lexer: function to check for uneven num of 
//double/single quotes before lexer 
//(or if single/double quote is not followed by same quote)
// function to check for expansion
