/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:24:59 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/13 22:51:27 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}

int	endline_search(char *stock)
{
	int	i;

	i = 0;
	while (stock[i])
	{
		if (stock[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char *read_and_stock(int fd, char *stock)
{
	int		rd;
	char	*buff;

	rd = 0;
	while (endline_search(stock) == -1)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd <= 0)
		{
			free(buff);
			break ;
		}
		buff[rd] = '\0';
		stock = ft_strjoin(stock, buff);
		free(buff);
	}
	return (stock);
}

char	*restart(char **stock)
{
	char	*tmp;

	tmp = *stock;
	if (!tmp || tmp[0] == '\0')
		return (NULL);
	tmp = ft_strdup(*stock);
	free(*stock);
	*stock = NULL;
	return (tmp);
}

char	*ft_rest(char *stock, int start)
{
	char *rest;
	int	i;

	rest = malloc(sizeof(char) * (ft_strlen(stock) - start));
	start++;
	i = 0;
	while (stock[start + i])
	{
		rest[i] = stock[start + i];
		i++;
	}
	rest[i] = '\0';
	return (rest);
}

char	*create_line(char **stock)
{
	char	*line;
	char	*tmp;
	char	*rest;
	int		end;
	int		i;

	end = endline_search(*stock);
	line = malloc(sizeof(char) * (end + 2));
	tmp = *stock;
	i = 0;
	while (i <= end)
	{
		line[i] = tmp[i];
		i++;
	}
	line[i] = '\0';
	rest = ft_rest(*stock, end);
	free(*stock);
	*stock = rest;
	return (line);
}

char	*get_next_line(int fd)
{
	static char *stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stock)
		stock = ft_strdup("");
	stock = read_and_stock(fd, stock);
	if (endline_search(stock) == -1)
		return (restart(&stock));
	line = create_line(&stock);
	return (line);
}
#include<stdio.h>
#include<fcntl.h>
int main()
{
	int fd = open("text.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}