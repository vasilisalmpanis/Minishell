/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:03:16 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/08 14:22:00 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_cmd	*ft_new_cmd(int id)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(*node));
	// get all env variables; node->env = 
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

void	ft_cmd_lst_free(t_cmd **lst)
{
	t_cmd	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		// free(temp->value); 
		free(temp);
	}
}

t_lex	*ft_new_tk(void *value, t_token token)
{
	t_lex	*node;

	node = (t_lex *)malloc(sizeof(t_lex));
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	node->token = token;
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
		free(temp->value);
		free(temp);
	}
}
