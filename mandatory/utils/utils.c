/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:52:47 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/11 12:08:38 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	**split_args(char *input)
{
	int		j;
	char	buf;
	char	**split;

	j = -1;
	while (input[++j])
	{
		if (ft_isspace(input[j]))
			input[j] = 26;
		if (input[j] == '"' || input[j] == '\'')
		{
			buf = input[j];
			++j;
			while (input[j] != buf && input[j])
				j++;
		}
	}
	input = handle_redirects(input, 0);
	if (!input)
		return (NULL);
	split = ft_split(input, 26);
	return (split);
}

char	*handle_redirects(char *input, int j)
{
	int		i;
	char	*new_input;
	int		red_no_sp;

	i = -1;
	red_no_sp = calc_redir_wo_space(input);
	new_input = malloc((ft_strlen(input) + red_no_sp + 1) * sizeof(*new_input));
	if (!new_input)
		return (NULL);
	while (input[++i])
	{
		new_input[j++] = input[i];
		if ((input[i] == '<' || input[i] == '>')
			&& (input[i + 1] != '<' && input[i + 1] != '>'
			&& !(ft_isspace(input[i + 1]))))
		{
			new_input[j++] = ' ';
			if (i > 0 && (input[i] == '<' && input[i - 1] == '>')
				|| (input[i] == '>' && input[i - 1] == '<'))
				j--;
		}
	}
	new_input[j] = '\0';
	return (new_input);
}

int	calc_redir_wo_space(char *input)
{
	int	redir_no_sp;
	int	i;

	redir_no_sp = 0;
	i = 0;
	while (input[++i + 1])
	{
		if ((input[i] == '<' || input[i] == '>')
			&& (input[i + 1] != '<' && input[i + 1] != '>'
			&& !(ft_isspace(input[i + 1]))))
		{
			redir_no_sp++;
			if (i > 0 && (input[i] == '<' && input[i - 1] == '>')
				|| (input[i] == '>' && input[i - 1] == '<'))
				redir_no_sp--;
		}
	}
	return (redir_no_sp);
}

char	*ft_charjoin_mod(char *s1, char s2)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + 1;
	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret)
		return (free(s1), NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i++] = s2;
	ret[i] = '\0';
	free(s1);
	return (ret);
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret)
		return (free(s1), NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	free(s1);
	return (ret);
}
