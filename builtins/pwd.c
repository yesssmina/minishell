#include "../minishell.h"

void	handle_pwd(t_data *data)
{
	ft_putstr_fd(data->pwd, 1);
	ft_putstr_fd("\n", 1);
	data->status = 0;
}
