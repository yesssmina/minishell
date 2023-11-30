#include "../minishell.h"

void	choose_action(char **inputs, t_data *data)
{
	if (!data->redir)
	{
		data->redir = 1;
		return ;
	}
	if (!ft_strncmp(inputs[0], "echo", ft_strlen("echo")))
		handle_echo(inputs);
	else if (!ft_strncmp(inputs[0], "pwd", ft_strlen("pwd")))
		handle_pwd(data);
	else if (!ft_strncmp(inputs[0], "cd", ft_strlen("cd")))
		handle_cd(inputs, data);
	else if (!ft_strncmp(inputs[0], "env", ft_strlen("env")))
		handle_env(data->env);
	else if (!ft_strncmp(inputs[0], "exit", ft_strlen("exit")))
		handle_exit(inputs, data);
	else if (!ft_strncmp(inputs[0], "export", ft_strlen("export")))
		handle_export(inputs, data);
	else if (!ft_strncmp(inputs[0], "unset", ft_strlen("unset")))
		handle_unset(inputs, data);
	else
		handle_exec(inputs, data);
}

void	free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		i++;
	}
	free(inputs);
}

void	close_fds(t_data *data)
{
	if (data->fd_in != 0)
	{
		close(data->fd_in);
		data->fd_in = 0;
	}
	if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 1;
	}
}

void	exit_pipe(t_data *data)
{
	free_inputs(data->env);
	free(data->pwd);
	exit(EXIT_SUCCESS);
}

int	handle_basic(char *clean_input, t_data *data, int piped)
{
	char	**inputs;
	int		oldfd[2];

	if (parser_error(clean_input))
	{
		free(clean_input);
		return (0);
	}
	oldfd[0] = dup(1);
	oldfd[1] = dup(0);
	clean_input = input_cleaner(clean_input);
	parser_redir(&clean_input, data);
	clean_input = input_cleaner(clean_input);
	inputs = input_split(clean_input);
	free(clean_input);
	choose_action(inputs, data);
	free_inputs(inputs);
	dup2(oldfd[0], 1);
	dup2(oldfd[1], 0);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	if (piped)
		exit_pipe(data);
	return (0);
}
