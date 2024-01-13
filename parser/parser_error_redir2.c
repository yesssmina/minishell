#include "../minishell.h"

int	redir_error5(char *str, int i)
{
	if (str[i + 1] == '<' && str[i + 2] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `<<'", 2);
		return(0);
	}
	else if (str[i + 1] == '<' && str[i + 2] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `<>'", 2);
		return(0);
	}
	else if (str[i + 1] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
		return(0);
	}
	return (1);
}

int	redir_error_pipe(char *str, int i)
{
	//printf("*%s\ni:%d\n", str, i);
	if (str[i + 1] == '|' && str[i - 1] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `||'", 2);
		return(0);
	}
	else if (str[i + 1] == '|' && str[i - 1] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `||'", 2);
		return(0);
	}
	else if (str[i - 1] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return(0);
	}
	else if (str[i - 1] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return(0);
	}
	return (1);
}

int	redir_error_pipe1(char *str, int i)
{
	if (!redir_error(str, i - 2))
		return (0);
	if (str[i + 1] && str[i - 1] && str[i + 1] == ';' && str[i - 1] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|;'", 2);
		return(0);
	}
	else if (str[i + 1] && str[i - 1] && str[i + 1] == ';' && str[i - 1] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|;'", 2);
		return(0);
	}
	return (1);
}

int	redir_error_semi(char *str, int i)
{
	//printf("*%s\ni:%d\n", str, i);
	if (str[i + 1] == ';' && str[i - 1] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;;'", 2);
		return(0);
	}
	else if (str[i + 1] == ';' && str[i - 1] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;;'", 2);
		return(0);
	}
	else if (str[i - 1] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
		return(0);
	}
	else if (str[i - 1] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
		return(0);
	}
	return (1);
}

int	redir_error_semi1(char *str, int i)
{
	//printf("*%s\ni:%d\n", str, i);
	if (!redir_error(str, i - 2))
		return (0);
	if (str[i + 1] == '|' && str[i - 1] == '<')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;|'", 2);
		return(0);
	}
	else if (str[i + 1] == '|' && str[i - 1] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;|'", 2);
		return(0);
	}
	return (1);
}