/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:55:38 by mlantonn          #+#    #+#             */
/*   Updated: 2018/07/26 12:14:34 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>
# include "defines.h"
# include "mygtk.h"
# include "clust.h"

typedef struct		s_client
{
	int					x;
	int					nb_client;
	int					csock;
	struct sockaddr_in	csin;
	int					working;
	pthread_t			thread;
	struct s_client		*next;
}					t_client;

typedef struct		s_clust
{
	int					sock;
	struct sockaddr_in	sin;
	struct s_client		*client_l;
	int					nb_client_for_free;
}					t_clust;

typedef struct		s_sockaddr_in
{
	short				sin_family;
	unsigned short		sin_port;
	struct in_addr		sin_addr;
	char				sin_zero[8];
}					t_sockaddr_in;

/*
**	Storing 3D coordinates or 3D vectors.
*/
typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

/*
**	Photon strucure. Used for photon mapping and caustics
*/
typedef struct		s_photon
{
	t_vec			pos;
	t_color			color;
	int				obj_i;
}					t_photon;

/*
**	Perlin structure
*/
typedef struct		s_perlin
{
	int				bx0;
	int				bx1;
	int				by0;
	int				by1;
	int				bz0;
	int				bz1;
	int				b00;
	int				b01;
	int				b11;
	int				b10;
	float			rx0;
	float			rx1;
	float			ry0;
	float			ry1;
	float			rz0;
	float			rz1;
	float			*q;
	float			sy;
	float			sz;
	float			a;
	float			b;
	float			c;
	float			d;
	float			t;
	float			u;
	float			v;
}					t_perlin;

/*
**	Intersection structure
*/
typedef struct		s_inter
{
	int				obj_i;
	int				depth;
	double			min_dist;
	double			t1;
	double			t2;
	double			t;
	double			delta;
	t_vec			origin;
	t_vec			oc;
	t_vec			ip;
	t_vec			normal;
	t_color			color;
	t_color			shadow;
	t_color			spec;
	double			trans_at_ip;
	t_point			uv;
}					t_inter;

/*
**	Camera structure. Used as an array in the data structure
*/
typedef struct		s_camera
{
	double			fov;
	t_vec			pos;
	t_vec			angle;
	t_vec			vp_up_left;
}					t_camera;

/*
**	Light structure
*/
typedef struct		s_light
{
	int				is_para;
	int				disabled;
	double			ambi;
	double			r;
	t_vec			pos;
	t_vec			dir;
	t_vec			angle;
	t_color			color;
	t_color			color_neg;
}					t_light;

/*
**	Object structure
*/
typedef struct		s_obj
{
	int				obj_type;
	int				limited;
	int				enabled;
	double			r;
	double			spec;
	double			alpha;
	double			shiny;
	double			trans;
	double			ior;
	t_color			color;
	t_color			color2;
	int				color_type;
	int				color_scale;
	int				perl_scale;
	int				perl_type;
	double			perl_opacity;
	int				bump_flag;
	double			bump_intensity;
	int				bump_scale;
	t_vec			pos;
	t_vec			dir;
	t_vec			angle;
	t_vec			y_dir;
	t_vec			z_dir;
	t_vec			min;
	t_vec			max;
	t_vec			oc;
	t_pixelbuf		*tex;
	t_point			tex_pos;
	int				tex_scale;
	int				tex_repeat;
	int				tex_limit;
	int				tex_trans;
	char			*tex_filename;
	int				(*intersect)(struct s_obj, t_vec, t_inter *);
	int				(*limit)(struct s_obj, t_vec, t_inter *);
	t_vec			(*get_normal)(struct s_obj, t_inter);
}					t_obj;

/*
**	UI structure, used as a global : g_ui
*/
typedef struct		s_ui
{
	GtkWidget		*tab;
	GtkWidget		*tab_light;
	GtkWidget		*tab_cams;
	GtkWidget		*tab_objs;
	GtkWidget		*ev_box;
	GtkWidget		*sc_fov;
	GtkSizeGroup	*gp_cam_pos;
	GtkSizeGroup	*gp_cam_angle;
	GtkSizeGroup	*gp_dof_focus;
	int				is_active;
	int				page_light;
	int				page_cam;
	int				page_obj;
}					t_ui;
t_ui				*g_ui;

/*
**	Data strucure. Used as a global : g_data
*/
typedef struct		s_data
{
	t_obj			*objs;
	int				nb_objects;
	t_light			*lights;
	int				nb_lights;
	int				nb_lights_on;
	t_camera		cams[CAM_NB];
	int				i;
	t_camera		cam;
	int				aa;
	int				px;
	int				depth_of_field;
	double			dof_coeff;
	int				cel_shading;
	int				filter;
	int				depth_max;
	int				caustic_flag;
	t_photon		*photon_map;
	int				photon_total;
	int				photon_hit;
	int				photon_ppx;
	double			photon_size;
	int				stereo_scale;
	void			*win;
	t_pixelbuf		*img;
	int				draw;
	char			*path;
	char			*long_path;
	int				(*intersect[4])(struct s_obj, t_vec, t_inter *);
	int				(*limit[6])(struct s_obj, t_vec, t_inter *);
	t_vec			(*get_normal[4])(struct s_obj, t_inter);
	int				clust_i;
	t_clust			clust;
	int				x;
	int				nb_client;
	uint32_t		*cimg;
}					t_data;
t_data				*g_data;

/*
**	To add colors
*/
typedef struct		s_added
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_added;

/*
**	This structure is used to handle the keyboard event
**	fill f with the function you want to use when the key is pushed
*/
typedef struct		s_funar_keyb
{
	int				key;
	void			(*f)(t_data*);
}					t_funar_keyb;

typedef struct		s_wid_data
{
	t_point			pos;
	t_point			size;
	t_ptdb			min_max;
	double			step;
	GtkWidget		*grid;
	gpointer		param;
	void			(*f)(GtkWidget*, gpointer);
	void			(*entry_f)(GtkWidget*, GdkEvent*, gpointer);
}					t_wid_data;

#endif
