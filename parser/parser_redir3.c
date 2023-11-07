#include "../minishell.h"

void		should_escape(int *i, char *str)
{
	if (str[(*i)] == '\\')
		(*i)++;
}

void redir_delimiter(char **input, int i, t_data *data)
{
	char	file_contents[4096];

	data->str = ft_strdup(*input);
    data->temp_file = "temp_here_document.txt";
    data->fd = open(data->temp_file, O_RDONLY);
    data->j = 0;
    i += 2;
    data->k = 0;
    data->file_contents_length = 0;
    data->delimiter = malloc(sizeof(char) * (ft_strlen(*input) + 1));
    data->input_line = NULL;
	while (data->str[i])
	{
		while (data->str[i] == ' ')
			i++;
		data->delimiter[data->j++] = data->str[i++];
		if (data->str[i] == ' ')
			break;

	}
	data->delimiter[data->j] = '\0';
	dup2(data->fd, 0);
	close(data->fd);

	while (1)
	{
		data->input_line = readline(">");
		if (data->input_line == NULL)
			break;
		if (ft_strncmp(data->input_line, data->delimiter, ft_strlen(data->input_line)) == 0
		&& ft_strlen(data->input_line) == ft_strlen(data->delimiter))
		{
			free(data->input_line);
			break;
		}
		if (data->file_contents_length + ft_strlen(data->input_line) < sizeof(file_contents))
		{
			ft_strlcpy(file_contents + data->file_contents_length, data->input_line, ft_strlen(file_contents) - data->file_contents_length);
			data->file_contents_length += ft_strlen(data->input_line);
			file_contents[data->file_contents_length++] = '\n';
		}
		free(data->input_line);
	}

	write(1, file_contents, data->file_contents_length);
	i = 0;
	while (data->str[i] != '<')
		i++;
	i = i + 2;
	while (data->str[i] == ' ')
		i++;
	while (data->str[i] != ' ' && data->str[i] != '\0')
		i++;
	while (data->str[i])
	{
		data->arg_error = NULL;
		data->j = 0;
		while (data->str[i] == ' ')
			i++;
		data->k = i;
		while (data->str[data->k] != ' ')
			data->k++;
		data->arg_error = malloc(sizeof(char) * (data->k + 1));
		while (data->str[i] != ' ' && data->str[i] != '\0')
			data->arg_error[data->j++] = data->str[i++];
		data->arg_error[data->j] = '\0';
		printf("cat: %s: No such file or directory\n", data->arg_error);
	}

	free(data->delimiter);
}

//gerer erreur fd
//gerer free
//gerer historique