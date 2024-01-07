#include "../minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		//puts("*CONT^C_handle_sig*");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		//puts("*CONT^D_handle_sig*");
		write(2, "\b\b  \b\b", 6);
	}
}

void	sig_init(t_data *data)
{
	if (signal(SIGINT, handle_sig) == SIG_ERR)
	{
		//puts("CONT^C_sig");
		data->status = 130;
		exit(EXIT_FAILURE);
	}
	else if (signal(SIGQUIT, handle_sig) == SIG_ERR)
	{
		//puts("CONT^D_sig");
		data->status = 131;
		exit(EXIT_FAILURE);
	}
}

void	handle_exec_sig(int sig)
{
	if (sig == SIGINT)
	{
		//puts("CONT^C_exec");
		g_signal = 130;
	}
	else if (sig == SIGQUIT)
	{
		//puts("CONT^D_exec");
		g_signal = 131;
	}
}

void	sig_exec_init(t_data *data)
{
	if (signal(SIGINT, handle_exec_sig) == SIG_ERR)
	{
		//puts("**sig_exec_init**");
		data->status = g_signal;
		exit(EXIT_FAILURE);
	}
}

void sigint_handler(int sig)
{
	(void)sig;
	close(0);
	write(1, "\n", 1);
	//puts("la");
   // Faire rien, donc le programme continuera à s'exécuter
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
