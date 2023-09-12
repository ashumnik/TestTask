# Task1 Review

## Changes: [commit](https://github.com/ashumnik/TestTask/commit/75dd9219ca9aac214dee7cbbb7b216ca2de4a8c4), [commit 2](https://github.com/ashumnik/TestTask/commit/4aa3a91017b296574dc0072e3df44d930037fb20) 

### count_list_items()
Compared to iteration, a reusable recursive function call takes more time. This is due to the fact that when a recursive method is called, its parameters are copied to the stack. At the end of the recursive function call, the previous parameter values are pulled from the stack, which leads to unnecessary operations. The iterative algorithm for this task works faster.

### insert_next_to_list()
The parenthesis operator has a higher priority, then the assignment operator, that is, memory is allocated first, and then a value is assigned, thus the pointer to item->next is redefined, and the value of the previous pointer is lost <br/>
\+ not very readable code

### remove_next_from_list()
First, the memory is freed, and then information is taken at the address of this memory

### item_data()
A pointer to a local variable is returned, which is cleared after exiting the function.
If the prototype of the function cannot be changed, then it is necessary to allocate dynamic memory for this variable. I don't like this solution, because there is a possibility that the programmer uses the function without knowing that memory is allocated there and forgets to clear it, so it's better to add another parameter passed to the function (a pointer to buff)
