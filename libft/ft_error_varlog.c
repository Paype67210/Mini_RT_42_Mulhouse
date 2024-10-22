/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_varlog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:45:26 by pdeson            #+#    #+#             */
/*   Updated: 2024/05/06 10:29:58 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_create_log_dir(void)
{
	struct stat	st;

	if (stat(LOG_DIR, &st) == -1)
	{
		if (mkdir(LOG_DIR, 0755) == -1)
			return (-1);
	}
	else if (!S_ISDIR(st.st_mode))
		return (-1);
	return (0);
}

// Fonction pour obtenir la date actuelle au format YYMMDD
void	get_current_date(char *date_str)
{
	time_t		t;
	struct tm	*tm_info;

	t = time(NULL);
	tm_info = localtime(&t);
	strftime(date_str, 7, "%y%m%d", tm_info);
}

void	get_current_time(char *date_str)
{
	time_t		t;
	struct tm	*tm_info;

	t = time(NULL);
	tm_info = localtime(&t);
	strftime(date_str, 6, "%H:%M", tm_info);
}

// Fonction pour ouvrir le fichier de journal
int	ft_open_log(int *fd)
{
	char	filename[20];
	char	date_str[10];
	char	*temp;

	get_current_date(date_str);
	snprintf(filename, sizeof(filename), "%s%s.log", FILE_PREFIX, date_str);
	temp = ft_strjoin(LOG_DIR, "/");
	temp = ft_strjoin(temp, filename);
	*fd = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_run_malloc(2, temp);
	if (*fd == -1)
		return (-1);
	return (0);
}

int	ft_open_stderr(int *fd_log)
{
	char		time_str[12];
	char		*message;

	get_current_time(time_str);
	message = ft_strjoin("OPEN : MESSAGES DE DEBOGAGE - ", time_str);
	if (ft_create_log_dir() == -1)
	{
		ft_run_malloc(2, message);
		return (EXIT_FAILURE);
	}
	if (ft_open_log(fd_log) == -1)
	{
		ft_run_malloc(2, message);
		close(*fd_log);
		return (EXIT_FAILURE);
	}
	if (ft_putendl_fd(message, *fd_log) == -1)
	{
		ft_run_malloc(2, message);
		close(*fd_log);
		return (EXIT_FAILURE);
	}
	ft_run_malloc(2, message);
	return (EXIT_SUCCESS);
}
