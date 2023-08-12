/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:11:39 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/12 18:05:26 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_redirects(char *input, int j)
{
	char	*new_input;
	char	*temp;

	temp = add_space_pre_redir(input, 0);
	new_input = add_space_post_redir(temp, 0);
	free(temp);
	return (new_input);
}

char	*add_space_pre_redir(char *input, int j)
{
	int		i;
	char	*new_input;
	int		red_no_sp;

	i = -1;
	red_no_sp = calc_redir_wo_space2(input);
	new_input = ft_calloc((ft_strlen(input) + red_no_sp + 1), sizeof(*new_input));
	if (!new_input)
		return (NULL);
	while (input[++i])
	{
		if (i > 0 && (input[i] == '<' || input[i] == '>')
			&& !(input[i - 1] == 26))
		{
			new_input[j++] = 26;
			if ((input[i] == '<' && input[i + 1] == '>')
				|| (input[i] == '>' && input[i + 1] == '<')
				|| (input[i - 1] == '<' || input[i - 1] == '>'))
				j--;
		}
		new_input[j++] = input[i];
	}
	// free(input);
	return (new_input);
}

char	*add_space_post_redir(char *input, int j)
{
	int		i;
	char	*new_input;
	int		red_no_sp;

	i = -1;
	red_no_sp = calc_redir_wo_space(input);
	new_input = ft_calloc((ft_strlen(input) + red_no_sp + 1), sizeof(*new_input));
	if (!new_input)
		return (NULL);
	while (input[++i])
	{
		new_input[j++] = input[i];
		if ((input[i] == '<' || input[i] == '>')
			&& (input[i + 1] != '<' && input[i + 1] != '>'
				&& !(input[i + 1] == 26) && input[i + 1]))
		{
			new_input[j++] = 26;
			if (i > 0 && (input[i] == '<' && input[i - 1] == '>')
				|| (input[i] == '>' && input[i - 1] == '<'))
				j--;
		}
	}
	return (new_input);
}

int	calc_redir_wo_space2(char *input)
{
	int	redir_no_sp;
	int	i;

	redir_no_sp = 0;
	i = -1;
	while (input[++i + 1])
	{
		if (i > 0 && (input[i] == '<' || input[i] == '>')
			&& !(input[i - 1] == 26))
		{
			redir_no_sp++;
			if ((input[i] == '<' && input[i + 1] == '>')
				|| (input[i] == '>' && input[i + 1] == '<')
				|| (input[i - 1] == '<' || input[i - 1] == '>'))
				redir_no_sp--;
		}
	}
	return (redir_no_sp);
}

int	calc_redir_wo_space(char *input)
{
	int	redir_no_sp;
	int	i;

	redir_no_sp = 0;
	i = -1;
	while (input[++i + 1])
	{
		if ((input[i] == '<' || input[i] == '>')
			&& (input[i + 1] != '<' && input[i + 1] != '>'
				&& !(input[i + 1] == 26) && input[i + 1]))
		{
			redir_no_sp++;
			if (i > 0 && (input[i] == '<' && input[i - 1] == '>')
				|| (input[i] == '>' && input[i - 1] == '<'))
				redir_no_sp--;
		}
	}
	return (redir_no_sp);
}
