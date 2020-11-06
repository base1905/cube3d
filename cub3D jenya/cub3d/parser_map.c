/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:56:15 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/18 18:56:38 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				check_map_symbols(t_all *all)
{
	int				y;
	int				x;

	y = -1;
	while (all->map.map[++y])
	{
		x = -1;
		while (all->map.map[y][++x])
		{
			if (0 != ft_strchr("02NSEW", all->map.map[y][x]))
			{
				if (y == 0 || x == 0 || y == all->map.max_y - 1 || x == all->map.max_x - 1)
					put_error("Error\n	--Not valid map--\n", all);
				if (0 == ft_strchr("102NSEW", all->map.map[y - 1][x]))
					put_error("Error\n	--Not valid map--\n", all);
				if (0 == ft_strchr("102NSEW", all->map.map[y][x - 1]))
					put_error("Error\n	--Not valid map--\n", all);
				if (0 == ft_strchr("102NSEW", all->map.map[y + 1][x]))
					put_error("Error\n	--Not valid map--\n", all);
				if (0 == ft_strchr("102NSEW", all->map.map[y][x + 1]))
					put_error("Error\n	--Not valid map--\n", all);
			}
		}
	}
}

void	ft_bspace(void *s, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = s;
	i = 0;
	while (i < n)
	{
		tmp[i] = ' ';
		i++;
	}
}

void		make_map(t_all *all, t_list *head)
{
	int		y;
	int		x;

	t_list	*tmp;

	y = 0;
	tmp = head;
	while (all->map.map[y])
	{
		ft_strcpy(all->map.map[y], tmp->content);
		x = -1;
		while (++x < all->map.max_x)
		{
			if (!all->map.map[y][x])
				all->map.map[y][x] = ' ';
			// printf("%c", all->map.map[y][x]);
		}
		// printf("|\n");
		all->map.map[y][all->map.max_x] = '\0';
	//	all->map.map[y] = ft_strdup(tmp->content);
		tmp = tmp->next;
		y++;
	}
}

void		init_map(t_all *all)
{
	// int		x;
	int		y;

	if (!(all->map.map = (char **)malloc(sizeof(char *) * (all->map.max_y + 1))))
		put_error("Error\n	--Malloc error--\n", all);
	all->map.map[all->map.max_y] = NULL;
	y = -1;
	while (++y < all->map.max_y)
	{
		if (!(all->map.map[y] = (char *)malloc(sizeof(char) * (all->map.max_x + 1))))
			put_error("Error\n	--Malloc error--\n", all);
		ft_bspace(all->map.map[y], all->map.max_x);
		all->map.map[y][all->map.max_x] = '\0';
	}
}

void		get_map(t_all *all, int *fd)
{
	int		len_x;
	char	*read_line;
	t_list	*head = NULL;

	get_next_line(*fd, &read_line);
	while (ft_strlen(read_line) == 0)
	{
		free(read_line);
		read_line = NULL;
		get_next_line(*fd, &read_line);
	}
	while ((len_x = ft_strlen(read_line)) > 0)
	{
		all->map.max_y++;
		if (all->map.max_x < len_x)
			all->map.max_x = len_x;
		// printf("%s\n",read_line);
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(read_line)));
		// printf("%s\n",read_line);
		free(read_line);
		read_line = NULL;
		get_next_line(*fd, &read_line);
	}
	// ft_lstadd_back(&head, ft_lstnew("\0"));
	free(read_line);
	read_line = NULL;
	init_map(all);
	make_map(all, head);
	// free(head);
	ft_lstclear(&head, free);
	// printf("%s\n",head->content);
}

void		parser_map(int *fd, t_all *all) 
{
	get_map(all, fd);
	close(*fd);
	check_map_symbols(all);
	// printf("%s\n",all->head->content);
}