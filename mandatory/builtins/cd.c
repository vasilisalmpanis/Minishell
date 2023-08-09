/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:58:26 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/08 11:58:32 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_dir(t_cmd cmd)
{
	const char	*target_dir = cmd.args[1];

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