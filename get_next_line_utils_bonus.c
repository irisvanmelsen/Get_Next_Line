/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:29:28 by ivan-mel          #+#    #+#             */
/*   Updated: 2022/12/05 13:29:31 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// checkchar: 
// this goes through 'buffy' to find out whether it has a
// '\0' (terminating character) or '\n' (new line) in the line.
// it basically returns a true (1) or false (0)
// depending on whether there is a '\n' or not. */

int	checkchar(char *buffy)
{
	int	i;

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
