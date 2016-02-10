/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdruta <vdruta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 16:19:54 by vdruta            #+#    #+#             */
/*   Updated: 2016/02/10 21:29:01 by vdruta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	ft_set_level_0_to_start(int start, int **level, int vertices)
{
	int k;

	k = 0;
	while (k < vertices)
	{
		level[start][k] = 0;
		k++;
	}
}

void	ft_recreate_que_with_adjacent_vertices_with_last_level_set(int *que, int **level, int lvl)
{
	int i;
	int j;

	i = 0;
	while (i < 9)
	{
		que[i] = 9;
		i++;
	}
	i = 0;
	j = 0;
	while (i < 9)
	{
		if (level[i][0] == lvl)
		{
			que[j] = i;
			j++;
		}
		i++;
	}
}

void	ft_find_adjacent_vertices_with_no_level_set(int *que, int **imap, int **level, int **parent, int vertices, int lvl)
{
	int start;
	int j;
	int k;
	int w;

	w = 0;
	while (que[w] != 9)
	{
		start = que[w];
		j = 0;
		while (j < vertices)
		{
			if (imap[start][j] == 1 && level[j][0] == 9)
			{
				k = 0;
				while (k < vertices)
				{
					level[j][k] = lvl;
					parent[j][k] = start;
					k++;
				}
			}
			j++;
		}
		w++;
	}
}

void	ft_print_int_matrix(int **imap, int vertices)
{
	int i;
	int j;

	i = 0;
	while (i < vertices)
	{
		j = 0;
		ft_putnbr(i);
		ft_putstr(": ");
		while (j < vertices)
		{
			ft_putnbr(imap[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	ft_putendl("--------------");
}

int		main()
{
	int		fd;
	char	*line;
	int		vertices;
	char	**map;
	char	**temp;
	int		**imap;
	int		**level;
	int		**parent;
	int		i;
	int		j;

	fd = open("in", O_RDONLY);
	ft_get_next_line(fd, &line);
	vertices = ft_atoi(line);
	map = (char**)malloc(sizeof(*map) * 13);
	i = 0;
	while (ft_get_next_line(fd, &line))
	{
		map[i] = line;
		i++;
	}
	map[i] = 0;
	//create adjency matrix
	imap = (int**)malloc(sizeof(*imap) * vertices);
	i = 0;
	while (i < vertices)
	{
		imap[i] = (int*)malloc(sizeof(int) * vertices);
		i++;
	}
	//initialize adjency matrix values to 0
	i = 0;
	while (i < vertices)
	{
		j = 0;
		while (j < vertices)
		{
			imap[i][j] = 0;
			j++;
		}
		i++;
	}
	//connect the vertices
	i = 0;
	while (map[i])
	{
		temp = ft_strsplit(map[i], ' ');
		imap[ft_atoi(temp[0])][ft_atoi(temp[1])] = 1;
		imap[ft_atoi(temp[1])][ft_atoi(temp[0])] = 1;
		i++;
	}

	//print adjacency matrix
	ft_print_int_matrix(imap, vertices);

	//create level matrix
	level = (int**)malloc(sizeof(*level) * vertices);
	i = 0;
	while (i < vertices)
	{
		level[i] = (int*)malloc(sizeof(int) * vertices);
		i++;
	}
	i = 0;
	while (i < vertices)
	{
		j = 0;
		while (j < vertices)
		{
			level[i][j] = vertices;
			j++;
		}
		i++;
	}
	//	ft_print_int_matrix(level, vertices);
	//create parent matrix
	parent = (int**)malloc(sizeof(*parent) * vertices);
	i = 0;
	while (i < vertices)
	{
		parent[i] = (int*)malloc(sizeof(int) * vertices);
		i++;
	}
	i = 0;
	while (i < vertices)
	{
		j = 0;
		while (j < vertices)
		{
			parent[i][j] = vertices;
			j++;
		}
		i++;
	}
	//	ft_print_int_matrix(parent, vertices);
	// BFS : start 0 ; end 4
	int start;
	int end;
	int lvl;
	int que[vertices];


	start = 0;
	end = 4;
	ft_set_level_0_to_start(start, level, vertices);
	lvl = 1;
	i = 0;
	while (i < vertices)
	{
		que[i] = 9;
		i++;
	}
	que[0] = 0;

	while (que[0] != 9)
	{
		ft_find_adjacent_vertices_with_no_level_set(que, imap, level, parent, vertices, lvl);
		ft_recreate_que_with_adjacent_vertices_with_last_level_set(que, level, lvl);
		lvl++;
	}


	ft_print_int_matrix(level, vertices);
	ft_print_int_matrix(parent, vertices);

}
