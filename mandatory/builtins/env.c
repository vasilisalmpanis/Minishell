/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:21:30 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/09 16:21:30 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_env *lst, t_cmd cmd)
{
	t_env	*env;

	env = lst;
	if (cmd.args != NULL)
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(cmd.args[0], 1);
		ft_putstr_fd(": No such file or directory", 1);
		return (1);
	}
	while (env != NULL)
	{
		if (env->value != NULL)
			printf("%s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

//adds the new nodes in the end of the list. normal env adds in random places