/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:33:01 by ivan-mel          #+#    #+#             */
/*   Updated: 2022/11/24 17:06:54 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//checkchar : this function checks whether we are at the end of a line (\n) or not each time you run it

int checkchar(char *buffy)
{
	int i;

	i = 0;
	while (buffy[i] != '\0')
	{
		i++;
		if (buffy[i] == '\n')
			return (1);
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
	if (!line)
	{
		line = malloc(sizeof(char) * (1));
		line[0] = '\0';
	}
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

void	trim_buffy(char *buffy)
{
	size_t	before;
	size_t	after;

	before = 0;
	after = 0;
	if (buffy[before] == '\0')
		return ;
	while (buffy[before] != '\n')
		before++;
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
	line[0] = '\0';
	if (!line || fd < 0)	
		return (NULL);
	is_read = 1;
	while (checkchar(buffy) != 1 && is_read > 0)
	{
		is_read = read(fd, buffy, BUFFER_SIZE);
		if (is_read < BUFFER_SIZE)
		{
			if (is_read == -1 || (is_read == 0 && *line == '\0'))
				return (free(line), NULL);
			buffy [is_read] = '\0';
			line = ft_strjoin(line, buffy);
			return (line);
		}
	line = ft_strjoin(line, buffy);
	}
	trim_buffy(buffy);
	free(line);
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
// 	while(line)
// 	{
// 		printf("%s", line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// }