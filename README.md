# get_next_line
>This project aim to read a line the file description - fd (can be a file, a input or output, the fd must exist, and must have something inside this space)  

# How to use
>The way to use this function is pretty simple, it have as parameter two variables:
>* First is a integer 'fd', that is the file description, (it can be a file opened, or a standard fd: stdin, stdout, stderr);
>* Second is a string where do you want to store the line found;<br />

### The implementation looks like this:

```c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd;
	int return_fd;
	int count;
	char *aws;

	count = 1;
	fd = open('test.txt', O_RDONLY);
	return_fd = get_next_line(fd, &aws);
	while (return_fd > 0)
	{
		printf("line %i: %s", count++, aws);
		free(aws);
		return_fd = get_next_line(fd, &aws);
	}
	printf("line %i: %s", count++, aws);
	free(aws);
	close(fd);
}
```

The return of this function is store in 'return_fd' that returns:
* 1 if found a line with \n on the end;
* 0 if found the last line of the file;
* -1 if a error is found

# get_next_line_bonus
>Is similar to get_next_line, but, in this function you can walk through the files
simultaneously, without lose the line that you stopped read

The implementation is the same the get_next_line, with the same parameters:
```c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd1;
	int fd2;
	char *aws;

	fd1 = open('test1.txt', O_RDONLY);
	fd2 = open('test2.txt', O_RDONLY);
	get_next_line(fd1, &aws);
	printf("line 1 txt 1: %s", aws);
	free(aws);
	get_next_line(fd2, &aws);
	printf("line 1 txt 1: %s", aws);
	free(aws);
	get_next_line(fd1, &aws);
	printf("line 1 txt 1: %s", aws);
	free(aws);
	get_next_line(fd2, &aws);
	printf("line 1 txt 1: %s", aws);
	free(aws);
	close(fd);
}
```
>Note in this example, that i call my function fisrt passing my fd1,and then calls again with fd2, in the third call of my function, the fd1 will start read again from where stopped.

### Observations
* In all those examples, i use free() on 'aws' because, inside the function, is used malloc to store the line in variable.
* For this function works, must initialize the function BUFFER_SIZE on compilation moment, with the number of bytes the read()(that is inside the function get_next_line) will read.
