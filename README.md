**Get_Next_Line**

Summary: This is a 42 school project. The goal of the project is to write a function that returns a line read from a
file descriptor

---
The requirements:
1. Repeated calls (e.g., using a loop) to your get_next_line() function should let
you read the text file pointed to by the file descriptor, one line at a time.
2. Your function should return the line that was read. If there is nothing else to read or if an error occurred, it should return NULL.
3. Using external functions other than read, malloc, free is forbidden and global variables are forbidden.
4. In the bonus part you need to develop get_next_line() using only one static variable and your get_next_line() can manage multiple file descriptors at the same time.
