#include "../minishell.h"

void	redir_delimiter2(t_data *data)
{
	while (1)
	{
		data->input_line = readline(">");
		if (data->input_line == NULL)
			break ;
		if (ft_strncmp(data->input_line, data->delimiter,
				ft_strlen(data->input_line))
			== 0 && ft_strlen(data->input_line) == ft_strlen(data->delimiter))
		{
			free(data->input_line);
			break ;
		}
		data->temp = malloc(data->file_contents_length
				+ ft_strlen(data->input_line) + 2);
		if (data->temp != NULL)
		{
			ft_memcpy(data->temp, data->file_contents,
				data->file_contents_length);
			free(data->file_contents);
			data->file_contents = data->temp;
			ft_strlcpy(data->file_contents + data->file_contents_length,
				data->input_line, ft_strlen(data->input_line) + 1);
			data->file_contents_length += ft_strlen(data->input_line);
			data->file_contents[data->file_contents_length++] = '\n';
		}
		free(data->input_line);
	}
}

void	init_redir_data(t_data *data, char **input, int i)
{
	data->str = ft_strdup(*input);
	data->temp_file = "./temp_here_document.txt";
	data->fd = open(data->temp_file, O_CREAT | O_RDONLY, 0644);
	data->j = 0;
	i += 2;
	data->k = 0;
	data->file_contents_length = 0;
	data->delimiter = malloc(sizeof(char) * (ft_strlen(*input) + 1));
	data->input_line = NULL;
	data->temp = NULL;
	data->file_contents = NULL;
	while (data->str[i] == ' ')
		i++;
	while (data->str[i])
	{
		data->delimiter[data->j++] = data->str[i++];
		if (data->str[i] == ' ')
			return ;
	}
	data->delimiter[data->j] = '\0';
	close(data->fd);
}

void	redir_delimiter(char *str, char **input, int i, t_data *data)
{
	int		j;

	init_redir_data(data, input, i);
	j = i + 2;
	while (str[j] == ' ')
		j++;
	while (str[j] != ' ' && str[j] != '\0')
		j++;
	remove_redir_input(input, i, j);
	redir_delimiter2(data);
	write(1, data->file_contents, data->file_contents_length);
	free(data->file_contents);
	free(data->delimiter);
	if (unlink(data->temp_file) != 0)
	{
		perror("Error\ndeleting here doc");
		exit(EXIT_FAILURE);
	}
	parser_redir(input, data);
}
