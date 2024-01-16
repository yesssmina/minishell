#include "../minishell.h"

void	copy_inside_quotes(char **src, char **dst, char quote)
{
	int	slash_count;

	while (**src != quote)
	{
		slash_count = 0;
		while (**src == '\\' && quote == '"')
		{
			*((*dst)++) = *((*src)++);
			slash_count++;
		}
		if (slash_count && !(slash_count % 2))
			*((*dst)--) = *((*src)--);
		*((*dst)++) = *((*src)++);
	}
}

void	input_copy(char *dst, char *src)
{
	char	quote;

	while (*src)
	{
		if (*src == ' ' && (*(src + 1) == ' ' || *(src + 1) == '\0'))
			src++;
		else if (*src == '"' || *src == '\'')
		{
			*(dst++) = *src;
			quote = *(src++);
			copy_inside_quotes(&src, &dst, quote);
			*(dst++) = *(src++);
		}
		else if (*src == '\\' && *(src + 1))
			escape_char(&dst, &src);
		else
			*(dst++) = *(src++);
	}
	*dst = '\0';
}

static int	input_len(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (*str)
	{
		if (*str == ' ' && (*(str + 1) == ' ' || *(str + 1) == '\0'))
			str++;
		else if (*str == '\\' && (str += 2))
			i += 4;
		else if (*str == '"' || *str == '\'')
		{
			quote = *(str++);
			quote_len(&str, &i, quote);
			if (!*str)
				return (-1);
			str++;
			i = i + 2;
		}
		else if (str++)
			i++;
	}
	return (i);
}

char	*input_cleaner(char *str)
{
	int		len;
	char	*clean_input;
	char	*str_start;

	str_start = str;
	while (*str == ' ' && *str)
		str++;
	len = input_len(str);
	if (len == -1)
		return (0);
	clean_input = (char *)malloc((len + 1) * sizeof(char));
	if (!clean_input)
		exit(EXIT_FAILURE);
	input_copy(clean_input, str);
	free(str_start);
	return (clean_input);
}

int	parser_start(char *input, t_data *data)
{
	char	*clean_input;

	if (!ft_strncmp(input, "echo\\", 5))
	{
		input = input_cleaner(input);
		error_sentence_exec(input, 127, data);
		free(input);
		return (0);
	}
	clean_input = input_cleaner(input);
	if (clean_input == 0)
	{
		free(clean_input);
		ft_putstr_fd("This minishell does not support multiline\n", 2);
		return (0);
	}
	if (!*clean_input)
	{
		free(clean_input);
		return (0);
	}
	return (parser_delegator(clean_input, data, 0));
}
