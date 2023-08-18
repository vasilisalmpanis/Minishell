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


void	ft_file_lst_add(t_file **lst, t_file *new_file)
{
	t_file	**ptr;

	ptr = lst;
	while (*ptr)
		ptr = &(*ptr)->next;
	*ptr = new_file;
}


t_file	*create_new_file(char *delim, t_token token, char *name)
{
	t_file	*node;

	node = (t_file *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(*node));
	if (name)
	{
		node->name = ft_strdup(name);
		if (!node->name)
			return (NULL);
	}
	if (delim)
	{
		node->delim = ft_strdup(delim);
		if (!node->delim)
			return (NULL);
	}
	node->token = token;
	node->next = NULL;
	return (node);
}

t_cmd	*ft_new_cmd(int id, char **env_paths, int exit_code)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(*node));
	if (env_paths)
		node->env_flag = 1;
	node->exit_code = exit_code;
	node->cmd_id = id;
	node->next = NULL;
	return (node);
}

void	ft_cmd_lstadd_end(t_cmd **lst, t_cmd *new)
{
	t_cmd	**ptr;

	ptr = lst;
	while (*ptr)
		ptr = &(*ptr)->next;
	*ptr = new;
}

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
