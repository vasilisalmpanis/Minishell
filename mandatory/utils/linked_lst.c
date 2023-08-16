/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:03:16 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/16 14:32:50 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_cmd	*ft_new_cmd(int id, char **env_paths)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(*node));
	if (env_paths)
		node->env_flag = 1;
	node->cmd_id= id;
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
		if (temp->delim)
			free(temp->delim);
		if (temp->in_file)
			free(temp->in_file);
		if (temp->out_file)
			free(temp->out_file);
		if (temp->app_file)
			free(temp->app_file);
		//free env?
		free(temp);
	}
}

t_lex	*ft_new_tk(void *value, t_token token, int pos)
{
	t_lex	*node;

	node = (t_lex *)malloc(sizeof(t_lex));
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	if (!node->value)
		return (free(node), NULL);
	node->token = token;
	node->pos = pos;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_end(t_lex **lst, t_lex *new)
{
	t_lex	**ptr;

	ptr = lst;
	while (*ptr)
		ptr = &(*ptr)->next;
	*ptr = new;
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


