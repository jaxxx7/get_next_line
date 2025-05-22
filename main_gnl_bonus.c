#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1, fd2;
    char *line1 = NULL;
    char *line2 = NULL;
    int read1 = 1;
    int read2 = 1;

    fd1 = open("test1.txt", O_RDONLY);
    if (fd1 < 0)
    {
        perror("Error opening test1.txt");
        return (1);
    }

    fd2 = open("test2.txt", O_RDONLY);
    if (fd2 < 0)
    {
        perror("Error opening test2.txt");
        close(fd1);
        return (1);
    }

    while (read1 || read2)
    {
        if (read1)
        {
            line1 = get_next_line(fd1);
            if (line1)
            {
                printf("test1.txt: %s", line1);
                free(line1);
            }
            else
                read1 = 0;
        }
        if (read2)
        {
            line2 = get_next_line(fd2);
            if (line2)
            {
                printf("test2.txt: %s", line2);
                free(line2);
            }
            else
                read2 = 0;
        }
    }

    close(fd1);
    close(fd2);
    return (0);
}
