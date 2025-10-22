- No Dynamic Memory:
In Linux, the maximum argument size execve can handle is 2mb, with a 128kb limit per argument
This is well beneath the 8mb stack limit, meaning that each command can comfortably be executed without exceeding memory constraints.

Solution:
- 128kb reading buffer
- 2mb execve buffer

As the line is read, the program executes as soon as a single sintactic unit is formed.
Given that code executes from left to right, and values on the RHS do not affect the LHS, the buffer can be passed off to execve and cleared after execution

Despite the line length being unbounded, code execution works because the values don't need to be saved.

However, this presents a problem for the working history, because it needs to be saved in its entirety.

Possible solution is to have the working history be saved in the stack (4mb), and when it needs more space 


# Create safe_write
Short writes: write(fd, buf, len) can return 0 < n < len. That means only n bytes were written (common with pipes, sockets, terminals, nonblocking fds). You must advance the pointer and loop until all bytes are written or an error occurs.

EINTR: A system call was interrupted by a signal before it made progress. write() returns -1 with errno == EINTR. Just retry the call.