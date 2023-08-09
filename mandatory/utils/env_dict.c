/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dict.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:57:46 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/09 12:57:46 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*lst_env_node(char *key, char *value)
{
	t_env	*node;
	int		temp;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (ft_strncmp(node->key, "SHLVL", ft_strlen(node->key)) == 0)
	{
		temp = ft_atoi(value);
		temp += 1;
		node->value = ft_itoa(temp);
	}
	else
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	ft_env_addback(t_env **lst, t_env *new)
{
	t_env	**ptr;

	ptr = lst;
	while (*ptr)
		ptr = &(*ptr)->next;
	*ptr = new;
}

void	ft_env_free(t_env **lst)
{
	t_env	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

int main(int argc, char **argv, char **en)
{
	t_env	*lst;
	t_env	*tmp;
	char	**temp;
	int		i;

	i = 0;
	temp = ft_split(en[i], '=');
	lst = lst_env_node(temp[0], temp[1]);
	ft_free(temp);
	while (en[++i])
	{
		temp = ft_split(en[i], '=');
		tmp = lst_env_node(temp[0], temp[1]);
		ft_env_addback(&lst, tmp);
		ft_free(temp);
	}
	ft_env_free(&lst);
	return (0);
}