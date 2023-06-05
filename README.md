# TestTask

## Task 1

In the [taks1](https://github.com/ashumnik/TestTask/tree/main/task1) folder

## Task 2

1) Safety and isolation: Static linking of an application reduces the likelihood of an attack and increases security by eliminating dependence on external libraries, which makes it useful for confidential applications or deployments in untrusted environments.
2) Portability: Static linking ensures that the application runs without external dependencies, which makes it portable to various systems or environments where the availability or compatibility of shared libraries cannot be guaranteed.
3) Simplified Deployment: Static linking simplifies the deployment process by eliminating the need to install and manage shared libraries on the target system
4) Dependency control: Static linking of the application gives more control over dependencies. By combining all the necessary libraries, you can ensure consistent behavior and avoid conflicts with other installed libraries.
5) Performance Optimization: Static linking eliminates the overhead associated with dynamic loading and character resolution, resulting in potentially faster startup and improved runtime performance.

## Task 3

In the [taks3](https://github.com/ashumnik/TestTask/tree/main/task3) folder

## Task 4

The breakpoint function in the Unix operating system debugger is implemented using the processor interrupt mechanism. When the debugger sets a breakpoint in a program, it modifies the code to insert a special instruction that causes the processor to interrupt at a certain point in the program execution. This instruction is usually called "int 3" in the x86 architecture assembler. <br/>
When the processor reaches the "int 3" instruction, it generates an interrupt, which leads to the transfer of control to the operating system kernel. The kernel detects that the interrupt is caused by the debugger and switches to debug mode. <br/>
The debugger, working in kernel mode, has access to the state of the process, its memory and processor registers. He can analyze the current state of the program and perform the necessary debugging operations, for example, analyze the values of variables, change values, monitor the call stack, perform execution steps. <br/>
After performing the necessary debugging operations, the debugger may decide to continue executing the program by removing the breakpoint and restoring the original instruction, which was replaced by the "int 3" instruction. The processor then resumes executing the program.


## Task 5

No, a breakpoint that is placed in a function defined by a dynamically linked library will not stop other applications using the same library. The Linux kernel implements COW (copy on write): if the shared library code is being written, the kernel first creates a private duplicate copy of the shared page, reassigns the internal virtual memory for that process only to the copy, and allows the application to continue.  <br/>
Thus, until a software breakpoint is placed in a shared library for the first time, its code is indeed shared, but not afterwards. After that, the process works with a private copy.

## Task 6

In the case when the user process has started an I/O operation with the device, but is stuck waiting for the end of the operation, the operation will be completed while another process is running. The operating system will handle the hardware interrupt. If the system is single-processor, then the current process will be suspended, since it takes time to process the interrupt. Consequently, any process in the system unpredictably affects the performance of other processes, regardless of their priorities.
