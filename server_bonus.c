#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

void handle_signal(int sig)
{
    static char byte;
    static int mask = 128;
    static  int counter;

    if (sig == SIGUSR1)
        byte = byte | mask;

    mask = mask >> 1;
    counter++;
    if (counter == 8)
    {
        write(1, &byte, 1);
        counter = 0;
        mask = 128;
        byte = 0;
    }
}

int	count_digits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	fill_rec(int n, char *buff, int *i)
{
	if (n > 0)
	{
		fill_rec(n / 10, buff, i);
		buff[*i] = (n % 10) + 48;
		*i = *i + 1;
	}
}

char	*ft_itoa(int n, int *len)
{
	char	*buff;
	int		i;

	*len = count_digits(n);
	buff = malloc((*len + 1) * sizeof(char));
	if (buff == 0)
		return (0);
	buff[*len] = '\0';
	i = 0;
    fill_rec(n, buff, &i);
	return (buff);
}


void sigact_handler(int sig, siginfo_t *info, void *context)
{
	static char byte;
	static int mask = 128;
	static int count;
	if (sig == SIGUSR1)
		byte = byte | mask;
	mask = mask >> 1;
	count++;
	if (count == 8)
	{
		count = 0;
		mask = 128;
		write(1, &byte, 1);
		if (byte == 0)
			kill(info->si_pid, SIGUSR1);
		byte = 0;
	}

}

int main(int ac, char *av[])
{
	pid_t pid = getpid();
	struct sigaction sa;
	sa.sa_sigaction = sigact_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("pid -> %d\n", pid);
    // printf(" -> %d\n", pid);
    // signal(SIGUSR1, handle_signal);
    // signal(SIGUSR2, handle_signal);
    while (1)
    {
        pause();
    }

}