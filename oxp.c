/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oxp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:03:19 by skholodn          #+#    #+#             */
/*   Updated: 2017/03/06 15:03:23 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    get_lower(t_oxp *oxp)
{
    int     i;

    if (oxp->prefix != NULL && oxp->prefix[1] == 'X')
        oxp->prefix[1] = 'x';
    i = 0;
    while (oxp->nbr[i])
    {
        oxp->nbr[i] = (char)ft_tolower(oxp->nbr[i]);
        i++;
    }
}

void    init_char_oxp(t_oxp *oxp, t_e *e)
{
    int  sz_zero;
    int  sz_space;

    sz_space = oxp->size_space;
    sz_zero = oxp->size_zero;
    oxp->zero = ft_strnew((size_t)sz_zero);
    while (--sz_zero > -1)
        oxp->zero[sz_zero] = '0';
    oxp->space = ft_strnew((size_t)sz_space);
    while (--sz_space > -1)
        oxp->space[sz_space] = ' ';
    oxp->prefix = ft_strnew((size_t)oxp->size_prefix);
    if (oxp->size_prefix == 2)
        oxp->prefix = ft_strcat(oxp->prefix, "0X");
    else if (oxp->size_prefix == 1)
        oxp->prefix = ft_strcat(oxp->prefix, "0");
    if (e->spec == 'x' || e->spec == 'p')
        get_lower(oxp);
}

t_oxp    *init_oxp(uintmax_t nb, t_e *e)
{
    t_oxp    *oxp;

    oxp = malloc(sizeof(t_oxp));
    if (e->spec == 'o' || e->spec == 'O')
        oxp->nbr = (e->precision == 0 && !nb) ? ft_strnew(0) : u_itoa_base(nb, 8);
    else
        oxp->nbr = (e->precision != -1 && !nb) ? ft_strnew(0) : u_itoa_base(nb, 16);
    oxp->size_nbr = (int)ft_strlen(oxp->nbr);
    oxp->size_space = 0;
    oxp->size_prefix = 0;
//    if (nb == 0 && (e->spec == 'o' || e->spec == 'O'))
//        oxp->size_nbr = 0;
    if (P_N_X >= 0 && nb && (e->precision < e->width))
        oxp->size_space = 1;
    if (e->spec == 'p' || ((e->spec == 'x' || e->spec == 'X') && e->f->hash && nb != 0))
        oxp->size_prefix = 2;
    else if ((e->spec == 'o' || e->spec == 'O') && e->f->hash)
        oxp->size_prefix = 1;
    oxp->size_zero = 0;
    if (e->precision > e->width || e->precision > oxp->size_nbr)
        oxp->size_zero = (P_N_X < 0 ? 0 : P_N_X);
    else if ((e->precision < e->width) && e->f->zero && !e->f->minus)
        oxp->size_zero = (W_N_X < 0 ? 0 : W_N_X - oxp->size_prefix);
    if ((e->precision < e->width) && (oxp->size_nbr < e->width) && (!e->f->zero || e->f->minus))
        oxp->size_space = (e->width - (e->precision < oxp->size_nbr ? (oxp->size_nbr + oxp->size_zero) : e->precision) - oxp->size_prefix);
    else if ((e->precision > e->width) && (oxp->size_nbr < e->precision) && e->f->zero)
        oxp->size_space = (e->precision - oxp->size_nbr);
    init_char_oxp(oxp, e);
    return (oxp);
}

void    free_oxp(t_oxp *oxp)
{
    free(oxp->space);
    free(oxp->zero);
    free(oxp->nbr);
    free(oxp);
}

void    get_oxp(uintmax_t nb, t_e *e)
{
    t_oxp    *oxp;


    oxp = init_oxp(nb, e);
    if (e->f->minus == 1)
    {
        e->buf = ft_strjoin(e->buf, oxp->prefix);
        e->buf = ft_strjoin(e->buf, oxp->zero);
        e->buf = ft_strjoin(e->buf, oxp->nbr);
        e->buf = ft_strjoin(e->buf, oxp->space);
    }
    else
    {
        e->buf = ft_strjoin(e->buf, oxp->space);
        e->buf = ft_strjoin(e->buf, oxp->prefix);
        e->buf = ft_strjoin(e->buf, oxp->zero);
        e->buf = ft_strjoin(e->buf, oxp->nbr);
    }
    free_oxp(oxp);
}

