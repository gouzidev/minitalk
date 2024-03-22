#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int sig)
{
    static char byte;
    static char mask = 1;

    if (sig == SIGUSR1)
    {
        byte = byte | mask;
        mask = mask << 1;
    }
    else
        mask = mask << 1;
        write(1, &byte, 1);
}

int main(int ac, char *av[])
{
    pid_t pid = getpid();
    printf(" -> %d\n", pid);
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);
    while (1)
    {
        pause();
    }

}