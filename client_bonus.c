#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int	    res;

	res = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}
void handle_reply(int sig, siginfo_t *info, void *idk)
{
    if (sig == SIGUSR1)
    {
        write(1, "received good\n", 15);
    }
}
int ft_strlen(char  *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        i++;
    }
    return (i);
    
}

int main(int ac, char *av[])
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_reply;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
    int pid;
    int i;
    int j;
    int len;
    char *msg;
    int mask;
    mask = 128;
    pid = ft_atoi(av[1]);
    if (ac != 3 || pid <= 0)
        return 1;
    msg = av[2];
    i = 0;
    len = ft_strlen(msg);
    i = 0;
    while (i <= len)
    {
        j = 0;
        while (j++ < 8)
        {
            if (mask & msg[i])
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            usleep(1000);
            mask = mask >> 1 ;
        }
        mask = 128;
        i++;
    }
    while (1)
    {
        pause();
    }
}