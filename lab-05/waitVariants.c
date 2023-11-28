// #include<stdio.h>
// #include<sys/wait.h>
// #include<unistd.h>

// int main()
// {
// 	if (fork()== 0)
// 		printf("HC: hello from child\n");
// 	else
// 	{
// 		printf("HP: hello from parent\n");
// 		wait(NULL);
// 		printf("CT: child has terminated\n");
// 	}

// 	printf("Bye\n");
// 	return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>

// int main() {
//     pid_t child_pid;

//     if ((child_pid = fork()) == 0) {
//         // Child process
//         printf("Child process running...\n");
//         sleep(2);
//         printf("Child process completed.\n");
//         exit(0);
//     } else if (child_pid > 0) {
//         // Parent process
//         printf("Parent process waiting for child...\n");
//         int status;
//         waitpid(child_pid, &status, 0); // Parent waits for a specific child
//         printf("Parent process resumed.\n");
//     } else {
//         perror("Fork failed");
//         return 1;
//     }

//     return 0;
// }