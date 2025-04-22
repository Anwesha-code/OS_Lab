// Online C compiler to run C program online
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2], n;
    char buffer[100];
    pid_t p;

    pipe(fd); 
    p = fork();

    if (p > 0) {          // Parent process
        printf("Parent Passing value to child\n");
        write(fd[1], "hello\n", 6); // fd[1] write end 
                                       //fd[i], message, no. of bytes h.e.l.l.o.\n=6

        wait(NULL);       //parent waits for child to finish

        n = read(fd[0], buffer, 100); // fd[0] read end

        write(1, buffer, n);         //prints recieved message

    } 
    else {                         // Child process
        printf("Child printing received value\n");
        n = read(fd[0], buffer, 100); 

        write(1, buffer, n);

        write(fd[1], "Message Received\n", 16);
        
        exit(0);
    }

    return 0;
}
