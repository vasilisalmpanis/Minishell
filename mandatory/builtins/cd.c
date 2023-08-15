/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:58:26 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/14 17:51:20 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_change_env(t_env *env, char *target_dir)
{
	char	*pwd;
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strncmp(env->key, "PWD", ft_strlen(env->key)) == 0)
		{
			pwd = ft_strdup(env->value);
			if (!pwd)
				return (1);
		}
		env = env->next;
	}
	env = tmp;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", ft_strlen(tmp->key)) == 0)
		{
			if (tmp->value[0])
				free(tmp->value);
			tmp->value = ft_strdup(pwd);
			if (!tmp->value)
				return (1);
		}
		tmp = tmp->next;
	}
	while (env)
	{
		if (ft_strncmp(env->key, "PWD", ft_strlen(env->key)) == 0)
		{
			if (env->value[0])
				free(env->value);
			env->value = ft_strdup(target_dir);
			if (!env->value)
				return (1);
		}
		env = env->next;
	}
	if (pwd)
		free(pwd);
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

	if (!cmd->args[0])
	{
		home = getenv("HOME");
		if (!home)
			return (printf("error\n"), 1);
		ft_change_env(env, home);
		chdir(home);
		// free(home);
	}
	else
	{
		if (ft_strncmp(cmd->args[0], "~", ft_strlen(cmd->args[0])) == 0)
			return (ft_printf("cd: ~: Not handled by minishell\n"), 1);
		else
		{
			if (chdir(cmd->args[0]) == 0)
			{
				home = getcwd(NULL, 0);
				if (!home)
				{
					ft_printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
					home = ft_strdup(getenv("HOME"));
				}
				ft_change_env(env, home);
				free(home);
			}
			else
				return (1);
		}
	}
	return (0);
}

//int main(int argc, char **argv, char **en)
//{
//	t_cmd	cmd;
//	t_env *lst;
//
//	lst = create_env(en);
//	cmd.args = (char **)malloc(2 * sizeof(char *));
//	cmd.args[0] = "..";
//	cmd.args[1] = NULL;
//
//	cd_dir(cmd, lst);
//	free(cmd.args);
//	cmd.args = NULL;
////	int i = -1;
////	while (en[++i])
////	{
////		ft_putstr_fd(en[i], 1);
////		ft_putstr_fd("\n", 1);
////	}
//
//	env(lst, cmd);
//	ft_env_free(&lst);
//	return (0);
//}