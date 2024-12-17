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
void map_wall_side(char *line, int length, int *flag)
{
    if(line[0] != '1' || line[length - 2] != '1')
        {
            write(2,"side wall is wrong\n",19);
            *flag = 1;
        }
}

void map_wall_bottom(char *line, int length, int *flag)
{
    for (int i = 0; i < length - 1; i++)
    {
        if (line[i] != '1')
        {
            write(2,"bottom wall is wrong\n",21);
            *flag = 1;
            break;
        }
    }
}

void map_wall_main(char *av)
{
    int fd;
    int i;
    int length;
    int flag;
    char *line;
    char *last_line = NULL;

    i = -1;
    flag = 0;
    fd = open(av, O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error opening file\n", 19);
        exit(1);
    }
    line = get_next_line(fd);
    if (line == NULL)
    {
        write(2, "Error reading file\n", 19);
        close(fd);
        exit(1);
    }
    length = ft_strlen(line);
    while (++i < length - 1)
    {
        if (line[i] != '1')
        {
            write(2, "up wall is wrong\n", 17);
            flag = 1;
        }
    }
    free(line);
    while ((line = get_next_line(fd)) != NULL)
    {
        if (last_line != NULL)
            free(last_line);
        last_line = line;
        map_wall_side(line, length, &flag);
    }
    if (last_line != NULL)
    {
        map_wall_bottom(last_line, length, &flag);
        free(last_line);
    }
    close(fd);
    if (flag == 1)
        exit(0);
}
void error_handel(char *av)
{
    cheack_name(av);
    cheack_empty(av);
    map_rectangular(av);
    map_wall_main(av);
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

// void map_wall_main(char *av)
// {
//     int fd;
//     int i;
//     int length;
//     int flag;
//     char    *line;

//     i = -1;
//     flag = 0;
//     fd = open(av,O_RDONLY);
//     line = get_next_line(fd);
//     length = ft_strlen(line);
//     while(++i < length - 1)
//         if(line[i] != '1')
//         {
//             write(2,"up wall is wrong\n",17);
//             flag = 1;
//         }
//     free(line);
//     while((line = get_next_line(fd)) != NULL)
//     {
//         map_wall_side(line ,length ,&flag);
//         free(line);
//     }
//     free(line);
//     close(fd);
//     if (flag == 1)
//         exit(0);
// }