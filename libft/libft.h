/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:50:00 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 15:16:45 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>
# include <math.h>
# include <ctype.h>
# include <string.h>
# include <stddef.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <dirent.h>
# include <stdbool.h>
# include <sys/stat.h>
# include "def_list.h"

// # if defined (__linux__)
// #  define PTRNULL "(nil)"
// # elif defined (__APPLE__)
// #  define PTRNULL "0x0"
// # endif
# define PTRNULL "(nil)"
# define LOG_DIR "./.varlog"
# define FILE_PREFIX "debug"

int			ft_msg(char *str1, char *str2, char *str3, int value);
void		*ft_memset(void *mtr, int c, size_t n);
void		*ft_memset2(size_t count, size_t size);
void		ft_bzero(void *mtr, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(char c);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strncpy(char *str, size_t len);
char		*ft_strnlcpy(const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strchr(const char *str, int c);
int			ft_int_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *dst, const char *src);
int			ft_strncmp(const char *str, const char *s2, size_t n);
void		*ft_memchr(const void *str, int c, size_t n);
int			ft_memcmp(const void *str, const void *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(long n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *s, int fd);
int			ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);
char		*ft_strnchr(const char *src, int value, size_t i);
char		*ft_strwchr(char *str, char chr);
char		*ft_strbtwcpy(char *str, char chr1, char chr2);
int			ft_strstr(char *str, char *value);
int			ft_strstr_without_space(const char *src, const char *value);
/* ---------- CHAR TO FLOAT, INT, DOUBLE ----------*/
char		**ft_split(char const *str, char c);
char		**ft_spsplit(char const *str, int word_index);
int			ft_split_count(char **split);
int			ft_atoi(const char *nptr);
float		ft_strtof(const char *str, char **endptr);
double		ft_strtod(const char *str, char **endptr);
const char	*ft_skipspaces(const char *str);
const char	*ft_parse_sign(const char *s, int *sign);
const char	*ft_parse_int_part(const char *str, float *result);
const char	*ft_parse_fract_part(const char *str, float *result, float *power);
const char	*ft_parse_exp_part(const char *str, float *result);
/* ---------- LINKED LISTS ------- */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstfirst(t_list *lst);
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_lstsize(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstclear_safe(t_list **lst, void (*del)(void *));
// void	ft_lstiter(t_list *lst, void (*f)(void *));
int			ft_lstremove(t_list **lst, t_list *node, void (*del)(void*));
t_list		*ft_lstretrieve(t_list **lst, t_list *node);
int			ft_lstreplace(t_list **lst, t_list *node);
t_list		*ft_lstaddafter(t_list *lst, t_list *new);
t_list		*ft_lstaddbefore(t_list *lst, t_list *new);
t_list		*ft_lstcopy(t_list *lst);
/* ---------- EXTRAS ---------- */
void		ft_free_2d(char **array);
void		ft_free_array(char ***array);
size_t		ft_wcount(const char *str, char del);
size_t		ft_char_end(char *str, char n);
size_t		ft_char_start(char *str, char n);
char		**ft_split_args_cmd(char const *str);
/* ---------- GNL ------------ */
char		*get_next_line(int fd);
void		ft_read_line(int fd, char **keep, char **tmp);
char		*ft_parse_line(char **keep, char **tmp);
char		*get_before_newline(const char *s);
char		*get_after_newline(const char *s);
int			contains_newline(const char *s);
void		*ft_memset2(size_t count, size_t size);
void		ft_free_strs(char **str, char **str2, char **str3);
/* ---------- PRINTF ----------*/
int			ft_printf(const char *format, ...);
int			ft_formats(va_list args, const char format);
int			ft_printchar(int c);
int			ft_printstr(char *str);
int			ft_print_ptr(unsigned long long ptr);
int			ft_printnbr(int n);
int			ft_print_unsigned(unsigned int n);
int			ft_print_hex(unsigned int num, const char format);
void		ft_put_ptr(uintptr_t num);
int			ft_ptr_len(uintptr_t num);
char		*ft_uitoa(unsigned int n);
int			ft_num_len(unsigned	int num);
void		ft_put_hex(unsigned int num, const char format);
int			ft_hex_len(unsigned	int num);
/* --------- FT_FPRINTF ---------- */
int			ft_create_log_dir(void);
void		get_current_date(char *date_str);
void		get_current_time(char *date_str);
int			ft_open_log(int *fd);
int			ft_open_stderr(int *fd);
int			ft_putptr_fd(unsigned long long ptr, int fd);
int			ft_putnbr_base_fd(long int nb, char format, int fd);
int			ft_fprintf(int fd_log, const char *format, ...);
int			ft_fformats(va_list args, const char format, int fd_log);
/* --------- FT_MALLOC --------- */
void		*ft_malloc(t_list **ouille, size_t size);
int			ft_free(t_list **ouille, void *ptr);
int			ft_freeall(t_list **ouille);
int			*ft_realloc(t_list **list, void *ptr, size_t size);
void		*ft_run_malloc(int function, ...);

#endif
