#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

char *str;

static void signal_handler(int signo) {
    if (signo == SIGALRM)
        printf("%s\n", str);

    exit(EXIT_SUCCESS);
}

int main (int argc, char *argv[])
{
    if (argc < 3) //Если аргументов в командной строке мало то ошибка
	{
		fprintf(stderr, "Too few arguments\n");
		return 1;
	}
    int time = atoi(argv[1]);
    str = argv[2];

    pid_t p = fork();

    if (p > 0) {
        if(signal(SIGALRM, signal_handler) == SIG_ERR) {
            fprintf(stderr, "Невозможно перехватить SIGALRM!\n");
            exit(EXIT_FAILURE);
        }

        alarm(time);

        while(1)
            pause();
    }
}