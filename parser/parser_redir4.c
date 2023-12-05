#include "../minishell.h"

void	start_end_heredoc(int heredoc_pos, char *temp_filename, t_data *data)
{
	data->heredoc_i = 0;
	data->length = 0;
	while (data->old_command[heredoc_pos]
		&& data->old_command[heredoc_pos] != '<')
		heredoc_pos++;
	heredoc_pos += 2;
	while (data->old_command[heredoc_pos]
		&& data->old_command[heredoc_pos] == ' ')
		heredoc_pos++;
	data->delimiter_start = &data->old_command[heredoc_pos];
	while (*data->delimiter_start == ' ')
		data->delimiter_start++;
	data->delimiter_end = data->delimiter_start;
	while (*data->delimiter_end && *data->delimiter_end != ' '
		&& *data->delimiter_end != '<'
		&& *data->delimiter_end != '>')
		data->delimiter_end++;
	data->length = heredoc_pos + ft_strlen(temp_filename)
		+ ft_strlen(data->delimiter_end) + 1;
	data->heredoc_i = heredoc_pos;
}

void	modify_input(char **input, int heredoc_i, char *filename, t_data *data)
{
	data->old_command = *input;
	start_end_heredoc(heredoc_i, filename, data);
	data->new_command = (char *)malloc(data->length);
	if (!data->new_command)
	{
		ft_putstr_fd("Error: Allocation failed\n", 2);
		return ;
	}
	while (data->old_command[--data->heredoc_i] == ' ')
		;
	while (data->old_command[--data->heredoc_i] == '<')
		;
	ft_strlcpy(data->new_command, data->old_command, data->heredoc_i + 1);
	data->new_command[data->heredoc_i] = '\0';
	ft_strlcat(data->new_command, " < ", data->length);
	ft_strlcat(data->new_command, filename, data->length);
	ft_strlcat(data->new_command, data->delimiter_end, data->length);
	free(*input);
	*input = data->new_command;
}

void	cmp_delim_input(char *delimiter, int fd_temp)
{
	char	*line;

	line = "1";
	while (line != NULL)
	{
		line = readline("> ");
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(delimiter) == ft_strlen(line))
			break ;
		write(fd_temp, line, ft_strlen(line));
		write(fd_temp, "\n", 1);
		free(line);
	}
	free(line);
}

void	redir_delimiter(char *str, char **input, int i, t_data *data)
{
	char	*delimiter;
	char	*temp_file;
	int		fd_temp;

	temp_file = ".heredoc_tmp";
	fd_temp = open(temp_file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd_temp < 0)
	{
		ft_putstr_fd("Error: Could not create temporary file", 2);
		return ;
	}
	if (str[i + 2] == ' ')
		delimiter = get_filename(&(str[i + 3]), &i);
	else
		delimiter = get_filename(&(str[i + 2]), &i);
	cmp_delim_input(delimiter, fd_temp);
	free(delimiter);
	close(fd_temp);
	modify_input(input, 0, temp_file, data);
	str = *input;
	i -= 2;
	handle_redir(input, data->i_memory, data);
}
