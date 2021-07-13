#include "../minitalk.h"

int	weird_magic(int pid, unsigned char byte)
{
	static uint8_t	mask[8] = {126, 125, 123, 119, 111, 95, 63};
	int				i;
	unsigned char	byte_tmp;
	bool			sig;

	i = 0;
	while (i < 8)
	{
		sig = mask[i] ^ (uint8_t)byte;
		if (sig)
		{
			write(1, "1", 1);
			if (kill(pid, SIGUSR1) < 0)
				return (1);
		}
		else
		{
			write(1, "0", 1);
			if (kill(pid, SIGUSR2) < 0)
				return (1);
		}
		++i;
		write(1, "\t", 1);
	}
	return (0);
}

void	send_data(int pid, void *message)
{
	unsigned char	*msg;
	int				i;

	i = 0;
	msg = (unsigned char *)message;
	while (msg[i])
	{
		if (weird_magic(pid, msg[i]))
			error_throw("Bit transmittion failed ;[");
		++i;
	}
}

void	client_handler(int sigtype, siginfo_t *siginfo, void *data)
{
	(void)siginfo;
	(void)data;
	if (sigtype == SIGUSR1)
		ft_putstr("Signal SIGUSR1 received!\n");
	else if (sigtype == SIGUSR2)
		ft_putstr("Signal SIGUSR2 received!\n");
}

int	main(int ac, char **av)
{
	struct sigaction	catch;

	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = client_handler;
	if ((sigaction(SIGUSR2, &catch, 0)) == -1)
		error_throw("Error sigaction\n");
	if (ac == 3)
		send_data(atoi(av[1]), av[2]);
	else
		error_throw("Error arguments\n");
	while (1)
		pause();
	return (0);
}