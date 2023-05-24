/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:10:31 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 23:12:20 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "../includes/minishell.h"

typedef struct s_list_lib
{
	void				*content;
	struct s_list_lib	*next;
}					t_list_lib;

void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_tablen(char **s);
size_t				ft_tablen_pipe(char **s);
int					ft_isalpha(int c);
int					ft_isdigit(char *str);
int					ft_isalnum(int c);
int					ft_isalnum_spe(int c);
int					ft_isascii(int c);
int					ft_isprint(char c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strncmp_check_len(const char *s1, const char *s2,
						size_t n);
char				*ft_strncpy(char *dst, char *src, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strcat(char *dst, char *src);
char				*ft_strncat(char *dst, char *src, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putstr(char *str);
void				ft_putchar(char c);
void				ft_putnbr(int n);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strjoinfree(char const *s1, char *s2);
char				*ft_strjoin_null(char *s1, char *s2, int j);
char				*ft_free_tab(char **str);
int					ft_is_digit(char c);
void				ft_strdel(char **to_del);

#endif
