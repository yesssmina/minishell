#include "../minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(2, "\b\b  \b\b", 6);
	}
}

void	sig_init(t_data *data)
{
	if (signal(SIGINT, handle_sig) == SIG_ERR)
	{
		data->status = 130;
		exit(EXIT_FAILURE);
	}
	else if (signal(SIGQUIT, handle_sig) == SIG_ERR)
	{
		data->status = 131;
		exit(EXIT_FAILURE);
	}
}

void	handle_exec_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
	}
}

void	sig_exec_init(t_data *data)
{
	if (signal(SIGINT, handle_exec_sig) == SIG_ERR)
	{
		data->status = g_signal;
		exit(EXIT_FAILURE);
	}
}


void sigint_handler(int sig)
{
	(void)sig;
	close(0);
	g_signal = 130;
	write(1, "\n", 1);
}

void 	sig_reset()
{
   struct sigaction act;

   act.sa_handler = sigint_handler;
   sigemptyset(&act.sa_mask);
   act.sa_flags = 0;

   if (sigaction(SIGINT, &act, NULL) < 0)
   {
       perror("Error\nsigaction\n");
       exit(1);
   }
}
