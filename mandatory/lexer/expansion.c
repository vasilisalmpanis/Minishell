/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:43:19 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/16 16:39:12 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_expand(char *word, int i, int exit_code, int trim_flag)
{
	char	*exp_word;

	exp_word = ft_calloc(1, 1);
	if (!exp_word)
		return (NULL);
	while (word[++i])
	{
		if (word[0] != '\'' && word[i] == '$')
		{
			if (word[i + 1] != '\0' && !ft_isspace(word[i + 1]) // what else needs to be added? e.g. '+'
				&& word[i + 1] != '"' && word[i + 1] != '\'' 
				&& word[i + 1] != '}' && word[i + 1] != ')')
			{
				i++;
				if (expand(word, &i, &exp_word, exit_code) == 2)
					return (NULL);
				i--;
			}
			else 
			{
				exp_word = ft_charjoin_mod(exp_word, word[i]);
				if (!exp_word)
					return (NULL);
			}
		}
		else
		{
			exp_word = ft_charjoin_mod(exp_word, word[i]);
			if (!exp_word)
				return (NULL);
		}
		if (!word[i])
			break ;
	}
	if (trim_flag)
		exp_word = trim_word(exp_word);
	return (exp_word);
}


char	*trim_word(char *word)
{
	char	*trimmed_word;

	if (word[0] == '"')
		trimmed_word = ft_strtrim(word, "\"");
	else if (word[0] == '\'')
		trimmed_word = ft_strtrim(word, "'");
	else
		return (word);
	if (!trimmed_word)
		return (free(word), NULL);
	free(word);
	return (trimmed_word);
}

int	expand(char *word, int *i, char **exp_word, int exit_code)
{
	char	*temp;
	char	*exp_var;
	int		offset;
	int		start;

	start = *i;
	temp = NULL;
	if (word[*i] && word[*i] == '$')
		exp_var = find_pid(i);
	else
	{
		while (word[*i] && word[*i] != '"' && word[*i] != '\''
			&& word[*i] != '}' && word[*i] != ')' && word[*i] != '$'
			&& !ft_isspace(word[*i]))
			(*i)++;
		offset = calc_offset(word, start, i);
		if (offset == -1)
			return (free(*exp_word), 2);
		temp = ft_substr(word, start + offset, *i - start - (2 * offset));
		if (!temp)
			return (free(*exp_word), 1);
		exp_var = determine_exp_var(temp, exit_code);
	}
	if (exp_var)
	{
		*exp_word = ft_strjoin_mod(*exp_word, exp_var);
		if (!(*exp_word))
			return (free(temp), 1);
	}
	free(exp_var);
	free(temp);
	return (0);
}

int	calc_offset(char *word, int start, int *i)
{
	int	offset;

	offset = 0;
	if ((word[start] == '{' && word[*i] == '}')
		|| (word[start] == '(' && word[*i] == ')'))
	{
		offset++;
		(*i)++;
	}
	if (word[start + 1] == '{')
	{
		offset = -1;
		ft_putstr_fd("Error: Bad syntax near '{'\n", 2);
	}
	return (offset);
}

char	*determine_exp_var(char *temp, int exit_code)
{
	char	*exp_var;
	int		len;

	len = ft_strlen(temp);
	if (temp[0] == '(' && temp[1] == '('
		&& temp[len - 1] == ')' && temp[len - 2] == ')') // --> not completely working because word/temp stopped at space
	{
		exp_var = ft_strdup("You can calculate in your head"); // may implement do_op
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
	// char	*temp2;
	char	*exp_var;
	
	(*i)++;
	exp_var = ft_itoa(67672);
	if (!exp_var)
		return (NULL);
	return (exp_var);
}



// char	*find_pid(char *temp)
// {
// 	char	*temp2;
// 	char	*exp_var;
	
// 	temp2 = ft_itoa(67672);
// 	if (!temp2)
// 		return (NULL);
// 	if (temp[1])
// 	{
// 		exp_var = ft_strjoin(temp2, &temp[1]);
// 		free(temp2);
// 	}
// 	else
// 		exp_var = temp2;
// 	return (exp_var);
// }


///// TESTING /////

// int main(void)
// {
// 	char *ret;
	
// 	ret = check_expand("\"Hello ${USER}T\"");
	
// //	temp = "Hello $SHLVL $XPC_FLAGS $TERMINAL_EMULATOR";
// 	printf("%s\n", ret);
// 	free(ret);
// }