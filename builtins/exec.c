#include "../minishell.h"

int	execute_2(char **inputs, t_data *data)
{
	int			i;
	char		**paths;
	int			index;
	struct stat	statounet;

	i = 0;
	statounet.st_mode = 0;
	index = var_index("PATH=", data);
	paths = gen_paths(index, data, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &statounet);
		if ((statounet.st_mode & S_IXUSR)
			&& (execve(paths[i], inputs, data->env) != -1))
			return (0);
		i++;
	}
	free_env(paths);
	return (1);
}

int	execute(char **inputs, t_data *data)
{
	int			index;
	struct stat	statounet;

	statounet.st_mode = 0;
	index = var_index("PATH=", data);
	stat(inputs[0], &statounet);
	if (ft_strchr(inputs[0], '/') && (statounet.st_mode & S_IXUSR)
		&& (execve(inputs[0], &inputs[0], data->env) != -1))
		return (0);
	else if (index >= 0)
	{
		if (!execute_2(inputs, data))
			return (0);
	}
	error_sentence_exec(inputs[0], 127);
	return (127);
}

void	handle_exec(char **inputs, t_data *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (pid == 0)
			exit(execute(inputs, data));
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		sig_exec_init();
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			g_status = WTERMSIG(status) + 128;
		else
			g_status = WEXITSTATUS(status);
	}
}
