/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:02:51 by skholodn          #+#    #+#             */
/*   Updated: 2017/03/11 18:09:25 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     get_size_nb(uintmax_t nb)
{
    int         i;

    i = 1;
    while (nb > 9)
    {
        nb /= 10;
        i++;
    }
    return (i);
}

void    init_char_di(t_di *di, intmax_t nb, t_e *e)
{
    int  sz_zero;
    int  sz_space;

    sz_space = di->size_space;
    sz_zero = di->size_zero;
    di->nbr = (e->precision != -1 && !nb ? ft_strnew(0) : u_itoa_base((uintmax_t)MOD(nb), 10));
    di->zero = ft_strnew((size_t)sz_zero);
    while (--sz_zero > -1)
        di->zero[sz_zero] = '0';
    di->space = ft_strnew((size_t)sz_space);
    while (--sz_space > -1)
        di->space[sz_space] = ' ';
    di->sign = ft_strnew((size_t)di->size_sign);
    if (di->size_sign && nb < 0)
        di->sign[0] = '-';
    else if (di->size_sign && e->f->plus)
        di->sign[0] = '+';
    else if (di->size_sign && e->f->space)
        di->sign[0] = ' ';
}

t_di    *init_di(intmax_t nb, t_e *e)
{
    t_di    *di;

    di = malloc(sizeof(t_di));
    di->size_nbr = get_size_nb((uintmax_t)MOD(nb));
    di->size_sign = 0;
    di->size_space = 0;
    di->size_zero = 0;
    if (nb < 0 || e->f->plus || e->f->space)
        di->size_sign = 1;
    if (nb == 0)
        di->size_nbr = 0;
    /*if (e->precision > e->width)
        di->size_zero = (P_N < 0 ? 0 : P_N);
    else */if (e->precision == -1 && e->f->zero && !e->f->minus)
        di->size_zero = (W_N < 0 ? 0 : W_N - di->size_sign);
    else if (e->precision > di->size_nbr)
        di->size_zero = (P_N < 0 ? 0 : P_N);
//    if (!(e->precision > e->width) && (nb < 0 || e->f->plus))
//        di->size_zero -= 1;
//    if (/*((e->precision + di->size_sign) < e->width) && (di->size_nbr < e->width) && */e->precision > -1 && !e->f->zero && e->f->minus)
    di->size_space = (e->width - (e->precision > di->size_nbr ? e->precision : (di->size_nbr + di->size_zero)) - di->size_sign);
    init_char_di(di, nb, e);
    return (di);
}

void    free_di(t_di *di)
{
    free(di->space);
    free(di->sign);
    free(di->zero);
    free(di->nbr);
    free(di);
}

void    get_nbr(intmax_t nb, t_e *e)
{
    t_di    *di;

    di = init_di(nb, e);
    if (e->f->minus == 1)
    {
        e->buf = ft_strjoin(e->buf, di->sign);
        e->buf = ft_strjoin(e->buf, di->zero);
        e->buf = ft_strjoin(e->buf, di->nbr);
        e->buf = ft_strjoin(e->buf, di->space);
    }
    else
    {
        e->buf = ft_strjoin(e->buf, di->space);
        e->buf = ft_strjoin(e->buf, di->sign);
        e->buf = ft_strjoin(e->buf, di->zero);
        e->buf = ft_strjoin(e->buf, di->nbr);
    }
    free_di(di);
}
