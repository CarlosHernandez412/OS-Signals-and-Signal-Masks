#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      /* header file for the POSIX API */
#include <time.h>        /* to write time */
#include <sys/types.h>   /* standard data types for systems programming */
#include <sys/file.h>    /* file-related system calls */
#include <sys/wait.h>    /* for wait() system call */ 
#include <signal.h>      /* signal handling */ 
#include <errno.h>       /* for perror() call */ 


int flag = 0;
int status;
pid_t parent, cpid;
int logfd;


void myhandler (int sig)    {
    if(sig==SIGUSR1)
    write( logfd, "got signal\n",10);
    return;
}


int main(int argc, char *argv[], char *envp[]) {
    int ret;
    sigset_t mask;
    sigfillset(&mask);
   sigprocmask(SIG_BLOCK, &mask, NULL);


    struct sigaction sa;
    sa.sa_handler = myhandler;
    sa.sa_flags = 0;
    sa.sa_flags = SA_RESTART;
    sigfillset (&sa.sa_mask);
    sigaddset(&mask, SIGUSR1);
     ret = sigaction(SIGUSR1, &sa, NULL);
    cpid= fork();
    parent = getpid();

    if (cpid == 0)
       {
    logfd = open("log", O_WRONLY|O_CREAT|O_TRUNC, 0644);

    write(logfd, "hello  ", 7);
    sigdelset(&mask, SIGUSR1);
    sigsuspend(&mask);
    write(logfd, "  world\n", 9);
    close(logfd);
    exit(0);
        }
    else 
       {
            if(kill(cpid, SIGTERM) < 0)
                perror("\nkill: SIGTERM\n");


            if(kill(cpid, SIGUSR1) < 0)
                perror("\nkill: SIGUSR1\n");
            wait (&status);

            
            if (WIFEXITED (status))
                printf ("child exited normally with code %d\n",WEXITSTATUS (status ));
            exit(EXIT_SUCCESS);
        }
}
