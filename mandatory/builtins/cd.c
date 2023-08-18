/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:58:26 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/16 19:07:36 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_key(t_env *env, char *key)
{
	char	*pwd;

	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			pwd = ft_strdup(env->value);
			if (!pwd)
				return (NULL);
		}
		env = env->next;
	}
	return (pwd);
}

int	set_value_env(t_env *env, char *key, char *pwd)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			if (env->value[0])
				free(env->value);
			env->value = ft_strdup(pwd);
			if (!env->value)
				return (1);
		}
		env = env->next;
	}
	return (0);
}

int	ft_change_env(t_env *env, char *target_dir)
{
	char	*pwd;

	pwd = find_key(env, "PWD");
	if (set_value_env(env, "OLDPWD", pwd))
		return (1);
	if (set_value_env(env, "PWD", target_dir))
		return (1);
	if (pwd)
		free(pwd);
	if (target_dir)
		free(target_dir);
	return (0);
}

int	cd_home(t_cmd *cmd, t_env *env)
{
	char		*home;

	if (cmd->args[0])
		return (1);
	if (!cmd->args[0])
	{
		home = getenv("HOME");
		if (!home)
			return (printf("error\n"), 1);
		ft_change_env(env, home);
		chdir(home);
	}
	return (0);
}

/*
 * Function:  cd
 * --------------------
 * Changes directory to the absolute or relative path passed to it.
 * If cmd has more than one argument it is supposed to display an error message
 * and set the error code accordingly
 * @cmd Reference to the command given by lexer
 */
int	cd_dir(t_cmd *cmd, t_env *env)
{
	char		*home;

	if (!cd_home(cmd, env))
		return (1);
	else
	{
		if (ft_strncmp(cmd->args[0], "~", ft_strlen(cmd->args[0])) == 0)
			return (ft_printf("cd: ~: Not handled by minishell\n"), 1);
		else
		{
			if (chdir(cmd->args[0]) == 0)
			{
				home = ft_strdup(getcwd(NULL, 0));
				if (!home)
				{
					ft_printf("%s%s", CD1, CD2);
					home = ft_strdup(getenv("HOME"));
				}
				ft_change_env(env, home);
			}
			else
				return (printf(NO_CD" %s\n", cmd->args[0]), 1);
		}
	}
	return (0);
}
