/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:23:25 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/07 16:28:04 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double dirX = -1, dirY = 0; 						//initial direction vector
double planeX = 0, planeY = 0.66;					//the 2d raycaster version of camera plane

t_texture	*get_texture(t_game *game, int direction)
{
	switch (direction)
	{
		case NORTH: return (game->north);
		case SOUTH: return (game->south);
		case EAST: return (game->east);
		case WEST: return (game->west);
	}
	return (NULL);
}

int	get_direction(int side, int step)
{
	// North or South
	if (side == 0)
		return (step > 0 ? SOUTH : NORTH);
	// West or East
	if (side == 1)
		return (step > 0 ? EAST : WEST);
	return (-1);
}

char	ft_getcaracter(t_game *game, int x, int y)
{
	if (y < 0 || y >= ft_strs_len(game->map))
		return (-1);
	if (x < 0 || x >= ft_strlen(game->map[y]))
		return (-2);
	return (game->map[y][x]);
}

int		ft_iswall(t_game *game, int x, int y)
{
	return (ft_getcaracter(game, x, y) == '1');
}

void draw_rays_3d(t_game *game)
{
	for(int rayon_x = 0; rayon_x < SCREEN_WIDTH; rayon_x++)
    {
		//calculate ray position and direction
		double cameraX = 2 * rayon_x / (double) SCREEN_WIDTH - 1;		//x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		//which box of the map we're in
		int mapX = (int) game->player_x;
		int mapY = (int) game->player_y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player_x) * deltaDistX;
		}
		
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player_y) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (ft_iswall(game, mapX, mapY)) hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		// sky
		for (int i = 0; i < drawStart; i++)
			ft_pixel(game->img, rayon_x, i, game->ceil); // 0xf852e8
		// ground
		for (int i = drawEnd; i < drawEnd + SCREEN_HEIGHT; i++) // SCREEN_HEIGHT
		{
			ft_pixel(game->img, rayon_x, i, game->floor); //0x984beeSCREEN_HEIGHT
		}
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = game->player_y + perpWallDist * rayDirY;
		else           wallX = game->player_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		t_texture *tex = get_texture(game, get_direction(side, side == 0 ? stepX : stepY));

		//x coordinate on the texture
		int texX = (int) (wallX * (double) tex->width);
		if(side == 0 && rayDirX > 0) texX = tex->width - texX - 1;
		if(side == 1 && rayDirY < 0) texX = tex->width - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * tex->height / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			int texY = texPos;
			texPos += step;
			int color = ft_pixel_color(tex->data, texX, texY);
			
			ft_pixel(game->img, rayon_x, y, color);
		}
	}
}

int render_next_frame(void *data)
{
	t_game		*game;

	game = (t_game*) data;
	if (game->key_a)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(ROTATION_SPEED) - dirY * sin(ROTATION_SPEED);
		dirY = oldDirX * sin(ROTATION_SPEED) + dirY * cos(ROTATION_SPEED);
		double oldPlaneX = planeX;
		planeX = planeX * cos(ROTATION_SPEED) - planeY * sin(ROTATION_SPEED);
		planeY = oldPlaneX * sin(ROTATION_SPEED) + planeY * cos(ROTATION_SPEED);
		draw_all((t_game*) data);
	}
	if (game->key_d)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(-ROTATION_SPEED) - dirY * sin(-ROTATION_SPEED);
		dirY = oldDirX * sin(-ROTATION_SPEED) + dirY * cos(-ROTATION_SPEED);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-ROTATION_SPEED) - planeY * sin(-ROTATION_SPEED);
		planeY = oldPlaneX * sin(-ROTATION_SPEED) + planeY * cos(-ROTATION_SPEED);
		draw_all((t_game*) data);
	}
	if (game->key_w)
	{
		if (!ft_iswall(game, (int) (game->player_x + dirX * MOVE_SPEED), (int)game->player_y))
			game->player_x += dirX * MOVE_SPEED;
		if (!ft_iswall(game, (int)game->player_x, (int) (game->player_y + dirY * MOVE_SPEED)))
			game->player_y += dirY * MOVE_SPEED;
		draw_all((t_game*) data);
	}
	if (game->key_s)
	{
		if (!ft_iswall(game, (int) (game->player_x - dirX * MOVE_SPEED), (int)game->player_y))
			game->player_x -= dirX * MOVE_SPEED;
		if (!ft_iswall(game, (int)game->player_x, (int) (game->player_y - dirY * MOVE_SPEED)))
			game->player_y -= dirY * MOVE_SPEED;
		draw_all((t_game*) data);
	}
	return (0);
}

void draw_all(t_game *game)
{
	ft_rect(game->img, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x00000000);
	draw_rays_3d(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
}

int	init_parameters(t_game *game, char *content)
{
	if (ft_read_parameters(game, content) != 1)
	{
		ft_error("Parameters read error\n");
		return (-1);
	}
	return (1);
}

int	init_map(t_game *game, char *content)
{
	game->map = ft_strs_alloc();
	if (!game->map)
	{
		ft_error("Map allocation error\n");
		return (-1);
	}
	if (ft_read_map(game, content) != 1)
	{
		ft_error("Map read error\n");
		ft_strs_free(&game->map);
		return (-1);
	}
	return (1);
}

int	init_global(t_game *game, char *file)
{
	char	*content;
	
	content = ft_read_file(file);
	if (content == NULL)
	{
		ft_error("File read error\n");
		return (0);
	}
	if (init_parameters(game, content) != 1)
	{
		free(content);
		return (-1);
	}
	if (init_map(game, content) != 1)
	{
		free(content);
		return (-2);
	}
	free(content);
	return (1);
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cat3d");
	if (!game->mlx_win)
		return (-1);
	game->img = malloc(sizeof(t_data));
	if (!game->img)
		return (-2);
	game->img->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img->img)
		return (-2);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bits_per_pixel, &game->img->line_length,
									  &game->img->endian);
	if (!game->img->addr)
		return (-2);
	
	return (1);
}

t_game	*init_game()
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
	game->img = 0;
	game->map = 0;
	game->mlx = 0;
	game->mlx_win = 0;
	game->north = 0;
	game->south = 0;
	game->east = 0;
	game->west = 0;
	game->key_a = 0;
	game->key_d = 0;
	game->key_w = 0;
	game->key_s = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->player_position_set = 0;
	game->floor = -1;
	game->ceil = -1;
	return (game);
}

// Error dans stderr
// Check for closed map
// Free game structure
// Change vector angle relative to NSEW (Config file)
// Check de la bonne direction des textures
// Movement < > for move camera & WSAD for move player in space
// Norm

int	check_filename(char *filename)
{
	int	i;

	i = ft_strlen(filename);
	if (i < 4)
		return (0);
	return (filename[i - 1] == 'b' && filename[i - 2] == 'u' &&
			filename[i - 3] == 'c' && filename[i - 4] == '.');
}

int main(int ac, char **av)
{
	t_game	*game;
	(void) ac;
	(void) av;

	if (ac != 2)
	{
		ft_error("The program must only have the map file path in first argument\n");
		return (0);
	}

	if (!check_filename(av[1]))
	{
		ft_error("The map filename must have .cub extension");
		return (-1);
	}
	
	game = init_game();//malloc(sizeof(t_game));
	if (!game)
	{
		ft_error("Game allocation error\n");
		return (-2);
	}
	
	if (init_mlx(game) != 1)
	{
		ft_error("Mlx initialisation error\n");
		//TODO free game structure
		return (-3);
	}
	
	if (init_global(game, av[1])!= 1)
	{
		//TODO free game structure
		return (-4);
	}

	//both camera direction and camera plane must be rotated
	// double rot = WEST_RADIANS;
	// double oldDirX = dirX;

	// dirX = dirX * cos(rot) - dirY * sin(rot);
	// dirY = oldDirX * sin(rot) + dirY * cos(rot);
	// double oldPlaneX = planeX;
	// planeX = planeX * cos(rot) - planeY * sin(rot);
	// planeY = oldPlaneX * sin(rot) + planeY * cos(rot);
	
	mlx_hook(game->mlx_win, 2, 1L << 0, ft_event_keydown, game);
	mlx_hook(game->mlx_win, 3, 1L << 0, ft_event_keyup, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
	draw_all(game);
	mlx_loop(game->mlx);

	
	return (0);
}
