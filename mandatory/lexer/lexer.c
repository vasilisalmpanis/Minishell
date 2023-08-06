/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:15:37 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/06 18:44:46 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *input)
{
	int	i;
	int	flag;
	char	buf;

	i = -1;
	flag = 0;
	while (input[++i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '"' || input[i] == '\'')
		{
			flag = 1;
			buf = input[i];
			i++;
		}
		ft_putnbr_fd(flag, 1);
		while (input[i] != buf && input[i])
			i++;
		if (input[i] == buf)
		{
			flag = 0;
			buf = 0;
		}
	}
	return (flag);
}

// pre_lexer: function to check for uneven num of double/single quotes before lexer (or if single/double quote is not followed by same quote)
// function to check for expansion

