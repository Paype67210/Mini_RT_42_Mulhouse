/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:05:02 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 09:34:15 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <X11/Xlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"	
# include "../MLX42/include/MLX42/MLX42.h"

// Definition de la variable THREADS a 8 si la compilation a 
// 	pas defini la valeur reelle
# ifndef THREADS
#  define THREADS	8
# endif

// # define _USE_MATH_DEFINES

// Definition de la variable O_BINARY a 0 pour la portabilité Windows / Linux
// de l'écriture du fichier .BMP
# ifndef O_BINARY
#  define O_BINARY 0
# endif

// Definition du nombre d'iterations maximum
// Limiter a 1000 pour eviter les temps de traitements trop longs
# ifndef MAX_ITER
#  define MAX_ITER 50
# endif

// Dder au compilateur de sauvegarder l'alignement actuel (avec push) et
// passer à un alignement de 1 octet (avec 1).
// Aucun remplissage entre les champs (pas de "padding").
#pragma pack(push, 1)

typedef struct s_bmp_file_header
{
	uint16_t			bf_type;
	uint32_t			bf_size;
	uint16_t			bf_reserved1;
	uint16_t			bf_reserved2;
	uint32_t			bf_off_bits;
}	t_bmp_file_header;

typedef struct s_bmp_info_header
{
	uint32_t			bi_size;
	int32_t				bi_width;
	int32_t				bi_height;
	uint16_t			bi_planes;
	uint16_t			bi_bit_count;
	uint32_t			bi_compression;
	uint32_t			bi_size_image;
	int32_t				bi_x_pels_per_meter;
	int32_t				bi_y_pels_per_meter;
	uint32_t			bi_clr_used;
	uint32_t			bi_clr_important;
}	t_bmp_info_header;

// pack(pop) restaure l'alignement précédent sauvegardé par push
#pragma pack(pop)

typedef struct s_vec3
{
	double				x;
	double				y;
	double				z;
}	t_vec3;

typedef struct s_color
{
	uint8_t				r;
	uint8_t				g;
	uint8_t				b;
	uint8_t				a;
}	t_color;

typedef struct s_obj
{
	t_vec3				coordos;
	t_vec3				vector;
	double				ratio;
	double				dt;
	double				height;
	t_color				color;
	int					type;
}	t_obj;

typedef struct s_ambiant
{
	bool				exist;
	double				ratio;
	t_color				color;
}	t_ambiant;

typedef struct s_camera
{
	bool				exist;
	t_vec3				coordos;
	t_vec3				vect_norm;
	int					fov;
}	t_camera;

typedef struct s_viewport
{
	double				ratio;
	double				focal;
	double				scale;
	t_vec3				vp_u;
	t_vec3				vp_v;
	t_vec3				delta_u;
	t_vec3				delta_v;
	t_vec3				img_center;
	t_vec3				pixel00;
}	t_viewport;

typedef struct s_img
{
	mlx_t				*mlxptr;
	mlx_image_t			*winptr;
	int					img_width;
	int					img_height;
	int					vp_width;
	int					vp_height;
	uint32_t			*pixels;
	t_viewport			*vp;
	pthread_mutex_t		mut;
}	t_img;

typedef struct s_scene
{
	bool				exist;
	bool				save;
	int					fd;
	const char			*file;
	t_ambiant			*ambiant;
	t_camera			*camera;
	t_list				*objects;
	t_list				*lights;
	bool				calc;
	bool				ok;
	bool				end;
	t_vec3				*trashcoordos;
	t_vec3				*trashvector;
}	t_scene;

typedef struct s_ray
{
	t_vec3				direct;
	t_vec3				perp;
	t_vec3				origin;
	t_color				color;
	int					depth;
}	t_ray;

// Structure pour le multi-threading
typedef struct s_rendertask
{
	int					startx;
	int					starty;
	int					width;
	int					height;
	bool				depth;
	int					count;
	t_scene				*scene;
}	t_rendertask;

typedef struct s_node
{
	struct s_rendertask	task;
	struct s_node		*next;
}	t_node;

typedef struct s_taskqueue
{
	t_node			*head;
	t_node			*tail;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
}	t_taskqueue;

// Définir la poison pill
# define POISON_PILL_STARTX -1

extern t_img		*g_image;

/* Fonctions liees aux vecteurs */
t_vec3			vec3_create(double x, double y, double z);
t_vec3			vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_mul(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_div(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_scale(t_vec3 v, double scale);
double			vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_cross(t_vec3 v1, t_vec3 v2);
double			vec3_length(t_vec3 v);
t_vec3			vec3_normalize(t_vec3 v);
t_vec3			vec3_reflect(t_vec3 v, t_vec3 n);
t_vec3			vec3_min(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_max(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_zero(void);
int				ft_parse_vec3(const char *str, t_vec3 *result);
t_vec3			vec3_perp(t_vec3 v, t_vec3 p);
double			vec3_dis(t_vec3 p1, t_vec3 p2);
int				vec3_cmp(t_vec3 p1, t_vec3 p2);

/* extractions depuis *.rt */
int				ft_check_file(t_scene *scene, char *file);
int				ft_parse_file(t_scene *scene, char *file);
int				ft_extract_params(t_scene *scene, char *line, int status);
int				ft_validation_scene(t_scene *scene);
int				ft_extract_resol(char *line);
int				ft_extract_amb(t_scene *scene, char *line);
int				ft_extract_cam(t_scene *scene, char *line);
int				ft_extract_lights(t_scene *scene, char *line);
int				ft_extract_sp(t_scene *scene, char *line);
int				ft_extract_pl(t_scene *scene, char *line);
int				ft_extract_cy(t_scene *scene, char *line);
int				ft_extract_co(t_scene *scene, char *line);

/* utilities */
t_obj			*obj_cont(t_list *list);
t_rendertask	*render_cont(t_list *list);
double			ft_rand(void);
t_scene			*scene_cont(void *scene);
double			calc_height(t_obj *obj);
double			ft_vector_turn(double vector, double delta);
unsigned char	get_red(uint32_t color);
unsigned char	get_green(uint32_t color);
unsigned char	get_blue(uint32_t color);
unsigned char	get_alpha(uint32_t color);

/* image definitions */
void			ft_getscreensize(void);

/* color_treatments */
t_color			ft_color_blend(double f, t_color c1, t_color c2);
t_color			ft_define_colors(int32_t r, int32_t g, int32_t b);
int				ft_parse_color(t_color *color, const char *str);
int				ft_str_to_int(const char *str, uint32_t min, \
					uint32_t max, uint32_t *resol);
t_color			ft_color_scale(double f, t_color color);
uint32_t		rgb_to_int(unsigned char r, unsigned char g, unsigned char b, \
					unsigned char a);
int				scene_light_weights(t_list *lights);
int				def_intrgb(t_color color);

/* rendering functions */
int				ft_launch_render(t_scene *scene);
int				th_render(t_scene *scene);
int				is_in_shadow(t_scene *scene, t_ray *ray, t_obj *tmp);
t_color			light_hit(t_scene *scene, t_list *lights, t_ray *hit, \
					t_obj *tmp);
void			init_ray(t_scene *scene, t_ray *ray, double x, double y);

/* viewport functions */
int				ft_viewport(t_scene *scene);
t_obj			*ft_find_pixel_color(t_scene *scene, t_ray *ray);
int				ft_launch_vp(t_scene *scene);
int				ft_render(t_scene *scene);
int				ft_deltas(t_scene *scene);
void			ft_move_obj(t_scene *scene, t_obj *obj, int x, int y);

/* Intersections with figures */
double			sp_intersection(t_obj *obj, t_ray *ray);
double			pl_intersection(t_obj *obj, t_ray *ray);
t_vec3			cylinder_normal(t_obj *tmp, t_ray *ray);
t_vec3			cone_normal(t_obj *tmp, t_ray *ray);
void			refraction(t_scene *scene, t_ray *ray, t_color color);
void			which_obj_perp(t_ray *ray, t_obj *tmp, double t);
double			which_obj(t_ray *ray, t_list *obj);
double			cone_base(t_ray *ray, t_obj *obj, double r);
double			co_intersection(t_obj *obj, t_ray *ray);
double			co_base(t_ray *ray, t_obj *obj, double r);
double			base_and_top(t_ray *ray, t_obj *obj, double r);
double			cy_intersection(t_obj *obj, t_ray *ray);
double			calc_r(t_obj *obj);
double			return_t(t_vec3 abc, double det);

/* Interseptions of hook & scroll */
void			ft_hook(void *scene);
void			ft_hook2(void *scene);
void			ft_scroll(double xdelta, double ydelta, void *scene);
void			ft_mouse(enum mouse_key key, enum action action, \
					enum modifier_key mods, void *scene);
void			ft_cam_move_ud(t_scene *scene, int delta);
void			ft_cam_move_lr(t_scene *scene, int delta);
void			ft_cam_move_bf(t_scene *scene, int delta);
void			ft_cam_turn(t_scene *scene, double horiz, double vert);

/* multi_threadings */
t_rendertask	ft_fill_task(t_scene *scene, int buffer, int i);
int				create_tasks(t_rendertask task, \
					t_taskqueue *queue, t_scene *scene);
t_color			ft_mix_color(t_ray *ray, uint32_t existing_pixel_color);
void			initqueue(t_taskqueue *queue);
void			enqueue(t_taskqueue *queue, t_rendertask task);
int				dequeue(t_taskqueue *queue, t_rendertask *task);
void			cleanupqueue(t_taskqueue *queue);
void			*renderthread(void *arg);
void			th_set_ray(t_rendertask *task);
void			th_launch_threads(t_scene *scene);

/* exit functions */
int				ft_exit(t_scene *scene, int status);
void			ft_handle_signal(int signal);

/* file saving */
void			ft_create_file_header(t_bmp_file_header *file_header, \
					int file_size);
void			ft_create_info_header(t_bmp_info_header *info_header);
int				verif_bmp_name(t_scene *scene, const char *filename);
int				write_bmp_headers(int fd_bmp);
int				write_bmp_pixels(int fd_bmp);
uint32_t		ft_rgba_to_barg(uint32_t color);
int				save_bmp(const char *filename);

/* debug functions */
int				ft_print_debug(t_scene *scene);
int				ft_print_object_list(t_scene *scene);
void			ft_prt_draw_size(t_scene *scene);

#endif