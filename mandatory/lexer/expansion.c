/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:43:19 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/07 12:48:52 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_expand(char *word)
{
	int	i;
	int	start;
	char *temp;
	char *ret;

	i = -1;
	ret = "";
	while (word[++i])
	{
		start = i;
		if (word[i] == '$')
		{
			while (word[i] && !ft_isspace(word[i]))
				i++;
			temp = ft_substr(word, start + 1, i - start - 1);
			ret = ft_strjoin(ret, getenv(temp));
			free(temp);
		}
		else
			ret = ft_charjoin(ret, word[i]);
	}
	printf("%s\n", ret);
}

int main(void)
{
	char temp[] = "Hello $SHLVL $XPC_FLAGS $TERMINAL_EMULATOR ";

//	temp = "Hello $SHLVL $XPC_FLAGS $TERMINAL_EMULATOR";
	check_expand(temp);
}
