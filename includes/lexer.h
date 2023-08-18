/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:31:53 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 12:35:50 by mamesser         ###   ########.fr       */
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

int		check_quotes(const char *input, int single, int dbl);
t_lex	*lex(char *input, int exit_code);
t_lex	*create_token(char *split, int *pos, int exit_code);
int		create_word_token(char *split, int *pos, t_lex **new_token, int exit_code);
int		check_syntax_err(char *word);

char	*check_expand(char *word, int i, int exit_code, int trim_flag);
int		check_expand_helper(char *word, int *i, char **exp_word, int exit_code);
int		expand(char *word, int *i, char **exp_word, int exit_code);

char	*trim_word(char *word);
int		calc_offset(char *word, int start, int *i);

char	*create_exp_var(char *word, int *i, char **exp_word, int exit_code);
char	*determine_exp_var(char *temp, int exit_code);
char	*find_exp_var(char *temp);
char	*find_exit_code(char *temp, int exit_code);
char	*find_pid(int *i);

#endif
