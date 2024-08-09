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

# define SCREEN_H 768
# define SCREEN_W 1024
# define FOV (PI / 2)
# define WALL 3.0f
# define GRID_SIZE 64
# define PLANE 512
# define NORTH_TEX 0
# define WEST_TEX 1
# define SOUTH_TEX 2
# define EAST_TEX 3
# define IMG 4
# define EPSILON 0.0001

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

}					AllocType;

typedef enum
{
	PLAY = 0,
}					Activity;

typedef struct s_type
{
	int				type;
}					t_type;

typedef struct s_player
{
	t_type			type;
	float			facing;
	float			player_x;
	float			player_y;
}					t_player;

typedef struct s_rgb
{
	t_type			type;
	int				num;
	int				value;
	struct s_rgb	*next;
}					t_rgb;

typedef struct s_map
{
	t_type			type;
	char			**map2d;
	char			**check;
	char			*line;
	int				map_width;
	int				map_height;
}					t_map;

typedef struct s_specs
{
	t_type			type;
	char			*floor_spec;
	char			*ceil_spec;
	int				floor_color;
	int				ceil_color;
	t_rgb			*floor;
	t_rgb			*ceil;
	t_rgb			*ptr;
	char			*n_spec;
	char			*s_spec;
	char			*e_spec;
	char			*w_spec;
	int				rows;
}					t_specs;

typedef struct s_mlx
{
	int				win_h;
	void			*img;
	char			*addr[5];
	int				bpp[5];
	int				line_length[5];
	int				endian[5];
	int				win_w;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*north_tex;
	void			*west_tex;
	void			*south_tex;
	void			*east_tex;
	int				width[4];
	int				height[4];
	int				texture;

}					t_mlx;

typedef struct s_rays
{
	float			x;
	float			y;
	float			a;
	float			b;
	float			c;
	float			h;
	char			wall_direction;
	char			wall_direction_v;
	char			wall_direction_h;
	float			angle_left;
	float			angle_right;
	float			distance_to_wall;
	float			horizontal_distance;
	float			vertical_distance;
	char			*rgb_floor;
	char			*rgb_ceil;
	float			wall_hit;
	float			hit_v;
	float			hit_h;
	int draw_start;
	int draw_end;
	int texture_height;
	int wall_height;
	int tex_y;
	int tex_x;
	int box;

}					t_rays;

typedef struct s_cub
{
	t_rays			*rays;
	t_type			type;
	t_specs			*specs;
	t_map			*map;
	t_player		*player;
	t_mlx			*mlx;
}					t_cub;

// main
int					main(int argc, char *argv[]);
// parsing

void				parse_cub_file_specs(char *path, t_specs *specs,
						t_type *type);
char				*get_path(char *line, char *new, t_type *type, int k);
void				check_line(char *line, t_specs *specs, t_type *type);
void				build_map2d(char *line, t_map *map, t_type *type,
						int *index);
void				check_tracker(char *line, int *tracker);
void				parse_cub_file_map(char *path, t_map *map, t_type *type);
char				*trim_line(char *line, t_type *type);
t_map				*set_map(char *path);
void				get_rgb(char **str, t_rgb **rgb, t_type *type,
						t_specs *specs);

// init
t_cub				*set_cub(char *argv[]);
t_cub				*get_cub(void);
t_specs				*set_specs(char *path);
t_specs				*get_specs(void);
t_player			*set_player(void);
t_player			*get_player(void);
void				give_player_values(int i, int j, t_player *player);
t_mlx				*init_mlx(t_mlx *mlx_struct, t_cub *cub);

// utils
void				*allocate_memory(int size, int alloc_type, t_type *ret);
void				print2d_array(char **array);
void				print_and_exit_specs(char *str, t_specs *specs);
void				print_and_exit_map(char *str, t_map *map, char **line);
int					key_hook(int keycode, t_cub *cub);
void				get_map_parameters(t_map *map, char **array);
void				fix_fisheye(float *distance, int i);
//void				fix_fisheye(float *distance, int i);

// checks
void				first_check(int argc, char *argv[]);
void				check_map_path(char *path);
int					rgb_check(char *rgb, t_specs *specs);
void				check_specs(t_specs *specs);
int					check_border(char *line, t_map *map, int *tracker);
void				check_line2(char *line, t_specs *specs, int *flag);
// dfs
void				final_map_check_dfs(char **array, t_map *map);
int					check_borders(char **arr, int i, int j, char **check);
bool				space_check(char c, int left);
void				find_player(char **array, int *i, int *j, t_map *map);
bool				is_all_good(char **arr, int i, int j);
bool				check_field(char c);
void				check_players(char **array, t_map *map);
// exit
int					end_game(t_cub *cub);
// render
int					render(t_cub *cub);
void				launch_rays(t_player *player, t_map *map, t_rays *rays,
						float angle);
void				my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void				render_walls(t_mlx *mlx, t_rays *rays, int x,
						t_specs *specs);
void				horizontal_angle(t_map *map, t_rays *rays, float angle,
						int quarter);
void				vertical_angle(t_map *map, t_rays *rays, float angle,
						int quarter);
void				change_rgb_to_hex(int *color, t_rgb *rgb);
void	update_rays_values(t_rays *rays);
#endif
