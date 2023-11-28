// #include <unistd.h>
// int main(void) {
//     char *file = "/bin/echo";
//     char *arg1 = "Hello world!";
	
//     execl(file, file, arg1, NULL);

//     return 0;
// }

// #include <unistd.h>
// int main(void) {
//     char *file = "/bin/echo";
//     char *const args[] = {"/bin/echo", "Hello world!", NULL};
	
//     execv(file, args);

//     return 0;
// }

// #include <unistd.h>
// int main(void) {
//     char *file = "/bin/bash";
//     char *arg1 = "-c";
//     char *arg2 = "echo $ENV1 $ENV2!";
//     char *const env[] = {"ENV1=Hello", "ENV2=World", NULL};
	
//     execle(file, file, arg1, arg2, NULL, env);

//     return 0;
// }

// #include <unistd.h>
// int main(void) {
//     char *file = "/bin/bash";
//     char *const args[] = {"/bin/bash", "-c", "echo Hello $ENV!", NULL};
//     char *const env[] = {"ENV=World", NULL};
	
//     execve(file, args, env);

//     return 0;
// }

// #include <unistd.h>
// int main(void) {
//     char *file = "echo";
//     char *arg1 = "Hello world!";

//     execlp(file, file, arg1, NULL);
//     return 0;
// }

// #include <unistd.h>
// int main(void) {
//     char *file = "echo";
//     char *const args[] = {"/bin/echo", "Hello world!", NULL};
	
//     execvp(file, args);

//     return 0;
// }