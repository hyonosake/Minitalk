#include "../minitalk.h"

void	server_handler(int sigtype, siginfo_t *siginfo, void *data)
{
	static unsigned char	ch = 0;
	static int	i = 0;

	(void)data;
	if (sigtype == SIGUSR1)
		ch |= 1LU << i;
	++i;
	if (i == 8)
	{
		write(1, &ch, 1);
		i = 0;
		ch = 0;
		if (kill(siginfo->si_pid, SIGUSR2) == -1)		//?????
			error_throw("Task failed successfully!\n");
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 1 || av[1])
		error_throw("Server should not recieve any input values\n");
	write(1, "Server is ready to recieve your VERY IMPORTANT messages...\n",60); 
	write(1, "ServerPID:\t", 12);
	ft_putnbr_base(getpid(), 10);
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_handler;
	if ((sigaction(SIGUSR1, &sa, 0)) == -1)
		error_throw("Sigaction of SIGUSR1 neg\n");;
	if ((sigaction(SIGUSR2, &sa, 0)) == -1)
		error_throw("Sigaction of SIGUSR2 neg\n");;
	while (1)
		pause();
	return (0);
}