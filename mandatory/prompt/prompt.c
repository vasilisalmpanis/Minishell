/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:29:33 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/06 14:29:33 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_git_head(void)
{
	char	buf[100];
	char	*temp;
	int		fd;
	int		i;
	size_t	bytes;

	fd = open(".git/HEAD", O_RDONLY);
	bytes = read(fd, buf, 100);
	i = 0;
	buf[bytes] = 0;
	while (buf[i])
		++i;
	while (buf[i] != '/')
		--i;
	i++;
	temp = ft_substr(buf, i, ft_strlen(buf) - (size_t)i);
	temp[ft_strlen(temp) - 1] = '\0';
	return (temp);
}

void	get_repo(char **input)
{
	char	*temp;
	char	*last_str;

	temp = get_git_head();
	last_str = ft_strjoin(*input, LIGHT_BLUE"git:("RED);
	free(*input);
	*input = ft_strdup(last_str);
	free(last_str);
	last_str = ft_strjoin(*input, temp);
	free(*input);
	free(temp);
	*input = ft_strjoin(last_str, LIGHT_BLUE") "ESCAPE);
	free(last_str);
}