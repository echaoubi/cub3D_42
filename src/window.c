
#include "../inc/cub3d.h"

void draw_map(t_vars *vars)
{
	int x;
	int y;

	y = -1;
	while (++y < vars->map.height)
	{
		x = -1;
		while (++x < vars->map.width)
			draw_tile(vars, y, x);
	}
}

void clean_window(t_vars *vars)
{
	for (int y = 0; y < 1024; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			mlx_put_pixel(vars->img, y, x, create_color(255, 164, 66, 255 - (y) / 6));
		}
	}

	for (int y = 0; y < 1024; y++)
	{
		for (int x = 512; x < 1024; x++)
		{
			mlx_put_pixel(vars->img, y, x, create_color(50, 255, 125, 255 - (y) / 4));
		}
	}
}

void draw_tile(t_vars *vars, int y, int x)
{
	int i;
	int j;
	uint32_t color_black = create_color(0, 0, 0, 255);
	uint32_t color_white = create_color(255, 255, 255, 255);
	uint32_t color_grey = create_color(160, 60, 60, 255);
	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			// mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, color_black);
			if (g_map[y][x])
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, color_grey);
			if (j == 15 || i == 15)
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, color_white);
		}
	}
}

void redraw(t_vars *vars)
{
	// static int frame =1;
	static int frame =1;
	char *str=ft_strjoin("./src/textures/lol/",ft_itoa(frame));
	str=ft_strjoin(str,".png");
	// printf("%s\n",str);
	mlx_delete_image(g_vars->mlx,g_vars->weapon_img);
	g_vars->weapon_texture  = mlx_load_png(str);
	g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, g_vars->weapon_texture);
	clean_window(vars);
	draw_ray(vars);
	draw_partcle(vars);
	draw_map(vars);
	mlx_image_to_window(vars->mlx,vars->weapon_img,50,257);
	mlx_delete_texture(g_vars->weapon_texture);
	
	frame++;
	if(frame ==59)
		frame =1;
	free(str);
}

void render_window(t_vars *vars)
{
	int width;
	int height;

	width = vars->window_info.width;
	height = vars->window_info.height;
	vars->mlx = mlx_init(width, height, "cub3D", 1);
	g_vars->wall_texture  = mlx_load_png("./src/textures/wall_1.png");
	// g_vars->wall_img = mlx_texture_to_image(g_vars->mlx, g_vars->wall_texture);
	g_vars->weapon_texture  = mlx_load_png("./src/textures/StechkinEx1.png");
	g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, g_vars->weapon_texture);
	g_vars->wall_texture2  = mlx_load_png("./src/textures/wall_2.png");
	g_vars->wall_texture3  = mlx_load_png("./src/textures/wall_3.png");
	g_vars->wall_texture4  = mlx_load_png("./src/textures/wall_4.png");
	// g_vars->wall_img2 = mlx_texture_to_image(g_vars->mlx, g_vars->wall_texture);
	mlx_set_window_limit(vars->mlx, width - 200, height - 200, width, height);
	vars->img = mlx_new_image(vars->mlx, width, height);
	redraw(vars);
	mlx_set_cursor_mode(vars->mlx, vars->keyboard.cursor ? MLX_MOUSE_NORMAL : MLX_MOUSE_DISABLED);

	mlx_key_hook(vars->mlx, (mlx_keyfunc)key_press_handler, vars);
	
	mlx_cursor_hook(vars->mlx, (mlx_cursorfunc)mouse_handler, vars);
	mlx_image_to_window(vars->mlx, vars->img, 0, 0);
	mlx_loop_hook(vars->mlx,&loop_func,vars);
	mlx_loop(vars->mlx);
	
	mlx_terminate(vars->mlx);
}