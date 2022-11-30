/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:33:01 by ivan-mel          #+#    #+#             */
/*   Updated: 2022/11/30 17:15:49 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  #define BUFFER_SIZE 10

// checkchar: 
// this goes through 'buffy' to find out whether it has a
// '\0' (terminating character) or '\n' (new line) in the line.
// it basically returns a true (1) or false (0)
// depending on whether there is a '\n' or not. */

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

// strlen:
// checks whether the string exists. If the string does exist then
// it will return the length of the string, otherwise it returns 0.

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	if (!s)
		return (0);
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

// strjoin:
// joins two strings together as a third new string.
// the function checks whether the line and the buffer exist
// if it exists it will then allocate enough memory for both of them (malloc)
// then it makes new string called new_line equal to line by itterating through
// it afterwards it does the same with the buffer as long as there
// is no terminating '\0' character or new line '\n' character
// if buffy is at a new line then we have to make sure we copy it
// correctly by also adding a '\n' to our new_line after
// which we end with a terminating character '\0'

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

// trim_buffy:
// this function itterates through buffy until it either reaches
// a '\n' new line or a '\0' terminating character
// if it is a terminating character then buffy should be
// at the end therefore we are adding a '\0' as well
// if we go out of the while loop because we have a 
// '\n' then we should + once more to add space for the
// '\0' terminating character that comes afterwards
// then we make a buffer[after] which is equal to our
// previous buffer up until it reached the '\0' or '\n'

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

// trim_malloc:
// this functions is similar to trim buffy but it trims
// malloc instead to make sure that you don't allocate too
// much memory which can lead to memory leaks
// this is done by allocating space for the length of the line
// and making extra space for the terminating character '\0'
// then we say that the char result is equal to the line
// and finally add the terminating '\0' character

char	*trim_malloc(char *line)
{
	char *result;
	int	length;
	int	i;
	int	j;

	i = 0;
	j = 0;
	length = ft_strlen(line);
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (free(line), NULL);
	while (line[j])
	{
		result[i] = line[j];
		i++;
		j++;
	}
	result[i] = '\0';
	free(line);
	return (result);
}

// ft_calloc:
// this function allocates a specified amount of
// memory and then initialize it to zero
// it is similar to malloc but malloc does not initialize it to zero
// we do this by making sure we allocate enough space through malloc
// then we continue until to do so until i is equal to our count * size

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	str = malloc(count * size);
	i = 0;
	if (!str)
		return (str);
	while (i < (count * size))
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

// get_next_line:
// this function allocates space for our BUFFER_SIZE
// we say line is equal to the line and buffy as long
// as buffy exists, afterwards we check whether there is
// a new line '\n' character in buffy or not
// if it is not then we continue in the while loop which 
// reads the amount of BUFFER_SIZE from the file and
// joins the buffer to the line by calling ft_strjoin
// whe there is no line or we read zero or less then
// the function will return 0
// if there is a new line then we have to trim buffy
// and afterwards trim malloc so we don't have too
// much space allocated, at last we can return the line

char *get_next_line(int fd)
{
	static char	buffy[BUFFER_SIZE + 1];
	char 		*line;
	int 		is_read;

	line = calloc(sizeof(BUFFER_SIZE + 1), 1);
	if (*buffy != '\0')
		line = ft_strjoin(line, buffy);
	while (checkchar(buffy) != 1 && line)
	{
		is_read = read(fd, buffy, BUFFER_SIZE);
		if (is_read == -1 || (is_read == 0 && *line == '\0'))
			return (buffy[0] = '\0', free(line), NULL);
		buffy [is_read] = '\0';
		line = ft_strjoin(line, buffy);
		if (!line)
			return (NULL);
		if (is_read < BUFFER_SIZE)
			break ;
	}
	if (!line)
		return (NULL);
	trim_buffy(buffy);
	line = trim_malloc(line);
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