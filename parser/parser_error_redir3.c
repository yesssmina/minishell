#include "../minishell.h"

int	redir_error_space(char *str, int i)
{
	if (str[i + 1] == '<' || str[i + 1] == '>')
		return (1);
	while (str[i + 1] == ' ')
		i++;
	if (str[i + 1] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `>'", 2);
		return(0);
	}
	else if (str[i + 1] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
		return(0);
	}
	else if (str[i + 1] == ';')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
		return(0);
	}
	else if (str[i + 1] == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return(0);
	}
	return (1);
}

int	ambigus_redir(char *str, int i, t_data *data)
{
	while (str[i - 1] == ' ')
		i--;
	if (str[i - 1] == '<' || str[i - 1] == '>')
	{
		data->status = 1;
		ft_putendl_fd("minishell: ambiguous redirection", 2);
		return(0);
	}
	else if (i == 0)
	{
		data->status = 0;
		return (0);
	}
	return (1);
}