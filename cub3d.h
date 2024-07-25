#ifndef CUB3D_H
# define CUB3D_H

# define PI 3.14f
# define ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

//# define SCREEN_H 768
//# define SCREEN_W 1024
# define SCREEN_H 768
# define SCREEN_W 1024
# define FOV (PI / 2)
# define WALL 3.0f
# define GRID_SIZE 64
# define PROJ_PLANE_DIST (SCREEN_W / (2.0 * tan(FOV / 2.0)))

# define TEXTURE_H 64
# define TEXTURE_W 64

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum
{
	SPECS,
	ARRAY,
	ARRAY2D,
	MAP,
	CUB,
	RGB,
	PLAYER,
	MLX,
	RAYS

}				AllocType;

typedef enum
{
	PLAY = 0,
}				Activity;

typedef struct s_type
{
	int			type;
}				t_type;

typedef struct s_player
{
	t_type		type;
	float		facing;
	float		first_ray;
	float		middle_ray;
	float		last_ray;
	float		player_x;
	float		player_y;
}				t_player;

typedef struct s_rgb
{
	t_type		type;
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_map
{
	t_type		type;
	char		**map2d;
	char		**check;
	char		*line;
	int			map_width;
	int			map_height;
}				t_map;

typedef struct s_specs
{
	t_type		type;
	char		*floor_spec;
	char		*ceil_spec;
	t_rgb		*floor;
	t_rgb		*ceil;
	char		*n_spec;
	char		*s_spec;
	char		*e_spec;
	char		*w_spec;
	int			rows;
}				t_specs;

typedef struct s_mlx
{
	int			win_h;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			win_w;
	void		*mlx_ptr;
	void		*win_ptr;

}				t_mlx;

typedef struct s_rays
{
	float		x;
	float		y;
	float		a;
	float		b;
	float		c;
	float		h;
	float		angle_left;
	float		angle_right;
	float		distance_to_wall;
	float		horizontal_distance;
	float		vertical_distance;

}				t_rays;

typedef struct s_cub
{
	t_type		type;
	t_specs		*specs;
	t_map		*map;
	t_player	*player;
	t_mlx		*mlx;
}				t_cub;

// main
int				main(int argc, char *argv[]);
// parsing

void			parse_cub_file_specs(char *path, t_specs *specs, t_type *type);
char			*get_path(char *line, char *new, t_type *type, int k);
void			check_line(char *line, t_specs *specs, t_type *type);
void			build_map2d(char *line, t_map *map, t_type *type, int *index);
void			check_tracker(char *line, int *tracker);
void			parse_cub_file_map(char *path, t_map *map, t_type *type);
char			*trim_line(char *line, t_type *type);
t_map			*set_map(char *path);
void			get_rgb(char *str, t_rgb **rgb, t_type *type);

// init
t_cub			*set_cub(char *argv[]);
t_cub			*get_cub(void);
t_specs			*set_specs(char *path);
t_specs			*get_specs(void);
t_player		*set_player(void);
t_player		*get_player(void);
void			give_player_values(int i, int j, t_player *player);
t_mlx			*init_mlx(t_mlx *mlx_struct, t_cub *cub);

// utils
void			*allocate_memory(int size, int alloc_type, t_type *ret);
void			print2d_array(char **array);
void			print_and_exit_specs(char *str, t_specs *specs);
void			print_and_exit_map(char *str, t_map *map, char **line);
int				key_hook(int keycode, t_cub *cub);
void			get_map_parameters(t_map *map, char **array);
// checks
void			first_check(int argc, char *argv[]);
void			check_map_path(char *path);
int				rgb_check(int num);
void			check_specs(t_specs *specs);
int				check_border(char *line, t_map *map, int *tracker);
void			check_line2(char *line, t_specs *specs, int *flag);
// dfs
void			final_map_check_dfs(char **array, t_map *map);
int				check_borders(char **arr, int i, int j, char **check);
bool			space_check(char c, int left);
void			find_player(char **array, int *i, int *j, t_map *map);
bool			is_all_good(char **arr, int i, int j);
bool			check_field(char c);
void			check_players(char **array, t_map *map);
// exit
int				end_game(t_cub *cub);
// render
int				render(t_cub *cub);
void			launch_rays(t_player *player, t_map *map, t_rays *rays,
					float angle);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void			render_walls(t_mlx *mlx, t_rays *rays, int x);
void			horizontal_angle(t_map *map, t_rays *rays, float angle,
					int quarter);
void			vertical_angle(t_map *map, t_rays *rays, float angle,
					int quarter);
#endif
