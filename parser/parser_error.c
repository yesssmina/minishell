#include "../minishell.h"

int	error_redir(char *str, int *i, char c)
{
	int	count;

	count = 0;
	while (str[(*i)] == c)
	{
		count++;
		(*i)++;
	}
	if ((c == '>' && count > 2) || (c == '<' && count > 2))
		return (1);
	while (str[(*i)] == ' ')
		(*i)++;
	if (!str[(*i)])
		return (1);
	return (0);
}

void	skip_quotes(char *str, int *i)
{
	char	quote;

	quote = str[(*i)++];
	while (str[(*i)] != quote)
	{
		if (str[(*i)] == '\\' && quote == '"')
			(*i) += 2;
		else
			(*i)++;
	}
}

int	parser_error(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		if (str[i] == '"' || str[i] == '\'')
			skip_quotes(str, &i);
		if (str[i] == '>' || str[i] == '<')
		{
			if (error_redir(str, &i, str[i]))
			{
				data->status = 1;
				ft_putstr_fd("Error: wrong or unsupported redirection\n", 2);
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}
