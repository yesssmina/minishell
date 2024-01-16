#include "../minishell.h"

int	redir_error_space(char *str, int i)
{
	if (str[i + 1] != '\0' && (str[i + 1] == '<' || str[i + 1] == '>'))
		return (1);
	while (str[i + 1] && str[i + 1] == ' ')
		i++;
	if (str[i + 1] && str[i + 1] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `>'", 2);
		return (0);
	}
	else if (str[i + 1] && str[i + 1] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
		return (0);
	}
	else if (str[i + 1] && str[i + 1] == ';')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
		return (0);
	}
	else if (str[i + 1] && str[i + 1] == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (0);
	}
	return (1);
}
