#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <curses.h>
# include <termios.h>
# include <stdint.h>
# include <sys/ioctl.h>

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_data
{
	char	**env;
	int		fd_in;
	int		fd_out;
	char	*pwd;
	int		redir;

	pid_t	parent_pid;
	char	*str;
	char	*delimiter;
	int		j;
	int		k;
	char	*temp_file;
	int		fd;
	char	*input_line;
	int		file_contents_length;
	char	*arg_error;
	char	*file_contents;
	char	*temp;

	char	*new_command;
	char	*old_command;
	int		length;
	char	*delimiter_start;
	char	*delimiter_end;
	int		i_memory;
	int		heredoc_i;
	int		p;
	int		status;
	int		succes_redir;
}				t_data;

extern int		g_signal;

int				envlen(char **env);
void			free_env(char **env);
char			**dup_env(char **env);
void			close_fds(t_data *data);

int				parser_start(char *str, t_data *data);
void			quote_len(char **str, int *i, char quote);
char			**input_split(char *str);

int				handle_basic(char *clean_input, t_data *data, int piped);
void			handle_echo(char **args, t_data *data);
void			handle_cd(char **args, t_data *data);
void			handle_unset(char **inputs, t_data *data);

char			**export_env(char **old_env, char *export);
void			handle_env(char **env, t_data *data);

int				change_pwd(t_data *data, char *input);
void			handle_pwd(t_data *data);

int				is_relative(char *str);
char			**gen_paths(int index, t_data *data, char *input);
int				check_exec(char **inputs, t_data *data);
void			handle_exec(char **args, t_data *data);
void			handle_sig(int sig);

void			replace_var(char *new_var, t_data *data, int index);
int				var_index(char *name, t_data *data);
int				print_export(char **env);
int				check_export(char *str);
char			**copy_export_env(char **env);
void			handle_export(char **args, t_data *data);

int				handle_pipe(char *input1, char *input2, t_data *data);
int				parser_delegator(char *input, t_data *data, int piped);
int				parser_error(char *str, t_data *data);
void			parser_variable(char **input_address, int *i, t_data *data);
int				parser_redir(char **input_address, t_data *data);
int				handle_redir(char **input_address, int i, t_data *data);
int				redir_delimiter(char *str, char **input, int i, t_data *data);
void			remove_redir_input(char **input_address, int i, int j);
int				get_name_len(char *str);
char			*get_filename(char *str, int *j);
void			input_copy(char *dst, char *src);
char			*input_cleaner(char *str);
void			copy_newsplit(char *src, char *dst, char quote);
void			escape_char(char **dst, char **src);
void			should_escape(int *i, char *str);

void			sig_exec_init(t_data *data);
void			sig_init(t_data *data);
void			sig_init_main(void);
void			sig_ignore(void);


void			error_sentence(char *str, int status, t_data *data);
void			error_sentence_exec(char *input, int status, t_data *data);
void			handle_exit(char **inputs, t_data *data);

int				create_line(char **str, char **line);
int				check_nl(char *str);
int				last_line(char **str, char **line);
int				mega_error(char *str1, char *str2);

void			redir_from(char *str, int i, char **input, t_data *data);
void			redir_to_append(char *str, int i, char **input, t_data *data);
void 			sigint_handler(int sig);
void 			sig_reset();

int	redir_error(char *str, int i);
int	redir_error1(char *str, int i);
int	redir_error2(char *str, int i);
int	redir_error3(char *str, int i);
int	redir_error4(char *str, int i);
int	redir_error5(char *str, int i);
int	redir_error_pipe(char *str, int i);
int	redir_error_pipe1(char *str, int i);
int	redir_error_semi(char *str, int i);
int	redir_error_semi1(char *str, int i);
int	redir_error_space(char *str, int i);
int	ambigus_redir(char *str, int i, t_data *data);


#endif
