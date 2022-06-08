/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:23:25 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 20:43:02 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_rays_3d(t_game *game)
{
	for(int rayon_x = 0; rayon_x < SCREEN_WIDTH; rayon_x++)
    {
		//calculate ray position and direction
		double cameraX = 2 * rayon_x / (double) SCREEN_WIDTH - 1;		//x-coordinate in camera space
		double rayDirX = game->dir_x + game->plane_x * cameraX;
		double rayDirY = game->dir_y + game->plane_y * cameraX;

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
		ft_rotate_camera(game, ROTATION_SPEED);
		draw_all((t_game*) data);
	}
	if (game->key_d)
	{
		ft_rotate_camera(game, -ROTATION_SPEED);
		draw_all((t_game*) data);
	}
	if (game->key_w)
	{
		if (!ft_iswall(game, (int) (game->player_x + game->dir_x * MOVE_SPEED), (int)game->player_y))
			game->player_x += game->dir_x * MOVE_SPEED;
		if (!ft_iswall(game, (int)game->player_x, (int) (game->player_y + game->dir_y * MOVE_SPEED)))
			game->player_y += game->dir_y * MOVE_SPEED;
		draw_all((t_game*) data);
	}
	if (game->key_s)
	{
		if (!ft_iswall(game, (int) (game->player_x - game->dir_x * MOVE_SPEED), (int)game->player_y))
			game->player_x -= game->dir_x * MOVE_SPEED;
		if (!ft_iswall(game, (int)game->player_x, (int) (game->player_y - game->dir_y * MOVE_SPEED)))
			game->player_y -= game->dir_y * MOVE_SPEED;
		draw_all((t_game*) data);
	}
	return (0);
}

void draw_all(t_game *game)
{
	// ft_rect(game->img, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x00000000);
	draw_rays_3d(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
}

// Change vector angle relative to NSEW (Config file)
// Check de la bonne direction des textures
// Movement < > for move camera & WSAD for move player in space

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
	
	game = ft_init_game();
	if (!game)
	{
		ft_error("Game allocation error\n");
		return (-2);
	}
	
	if (ft_init_mlx(game) != 1)
	{
		ft_error("Mlx initialisation error\n");
		ft_free_game(game);
		return (-3);
	}
	
	if (ft_init_global(game, av[1])!= 1)
	{
		ft_free_game(game);
		return (-4);
	}

	mlx_hook(game->mlx_win, 2, 1L << 0, ft_event_keydown, game);
	mlx_hook(game->mlx_win, 3, 1L << 0, ft_event_keyup, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
	draw_all(game);
	mlx_loop(game->mlx);

	return (0);
}
