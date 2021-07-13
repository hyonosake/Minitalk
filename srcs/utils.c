#include "minitalk.h"

uint32_t	ft_strlen(char *s)
{
	uint32_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}

uint32_t	ft_putstr(char *s)
{
	uint32_t	ret_val;

	ret_val = write(1, s, ft_strlen(s));
	return (ret_val);
}

void	ft_putnbr_base(u_int32_t num, int base)
{
	static char	base_set[17] = "0123456789ABCDEF\0";
	char		result[15];
	int			i;

	i = 0;
	if (num == 0)
	{
		write (1, "0", 1);
		return ;
	}
	while (num)
	{
		result[i++] = base_set[num % base];
		num /= base;
	}
	--i;
	while (i > -1)
		write (1, &result[i--], 1);
	write (1, "\n", 1);
	return ;
}

void	error_throw(char *s)
{
	ft_putstr(s);
	write(1, "\n", 1);
	exit(0);
}

uint32_t	ft_atoi(char *s)
{
	int			i;
	uint32_t	num;

	i = 0;
	num = 0;
	while (s[i] >= '0' && s[i] <= '9')
		num = num * 10 + (s[i++] - '0');
	if (s[i])
		error_throw("Invalid PID input. Try again, I'll wait..");
	return (num);
}


