/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sannagar <sannagar@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:37:15 by sannagar          #+#    #+#             */
/*   Updated: 2024/01/17 18:28:22 by sannagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_parentps(char *input2, t_data *data, int pid, int *fds)
{
	int	oldfd;
	int	status;

	status = 0;
	oldfd = dup(0);
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
	parser_start(input2, data);
	dup2(oldfd, 0);
	close(oldfd);
	waitpid(pid, &status, 0);
}

int	handle_pipe(char *input1, char *input2, t_data *data)
{
	pid_t	pid;
	int		fds[2];

	sig_exec_init(data);
	if (pipe(fds) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		free(input2);
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		handle_basic(input1, data, 1);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		free(input1);
		input1 = NULL;
		handle_parentps(input2, data, pid, fds);
	}
	return (1);
}
