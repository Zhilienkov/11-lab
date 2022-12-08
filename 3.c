#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

pid_t p;

static void main_signal_handler(int signo) {
    sleep(1);

    if (signo == SIGUSR1) {
        printf("HELLO FROM MAIN!!\n");
    }
}

static void sub_signal_handler(int signo) {
    sleep(1);
    
    if (signo == SIGUSR1) {
        printf("HELLO FROM SUB!!\n");
        kill(0, SIGUSR1);
    }
}

int main ()
{
    p = fork();

    if (p > 0) {
        while(1) {
            if(signal(SIGUSR1, sub_signal_handler) == SIG_ERR) {
                fprintf(stderr, "Невозможно перехватить SIGALRM!\n");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        while(1) {
            if(signal(SIGUSR1, main_signal_handler) == SIG_ERR) {
                fprintf(stderr, "Невозможно перехватить SIGALRM!\n");
                exit(EXIT_FAILURE);
            }

            kill(p, SIGUSR1);
        }    
    }
}