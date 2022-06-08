/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:23:29 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 20:42:33 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include <mlx.h>
# include "math.h"
# include <fcntl.h>

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

# define NORTH_RADIANS (3 * PI) / 2
# define SOUTH_RADIANS PI / 2
# define EAST_RADIANS PI
# define WEST_RADIANS 0

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_texture {
	int		height;
	int		width;
	void	*data;
}				t_texture;

typedef struct s_game {
	void		*mlx_win;
	void		*mlx;
	t_data		*img;

	double		player_x;
	double		player_y;
	int			player_position_set;
	t_texture	*north;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
	int			ceil;
	int			floor;
	int			key_a;
	int			key_d;
	int			key_w;
	int			key_s;
	char		**map;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_game;

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/ft_events_keys.c                         */
/* -------------------------------------------------------------------------- */
int				ft_event_keydown(int keycode, void *data);
int				ft_event_keyup(int keycode, void *data);

/* -------------------------------------------------------------------------- */
/*                            FILE = srcs/ft_free.c                           */
/* -------------------------------------------------------------------------- */
void			ft_free_game(t_game *game);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/ft_get_utils_main.c                      */
/* -------------------------------------------------------------------------- */
t_texture		*get_texture(t_game *game, int direction);
int				get_direction(int side, int step);
char			ft_getcaracter(t_game *game, int x, int y);
int				ft_iswall(t_game *game, int x, int y);

/* -------------------------------------------------------------------------- */
/*                            FILE = srcs/ft_init.c                           */
/* -------------------------------------------------------------------------- */
int				ft_init_parameters(t_game *game, char *content);
int				ft_init_map(t_game *game, char *content);
int				ft_init_global(t_game *game, char *file);
int				ft_init_mlx(t_game *game);
t_game			*ft_init_game();

/* -------------------------------------------------------------------------- */
/*                            FILE = srcs/ft_rgb.c                            */
/* -------------------------------------------------------------------------- */
int				ft_readint(char *str, int from, int end);
int 			ft_rgb_write(char *str, int *rgb);
int				check_format(char *str);
int				ft_rgb(char *str);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/ft_rotate_camera.c                        */
/* -------------------------------------------------------------------------- */
void			ft_rotate_camera(t_game *game, double rot);
double			ft_rotate_camera_relative(char c);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/ft_texture.c                           */
/* -------------------------------------------------------------------------- */
t_texture		*ft_texture(void *mlx, char *filename);
void			ft_free_texture(void *mlx_ptr, t_texture *texture);

//				PARSING				//
/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/parsing/ft_parse.c                        */
/* -------------------------------------------------------------------------- */
char			*ft_read_file(char *file);
char			*ft_read_value(char *line, int len);
void			ft_apply_value(t_game *game, char *line, char *value);
int				ft_read_parameter(t_game *game, char *config, int begin, int len);
int				ft_check_for_missing(t_game *game);
int				ft_read_parameters(t_game *game, char *config);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/parsing/ft_parse.c                        */
/* -------------------------------------------------------------------------- */
void			ft_write_player_position(t_game *game, char direction, int x, int y);
int				ft_read_map_is_valid(char *str, int len);
int				ft_write_map(char *str, int len, char ***map);
int				ft_read_map_content(char *str, char ***map);
int				ft_check_closing(char **map, int x, int y);
int				ft_check_closed(char **map);
int				ft_read_map(t_game *game, char *config);

//				UTILS				//
/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/ft_calloc.c                        */
/* -------------------------------------------------------------------------- */
void			*ft_calloc(size_t count, size_t size);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/ft_error.c                         */
/* -------------------------------------------------------------------------- */
void			ft_error(char *str);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/utils/ft_memcpy.c                         */
/* -------------------------------------------------------------------------- */
void			*ft_memcpy(void *dst, void *src, size_t n);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/utils/ft_strdup.c                         */
/* -------------------------------------------------------------------------- */
char			*ft_strdup2(char *s1, int len);
char			*ft_strdup(char *s1);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/utils/ft_strjoin.c                        */
/* -------------------------------------------------------------------------- */
char			*ft_strjoin(char *s1, char *s2);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/utils/ft_strlcat.c                        */
/* -------------------------------------------------------------------------- */
size_t			ft_strlcat(char *dst, char *src, size_t dstsize);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/utils/ft_strlen.c                         */
/* -------------------------------------------------------------------------- */
int				ft_strlen(char *s);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/ft_strncmp.c                         */
/* -------------------------------------------------------------------------- */
int				ft_strncmp(char *s1, char *s2, unsigned long long n);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/utils/ft_utils_maths.c                      */
/* -------------------------------------------------------------------------- */
float			ft_dist(float ax, float ay, float bx, float by, float ang);
float			degToRad(float a);
float			FixAng(float a);
float			distance(float ax, float ay, float bx, float by, float ang);

/* -------------------------------------------------------------------------- */
/*                  FILE = srcs/utils/ft_utils_pixel.c                        */
/* -------------------------------------------------------------------------- */
void			ft_pixel(t_data *data, int x, int y, int color);
unsigned int	ft_pixel_color(void *image, int x, int y);
int				ft_pixels(int x, int y, int x2, int y2);
void			ft_line(t_data *data, int x, int y, \
						float dx, float dy, float pixels, int color);
int				ft_rgb_to_int(int r, int g, int b);

/* -------------------------------------------------------------------------- */
/*                  FILE = srcs/utils/ft_utils_pixel_2.c                      */
/* -------------------------------------------------------------------------- */
void			ft_rect(t_data *data, int x, int y, int width, int height, int color);
void			ft_square(t_data *data, int x, int y, int x2, int y2, int color);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/utils/ft_utils_str.c                         */
/* -------------------------------------------------------------------------- */
int				ft_str_writeon(char **str, char *to_add);
int				ft_str_cwriteon(char **str, char c);
int				ft_str_isempty(char *str, int begin, int len);
int				ft_str_startswith(char *str, char *something);
int				ft_str_contains(char *str, char c);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/utils/ft_utils_str_2.c                         */
/* -------------------------------------------------------------------------- */
char			**ft_strs_alloc(void);
int				ft_strs_len(char **tab);
void			ft_strs_free(char ***tab);
char			**ft_strs_allocate(char *str);
int				ft_strs_copy_into(char **tab, char **dst);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/utils/ft_utils_str_3.c                         */
/* -------------------------------------------------------------------------- */
int				ft_strs_writeon(char ***tab, char *str);
int				is_numeric(char c);
int				check_value(int i);

//				MAIN				//
/* -------------------------------------------------------------------------- */
/*                              FILE = srcs/main.c                            */
/* -------------------------------------------------------------------------- */
void	draw_rays_3d(t_game *game);
int		render_next_frame(void *data);
void	draw_all(t_game *game);
int		check_filename(char *filename);

#endif
