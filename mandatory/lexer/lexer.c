/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:15:37 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/09 15:12:37 by mamesser         ###   ########.fr       */
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
	t_lex	*token_lst;
	t_lex	*new_token;
	int		i;
	int		pos;

	i = -1;
	pos = 0;
	if (check_quotes(input))
		return (NULL);
	split = split_args(input);
	token_lst = NULL;
	if (!split)
		return (NULL);
	while (split[++i])
	{
		new_token = create_token(split[i], &pos);
		if (!(new_token->value))
			return (ft_lst_free(&token_lst), NULL);
		ft_lstadd_end(&token_lst, new_token);
	}
	ft_free(split);
	return (token_lst);
}

t_lex	*create_token(char *split, int *pos)
{
	t_lex	*new_token;
	char	*word;

	(*pos)++;
	if (!(ft_strncmp(split, "|", ft_strlen(split))))
	{
		new_token = ft_new_tk(split, TK_PIPE, 0);
		*pos = 0;
	}
	else if (!(ft_strncmp(split, "<", ft_strlen(split))))
		new_token = ft_new_tk(split, TK_IN_R, *pos);
	else if (!(ft_strncmp(split, ">", ft_strlen(split))))
		new_token = ft_new_tk(split, TK_OUT_R, *pos);
	else if (!(ft_strncmp(split, ">>", ft_strlen(split))))
		new_token = ft_new_tk(split, TK_APP_R, *pos);
	else if ((!ft_strncmp(split, "<<", ft_strlen(split))))
		new_token = ft_new_tk(split, TK_HERE_DOC, *pos);
	else
	{
		word = check_expand(split);
		if (!word)
			return (NULL);
		new_token = ft_new_tk(word, TK_WORD, *pos);
		free(word);
	}
	return (new_token);
}

// for testing lexer
// void	ft_show_tab(t_lex *list)
// {
// 	while (list)
// 	{
// 		ft_putstr_fd(list->value, 1);
// 		write(1, "\n", 1);
// 		printf("token: %c\n", list->token);
// 		// write(1, "\n", 1);
// 		list = list->next;
// 	}
// }
// function to check for expansion