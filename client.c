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
    int pid;
    int i;
    int len;
    int j;
    char *msg;
    int mask;

    mask = 128;
    if (ac != 3)
        return(printf("error in argument count, syntax: ./client [pid] [msg]\n"), 1);
    pid = ft_atoi(av[1]);
    if (pid <= 0)
        return(printf("error in pid\n"), 1);
    msg = av[2];
    len = ft_strlen(msg);
    i = 0;
    while (i <= len)
    {
        if (msg[i] == '\0')
            write(1,"\n",1);
        else
            write(1, &msg[i], 1);
        j = 0;
        while (j++ < 8)
        {
            if (mask & msg[i])
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            usleep(1000);
            mask = mask >> 1;
        }
        mask = 128;
        i++;
    }
}