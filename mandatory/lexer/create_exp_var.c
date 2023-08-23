/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exp_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:32:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/23 11:30:32 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_exp_var(char *split, int *i, int exit_code, char **exp_var)
{
	int		offset;
	int		start;
	char	*temp;

	start = *i;
	offset = 0;
	temp = NULL;
	while (split[*i] && split[*i] != '"' && split[*i] != '\''
		&& split[*i] != '}' && split[*i] != ')' && split[*i] != '$'
		&& !ft_isspace(split[*i]))
		(*i)++;
	offset = calc_offset(split, start, i);
	if (offset == -1)
		return (1);
	temp = ft_substr(split, start + offset, *i - start - (2 * offset));
	if (!temp)
		return (1);
	if (determine_exp_var(temp, exit_code, exp_var))
		return (free(temp), 1);
	free(temp);
	return (0);
}

int	determine_exp_var(char *temp, int exit_code, char **exp_var)
{
	int		len;

	len = ft_strlen(temp);
	if (temp[0] == '(' && temp[1] == '(')
	{
		*exp_var = ft_strdup("You can calculate in your head");
		if (!(*exp_var))
			return (1);
	}
	else if (ft_isdigit(temp[0]))
	{
		*exp_var = ft_strdup(temp + 1);
		if (!(*exp_var))
			return (1);
	}
	else if (temp[0] == '?')
	{
		*exp_var = find_exit_code(temp, exit_code);
		if (!(*exp_var))
			return (1);
	}
	else
		if (find_exp_var(temp, exp_var))
			return (1);
	return (0);
}

int	find_exp_var(char *temp, char **exp_var)
{
	char	*temp2;
	char	*temp3;
	int		i;

	i = -1;
	temp2 = ft_calloc(1, 1);
	*exp_var = NULL;
	while (temp[++i])
	{
		temp2 = ft_charjoin_mod(temp2, temp[i]);
		if (!temp2)
			return (1);
		temp3 = getenv(temp2);
		if (temp3)
			break ;
	}
	free(temp2);
	if (temp3 && !(ft_isalnum(temp[i + 1])) && temp[i + 1] != '_') // more cases? should be related to export?
	{
		*exp_var = ft_strjoin(temp3, &temp[i + 1]);
		if (!(*exp_var))
			return (1);
	}
	return (0);
}

char	*find_exit_code(char *temp, int exit_code)
{
	char	*temp2;
	char	*exp_var;

	temp2 = ft_itoa(exit_code);
	if (!temp2)
		return (NULL);
	if (temp[1])
	{
		exp_var = ft_strjoin(temp2, &temp[1]);
		free(temp2);
	}
	else
		exp_var = temp2;
	return (exp_var);
}

char	*find_pid(int *i)
{
	char	*exp_var;

	(*i)++;
	exp_var = ft_itoa(67672);
	if (!exp_var)
		return (NULL);
	return (exp_var);
}
