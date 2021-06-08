/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:37:56 by jestevam          #+#    #+#             */
/*   Updated: 2021/06/08 18:53:00 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	char	*myline;
	size_t	arq;
	int		count;

	count = 0;
	arq = 1;
	if (fd < 0)
		return (-1);
	myline = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (arq > 0 && count < BUFFER_SIZE)
	{
		arq = read(fd, &myline[count], 1);
		if (myline[count++] == '\n')
		{
			count--;
			break ;
		}
	}
	myline[count] = 0;
	*line = myline;
	return (arq);
}
