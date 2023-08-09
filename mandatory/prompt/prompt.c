/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:43:49 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/09 12:47:27 by valmpani         ###   ########.fr       */
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

void	get_repo(char **input, char *head)
{
	char	*temp;
	char	*last_str;

	if (!head)
		temp = get_git_head();
	else
		temp = ft_strdup(head);
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

char	*current_dir(void)
{
	char	**temp;
	char	*buf;
	char	*string;
	int		i;

	i = 0;
	buf = getcwd(NULL, 0);
	if (!buf)
		return (ft_strdup("  minishell "));
	if (ft_strncmp(buf, "/", ft_strlen(buf)) == 0)
	{
		free(buf);
		return (ft_strdup("/"));
	}
	temp = ft_split(buf, '/');
	if (!temp)
	{
		string = ft_strdup("  minishell ");
		return (free (buf), string);
	}
	while (temp[i])
		i++;
	free(buf);
	string = ft_strdup(temp[i - 1]);
	return (ft_free(temp), string);
}

char	*prompt(char **cur_dir)
{
	char	*temp;
	char	*last_str;
	char	*gcwd;

	temp = current_dir();
	gcwd = getcwd(NULL, 0);
	if (temp == NULL || (ft_strncmp(gcwd, "/", ft_strlen(gcwd)) == 0))
	{
		free(gcwd);
		free(temp);
		return (ft_strdup(GREEN"→" BLUE"  / "ESCAPE));
	}
	last_str = ft_strjoin(GREEN"→" BLUE"  ", temp);
	if (!last_str)
		return (ft_strdup(GREEN"→" BLUE"  minishell "ESCAPE));
	free(temp);
	temp = ft_strjoin(last_str, " "ESCAPE);
	if (temp == NULL)
		return (ft_strdup(GREEN"→" BLUE"  minishell "ESCAPE));
	free(last_str);
	if (access(".git/HEAD", O_RDONLY) == 0)
		get_repo(&temp, NULL);
	else if (strstr(gcwd, cur_dir[0]))
		get_repo(&temp, cur_dir[1]);
	return (free(gcwd), temp);
}
