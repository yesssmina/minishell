#include "../minishell.h"

void	relir_delim_error2(t_data *data, int i)
{
	while (data->str[i])
	{
		data->arg_error = NULL;
		data->j = 0;
		while (data->str[i] == ' ')
			i++;
		data->k = i;
		while (data->str[data->k] != ' ' && data->str[data->k] != '\0')
			data->k++;
		data->arg_error = malloc(sizeof(char) * (data->k + 1));
		while (data->str[i] != ' ' && data->str[i] != '\0')
			data->arg_error[data->j++] = data->str[i++];
		data->arg_error[data->j] = '\0';
		printf("cat: %s: No such file or directory\n", data->arg_error);
		free(data->arg_error);
	}
}

void	relir_delim_error(t_data *data)
{
	int	i;

	i = 0;
	while (data->str[i] != '<')
		i++;
	i = i + 2;
	while (data->str[i] == ' ')
		i++;
	while (data->str[i] != ' ' && data->str[i] != '\0')
		i++;
	//if (data->str[i] != '\0')
	//{
	//	i++;
	//	while (data->str[i] != ' ' && data->str[i] != '\0')
	//		i++;
	//}
	relir_delim_error2(data, i);
}

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
			break ;
	}
	data->delimiter[data->j] = '\0';
	close(data->fd);
}

void	redir_delimiter(char **input, int i, t_data *data)
{
	init_redir_data(data, input, i);
	redir_delimiter2(data);
	write(1, data->file_contents, data->file_contents_length);
	relir_delim_error(data);
	free(data->file_contents);
	free(data->delimiter);
	if (unlink(data->temp_file) != 0)
	{
		perror("Error\ndeleting here doc");
		exit(EXIT_FAILURE);
	}
}
