/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:23:29 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/06 15:47:58 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include <mlx.h>
# include "math.h"
#include <fcntl.h>

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2

# define SCREEN_WIDTH 1080
# define SCREEN_HEIGHT 720

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define MOVE_SPEED 0.1
# define ROTATION_SPEED 0.1

# define PI 3.14159265359

# define NORTH_RADIANS PI
# define SOUTH_RADIANS 0
# define EAST_RADIANS PI / 2
# define WEST_RADIANS (3 * PI) / 2

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_game {
	void	*mlx_win;
	void	*mlx;
	t_data	*img;
	
	double	player_x;
	double	player_y;
	int		player_position_set;
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	int		key_a;
	int		key_d;
	int		key_w;
	int		key_s;
	char	**map;
}				t_game;

void	draw_all();
void	restore_map(int x1, int y1, int ray);

void	ft_pixel(t_data *data, int x, int y, int color);
void	ft_rect(t_data *data, int x, int y, int width, int height, int color);
void	ft_square(t_data *data, int x, int y, int x2, int y2, int color);
int		ft_pixels(int x, int y, int x2, int y2);
void	ft_line(t_data *data, int x, int y, float dx, float dy, float pixels, int color);
float	ft_dist(float ax, float ay, float bx, float by, float ang);
unsigned int	ft_pixel_color(void *image, int x, int y);

float degToRad(float a);
float FixAng(float a);;
float distance(float ax, float ay, float bx, float by, float ang);

int		ft_event_keydown(int keycode, void *game);
int		ft_event_keyup(int keycode, void *data);

int		ft_str_writeon(char **str, char *to_add);
int		ft_str_cwriteon(char **str, char c);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_str_isempty(char *str, int begin, int len);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(char *s1);
char	*ft_strdup2(char *s1, int len);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dst, void *src, size_t n);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
size_t	ft_strlen(char *s);
int	ft_str_contains(char *str, char c);

int		ft_str_isempty(char *str, int begin, int len);
int		ft_str_startswith(char *str, char *something);

char	*ft_read_file(char *file);
int	ft_read_parameters(t_game *game, char *config);
int	ft_read_map(t_game *game, char *config);
void	ft_putnbr_fd(int n, int fd);

int		ft_strs_writeon(char ***tab, char *str);
void	ft_strs_free(char ***tab);
char	**ft_strs_alloc();
int		ft_strs_len(char **tab);

# endif