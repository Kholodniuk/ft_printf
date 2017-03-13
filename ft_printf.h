/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:48:12 by skholodn          #+#    #+#             */
/*   Updated: 2017/03/03 16:48:44 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** LIBRARIES
*/

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include <string.h>
# include <stddef.h>

# define DIGIT(d) (d >= '0' && d <= '9' ? 1 : 0)
# define MOD(x) ((x) < 0 ? -(x) : (x))

# define SPEC "sSpdDioOuUxXcC"

# define P_N (e->precision - di->size_nbr)
# define W_N (e->width - di->size_nbr)
# define P_N_U (e->precision - u->size_nbr)
# define W_N_U (e->width - u->size_nbr)
# define P_N_X (e->precision - oxp->size_nbr)
# define W_N_X (e->width - oxp->size_nbr)

int     g_zero;

typedef struct s_di
{
    int         size_zero;
    int         size_space;
    int         size_nbr;
    int         size_sign;
    char        *zero;
    char        *space;
    char        *nbr;
    char        *sign;
}               t_di;

typedef struct s_u
{
    int         size_zero;
    int         size_space;
    int         size_nbr;
    char        *zero;
    char        *space;
    char        *nbr;
}               t_u;

typedef struct s_oxp
{
    int         size_zero;
    int         size_space;
    int         size_nbr;
    int         size_prefix;
    char        *zero;
    char        *space;
    char        *nbr;
    char        *prefix;
}               t_oxp;

typedef struct s_s
{
    int         size_space;
    int         size_str;
    char        *space;
    char        *str;
}               t_s;


typedef struct s_fl
{
    int     plus;
    int     minus;
    int     space;
    int     hash;
    int     zero;
}               t_fl;

//typedef struct s_mod
//{
//    int    hh; //== 1
//    int    h; //== 2
//    int    l; //== 3
//    int    ll; //== 4
//    int    j; //== 6
//    int    z; //== 5
//}               t_mod;

typedef struct  s_e
{
    char        *buf;
    t_fl        *f;
    int         mod;
    int         width;
    int         precision;
    int         dollar;
    char        spec;
}               t_e;

int		ft_printf(char *fmt, ...);
char    *ft_vsprintf(char *buf, char *fmt, va_list ar);
void    parse_persent(t_e *e, char **fmt, va_list ar);
void    make_fprintf(t_e *e, va_list ar);
void    get_nbr(intmax_t nb, t_e *e);
void    get_unbr(uintmax_t nb, t_e *e);
void    get_oxp(uintmax_t nb, t_e *e);
void    get_str(char *arg, t_e *e);
void    apply_width(t_e *e);
void    get_char(int c, t_e *e);
void    get_wstr(wchar_t *str, t_e *e);

char    *ft_charjoin(char *s1, char c);
void    ft_bzero(void *s, size_t n);
char    *ft_strcat(char *dest, const char *src);
size_t  ft_strlen(const char *str);
char    *ft_strnew(size_t size);
int     ft_atoi(const char *s);
char    *ft_strjoin(char const *s1, char const *s2);
int     ft_tolower(int c);
char    *ft_strncpy(char *dest, const char *src, size_t len);
char    *ft_strsub(char const *s, unsigned int start, size_t len);
char    *ft_strchr(const char *s, int c);

char    *u_itoa_base(uintmax_t value, uintmax_t base);
int     get_size_nb(uintmax_t nb);

#endif