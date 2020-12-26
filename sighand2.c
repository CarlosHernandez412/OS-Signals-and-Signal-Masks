/* sighand2.c
 * 
 *  Demonstrates what happens when the signal handler for one signal is 
 *  interrupted by a second incoming signal. This is accomplished by hitting 
 *  CTRL-C while in the middle of a system call.
 * 
 *  Compile and execute:
 *  
 *        $ gcc -o sighand2 sighand2.c
 *        $ ./sighand2
 * 
 *  Start typing something at the prompt. Hit CTRL-C before finishing. Note 
 *  what happens. The system call fgets is interrupted and generates its own
 *  signal EINTR (interrupted system call). Some system calls can be restarted, 
 *  fgets() is one. Make the change noted, recompile and see what happens now.
 *    
 *    The prototype for a signal handler is: 
 * 
 *       void sigint_handler(int sig); 
 * 
 *     Read 
 *        $ man sigaction 
 *     for details on flags
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

void sigint_handler(int sig)
{
   write(1, "Ahhh! SIGINT!\n", 14);  /* write is async-safe */ 
}

int main(int argc, char *argv[], char *envp[]) {
      
    char s[200];
    struct sigaction sa;
    int flag = 0;
    sa.sa_handler = sigint_handler;
    if (argc == 2)
       flag = atoi(argv[1]);
 
    /* pick one of the following */
    if (flag == 0)
       sa.sa_flags = 0; /* do NOT restart an interrupted system call */
    else
       sa.sa_flags = SA_RESTART; /*restart interrupted system calls in handler*/

    /* the mask for the handler is empty so no signals are blocked in handler */
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    printf("Enter a string:\n");
    if (fgets(s, sizeof s, stdin) == NULL)
        perror("fgets");
    else 
        printf("You entered: %s\n", s);

    return 0;
}
