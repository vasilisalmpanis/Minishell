/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:15:37 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/12 17:36:19 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//int	check_quotes(char *input)
//{
//	int		i;
//	int		flag;
//	char	buf;
//
//	i = -1;
//	flag = 0;
//	buf = 1;
//	while (input[++i])
//	{
//		if (input[i] == '"' || input[i] == '\'')
//		{
//			flag = 1;
//			buf = input[i];
//			++i;
//		}
//		while (input[i] != buf && input[i + 1] && buf != 0)
//			++i;
//		if (input[i] == buf)
//		{
//			flag = 0;
//			buf = 0;
//		}
//	}
//	return (flag);
//}

int	check_quotes(char *input, int single, int dbl)
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

t_lex	*lex(char *input)
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
		return (printf("error\n"), NULL);
	token_lst = NULL;
	split = split_args(input);

	if (!split)
		return (NULL);
	while (split[++i])
	{
		new_token = create_token(split[i], &pos);
		if (!(new_token))
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
		if (check_syntax_err(split))
			return ((ft_putstr_fd("Syntax error near '><'", 2)), NULL);
		word = check_expand(split); 
		if (!word)
			return (NULL);
		new_token = ft_new_tk(word, TK_WORD, *pos);
		free(word);
	}
	return (new_token);
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