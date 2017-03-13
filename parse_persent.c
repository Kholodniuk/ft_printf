/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_persent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:14:39 by skholodn          #+#    #+#             */
/*   Updated: 2017/03/04 16:14:43 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

int    find_flag(t_e *e, char c)
{
    if (c == '+')
        e->f->plus = 1;
    else if (c == '-')
        e->f->minus = 1;
    else if (c == ' ')
        e->f->space = 1;
    else if (c == '#')
        e->f->hash = 1;
    else if (c == '0')
        e->f->zero = 1;
    if (c == '+' || c == '-' || c == ' ' || c == '#' || c == '0')
        return (1);
    return (0);
}

int  find_mod(t_e *e, char **fmt)
{
    if (**fmt == 'h' && *(*fmt + 1) == 'h' && e->mod <= 1)
        e->mod = 1;
    else if (**fmt == 'h' && e->mod <= 2)
        e->mod = 2;
    else if (**fmt == 'l' && e->mod <= 3)
        e->mod = 3;
    else if (**fmt == 'l' && *(*fmt + 1) == 'l' && e->mod <= 4)
        e->mod = 4;
    else if (**fmt == 'z' && e->mod <= 5)
        e->mod = 5;
    else if (**fmt == 'j' && e->mod <= 6)
        e->mod = 6;
    if ((**fmt == 'h' && *(*fmt + 1) == 'h') || (**fmt == 'l' && *(*fmt + 1) == 'l'))
    {
        (*fmt) += 2;
        return (1);
    }
    else if (**fmt == 'h' || **fmt == 'l' || **fmt == 'z' || **fmt == 'j')
    {
        (*fmt)++;
        return (1);
    }
    return (0);
}

int     find_conver(t_e *e, char c)
{
    int     i;

    i = 0;
    while (SPEC[i])
    {
        if (SPEC[i] == c ? e->spec = c : 0)
            return (1);
        i++;
    }
    return (0);
}

void    find_precision(t_e *e, char **fmt)
{
    **fmt == '.' ? ((*fmt)++) : 0;
    e->precision = ft_atoi(*fmt);
    while (DIGIT(**fmt))
        (*fmt)++;
}

void    find_width(t_e *e, char **fmt)
{
    e->width = ft_atoi(*fmt);
    while (DIGIT(**fmt))
        (*fmt)++;
}

void    free_e(t_e *e)
{
    e->mod = 0;
    e->width = 0;
    e->precision = -1;
    e->dollar = 0;
    e->f->plus = 0;
    e->f->minus = 0;
    e->f->hash = 0;
    e->f->space = 0;
    e->f->zero = 0;

}

void    parse_persent(t_e *e, char **fmt, va_list ar)
{
    (*fmt)++;
    while (**fmt)
    {
        if (find_flag(e, **fmt))
            (*fmt)++;
        else if (find_mod(e, fmt))
            ;
        else if (**fmt == '.')
            find_precision(e, fmt);
        else if (DIGIT(**fmt))
            find_width(e, fmt);
        else if (find_conver(e, **fmt) || (e->spec = *(*fmt)))
            break;
    }
    (*fmt) += 1;
    make_fprintf(e, ar);
    free_e(e);
}