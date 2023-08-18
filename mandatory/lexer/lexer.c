/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:15:37 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 11:12:28 by mamesser         ###   ########.fr       */
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

	if (!input)
		return (NULL);
	i = -1;
	pos = 0;
	if (check_quotes(input, 0, 0))
		return (printf("Uneven quote number\n"), NULL);
	token_lst = NULL;
	split = split_args(input);
	if (!split)
		return (NULL);
	while (split[++i])
	{
		new_token = create_token(split[i], &pos, exit_code);
		if (!(new_token))
			return (ft_lst_free(&token_lst), NULL); // probably need to free split here
		ft_lstadd_end(&token_lst, new_token);
	}
	ft_free(split);
	return (token_lst);
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
	char	*word;

	if (check_syntax_err(split))
		return ((ft_putstr_fd("Syntax error near '><'\n", 2)), 1);
	word = check_expand(split, -1, exit_code, 1); 
	if (!word)
		return (1);
	*new_token = ft_new_tk(word, TK_WORD, *pos);
	if (!(*new_token))
		return (free(word), 1);
	free(word);
	return (0);
}

int	check_syntax_err(char *word)
{
	int	i;

	i = 0;
	while (word[i + 1])
	{
		if (word[0] != '"' && word[i] == '>' && word[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

// for testing lexer
//  void	ft_show_tab(t_lex *list)
//   {
//   	while (list)
//   	{
//   		ft_putstr_fd(list->value, 1);
//   		write(1, "\n", 1);
//   		printf("token: %c\n", list->token);
//   		// write(1, "\n", 1);
//   		list = list->next;
//   	}
//   }
// function to check for expansion