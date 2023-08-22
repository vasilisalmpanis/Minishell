/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:51:42 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 12:52:06 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int ft_check_lex(t_lex *lst)
{
	while (lst)
	{
		if (lst->value[0] != '\0')
			return (0);
		lst = lst->next;
	}
	return (1);
}
