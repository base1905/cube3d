/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:46:55 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 14:11:19 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <fcntl.h>
#include <errno.h>

#include "libft/libft.h"
#include "gnl/get_next_line.h"


typedef struct  s_all 
{
    int         fd;
    char        *line;
    char        *allmap;
    int         bmp;
    int         screen_x;
    int         screen_y;
    int         map_height;
    int         map_width;
    char        **map_array;
    
}               t_all;


#endif