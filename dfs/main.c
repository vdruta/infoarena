/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdruta <vdruta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 16:19:54 by vdruta            #+#    #+#             */
/*   Updated: 2016/02/17 15:40:08 by vdruta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int		ft_stack_pop(int *stack, int *vertices)
{
	int s;

	(*vertices)--;
	s = stack[(*vertices)];
	return (s);
}

void	ft_stack_push(int i, int *stack, int *vertices)
{
	(*vertices)++;
	stack[(*vertices - 1)] = i;
}

void	ft_mark_visited(int **visited, int i)
{
	visited[i][0] = 1;
}

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

void	ft_find_roads(int i, int **visited, int **imap, int **parent, int vertices, int end, int start, t_list **list)
{
	int j;
	int k;
	int route[vertices];
	int e;

	j = 0;
	visited[i][0] = 1;
	while (j < vertices)
	{
		if (imap[i][j] == 1 && visited[j][0] == 0)
		{
			parent[j][0] = i;
			if (j == end)
			{
				ft_putstr("parents:\n");
				k = 0;
				while (k < vertices)
				{
					route[k] = vertices;
					k++;
				}
				k = vertices - 2;
				route[vertices - 1] = j;
				e = end;
				while (e != start) 
				{
					route[k] = parent[e][0];
					e = route[k];
					k--;
				}
				k = 0;
				while (k < vertices)
				{
					if (route[k] != vertices)
						ft_putnbr(route[k]);
					k++;
				}
				ft_putendl("");
			}
			ft_find_roads(j, visited, imap, parent, vertices, end, start);
		}
		j++;
	}
	visited[i][0] = 0;
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
	int		**visited;
	int		**parent;
	int		i;
	int		j;

	fd = open("in2", O_RDONLY);
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
	visited = (int**)malloc(sizeof(*visited) * vertices);
	i = 0;
	while (i < vertices)
	{
		visited[i] = (int*)malloc(sizeof(int) * vertices);
		i++;
	}
	i = 0;
	while (i < vertices)
	{
		j = 0;
		while (j < vertices)
		{
			visited[i][j] = 0;
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
	int stack[vertices];
	int s;
	t_list *list;

	start = 0;
	end = 9;
	list = NULL;

	ft_find_roads(start, visited, imap, parent, vertices, end, start, &list);
	/*	ft_find_roads(i)
		{
		visited[i][0] = 1;

		}


		i = 0;
		while (i < vertices)
		{
		stack[i] = 9;
		i++;
		}

		vertices = 0;
		stack[0] = start;
		vertices++;

		while (stack[0] != 9)
		{
		s = ft_stack_pop(stack, &vertices);
		ft_putnbr(s);
		i = 0;
		while (i < 9)
		{
		if (imap[s][i] == 1 && visited[i][0] == 9)
		{
		ft_stack_push(i, stack, &vertices);
		ft_mark_visited(visited, i);
		}
		i++;
		}

		}
	 */
	//ft_print_int_matrix(visited, vertices);
	//ft_print_int_matrix(parent, vertices);

}
