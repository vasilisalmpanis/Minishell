#include "../includes/minishell.h"

int	main(int argc, char **argv, char **en)
{
	char				*input;
	char				*temp;
	t_env 				*lst;
	t_cmd				cmd;

	lst = create_env(en);
	while (1)
	{
		temp = prompt();
		input = readline(temp);
		if (ft_strncmp(input, "export", ft_strlen(input)) == 0)
		{
			cmd.args = NULL;
		}
		else if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			free(temp);
			free(input);
			ft_env_free(&lst);
			exit(1);
		}
		else
			cmd.args = split_args(input);
		export(&lst, &cmd);
		if (cmd.args)
			ft_free(cmd.args);
		free(temp);
		free(input);
	}
}