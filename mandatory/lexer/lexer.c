/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:15:37 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/07 12:14:27 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *input)
{
	int		i;
	int		flag;
	char	buf;

	i = -1;
	flag = 0;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			flag = 1;
			buf = input[i];
			i++;
		}
		while (input[i] != buf && input[i] && buf != 0)
			i++;
		if (input[i] == buf)
		{
			flag = 0;
			buf = 0;
		}
	}
	return (flag);
}


t_lex	*lex(char *input)
{
	char	**split;
	t_lex	*tokens;
	t_lex	*new_token;
	int		i;

	i = -1;
	split = split_args(input);
	tokens = NULL;
	if (!split)
		return (NULL);
	while (split[++i])
	{
		if (!(ft_strncmp(split[i], "|", ft_strlen(split[i]))))
			new_token = ft_new_tk(split[i], TK_PIPE);
		else if (!(ft_strncmp(split[i], "<", ft_strlen(split[i]))))
			new_token = ft_new_tk(split[i], TK_IN_R);
		else if (!(ft_strncmp(split[i], ">", ft_strlen(split[i]))))
			new_token = ft_new_tk(split[i], TK_OUT_R);
		else if (!(ft_strncmp(split[i], ">>", ft_strlen(split[i]))))
			new_token = ft_new_tk(split[i], TK_APP_R);
		else if ((!ft_strncmp(split[i], "<<", ft_strlen(split[i]))))
			new_token = ft_new_tk(split[i], TK_HERE_DOC);
		else
			new_token = ft_new_tk(split[i], TK_WORD);
		ft_lstadd_end(&tokens, new_token);
	}
	ft_free(split);
	return (tokens);
}

// for testing lexer
void	ft_show_tab(t_lex *list)
{
	while (list)
	{
		ft_putstr_fd(list->value, 1);
		write(1, "\n", 1);
		printf("token: %c\n", list->token);
		// write(1, "\n", 1);
		list = list->next;
	}
}

// function to check for expansion
