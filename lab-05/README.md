### parentChild.c
Write a C program which will create a child process from a parent process. In parent process, define one global array and take input from the user.
Perform following operations.
#### In Parent Process:
1. Update the array by subtracting 3 from each element of the array.
2. Print the elements, address of the elements and find the minimum element after performing 1
3. Print process id and it’s parent process id
#### In Child Process:
1. Update the global array by adding 2 on each element of the array.
2. Print the elements, address of the elements and find the maximum element after performing 1
3. Print process id and it’s parent process id

### parentChild2.c
Create parent and child processes using fork(). In each process, define an array of integer using malloc. Before that take the size of the array from the user. Insert values in your array (size and array elements may be different for both processes).
#### In Parent Process:
1. Print the array elements and their addresses
2. Sort the array and print its values.
#### In Child Process:
1. Print the array elements and their address
2. Reverse the array and print its values.

NOTE: Ensure that first child process should terminate, then Parent Process should start taking input.