#ifndef MINITALK_H
# define MINITALK_H
# define SIGUSR1 1
# define SIGUSR2 0
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# define SIGUSER1 1
# define SIGUSER2 0


uint32_t	ft_strlen(char *s);
uint32_t	ft_putstr(char *s);
void		ft_putnbr_base(u_int16_t num, int base);
void		error_throw(char *s);


#endif