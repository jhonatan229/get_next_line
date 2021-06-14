#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>

int			get_next_line(int fd, char **line);
void		*ft_memcpy(void *to, const void *from, size_t numBytes);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
