/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:15:37 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/21 17:08:02 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(const char *input, int single, int dbl)
{
	int		i;
	char	buf;

	i = -1;
	buf = '\0';
	while (input[++i])
	{
		if (input[i] == '\"' && (buf == '\"' || buf == '\0'))
		{
			dbl = 1 - dbl;
			if (buf == '\"')
				buf = '\0';
			else
				buf = '\"';
		}
		if (input[i] == '\'' && (buf == '\'' || buf == '\0'))
		{
			dbl = 1 - dbl;
			if (buf == '\'')
				buf = '\0';
			else
				buf = '\'';
		}
	}
	return (single + dbl);
}

t_lex	*lex(char *input, int exit_code)
{
	char	**split;
	t_lex	*token_lst;
	t_lex	*new_token;
	int		i;
	int		pos;

	i = -1;
	pos = 0;
	token_lst = NULL;
	if (check_quotes(input, 0, 0))
		return (printf("Uneven quote number\n"), NULL);
	split = split_args(input);
	if (!split)
		return (NULL);
	while (split[++i])
	{
		new_token = create_token(split[i], &pos, exit_code);
		if (!(new_token))
		{
			ft_free(split);
			return (ft_lst_free(&token_lst), NULL);
		}
		ft_lstadd_end(&token_lst, new_token);
	}
	return (ft_free(split), token_lst);
}

t_lex	*create_token(char *split, int *pos, int exit_code)
{
	t_lex	*new_token;

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
		if (create_word_token(split, pos, &new_token, exit_code))
			return (NULL);
	}
	return (new_token);
}

int	create_word_token(char *split, int *pos, t_lex **new_token, int exit_code)
{
	char	*word1;
	char	*word2;

	if (check_syntax_err(split))
		return ((ft_putstr_fd("Syntax error near '><'\n", 2)), 1);
	word1 = check_expand(split, -1, exit_code, 1);
	if (!word1)
		return (1);
	word2 = remove_quotes(word1, 0, 0);
	if (!word2)
		return (free(word1), 1);
	free(word1);
	*new_token = ft_new_tk(word2, TK_WORD, *pos);
	if (!(*new_token))
		return (free(word2), 1);
	free(word2);
	return (0);
}

int	check_syntax_err(char *split)
{
	int	i;

	i = 0;
	while (split[i + 1])
	{
		if (split[0] != '"' && split[i] == '>' && split[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}
