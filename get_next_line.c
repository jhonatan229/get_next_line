/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:37:56 by jestevam          #+#    #+#             */
/*   Updated: 2021/06/10 22:39:18 by jestevam         ###   ########.fr       */
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
	while (psub < len && s[start] != 0)
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
	while (s[count] != '\0')
	{
		if (s[count] == c)
			return (count);
		count++;
	}
	return (-1);
}

static char *addline (char *str, char **line, int point)
{
	int	count;
	int	len;

	if ((str == NULL && point == 0) || *str == '\n')
	{
		*line = ft_strdup("");
		return (0);
	}
	count = findc(str, '\n');
	len = ft_strlen(str);
	if (point == 0 && count == -1)
	{
		count = len;
		*line = ft_substr(str, 0, count);
		return (0);
	}
	else
		*line = ft_substr(str, 0, count);
	if (count + 1 < len)
		return (ft_substr(str, count + 1, len));
	return (0);
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
		if (strstatic == NULL || strstatic[0] == '\n')
			strstatic = ft_strdup(buf);
		else
		{
			back = ft_strjoin(strstatic, buf);
			free(strstatic);
			strstatic = back;
		}
		if (findc(strstatic, '\n') != -1)
		{
			rslt = 1;
			break ;
		}
		point = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	back = addline(strstatic, *&line, point);
	free(strstatic);
	strstatic = back;
	return (rslt);
}
