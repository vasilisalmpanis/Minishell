/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:03:16 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 13:00:38 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd_lex_env(t_cmd **cmd_lst, t_lex **lex_lst, char **env_paths)
{
	ft_cmd_lst_free(cmd_lst);
	ft_lst_free(lex_lst);
	if (env_paths)
		ft_free(env_paths);
}

void	ft_cmd_lst_free(t_cmd **lst)
{
	t_cmd	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp->cmd)
			free(temp->cmd);
		if (temp->path)
			free(temp->path);
		if (temp->args)
			ft_free(temp->args);
		//free file list
		free(temp);
	}
}

void	ft_lst_free(t_lex **lst)
{
	t_lex	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
