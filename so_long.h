# ifndef SO_LONG_H
# define SO_LONG_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx_linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include "/home/abdalrhman/test/Libft/libft.h"

char	*ft_strjoin2(char *s1, char *s2);
int		ft_strlen2(char *str);
char	*check_for_newline(char *str);
char	*get_next_line(int fd);

#endif