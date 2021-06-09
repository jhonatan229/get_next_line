/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:37:56 by jestevam          #+#    #+#             */
/*   Updated: 2021/06/09 20:42:30 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char *addline (char *str, char **line, int point)
{
	int count;
	count = findc(str, '\n');
	if (count == 0 && point == 0)
		count = ft_strlen(str);
	*line = ft_substr(str, 0, count);
	return (ft_substr(str, count + 1, ft_strlen(str + (count + 1))));
}

int	get_next_line(int fd, char **line)
{
	int			point;
	char		*buf;
	static char	*strstatic;
	int			rslt;
	char		*back;

	if (BUFFER_SIZE == 0)
		return (-1);
	rslt = 0;
	buf = malloc(BUFFER_SIZE + 1);
	point = read(fd, buf, BUFFER_SIZE);
	while (point > 0)
	{
		buf[point] = 0;
		if (strstatic == NULL)
			strstatic = ft_strdup(buf);
		else
		{
			back = ft_strjoin(strstatic, buf);
			free(strstatic);
			strstatic = back;
		}
		if (findc(strstatic, '\n') > 0)
		{
			rslt = 1;
			break ;
		}
		point = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	strstatic = addline(strstatic, *&line, point);
	return (rslt);
}
