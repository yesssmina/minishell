#include "../minishell.h"

int	is_n_flag(char *arg)
{
	int	i;

	i = 2;
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	handle_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	g_status = 0;
	while (args[i] && is_n_flag(args[i]) && i++)
		n_flag = 1;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
}
