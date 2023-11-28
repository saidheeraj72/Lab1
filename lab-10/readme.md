### problem1.c

Create a parent process and its child process using fork().

In the parent process, one array (A) is given as [2, 1, 3, 0, 5, 0, 7, 9]. Now, take one number from the user and find the remainder value when you will divide the same number by values present in each location of the array A. Handle the situation using signal if required.

In the child process, print a random value between 10 to 30. Whenever you get a value more than 20, exit form the child process using exit() system call.

### producer-consumer.c

Implement the producer – consumer problem’s solution using semaphore.

Use one producer thread and one consumer thread. Also, clearly define the produce_item() function and consume_item() function. 

### reader-writer.c

Implement the reader-writer problem’s solution using semaphore.

Use one writer thread and five reader threads. Also, clearly define the reader() function and writer() function that reader and writer thread execute separately. 