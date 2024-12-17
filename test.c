#include "so_long.h"

void cheack_name (char *av)
{
    int fd;
    int length;
    int j;
    char    *bar;

    fd = open(av,O_RDONLY);
    close(fd);
    if (fd < 0 )
    {
        write(2,"Error file doesn't open or doesn't exist\n",41);
        exit(1);
    }
    length=ft_strlen(av);
    bar = ".bar";
    j = 4;
    while(j > 0)
    {
        if(av[length--] != bar[j--])
        {
            write(2,"Not a .bar file\n",16);
            exit(1);
        }
    }
}

void cheack_empty(char *av)
{
    int fd;
    int byte_read;
    char    *buffer;

    fd = open(av,O_RDONLY);
    buffer = malloc(sizeof(char));
    byte_read = read(fd,buffer,1);
    free(buffer);
    close(fd);
    if(byte_read < 1)
    {
        write(2,"File is empty\n",14);
        exit(1);
    }
}
void map_rectangular(char *av)
{
    int fd;
    int length;
    int length2;
    char    *line;
    fd = open(av,O_RDONLY);
    line = get_next_line(fd);
    length = ft_strlen(line);
    free(line);
    while ((line = get_next_line(fd)) != NULL)
        {
            length2 = ft_strlen(line);
            if (length != length2)
            {
                close(fd);
                free(line);
                write(2,"the map shape is wrong\n",23);
                exit(1);
            }
            free(line);
        }
    free(line);
    close(fd);
}
void map_wall(char *av)
{
    int fd;
    int i;
    int length;
    char    *line;

    i = -1;
    fd = open(av,O_RDONLY);
    line = get_next_line(fd);
    length = ft_strlen(line);
    while(++i < length - 1)
        if(line[i] != '1')
        {
            write(2,"up wall is wrong\n",17);
            free(line);
            exit(0);
        }
    free(line);
    while((line = get_next_line(fd)) != NULL)
    {
        if(line[0] != '1' || line[length - 2] != '1')
        {
            printf("%d\n",line[0]);
            printf("%d\n",line[length - 2]);
            write(2,"side wall is wrong\n",18);
            free(line);
            close(fd);
            exit(0);
        }
        free(line);
    }
    free(line);
    close(fd);

}/////////////////////////////////////////////////////////////////////////// fix botom row and error one malloc from cut the line 

void error_handel(char *av)
{
    cheack_name(av);
    cheack_empty(av);
    map_rectangular(av);
    map_wall(av);
}
int main (int ac,char **av)
{
    if (ac != 2)
    {
        write(2, "Error1\n", 7);
        return (0);
    }
    error_handel(av[1]);
    
}
