#include "../minitalk.h"

void	server_handler(int signum, siginfo_t *siginfo, void *unused)
{
	static int	ascii = 0;
	static int	power = 0;

	(void)unused;
	if (signum == SIGUSR1)
		ascii += 1 << (7 - power);
	power += 1;
	if (power == 8)
	{
		if (ascii == 0)
			write(1, "\n", 1);
		else
		{
			write(1, &(ascii), 1);
			power = 0;
			ascii = 0;
		}
		if (kill(siginfo->si_pid, SIGUSR2) == -1)
			error_throw("Failed to send affirmative signal to client");
	
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 1 || av[1])
		error_throw("Server should not take any arguments");
	write(1, "Server is ready to recieve your VERY IMPORTANT messages...\n", 60);
	write(1, "Server PID is: ", 16);
	ft_putnbr_base(getpid(), 10);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_handler;
	if ((sigaction(SIGUSR1, &sa, 0)) == -1)
		error_throw("Sigaction error in server with SIGUSR1 signal");
	if ((sigaction(SIGUSR2, &sa, 0)) == -1)
		error_throw("Sigaction error in server with SIGUSR2 signal");
	while (1)
		pause();
	return (0);
}