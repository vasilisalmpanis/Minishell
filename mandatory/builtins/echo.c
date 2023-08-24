/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:23:37 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/23 15:43:02 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Function:  echo
 * --------------------
 * Echoes the arguments passed to the cmd. if the -n flag is present echo doesn't
 * print a newline.
 * @cmd Reference to the command given by lexer
 */
int	echo(t_cmd *cmd)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	if (cmd->args[0])
	{
		if (cmd->args[0][0] == '-')
		{
			while (cmd->args[0][i[0]] && cmd->args[0][i[0]] == 'n')
				i[0]++;
			if (cmd->args[0][i[0]])
				i[1] = 1;
		}
	}
	i[0] = 0;
	while (cmd->args[i[0]])
	{
		print_var(cmd->args[i[0]]);
		if (cmd->args[i[0] + 1] && cmd->args[i[0]][0] != '\0')
			ft_putchar_fd(' ', 1);
		i[0]++;
	}
	if (i[1] == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}

void	print_var(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar_fd(str[i], STDOUT_FILENO);
}
