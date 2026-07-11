/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferre <lucferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 03:07:50 by lucferre          #+#    #+#             */
/*   Updated: 2026/07/11 20:33:05 by lucferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*acc;
	char			*line;
	ssize_t			bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (line_end(acc) != 1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		acc = str_join(acc, buffer);
		if (!acc)
			break ;
	}
	free(buffer);
	if (!acc || acc[0] == '\0' || bytes_read < 0)
		return (free(acc), acc = NULL, NULL);
	line = read_line(acc);
	acc = extract_line(acc, line);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int				fd;
// 	char			*p;
// 	static int		c;

// 	fd = open("file.txt", O_RDONLY);
// 	p = get_next_line(fd);
// 	c = 1;
// 	while (p)
// 	{
// 		printf("linha %d: %s", c, p);
// 		free(p);
// 		p = get_next_line(fd);
// 		c++;
// 	}
// 	close(fd);
// 	return (0);
// }
