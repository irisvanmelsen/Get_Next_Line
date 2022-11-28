/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:33:01 by ivan-mel          #+#    #+#             */
/*   Updated: 2022/11/28 15:24:34 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  #define BUFFER_SIZE 10

//checkchar : this function checks whether we are at the end of a line (\n) or not each time you run it

int checkchar(char *buffy)
{
	int i;

	i = 0;
	while (buffy[i] != '\0')
	{
		if (buffy[i] == '\n')
			return (1);
		i++;
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

char *nextline(char *line)
{
	int	i;
	char *str;

	i = 0;
	if (!line)
		return (NULL);
	if (line[i] != '\0' && line[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (free(line), NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (free(line), str);
}

// strjoin : joins two strings together as a third new string

char	*ft_strjoin(char *line, char const *buffy)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!line || !buffy)
		return (NULL);
	new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffy) + 1));
	if (!new_line)
		return (free(line), NULL);
	while (line[i] != '\0')
		new_line[i++] = line[j++];
	j = 0;
	while (buffy[j] != '\n' && buffy[j] != '\0')
		new_line[i++] = buffy[j++];
	if (buffy[j] == '\n')
	{
		new_line[i] = '\n';
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

void	trim_buffy(char *buffy)
{
	size_t	before;
	size_t	after;

	before = 0;
	after = 0;
	while (buffy[before] != '\n' && buffy[before] != '\0')
		before++;
	if (buffy[before] == '\0')
	{
		buffy[0] = '\0';
		return ;
	}
	before++;
	while (buffy[before])
	{
		buffy[after] = buffy[before];
		after++;
		before++;
	}
	buffy[after] = '\0';
}

char *get_next_line(int fd)
{
	static char	buffy[BUFFER_SIZE + 1];
	int 		is_read;
	int 		i;
	char 		*line;

	i = 0;
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (checkchar(buffy) != 1)
	{
		if (*buffy != '\0')
			line = ft_strjoin(line, buffy);
		if (!line)
			return (NULL);
		is_read = read(fd, buffy, BUFFER_SIZE);
		if (is_read < BUFFER_SIZE)
		{
			if (is_read == -1 || (is_read == 0 && *line == '\0'))
			{
				buffy[0] = '\0';
				return (free(line), NULL);
			}
			buffy [is_read] = '\0';
			line = ft_strjoin(line, buffy);
			if (!line)
				return (NULL);
			trim_buffy(buffy);
			return (line);
		}
	}
	line = ft_strjoin(line, buffy);
	if (!line)
		return (NULL);
	trim_buffy(buffy);
	// line = nextline(line);
	// free(line);
	return (line);
}

// int	main(void)
// {
// 	char *line;
// 	int fd;
// 	int	i;

// 	i = 0;
// 	fd = open("text.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	// while(line)
// 	// {
// 	// 	printf("%s", line);
// 	// 	line = get_next_line(fd);
// 	// 	i++;
// 	// }
// 	close(fd);
// }