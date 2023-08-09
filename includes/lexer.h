/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:31:53 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/09 14:58:01 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token
{
	TK_WORD = 'w',
	TK_PIPE = '|',
	TK_IN_R = '<',
	TK_OUT_R = '>',
	TK_APP_R = 'A',
	TK_HERE_DOC = 'H',
}			t_token;

typedef struct s_lex
{
	t_token			token;
	char			*value;
	int				pos;
	struct s_lex	*next;
}				t_lex;

int		check_quotes(char *input);
t_lex	*lex(char *input);
t_lex	*create_token(char *split, int *pos);
void	expand(char *word, int *i, int start, char **exp_word);
void	ft_show_tab(t_lex *list);
char	*check_expand(char *word);
char	*trim_word(char *word);

#endif
