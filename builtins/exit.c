#include "../minishell.h"

void	error_sentence(char *str, int status, t_data *data)
{
	data->status = status;
	ft_putstr_fd(str, 2);
}

void	error_sentence_exec(char *input, int status, t_data *data)
{
	int	i;

	i = 0;
	if (var_index("PATH=", data) < 0 || (input[i] == '.'
			&& input[i + 1] == '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		data->status = status;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

int	is_number(char *str)
{
	int	i;
	int	digit_count;

	i = 0;
	digit_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
		digit_count++;
	}
	return (digit_count > 0);
}

void	handle_exit(char **inputs, t_data *data)
{
	data->status = 0;
	ft_putstr_fd("exit\n", 1);
	if (inputs[1])
	{
		if (is_number(inputs[1]) && !is_number_too_large(inputs[1]))
		{
			data->status = ft_atoi(inputs[1]);
			data->status = data->status % 256;
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(inputs[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(inputs[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			data->status = 2;
		}
	}
	free_env(inputs);
	free(data->pwd);
	free_env(data->env);
	exit(data->status);
}
