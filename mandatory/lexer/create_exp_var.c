/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exp_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:32:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 12:33:53 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_exp_var(char *word, int *i, char **exp_word, int exit_code)
{
	int		offset;
	int		start;
	char	*temp;
	char	*exp_var;

	start = *i;
	offset = 0;
	temp = NULL;
	exp_var = NULL;
	while (word[*i] && word[*i] != '"' && word[*i] != '\''
		&& word[*i] != '}' && word[*i] != ')' && word[*i] != '$'
		&& !ft_isspace(word[*i]))
		(*i)++;
	offset = calc_offset(word, start, i);
	if (offset == -1)
		return (free(*exp_word), NULL);
	temp = ft_substr(word, start + offset, *i - start - (2 * offset));
	if (!temp)
		return (free(*exp_word), NULL);
	exp_var = determine_exp_var(temp, exit_code);
	free(temp);
	return (exp_var);
}

char	*determine_exp_var(char *temp, int exit_code)
{
	char	*exp_var;
	int		len;

	len = ft_strlen(temp);
	if (temp[0] == '(' && temp[1] == '('
		&& temp[len - 1] == ')' && temp[len - 2] == ')') // --> not completely working because word/temp stopped at space
	{
		exp_var = ft_strdup("You can calculate in your head");
	}
	else if (ft_isdigit(temp[0]))
		exp_var = ft_strdup(temp + 1);
	else if (temp[0] == '?')
		exp_var = find_exit_code(temp, exit_code);
	else
		exp_var = find_exp_var(temp);
	return (exp_var);
}

char	*find_exp_var(char *temp)
{
	char	*temp2;
	char	*temp3;
	char	*exp_var;
	int		i;

	i = -1;
	temp2 = ft_calloc(1, 1);
	exp_var = NULL;
	while (temp[++i])
	{
		temp2 = ft_charjoin_mod(temp2, temp[i]);
		temp3 = getenv(temp2);
		if (temp3)
			break ;
	}
	free(temp2);
	if (temp3 && !(ft_isalnum(temp[i + 1])) && temp[i + 1] != '_') // more cases? should be related to export?
		exp_var = ft_strjoin(temp3, &temp[i + 1]);
	return (exp_var);
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
