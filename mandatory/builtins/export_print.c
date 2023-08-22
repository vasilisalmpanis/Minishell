/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:12:46 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/19 10:12:56 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * Function:  export_print
// * --------------------
// * Prints the env list with declare -x before and if node has no value
// * it doesn't print the ='${lst.value}'
// * @lst	Reference to the env list
// */
void	export_print(t_env *lst)
{
	t_env	**exp;
	int		length;
	int		i;

	exp = sort_list_env(lst, compare_keys);
	if (!exp)
		return ;
	length = env_lst_size(lst);
	i = -1;
	while (++i < length)
	{
		if (exp[i]->key[1] != '_' && exp[i]->key[0] != '\0')
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(exp[i]->key, 1);
			if (exp[i]->value[0] != '\0')
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(exp[i]->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
	}
	free(exp);
}

t_env	**sort_list_env(t_env *lst, int (*cmp)(char *, char *))
{
	t_env	**array;
	t_env	*current;
	int		length;
	int		i;

	length = env_lst_size(lst);
	array = (t_env **) malloc(length * sizeof(t_env *));
	if (array == NULL)
		return (NULL);
	current = lst;
	i = 0;
	while (current)
	{
		array[i] = current;
		++i;
		current = current->next;
	}
	sort_env_array(array, length, cmp);
	return (array);
}

void	sort_env_array(t_env **array, int length, int (*cmp)(char *, char *))
{
	int		i;
	int		j;
	int		min_index;
	t_env	*temp;

	i = -1;
	while (++i < length - 1)
	{
		min_index = i;
		j = i + 1;
		while (j < length)
		{
			if (cmp(array[j]->key, array[min_index]->key) < 0)
				min_index = j;
			j++;
		}
		if (min_index != i)
		{
			temp = array[i];
			array[i] = array[min_index];
			array[min_index] = temp;
		}
	}
}

int	compare_keys(char *a, char *b)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(a);
	j = ft_strlen(b);
	if (i > j)
		return (ft_strncmp(a, b, i));
	return (ft_strncmp(a, b, j));
}
