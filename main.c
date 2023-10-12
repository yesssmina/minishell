#include "minishell.h"
#include "libft/libft.h"

char *g_user_input;
int g_status;
int g_quit;

void	end_of_file(t_data *data, char *user_input)
{
	free_env(data->env);
	free(user_input);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

void	data_init(t_data *data, char **env)
{
	data->env = dup_env(env);
	data->pwd = getcwd(NULL, 0);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
}

int		main(int ac, char **av, char **env)
{
	t_data	data;
    int		gnl;

	(void)ac;
	(void)av;
	data_init(&data, env);
	g_status = 0;
	g_user_input = NULL;
	if (!data.env)
		exit(EXIT_FAILURE);
	while (1)
	{
		g_quit = 0;
		free(g_user_input);
		sig_init();
		ft_putstr_fd("minishell> ", 2);
		gnl = get_next_line(0, &g_user_input);
		if (!gnl)
			end_of_file(&data, g_user_input);
		else
			parser_start(g_user_input, &data);
	}
	return (0);
}
