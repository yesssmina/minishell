#include "../minishell.h"

void	modify_command_for_heredoc(char **input, int heredoc_pos, char *temp_filename, t_data *data)
{
	data->old_command = *input;
	while (data->old_command[heredoc_pos] && data->old_command[heredoc_pos] != '<')
		heredoc_pos++;
	heredoc_pos += 2;
	while (data->old_command[heredoc_pos] && data->old_command[heredoc_pos] == ' ')
		heredoc_pos++;
	data->delimiter_start = &data->old_command[heredoc_pos];
	while (*data->delimiter_start == ' ')
		data->delimiter_start++;
	data->delimiter_end = data->delimiter_start;
	while (*data->delimiter_end && *data->delimiter_end != ' ' && *data->delimiter_end != '<'
		&& *data->delimiter_end != '>')
		data->delimiter_end++;
	data->length = heredoc_pos + ft_strlen(temp_filename) + ft_strlen(data->delimiter_end) + 1;
	data->new_command = (char *)malloc(data->length);
	if (!data->new_command)
	{
		ft_putstr_fd("Error: Allocation failed\n", 2);
		return ;
	}
	while (data->old_command[--heredoc_pos] == ' ')
		;
	while (data->old_command[--heredoc_pos] == '<')
		;
	ft_strlcpy(data->new_command, data->old_command, heredoc_pos + 1);
	data->new_command[heredoc_pos] = '\0';
	ft_strlcat(data->new_command, " < ", data->length);
	ft_strlcat(data->new_command, temp_filename, data->length);
	ft_strlcat(data->new_command, data->delimiter_end, data->length);
	free(*input);
	*input = data->new_command;
}

void	redir_delimiter(char *str, char **input, int i, t_data *data)
{
	char	*delimiter;
	char	*temp_filename;
	int		fd_temp;
	char	*line;

	temp_filename = ".heredoc_tmp";
	fd_temp = open(temp_filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd_temp < 0)
	{
		ft_putstr_fd("Error: Could not create temporary file\n", 2);
		return ;
	}
	if (str[i + 2] == ' ')
		delimiter = get_filename(&(str[i + 3]), &i);
	else
		delimiter = get_filename(&(str[i + 2]), &i);
	while ((line = readline("> ")) != NULL)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(delimiter) == ft_strlen(line))
			break ;
		write(fd_temp, line, ft_strlen(line));
		write(fd_temp, "\n", 1);
		free(line);
	}
	free(line);
	close(fd_temp);
	modify_command_for_heredoc(input, 0, temp_filename, data);
	str = *input;
	i -= 2;
	handle_redir(input, data->i_memory, data);
}

//printf("delim:%s\n", delimiter);
//printf("old:%s.\n", data->old_command);
//printf("delimstart:%s.\n", data->delimiter_start);
//printf("delimend:%s.\n", data->delimiter_end);
//printf("delimend:%s.\n", data->delimiter_end);
//printf("start:%s.\nend:%s.\n", data->delimiter_start, data->delimiter_end);
//printf("len end:%ld.\n", ft_strlen(temp_filename));
//printf("len:%d.\n", data->length);
//printf("pos:%d.\n", heredoc_pos);
//printf("new:%s.\n", data->new_command);
//	printf("old:%s.\n", data->old_command);
//printf("new_fin:%s.\n", data->new_command);