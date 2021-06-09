/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:37:56 by jestevam          #+#    #+#             */
/*   Updated: 2021/06/09 17:54:20 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			psub;

	psub = 0;
	sub = malloc(len + 1);
	if (sub == NULL || s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (sub);
	while (psub < len)
	{
		sub[psub] = s[start];
		start++;
		psub++;
	}
	sub[psub] = 0;
	return (sub);
}

static int findc(char *s, char c)
{
	int	count;

	count = 0;
	while (s[count] != 0)
	{
		if (s[count] == c)
			return (count);
		count++;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			point;
	char		*buf;
	static char	*strstatic;
	int			count;
	int			rslt;

	rslt = 0;
	buf = malloc(BUFFER_SIZE + 1);
	point = read(fd, buf, BUFFER_SIZE);
	printf("point = %i\n", point);
	while (point > 0)
	{
		if (strstatic == NULL)
			strstatic = ft_strdup(buf);
		else
			strstatic = ft_strjoin(strstatic, buf);
		if (findc(strstatic, '\n') > 0)
		{
			rslt = 1;
			break ;
		}
		point = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	count = findc(strstatic, '\n');
	if (count == 0 && point == 0)
		count = ft_strlen(strstatic);
	*line = ft_substr(strstatic, 0, count);
	strstatic = ft_substr(strstatic, count + 1, ft_strlen(strstatic));
	return (rslt);
}

int main()
{
	int fd1 = open("text.txt", O_RDONLY);

    char *line;
    
    get_next_line(fd1, &line);
    printf("%s\n", line);
    get_next_line(fd1, &line);
    printf("%s\n", line);
    get_next_line(fd1, &line);
    printf("%s\n", line);
	get_next_line(fd1, &line);
    printf("%s\n", line);
	get_next_line(fd1, &line);
    printf("%s\n", line);

    close(fd1);
    free(line);
}