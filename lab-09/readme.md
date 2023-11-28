# Threading

## sumOfNumbers.c

Write a program to create five threads using pthread library. Find the sum of first 1000 numbers using five threads, where each thread can calculate sum of 200 numbers in each (parallel counting using threads). After completion of threads operation,  print the final sum from the main function.

## matrix-operations.c

Write a program where you create 3 threads. Consider two global matrix M1 and M2 of size 3 x 3. Perform addition, subtraction and multiplication in individual thread and store in matrix A[3][3], S[3][3] and M[3][3]. Print the individual matrix values (M1 and M2) and computed matrix of addition, subtraction, multiplication operation in the main function . Once all thread process will be completed, then only main function will execute.

## executionOrder.c

Given 2 threads, schedule the order of execution in such a way that Thread A has to wait for Thread B and vice versa. In other words, given the code below you must guarantee that Statement A1 happens before Statement B2 and Statement B1 happens before Statement A2. 

Thread A  
//Statement A1  
//Statement A2  

Thread B  
//Statement B1  
//Statement B2  

Note: Your solution should not enforce too many constraints. For ex: there is no mention about the order of execution of A1 and B1. Therefore, either order should be possible.