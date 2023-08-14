/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:23:37 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/14 17:29:15 by mamesser         ###   ########.fr       */
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
int	echo(t_cmd *cmd) // currently prints -n from arguments
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (cmd->opt == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}

//int	main(void)
//{
//	t_cmd	cmd1;
//	t_cmd	cmd2;
//	t_cmd	cmd3;
//
//	cmd1.args = (char **)malloc(4 * sizeof(char *));
//	cmd1.args[0] = "Hello,";
//	cmd1.args[1] = "";
//	cmd1.args[2] = "world!";
//	cmd1.args[3] = NULL;
//	cmd1.opts = 0;
//
//	cmd2.args = (char **)malloc(4 * sizeof(char *));
//	cmd2.args[0] = "This";
//	cmd2.args[1] = "is";
//	cmd2.args[2] = "a";
//	cmd2.args[3] = "test";
//	cmd2.args[4] = NULL;
//	cmd2.opts = "-nn";
//
//	cmd3.args = (char **)malloc(2 * sizeof(char *));
//	cmd3.args[0] = "Single";
//	cmd3.args[1] = NULL;
//	cmd3.opts = 0;
//
//	echo(cmd1);
//	echo(cmd2);
//	echo(cmd3);
//
//	free(cmd1.args);
//	free(cmd2.args);
//	free(cmd3.args);
//	return (0);
//}