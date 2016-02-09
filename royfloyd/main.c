/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdruta <vdruta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 13:29:10 by vdruta            #+#    #+#             */
/*   Updated: 2016/02/09 20:55:03 by vdruta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define BUFF_SIZE 2048
#include <sys/types.h>
#include <sys/stat.h>

void	ft_putchar_fd(char c, int fd)
{
	ssize_t i;

	i = write(fd, &c, 1);
	i++;
}

void	ft_putnbr_fd(int n, int fd)
{
	char	v[10];
	long	nb;
	int		i;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb == 0)
		ft_putchar_fd('0', fd);
	i = 0;
	while (nb > 0)
	{
		v[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		ft_putchar_fd(v[i], fd);
		i--;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		i;
	int		j;

	dst = (char*)malloc(sizeof(*dst) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
	{
		dst[i] = s1[j];
		j++;
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dst[i] = s2[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int		ft_atoi(const char *str)
{
	long	rez;
	int		rez2;
	int		s;
	int		i;

	i = 0;
	s = 1;
	rez = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rez = rez * 10 + str[i] - '0';
		i++;
	}
	rez2 = rez * s;
	return (rez2);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	if (!(dst = (char*)malloc(sizeof(*dst) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int		ft_parts_nr(char const *s, char c)
{
	int i;
	int cnt;
	int	part;

	i = 0;
	cnt = 0;
	part = 0;
	while (s[i])
	{
		if (s[i] == c && part == 1)
			part = 0;
		if (s[i] != c && part == 0)
		{
			part = 1;
			cnt++;
		}
		i++;
	}
	return (cnt);
}

static int		ft_part_len(char const *s, char c, int i)
{
	int len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**map;
	int		i;
	int		j;
	int		parts;

	parts = ft_parts_nr(s, c);
	if (!(map = (char**)malloc(sizeof(*map) * (parts + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (parts > 0)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		map[j] = ft_strsub(s, i, ft_part_len(s, c, i));
		j++;
		i = i + ft_part_len(s, c, i);
		parts--;
	}
	map[j] = 0;
	return (map);
}

int		**ft_get_int_map(char **map, int vertices)
{
	int 	i;
	int 	j;
	int		**imap;
	char	**temp;

	i = 0;
	imap = (int**)malloc(sizeof(*imap) * vertices);
	while (i < vertices)
	{
		imap[i] = (int*)malloc(sizeof(int) * vertices);
		temp = ft_strsplit(map[i], ' ');
		j = 0;
		while (j < vertices)
		{
			imap[i][j] = ft_atoi(temp[j]);
			j++;
		}
		i++;
	}
	return (imap);
}

void	ft_roy_floyd(int **imap, int vertices)
{
	int i;
	int j;
	int k;

	i = 0;
	while (i < vertices)
	{
		j = 0;
		while (j < vertices)
		{
			k = 0;
			while (k < vertices)
			{
				if (i != j && imap[i][k] && imap[k][j] && (imap[i][j] > imap[i][k] + imap[k][j] || !imap[i][j]))
					imap[i][j] = imap[i][k] + imap[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

static int		read_to_stock(int const fd, char **stock)
{
	char	*buff;
	int		ret;
	char	*temp;

	if (!(buff = (char *)malloc(sizeof(*buff) * (BUFF_SIZE + 1))))
		return (-1);
	ret = read(fd, buff, BUFF_SIZE);
	if (ret > 0)
	{
		buff[ret] = '\0';
		temp = ft_strjoin(*stock, buff);
		free(*stock);
		*stock = temp;
	}
	free(buff);
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char*)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char*)(s + i));
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	s2 = (char*)malloc(sizeof(*s2) * (i + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int				ft_get_next_line(int const fd, char **line)
{
	static char	*stock = NULL;
	char		*bn;
	int			ret;

	if ((!stock && (stock = (char *)malloc(sizeof(*stock))) == NULL) || !line
			|| fd < 0 || BUFF_SIZE < 0)
		return (-1);
	bn = ft_strchr(stock, '\n');
	while (bn == NULL)
	{
		ret = read_to_stock(fd, &stock);
		if (ret == 0)
		{
			if (ft_strlen(stock) == 0)
				return (0);
			stock = ft_strjoin(stock, "\n");
		}
		if (ret < 0)
			return (-1);
		else
			bn = ft_strchr(stock, '\n');
	}
	*line = ft_strsub(stock, 0, ft_strlen(stock) - ft_strlen(bn));
	stock = ft_strdup(bn + 1);
	return (1);
}

int		main()
{
	int		fd;
	char	*line;
	int		vertices;
	char 	**map;
	int		**imap;
	int		i;
	int		j;

	fd = open("royfloyd.in", O_RDONLY);
	ft_get_next_line(fd, &line);
	vertices = ft_atoi(line);
	map = (char**)malloc(sizeof(*map) * vertices + 1);
	i = 0;
	while (ft_get_next_line(fd, &line))
	{
		map[i] = line;
		i++;
	}
	map[i] = 0;
	close(fd);
	imap = ft_get_int_map(map, vertices);
	ft_roy_floyd(imap, vertices);
	fd = open("royfloyd.out", O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWUSR);
	i = 0;
	while (i < vertices)
	{
		j = 0;
		while (j < vertices)
		{
			ft_putnbr_fd(imap[i][j], fd);
			ft_putchar_fd(' ', fd);
			j++;
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
	close(fd);
	return (0);
}
