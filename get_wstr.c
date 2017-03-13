/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:05:25 by skholodn          #+#    #+#             */
/*   Updated: 2017/03/10 19:05:56 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     wchar_len(wchar_t *wstr)
{
    int     i;
    int     len;

    i = 0;
    len = 0;
    while (wstr[i])
    {
        if (wstr[i] <= 0x7F)
            len += 1;
        else if (wstr[i] <= 0x7FF)
            len += 2;
        else if (wstr[i] <= 0xFFFF)
            len += 3;
        else if (wstr[i] <= 0x10FFFF)
            len += 4;
        i++;
    }
    return (len);
}

char    *get_wchar_cpy(char *str, int wchar, int j)
{
    if (wchar <= 0x7F)
        str[j] = (char)wchar;
    else if (wchar <= 0x7FF)
    {
        str[j] = (char)((wchar >> 6) + 0xC0);
        str[j + 1] = (char)((wchar & 0x3F) + 0x80);
    }
    else if (wchar <= 0xFFFF)
    {
        str[j] = (char)((wchar >> 12) + 0xE0);
        str[j + 1] = (char)(((wchar >> 6) & 0x3F) + 0x80);
        str[j + 2] = (char)((wchar & 0x3F) + 0x80);
    }
    else if (wchar <= 0x10FFFF)
    {
        str[j] = (char)((wchar >> 18) + 0xF0);
        str[j + 1] = (char)(((wchar >> 12) & 0x3F) + 0x80);
        str[j + 2] = (char)(((wchar >> 6) & 0x3F) + 0x80);
        str[j + 3] = (char)((wchar & 0x3F) + 0x80);

    }
    return (str);
}

char    *wstrncpy(char *str, wchar_t *wstr, int n)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (wstr[i] && j < n)
    {
        str = get_wchar_cpy(str, wstr[i], j);
        if (wstr[i] <= 0x7F)
            j += 1;
        else if (wstr[i] <= 0x7FF)
            j += 2;
        else if (wstr[i] <= 0xFFFF)
            j += 3;
        else if (wstr[i] <= 0x10FFFF)
            j += 4;
        i++;
    }
    return (str);
}

t_s *wstr_init(wchar_t *wstr, t_e *e)
{
    t_s     *s;
    int     sz_space;

    s = malloc(sizeof(t_s));
    s->size_space = 0;
    s->size_str = wchar_len(wstr);
    if (e->precision < s->size_str && e->precision != -1)
        s->size_str = e->precision;
    s->str = ft_strnew((size_t)s->size_str);
    s->str = wstrncpy(s->str, wstr, s->size_str);
    if (e->width > s->size_str)
        s->size_space = (e->width - s->size_str);
    sz_space = s->size_space;
    s->space = ft_strnew((size_t)sz_space);
    while (--sz_space > -1)
    {
        if (e->f->minus || !e->f->zero)
            s->space[sz_space] = ' ';
        else
            s->space[sz_space] = '0';
    }
    return (s);
}

void    free_wstr(t_s *s)
{
    free(s->str);
    free(s->space);
    free(s);
}

void    get_wstr(wchar_t *wstr, t_e *e)
{
    t_s *s;

    s = wstr_init(wstr, e);
    if (e->f->minus)
    {
        e->buf = ft_strjoin(e->buf, s->str);
        e->buf = ft_strjoin(e->buf, s->space);
    }
    else
    {
        e->buf = ft_strjoin(e->buf, s->space);
        e->buf = ft_strjoin(e->buf, s->str);
    }
    free_wstr(s);
}