#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


// int main(int ac, char *av[])
// {
//     int i;
//     int j;
//     char *msg;
//     if (ac != 2)
//         return 1;

//     msg = av[1];
//     i = 0;
//     while (msg[i])
//     {
//         j = 0;
//         while (j < 8)
//         {

//         }
//     }
//     // kill()      
// }
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

int main(int ac, char *av[])
{
    int pid;
    int i;
    int mask;
    i = 0;
    mask = 128;
    pid = ft_atoi(av[1]);
    printf("pid -> %d\n", pid);
    char b = 63; // 128
    while (i < 8)
    {
        if (mask & b)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(10000);
        mask = mask >> 1 ;
        i++;
    }
    // kill()      
}