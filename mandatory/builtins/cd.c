/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:58:26 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/14 16:39:01 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Function:  cd
 * --------------------
 * Changes directory to the absolute or relative path passed to it.
 * If cmd has more than one argument it is supposed to display an error message
 * and set the error code accordingly
 * @cmd Reference to the command given by lexer
 */
int	cd_dir(t_cmd *cmd)
{
	const char	*target_dir = cmd->args[1];

	if (target_dir == NULL)
	{
		target_dir = getenv("HOME");
		if (target_dir == NULL)
		{
			ft_putstr_fd("cd: Could not retrieve home directory\n", 2);
			return (1);
		}
	}
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

//int main(void)
//{
//	t_cmd	cmd;
//
//	cmd.args = (char **)malloc(3 * sizeof(char *));
//	cmd.args[1] = "..";
//	cmd.args[2] = NULL;
//	cmd.opts = "-n";
//
//	cd_dir(cmd);
//	free(cmd.args);
//	return (0);
//}