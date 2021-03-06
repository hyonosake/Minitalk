#include "../minitalk.h"

void parse_bits(uint8_t byte, int pid)
{
    static unsigned char mask[] = {128, 64, 32, 16, 8, 4, 2, 1};
	int	pos;

	pos = 0;
	while (pos < 8)
	{
    	if ((byte & mask[pos]) != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				error_throw("Error transmitting signal SIGUSR1 to server");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error_throw("Error transmitting signal SIGUSR2 to server");
		}
		++pos;
		usleep(100);
	}
}

int	byte_transmit(int pid, void *data)
{
	unsigned char	*message;
	int				i;

	i = 0;
	message = (unsigned char *)data;
	while (message[i])
		parse_bits(message[i++], pid);
	return (0);
}

void	client_handler(int sig_num, siginfo_t *siginfo, void *data)
{
	(void)data;
	(void)siginfo;
	if (sig_num == SIGUSR2)
	{
		write(1, "Recieved by ID ", 16);
		ft_putnbr_base(siginfo->si_pid, 10);
	}
	else if (sig_num == SIGUSR1)
		error_throw("Weird signal. Exiting");
}

int	main(int ac, char **argv)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = client_handler;
	if (ac != 3)
		error_throw("You must pass server ID and a message!");
	if ((sigaction(SIGUSR2, &sa, 0)) == -1)
		error_throw("Client sigaction error occured");
	byte_transmit(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
