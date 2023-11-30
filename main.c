#include "minishell.h"

int	g_status;

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

void	sig_init_main(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sig;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*user_input;

	(void)ac;
	(void)av;
	data_init(&data, env);
	g_status = 0;
	if (!data.env)
		exit(EXIT_FAILURE);
	sig_init_main();
	while (1)
	{
		sig_init_main();
		user_input = readline("minishell> ");
		if (!user_input)
			break ;
		if (*user_input)
		{
			add_history(user_input);
			parser_start(user_input, &data);
		}
	}
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
