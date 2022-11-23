/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:33:01 by ivan-mel          #+#    #+#             */
/*   Updated: 2022/11/23 17:27:41 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

// checkchar : this function checks whether we are at the end of a line (\n) or not each time you run it

int checkchar(char *buffy)
{
	int i;

	i = 0;
	while (buffy[i] != '\0')
	{
		i++;
		if (buffy[i] == '\n')
			return (i);
	}
	return (0);
}

// strlen : checks the length of a string

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

// strjoin : joins two strings together as a third new string

char	*ft_strjoin(char *line, char const *buffy)
{
	char	*new_line;
	int		length_line;
	int		length_buffy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	length_line = ft_strlen(line);
	length_buffy = ft_strlen(buffy);
	if (!line || !buffy)
		return (NULL);
	new_line = malloc(sizeof(char) * (length_line + length_buffy + 1));
	if (!new_line)
		return (NULL);
	while (line[i] != '\0')
		new_line[i++] = line[j++];
	j = 0;
	while (buffy[j] != '\0')
		new_line[i++] = buffy[j++];
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

size_t	trim_buffy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (dstsize == 0)
		return (len);
	while (i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	return (len);
}

// read_and_save : reads a file and calls strjoin to save them

char *get_next_line(int fd)
{
	static char	buffy[BUFFER_SIZE + 1];
	int 		is_read;
	int 		i;
	char 		*line;
	
	i = 0;
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (0);
	is_read = 1;
	while (checkchar(buffy) == 0 && is_read > 0)
	{
		is_read = read(fd, buffy, BUFFER_SIZE);
		line = ft_strjoin(line, buffy);
	}
	i = checkchar(buffy);
	trim_buffy(buffy, &buffy[i + 1], ft_strlen(&buffy[i + 1]) + 1);
	return (line);
}

// char *get_next_line(int fd)
// {
// 	char *line;

// 	line = read_and_save(fd);
// 	return (line);
// }

int	main(void)
{
	int fd;
	int	i;

	i = 0;
	fd = open("text.txt", O_RDONLY);
	while(i < 10)
	{
		printf("GNL[%d]: %s\n", i, get_next_line(fd));
		i++;
	}
}
