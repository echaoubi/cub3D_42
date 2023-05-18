/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:44:14 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 18:44:51 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_map(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->map.height)
	{
		x = -1;
		while (++x < vars->map.width)
			draw_tile(vars, y, x);
	}
}

void	draw_tile(t_vars *vars, int y, int x)
{
	int			i;
	int			j;
	uint32_t	c_w;
	uint32_t	c_g;
	uint32_t	c_b;

	i = -1;
	c_w = create_color(255, 255, 255, 255);
	c_g = create_color(160, 60, 60, 255);
	c_b = create_color(66, 6, 156, 255);
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			if (vars->map.map[y][x] == 500)
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, c_b);
			else if (vars->map.map[y][x] > 0)
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, c_g);
			if ((j == 15 || i == 15))
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, c_w);
		}
	}
}

void	draw_aim(t_vars *vars)
{
	put_line(512, 506, 512, 519, create_color(0, 255, 0, 255), \
			vars->img->width, vars->img->height);
	put_line(506, 512, 519, 512, create_color(0, 255, 0, 255), \
			vars->img->width, vars->img->height);
}

void	draw_wal7(t_vars *vars, int r, int lineH, int32_t color)
{
	int		i;
	int		y;
	int		x1;
	int		y1;
	double	ligne_offset;

	i = 0;
	x1 = r * 2 + 513;
	y1 = 220 - lineH / 2;
	ligne_offset = 220 - lineH / 2;
	while (i < 2)
	{
		y = y1;
		while (y <= lineH + (int)ligne_offset)
		{
			mlx_put_pixel(vars->img, x1 - i, y, color);
			y++;
		}
		i++;
	}
}

void	draw_one_sprite_norm(t_vars *vars, t_sp *sp, int frame, int i)
{
	sp->porce_angle = (sp->porce_angle + 30) / 60 * 512;
	sp->v_dist = distance_to_wall(vars->player.x, \
	vars->player.y, sp->sprite_ax, sp->sprite_ay);
	sp->line_height = (64 * 600) / sp->v_dist;
	draw_the_sprite(vars, (int)sp->porce_angle, sp->v_dist, \
	sp->line_height, frame, vars->sprites[i].path);
}